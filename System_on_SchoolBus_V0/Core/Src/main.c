/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "rc522.h"
#include "gps.h"
#include "TEST.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Buf_size 150
#define warning_time 3
/* 
	warning_time tinh bang phut
*/ 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
RTC_TimeTypeDef TIME;
RTC_DateTypeDef DATE;
uint8_t CardID[5];

char Buf[Buf_size],Buf2[Buf_size],
			Buf3[Buf_size];
/*
Buf : Dung de gui tin nhan
Buf2: Dung de goi dien
Buf3: Bao dong
*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void call(char *sdt);
void message(char *sdt, char *nd);
void delay_ms (uint16_t us);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
	if(huart->Instance==USART2)
	{
		GPS_UART_CallBack();
		
		if(((GPS.dec_latitude||GPS.dec_longitude)==0))
			HAL_GPIO_WritePin(L2_GPIO_Port,L2_Pin,1);
		else 
		{HAL_GPIO_WritePin(L2_GPIO_Port,L2_Pin,0);
		}
				
		
	}
	if(huart->Instance==USART6)
	{

		
	}
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
	HAL_RTC_GetTime(&hrtc,&TIME,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&DATE,RTC_FORMAT_BIN);
	for(int j=0;j<=10;j++)
				{if((HOCSINH[j].hour==0)&&(HOCSINH[j].minute==0))
					{
					continue;
					}
				else
				{
						if(TIME.Hours-HOCSINH[j].hour==0)
					{
						if(TIME.Minutes-HOCSINH[j].minute>=warning_time)
						{ call(HOCSINH[j].SDT);
							
							/*
									BAO DONG
							*/
						}

					}
					else
					{
						if(TIME.Minutes+60-HOCSINH[j].minute>=warning_time)
							{
								call(HOCSINH[j].SDT);
							
							/*
									BAO DONG
							*/
						}
					
					}
				}
				}
					

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}

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
	kt();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
		MFRC522_Init();
		GPS_Init();
		HAL_TIM_Base_Start(&htim5);
		HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(MFRC522_Check(CardID)==MI_OK)
		{	
			HAL_GPIO_WritePin(L1_GPIO_Port,L1_Pin,1);
			HAL_Delay(150);
				for(int j=0;j<=10;j++)
				{
					if(MFRC522_Compare(CardID,HOCSINH[j].ID)==MI_OK)
							{
								
									HOCSINH[j].state+=1;
										delay_ms(50);
								switch((int)HOCSINH[j].state)
								{
										case 1:
									{

										HOCSINH[j].hour=TIME.Hours;
										HOCSINH[j].minute=TIME.Minutes;
										
										/*
												Luu thoi gian hoc sinh len
										*/
										sprintf(Buf2,"Hoc sinh: %s, Lop: %s\nDa LEN XE luc %02d:%02d\nTai vi tri(Vi do,Kinh do):(%f,%f)",HOCSINH[j].Ho_Ten,HOCSINH[j].Lop,HOCSINH[j].hour,HOCSINH[j].minute,GPS.dec_latitude,GPS.dec_longitude);
										message(HOCSINH[j].SDT,Buf2);
										memset(Buf2,0,Buf_size);
										/*
												Gui tin nhan hoc sinh len
										*/
										break;
									}
										case 2:
									{	
										HOCSINH[j].hour=TIME.Hours;
										HOCSINH[j].minute=TIME.Minutes;
										sprintf(Buf2,"Hoc sinh: %s, Lop: %s\nDa XUONG XE luc %02d:%02d\nTai vi tri(Vi do,Kinh do):(%f,%f)",HOCSINH[j].Ho_Ten,HOCSINH[j].Lop,HOCSINH[j].hour,HOCSINH[j].minute,GPS.dec_latitude,GPS.dec_longitude);
										message(HOCSINH[j].SDT,Buf2);
										memset(Buf2,0,Buf_size);
										/*
												Gui tin nhan hoc sinh xuong
										*/
										HOCSINH[j].hour=0;
										HOCSINH[j].minute=0;
										HOCSINH[j].state=0;
										/*
												Xoa thoi gian da luu
										*/
										break;
									}
										default:
									{
										/*
										Thong bao moi quet lai
										*/
										HOCSINH[j].state=0;
										break;
									}
								}
							break;
							}
				}
		 HAL_GPIO_WritePin(L1_GPIO_Port,L1_Pin,0);
		}

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void call(char *sdt)
{
	sprintf(Buf,"ATD%s\r\n",sdt);
	HAL_UART_Transmit(&huart6,Buf,20,20);
	memset(Buf,0,Buf_size);
}

void message(char *sdt, char *nd)
{
	HAL_UART_Transmit(&huart6,"AT+CMGF=1\r\n",14,10);
	delay_ms(1);
	sprintf(Buf,"AT+CMGS=\"%s\"\r\n %s \x1A",sdt,nd);
	HAL_UART_Transmit(&huart6,Buf,Buf_size,200);
	delay_ms(50);
	memset(Buf,0,Buf_size);
}

void delay_ms (uint16_t ms)
{
    __HAL_TIM_SET_COUNTER(&htim5,0);  // set the counter value a 0
    while (__HAL_TIM_GET_COUNTER(&htim5) < ms);  // wait for the counter to reach the us input in the parameter
}
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
