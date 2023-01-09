/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "KEYPAD.h"
#include "DHT.h"
#include "fonts.h"
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint16_t temp = 0;
uint16_t airHum = 0;
uint16_t pHHum = 0;
uint16_t lightHum = 0;

uint16_t tempSP = 50;
uint16_t airHumSP = 50;
uint16_t pHHumSP = 50;
uint16_t lightHumSP = 50;

uint8_t status = 0;
uint8_t failul = 0;

uint8_t valueType = 1;
char* keyEnter = "abc";

DHT_Name dht;

char KEYMAP[NUMROWS][NUMCOLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
KEYPAD_Name keypad;

uint32_t time = 0;
uint32_t time2 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t getMax(uint16_t num1, uint16_t num2) {
	if (num1 > num2) {
		return num1;
	}

	return num2;
}
uint8_t * numberToString(uint16_t val){
	
	static uint8_t buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= 10)
	
		buf[i] = "0123456789abcdef"[val % 10];
	
	return &buf[i+1];
	
}
uint16_t getADCValue(uint32_t channel) {
	ADC_ChannelConfTypeDef sConfig = {0};
	
	sConfig.Channel = channel;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);
	uint16_t value = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	return value;
}
void transmitString(uint8_t * value) {
	HAL_UART_Transmit(&huart1, value, strlen((char *)value), 10);	
	
} 
void transmitNumber(uint16_t value) {
	uint8_t * string = numberToString(value);
	HAL_UART_Transmit(&huart1, string, strlen((char *)string), 10);
} 

void valueShow() {
  if (valueType == 1) {
    SSD1306_GotoXY(10,0);
    SSD1306_Puts("Temp: ", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts((char *)numberToString(temp), &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);
    
    SSD1306_GotoXY(10,15);
    SSD1306_Puts("SP: ", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts((char *)numberToString(tempSP), &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);
  }
  if (valueType == 2) {
    SSD1306_GotoXY(10,0);
    SSD1306_Puts("Air Humi: ", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts((char *)numberToString(airHum), &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("%", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);
    
    SSD1306_GotoXY(10,15);
    SSD1306_Puts("SP: ", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts((char *)numberToString(airHumSP), &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("%", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts("             ", &Font_7x10, SSD1306_COLOR_WHITE);
  }
  if (valueType == 3) {
    
  }
  if (valueType == 4) {
    
  }
}

void commandEnter(char key) {
  char *c = keyEnter + strlen(keyEnter) - 1;
  *c = key;
}

void callBackMain() {
	while(1) {
		char key = KEYPAD3X4_Readkey(&keypad);

		if(key) {
			//getValue(key);
			//transmitString((uint8_t *)&key);
			// transmitNumber(pHHum);
			//status = dht.Status;
			//DHT_Start(&dht);
			//DHT_PollForConversion(&dht);
			//tempDHT = dht.Temp;
			//DHT_Stop(&dht);
      if (key == 'A') {
        valueType = 1;
      }
      if (key == 'B') {
        valueType = 2;
      }
      if (key == 'C') {
        valueType = 3;
      }
      if (key == 'D') {
        valueType = 4;
      }
      valueShow();
      commandEnter(key);
		}

		if (status == 0) {	
			DHT_ReadTempHum(&dht);
			if (dht.Temp < 1000) {
				temp = dht.Temp;
				airHum = dht.Humi;
			}
			return;
		}
		if (HAL_GetTick() - time > 2000) {
			DHT_ReadTempHum(&dht);
			if(dht.Status == 0) {
				SSD1306_Clear();
				if (dht.Temp > 1000) {
					failed();
				}
				time = HAL_GetTick();
			}
			if (dht.Temp < 1000) {
				temp = dht.Temp;
				airHum = dht.Humi;
			}
			
      valueShow();
      SSD1306_GotoXY(10,30);
			SSD1306_Puts("Command: ", &Font_7x10, SSD1306_COLOR_WHITE);

      SSD1306_Puts(keyEnter, &Font_7x10, SSD1306_COLOR_WHITE);

			SSD1306_GotoXY(10,45);
			SSD1306_Puts("CT: ", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_Puts((char *)numberToString(status), &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_Puts(" CF: ", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_Puts((char *)numberToString(failul), &Font_7x10, SSD1306_COLOR_WHITE);
				
			SSD1306_UpdateScreen();
		}
		
		if (HAL_GetTick() - time2 > 1000) {
			transmitString((uint8_t *)"Temperature: ");
			transmitNumber(pHHum);
			transmitString((uint8_t *)"\n");
			
			time2 = HAL_GetTick();
		}
	}
}
void plus() {
	status++;
}
void failed() {
	failul++;
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	KEYPAD3X4_Init(&keypad, KEYMAP, 
									GPIOA, GPIO_PIN_7, GPIOB, GPIO_PIN_0, GPIOB, GPIO_PIN_1, GPIOB, GPIO_PIN_10,
									GPIOA, GPIO_PIN_3, GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, GPIOA, GPIO_PIN_6);
	DHT_Init(&dht, DHT22, &htim4, GPIOA, GPIO_PIN_0);
	
	SSD1306_Init();
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_UpdateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//HAL_Delay(2000); // Wait for DHT22 ready (>1s)
	
  while (1)
  {	

		callBackMain();
    /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 0xffff;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
