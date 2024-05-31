/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_fatfs.h"
#include "i2c.h"
#include "app_lorawan.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lora_app.h"
#include <stdio.h>
#include "usart.h"
#include "icm20948.h"
#include "app_fatfs.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_BUFFER_SIZE 100  // Define the size of the receive buffer
uint8_t tx_buff[]={0,1,2,3,4,5,6,7,8,9};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Init_SD_Card ( void );
void Get_SOC ( void );
void open_sd_card ( void );
void UART_ReceiveAndPrint(UART_HandleTypeDef *huart);
void UART_SendFixedStringEveryFiveSeconds(UART_HandleTypeDef *huart);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
 {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LoRaWAN_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_I2C1_Init();
//  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
//  icm20948_init ( );
//  Init_SD_Card ( );
//  open_sd_card ( );


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
    /* USER CODE END WHILE */
    MX_LoRaWAN_Process();
//	  UART_SendFixedStringEveryFiveSeconds(&huart1);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void Init_SD_Card( void )
{
	if (f_mount(&USERFatFs, "", 0) != FR_OK) {
	    printf("Error mounting drive.\n");
	}

}

void UART_ReceiveAndPrint(UART_HandleTypeDef *huart)
{
    uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};  // Buffer to hold received data
    HAL_StatusTypeDef receiveStatus;

    // Receive data over UART
    receiveStatus = HAL_UART_Receive(huart, rxBuffer, RX_BUFFER_SIZE - 1, HAL_MAX_DELAY);

    // Check if the reception was successful
    if (receiveStatus == HAL_OK) {
        // Ensure the string is null-terminated
        rxBuffer[RX_BUFFER_SIZE - 1] = '\0';

        // Print the received string
        printf("Received raw data: ");
        for (int i = 0; i < RX_BUFFER_SIZE; i++) {
            printf("%02X ", rxBuffer[i]);  // Print each byte as a hex value
        }
        printf("\n");    }
    else {
        // Handle different kinds of errors, for example
//        printf("UART receive error!\r\n");
    }
}


void UART_SendFixedStringEveryFiveSeconds(UART_HandleTypeDef *huart)
{
    const char *str = "Hello, UART Receiver!";  // Hardcoded test string
    uint16_t len = strlen(str);  // Calculate the string length

    while (1) {  // Infinite loop to send the string continuously
    	  HAL_UART_Transmit(&huart1, tx_buff, 10, 1000);
    	  HAL_Delay(10000);
    }
}

void open_sd_card(void)
{
	FRESULT fres;
	char filename[32]; // Buffer to hold the filename
//	SysTime_t currSysTime = SysTimeGet(); // Get current system time
//	time_t rawTime = (time_t) currSysTime.Seconds; // Convert seconds to time_t for gmtime

	// Convert the time to broken-down structure
//	struct tm *timeinfo = gmtime(&rawTime);

	// Format the filename with the current date
//	strftime(filename, sizeof(filename), "%Y_%m_%d.txt", timeinfo);
    // Attempt to open the file with the generated filename
    fres = f_open(&USERFile, "nuts.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_OPEN_APPEND);
    if (fres == FR_OK) {
        printf("Success opening file\n");
    } else {
        printf("Error opening file %d\n", fres);
    }
}






//#ifdef __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif
//
//PUTCHAR_PROTOTYPE
//{
//  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//  return ch;
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  while (1)
  {
  }
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
