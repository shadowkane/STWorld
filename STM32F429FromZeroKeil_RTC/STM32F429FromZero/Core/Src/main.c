/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "RtcDriver.h"
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

/* USER CODE BEGIN PV */
UART_HandleTypeDef xHUart1;
I2C_HandleTypeDef xHI2c3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static uint16_t u16GetValueInRangeFromUser(uint16_t u16MinValue, uint16_t u16MaxValue);
void EXTI15_10_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
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
  //MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	// config LED3 and LED4 (green/red led)
	__HAL_RCC_GPIOG_CLK_ENABLE();
	
	GPIO_InitTypeDef xGpioInitStruct;
	xGpioInitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
	xGpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG ,&xGpioInitStruct);
	
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET); // turn Green led off
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET); // turn red led off
	
	// config user button (blue button)
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	xGpioInitStruct.Pin = GPIO_PIN_0;
	xGpioInitStruct.Mode = GPIO_MODE_INPUT;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &xGpioInitStruct);
	
	// config UART1 (Configure USART 1 interface as UART) PA9:TX | PA10:RX
	__HAL_RCC_USART1_CLK_ENABLE();
	//__HAL_RCC_GPIOA_CLK_ENABLE(); // enabling the pirepheral clock of GPIOA already done
	
	xGpioInitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	xGpioInitStruct.Mode = GPIO_MODE_AF_PP;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Alternate = GPIO_AF7_USART1;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &xGpioInitStruct);
	
	xHUart1.Instance = USART1;
	xHUart1.Init.BaudRate = 115200;
	xHUart1.Init.WordLength = UART_WORDLENGTH_8B;
	xHUart1.Init.StopBits = UART_STOPBITS_1;
	xHUart1.Init.Parity = UART_PARITY_NONE;
	xHUart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	xHUart1.Init.Mode = UART_MODE_TX_RX;
	xHUart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&xHUart1);
	
	// config I2C3 (PA8:SCL | PC9:SDA)
	//note: to make sure I2C works (make sure the PCLK1 which is the peripheral frequency of the APB1 is at least 2Mhz because the min Peripheral clock frequency for the I2C in the I2C_CR2 control register is 2Mhz, see "the min frequency for the I2C peripheral clock frequency is 2Mhz (https://controllerstech.com/stm32-i2c-configuration-using-registers/)")
	//__HAL_RCC_GPIOA_CLK_ENABLE(); // enabling the pirepheral clock of GPIOA already done
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	xGpioInitStruct.Pin = GPIO_PIN_8;
	xGpioInitStruct.Mode = GPIO_MODE_AF_OD;// need to be open drain because I2C require only pullup resistor and not connected to GND
	xGpioInitStruct.Pull = GPIO_NOPULL; // DS3231 already come with pullup resistor
	xGpioInitStruct.Alternate = GPIO_AF4_I2C3;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &xGpioInitStruct);
	
	xGpioInitStruct.Pin = GPIO_PIN_9;
	xGpioInitStruct.Mode = GPIO_MODE_AF_OD; // need to be open drain because I2C require only pullup resistor and not connected to GND
	xGpioInitStruct.Pull = GPIO_NOPULL; // DS3231 already come with pullup resistor
	xGpioInitStruct.Alternate = GPIO_AF4_I2C3;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &xGpioInitStruct);
	
	__HAL_RCC_I2C3_CLK_ENABLE();
	xHI2c3.Instance = I2C3;
	xHI2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	xHI2c3.Init.ClockSpeed = 100000; //100khz
	xHI2c3.Init.DutyCycle = I2C_DUTYCYCLE_2; // since the speed mode is the standard mode we set the duty cycle to the default value
	// disable and set default values to 0 for the slave config parameters since we use I2C master mode
	xHI2c3.Init.OwnAddress1 = 0;
	xHI2c3.Init.OwnAddress2 = 0;
	xHI2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	xHI2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	xHI2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	uint8_t error;
	error	= HAL_I2C_Init(&xHI2c3);
	if(error==HAL_OK)
	{
		printf("i2c init succ %u\r\n", error);
	}
	else
	{
		printf("i2c init problem %u\r\n", error);
	}
	
	// configure RTC driver
	vRtcDriverConfig(&xHI2c3, DS3231_I2C_ADDRESS);
	iRtcDisableAlarm1();
	iRtcDisableAlarm2();
	iRtcClearAlarm1InteeruptionFlag();
	iRtcClearAlarm2InteeruptionFlag();
	iRtcSetInerruptionMode(RtcInterruptionMode_Alarm);
	
	// config  RTC interruption  (GPIOC 12)
	//__HAL_RCC_GPIOC_CLK_ENABLE();  // already enabled
	xGpioInitStruct.Pin = GPIO_PIN_12;
	xGpioInitStruct.Mode = GPIO_MODE_IT_FALLING;
	xGpioInitStruct.Pull = GPIO_NOPULL; // DS3231 already come with pullup resistor
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &xGpioInitStruct);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	
	t_xRtcDateTime xDateTime;
	//get current datetime from RTC
	iRtcGetCurrentDateTime(&xDateTime);
	printf("current time: %u:%u:%u %u/%u/%u\r\n", xDateTime.u8Hours, xDateTime.u8Minutes, xDateTime.u8Seconds, xDateTime.u8Date, xDateTime.u8Month, xDateTime.u16Year);

	// ask user if he wants to change time
	char cUserYesNoAnswer;
	int iSecondsFromUser;
	int iMinutesFromUser;
	int iHoursFromUser;
	int iDateFromUser;
	int iMonthFromUser;
	int iYearFromUser;
	
	do
	{
		printf("Do you want to change time? (y/n)\r\n");
		scanf("%c", &cUserYesNoAnswer);
	}while(cUserYesNoAnswer!='y' && cUserYesNoAnswer!='n');
	
	if(cUserYesNoAnswer=='y')
	{
		// Year
		do
		{
			printf("Set Year (2000-2999): ");
			scanf("%d", &iYearFromUser);
			printf("\r\n");
		}while(iYearFromUser<2000 || iYearFromUser>=3000);
		xDateTime.u16Year = (uint16_t)iYearFromUser;
		
		// Month
		do
		{
			printf("Set Month (01-12): ");
			scanf("%d", &iMonthFromUser);
			printf("\r\n");
		}while(iMonthFromUser<1 || iMonthFromUser>12);
		xDateTime.u8Month = (uint8_t)iMonthFromUser;
		
		// Date
		do
		{
			printf("Set date (01-31): ");
			scanf("%d", &iDateFromUser);
			printf("\r\n");
		}while(iDateFromUser<1 || iDateFromUser>31);
		xDateTime.u8Date = (uint8_t)iDateFromUser;
		
		// Hours
		do
		{
			printf("Set Hours (00-23): ");
			scanf("%d", &iHoursFromUser);
			printf("\r\n");
		}while(iHoursFromUser<0 || iHoursFromUser>=24);
		xDateTime.u8Hours = (uint8_t)iHoursFromUser;
		
		// Minutes
		do
		{
			printf("Set Minutes (00-59): ");
			scanf("%d", &iMinutesFromUser);
			printf("\r\n");
		}while(iMinutesFromUser<0 || iMinutesFromUser>=60);
		xDateTime.u8Minutes = (uint8_t)iMinutesFromUser;
		
		// seconds
		do
		{
			printf("Set Seconds (00-59): ");
			scanf("%d", &iSecondsFromUser);
			printf("\r\n");
		}while(iSecondsFromUser<0 || iSecondsFromUser>=60);
		xDateTime.u8Seconds = (uint8_t)iSecondsFromUser;
		
		printf("New time: %u:%u:%u %u/%u/%u\r\n", xDateTime.u8Hours, xDateTime.u8Minutes, xDateTime.u8Seconds, xDateTime.u8Date, xDateTime.u8Month, xDateTime.u16Year);

		//set datetime from RTC
	//	xDateTime.u8Seconds = 50;
	//	xDateTime.u8Minutes = 59;
	//	xDateTime.u8Hours = 23;
	//	xDateTime.u8Date = 28;
	//	xDateTime.u8Month = 2;
	//	xDateTime.u16Year = 2005;
		iRtcSetDateTime(xDateTime);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t isButtonClicked = 0;
	//HAL_UART_Transmit(&xHUart1, "Start Program\n\r", 15, 1000);
  printf("Start Program\r\n");
	__disable_irq();
	iRtcSetAlarm(enRtcAlarmRate_A1_PerSecond, NULL);
	iRtcEnableAlarm1();
	__enable_irq();
	while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && isButtonClicked==0)
		{
			// get time from RTC
			if(iRtcGetCurrentDateTime(&xDateTime)==0)
			{
				// print time
				printf("h:%u|m:%u|s:%u d:%u/m:%u/y:%u\r\n", xDateTime.u8Hours, xDateTime.u8Minutes, xDateTime.u8Seconds, xDateTime.u8Date, xDateTime.u8Month, xDateTime.u16Year);
			}
			else
			{
				printf("iRtcGetCurrentDateTime: Error\r\n");
			}
//			u8TimeSeconds = DS3231_GetSecond();
//			printf("seconds:%u\r\n", u8TimeSeconds);
			// toggle led
			HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
			isButtonClicked = 1;
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			isButtonClicked = 0;
		}
		HAL_Delay(100);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4; // we divide by 4 to get 2Mhz in the ABP1 clock PCLK1 because the min frequency for the I2C peripheral clock frequency is 2Mhz (https://controllerstech.com/stm32-i2c-configuration-using-registers/)
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, NCS_MEMS_SPI_Pin|CSX_Pin|OTG_FS_PSO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ACP_RST_GPIO_Port, ACP_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, RDX_Pin|WRX_DCX_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LD3_Pin|LD4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A0_Pin A1_Pin A2_Pin A3_Pin
                           A4_Pin A5_Pin SDNRAS_Pin A6_Pin
                           A7_Pin A8_Pin A9_Pin */
  GPIO_InitStruct.Pin = A0_Pin|A1_Pin|A2_Pin|A3_Pin
                          |A4_Pin|A5_Pin|SDNRAS_Pin|A6_Pin
                          |A7_Pin|A8_Pin|A9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI5_SCK_Pin SPI5_MISO_Pin SPI5_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI5_SCK_Pin|SPI5_MISO_Pin|SPI5_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : ENABLE_Pin */
  GPIO_InitStruct.Pin = ENABLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(ENABLE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SDNWE_Pin */
  GPIO_InitStruct.Pin = SDNWE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(SDNWE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NCS_MEMS_SPI_Pin CSX_Pin OTG_FS_PSO_Pin */
  GPIO_InitStruct.Pin = NCS_MEMS_SPI_Pin|CSX_Pin|OTG_FS_PSO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : B1_Pin MEMS_INT1_Pin MEMS_INT2_Pin TP_INT1_Pin */
  GPIO_InitStruct.Pin = B1_Pin|MEMS_INT1_Pin|MEMS_INT2_Pin|TP_INT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : B5_Pin VSYNC_Pin G2_Pin R4_Pin
                           R5_Pin */
  GPIO_InitStruct.Pin = B5_Pin|VSYNC_Pin|G2_Pin|R4_Pin
                          |R5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ACP_RST_Pin */
  GPIO_InitStruct.Pin = ACP_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ACP_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OC_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : R3_Pin R6_Pin */
  GPIO_InitStruct.Pin = R3_Pin|R6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : A10_Pin A11_Pin BA0_Pin BA1_Pin
                           SDCLK_Pin SDNCAS_Pin */
  GPIO_InitStruct.Pin = A10_Pin|A11_Pin|BA0_Pin|BA1_Pin
                          |SDCLK_Pin|SDNCAS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin
                           D8_Pin D9_Pin D10_Pin D11_Pin
                           D12_Pin NBL0_Pin NBL1_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |D8_Pin|D9_Pin|D10_Pin|D11_Pin
                          |D12_Pin|NBL0_Pin|NBL1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : G4_Pin G5_Pin B6_Pin B7_Pin */
  GPIO_InitStruct.Pin = G4_Pin|G5_Pin|B6_Pin|B7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_HS_ID_Pin OTG_HS_DM_Pin OTG_HS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_HS_ID_Pin|OTG_HS_DM_Pin|OTG_HS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_HS_Pin */
  GPIO_InitStruct.Pin = VBUS_HS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_HS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D13_Pin D14_Pin D15_Pin D0_Pin
                           D1_Pin D2_Pin D3_Pin */
  GPIO_InitStruct.Pin = D13_Pin|D14_Pin|D15_Pin|D0_Pin
                          |D1_Pin|D2_Pin|D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : TE_Pin */
  GPIO_InitStruct.Pin = TE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RDX_Pin WRX_DCX_Pin */
  GPIO_InitStruct.Pin = RDX_Pin|WRX_DCX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : R7_Pin DOTCLK_Pin B3_Pin */
  GPIO_InitStruct.Pin = R7_Pin|DOTCLK_Pin|B3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : HSYNC_Pin G6_Pin R2_Pin */
  GPIO_InitStruct.Pin = HSYNC_Pin|G6_Pin|R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C3_SDA_Pin */
  GPIO_InitStruct.Pin = I2C3_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C3_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C3_SCL_Pin */
  GPIO_InitStruct.Pin = I2C3_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C3_SCL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : STLINK_RX_Pin STLINK_TX_Pin */
  GPIO_InitStruct.Pin = STLINK_RX_Pin|STLINK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : G7_Pin B2_Pin */
  GPIO_InitStruct.Pin = G7_Pin|B2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : G3_Pin B4_Pin */
  GPIO_InitStruct.Pin = G3_Pin|B4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD4_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : SDCKE1_Pin SDNE1_Pin */
  GPIO_InitStruct.Pin = SDCKE1_Pin|SDNE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
FILE __stdout;
FILE __stdin;

int fputc(int c, FILE * stream)
{
	HAL_UART_Transmit(&xHUart1, (uint8_t *) &c, 1, 30000);
	return c; //return the character written to denote a successfull write
}

int fgetc(FILE * stream)
{
	char c;
	HAL_UART_Receive(&xHUart1, (uint8_t *) &c, 1, 30000);
	return c; //return the character
}

// future use
static uint16_t u16GetValueInRangeFromUser(uint16_t u16MinValue, uint16_t u16MaxValue)
{
	
	char c;
	scanf("%c", &c);
	printf("u wrote %c\r\n", c);
	
	return 0;
}

void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_12)
	{
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		iRtcClearAlarm1InteeruptionFlag();
	}
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
