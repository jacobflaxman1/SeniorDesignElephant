#include "main_process.h"
#include <stdio.h>
#include "stm32_timer.h"
#include "rtc.h"
#include <stdbool.h>
#include <stdlib.h>
#include "stm32_systime.h"
#include "LmHandler.h"
#include "user_diskio_spi.h"
#include "ffconf.h"
#include "user_diskio.h"
#include "lora_app.h"
#include "platform.h"
#include "sys_app.h"
#include "lora_app.h"
#include "stm32_seq.h"
#include "stm32_timer.h"
#include "utilities_def.h"
#include "app_version.h"
#include "lorawan_version.h"
#include "subghz_phy_version.h"
#include "lora_info.h"
#include "LmHandler.h"
#include "adc_if.h"
#include "CayenneLpp.h"
#include "sys_sensors.h"
#include "flash_if.h"
#include "radio_driver.h"
#include "i2c.h"
#include "icm20948.h"
#include "app_fatfs.h"
/*/
 * 	STRUCT DEFINITIONS
 */
axises data;

RTC_TimeTypeDef sTime;

FIL fil;


/*/
 *   	SHARED VARIABLE DEFINITIONS
 */
int join_count = 0;

int initial_session = 0;

int initial_join_process_failed = 0;	// if 1 then join process failed

int gotNewTime = 0;

int waitForRx = 1;

float soc = 0.0;

int first_time = 1;

int time_updated = 0;

int opened_sd_card = 0;

SysTime_t leftForLoraTime;
bool leftForLora = false;


bool compareTimeStamps( SysTime_t time1, SysTime_t time2 )
{
	bool flag = false;

    int totalSeconds1 = time1.Seconds;
    int totalSeconds2 = time2.Seconds;

    int difference = abs( totalSeconds1 - totalSeconds2 );

    if ( difference >= PROCESS_PERIOD ) {
    	flag = true;
    }

    return flag;
}



bool checkSubSeconds( SysTime_t time1, SysTime_t time2, int period  )
{
	bool flag = false;

    int totalSeconds1 = time1.Seconds;
    int totalSeconds2 = time2.Seconds;
    int totalSubSeconds1 = time1.SubSeconds;
    int totalSubSeconds2 = time2.SubSeconds;

    int difference = ( totalSeconds1 - totalSeconds2 ) * 1000 + totalSubSeconds1 - totalSubSeconds2;

    if ( difference >= period ) {
    	flag = true;
    }

    return flag;
}


bool checkIf1970 ( ) {

	  SysTime_t sysTime = SysTimeGet ( );
	    time_t rawTime = ( time_t ) sysTime.Seconds;

	    struct tm *timeinfo;

	    timeinfo = gmtime ( &rawTime );

	 if ( ( timeinfo->tm_year + 1900 ) == 1970 &&
	        ( timeinfo->tm_mon ) == 0 &&
	        ( timeinfo->tm_mday ) == 1 ) {

		 return true;

	    } else {

	    	return false;
	    }

}


void main_process ( void )
{

	SysTime_t startTime;
	SysTime_t currTime;

	/*
	 * Process -> read data from icm -> get a time stamp -> time stamp data -> send data to sd card -> loop
	 *
	 *
	 * 		MAYBE we can create a session variable to know if we just started a new session and we can create a new file on the sd card
	 *
	 */

	bool timePeriodElapsed = false;
	if (
			(
				LmHandlerJoinStatus( ) == LORAMAC_HANDLER_SET &&
				time_updated == 1
//				!checkIf1970( )
//				gotNewTime									  &&
//				waitForRx == 0
			) 												  ||
				initial_join_process_failed == 1)
	{



	  	PauseTasks ( );

		startTime = SysTimeGet ( );
		SysTime_t currentWaitTime = SysTimeGet ( );
		SysTime_t previousWaitTime;

		previousWaitTime = ( leftForLora ) ? leftForLoraTime : currentWaitTime;

		bool elapsedTime = false;

		int data_log_count = 0;

		// if the network is joined run the data collection process in between transmissions

		uint16_t milliseconds = startTime.SubSeconds;

		time_t rawTime = ( time_t ) startTime.Seconds;

//		struct tm *timeinfo = gmtime( &rawTime );
//		char timeStr[80];

//		strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo );

		__disable_irq();  // disable all interrupts

		while( !timePeriodElapsed )
		{


			currentWaitTime = SysTimeGet ( );

			elapsedTime = checkSubSeconds( currentWaitTime, previousWaitTime, 50 );

			while (!elapsedTime)
			{
				currentWaitTime = SysTimeGet ( );
				elapsedTime = checkSubSeconds( currentWaitTime, previousWaitTime, 50 );   // Delay for the remainder of the 50ms period
			}

			previousWaitTime = currentWaitTime;

			icm20948_accel_read_g ( &data );

			currTime = SysTimeGet ( );

//			open_sd_card ( );

//			write_data_to_sd ( &data, currTime );

//			print_data ( &data );

			timePeriodElapsed = compareTimeStamps( currTime, startTime );

			data_log_count++;

		}

		leftForLoraTime = SysTimeGet ( );
		leftForLora = true;

//		close_sd_card ( );

		APP_LOG( TS_OFF, VLEVEL_M, "NUMBER OF ROWS LOGGED : %d\n", data_log_count);

		data_log_count = 0;
		__enable_irq();   // enable all interrupts

		ResumeTasks ( );

	}
}


void get_data(void)
{
	/*/
	 * FILL THIS IN WITH GYRO DATA?
	 * Collect accell and gyro data in one place '
	 *
	 */


}



void write_data_to_sd ( axises *data, SysTime_t currTime )
{
	FRESULT fres; //Result after operations
	UINT bw;
	char buffer[200];


	uint16_t milliseconds = currTime.SubSeconds;

	time_t rawTime = ( time_t ) currTime.Seconds;

	struct tm *timeinfo = gmtime( &rawTime );

	char timeStr[80];

	strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo );

	sprintf( buffer, "%s.%03u - X: %f, Y: %f, Z: %f\n", timeStr, milliseconds, data->x, data->y, data->z );

	fres = f_write( &USERFile, buffer, strlen( buffer ), &bw );

    if ( fres != FR_OK ) {
//        APP_LOG( TS_OFF, VLEVEL_M, "F_WRITE ERROR: %d\n", fres );

    }

    if ( bw < strlen( buffer ) ) {
//        APP_LOG( TS_OFF, VLEVEL_M, "NOT ALL BYTES WRITTEN\n" );
    }
}

FRESULT get_sd_card_size( DWORD *total, DWORD *free ) {
    FATFS *fs;
    DWORD fre_clust, fre_sect, tot_sect;
    FRESULT res;

    res = f_getfree("0:", &fre_clust, &fs);
    if (res != FR_OK) return res;

    tot_sect = (fs->n_fatent - 2) * fs->csize;
    fre_sect = fre_clust * fs->csize;

    *total = tot_sect * 512;
    *free = fre_sect * 512;

    return FR_OK;
}


void printAxises(const axises* data) {
    printf("X: %03f, Y: %03f, Z: %03f\n", data->x, data->y, data->z);
}


void close_sd_card ( )
{
	f_close(&fil);
}


