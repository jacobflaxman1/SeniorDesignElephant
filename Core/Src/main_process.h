/* main_process.h */

#ifndef MAIN_PROCESS_H
#define MAIN_PROCESS_H

#include "stdbool.h"
#include "stm32_systime.h"
#include "ff.h"
#include "icm20948.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform.h" // Include platform-specific definitions, adjust if needed

/* Exported constants --------------------------------------------------------*/
#define PROCESS_PERIOD 10

/* Exported types ------------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
extern int join_count;
extern int initial_session;
extern int initial_join_process_failed;
extern int gotNewTime;
extern int waitForRx;
extern float soc;
extern int first_time;
extern SysTime_t leftForLoraTime;
extern bool leftForLora;
extern int joined;
extern int time_updated;

/* Exported functions ------------------------------------------------------- */
bool compareTimeStamps(SysTime_t time1, SysTime_t time2);
bool checkSubSeconds(SysTime_t time1, SysTime_t time2, int period);
bool checkIf1970(void);
void main_process(void);
void get_data(void);
void write_data_to_sd ( axises *data, SysTime_t currTime );
FRESULT get_sd_card_size(DWORD *total, DWORD *free);
void open_sd_card(void);
void close_sd_card(void);
void time_stamp_data(void);
void printAxises(const axises* data);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_PROCESS_H */
