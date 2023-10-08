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
#include <string.h>
#include <stdlib.h>
#include "fatfs.h"
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
SPI_HandleTypeDef hspi4;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

FRESULT iListDirAndFile(char *pcPath, int iNbrTabs);
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
	
	// configure SD card
	// SPI GPIO configuration (SPI4) SPI_CLK: PE2 | SPI_MISO: PE5 | SPI_MOSI: PE6
	__HAL_RCC_GPIOE_CLK_ENABLE();
	xGpioInitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6;
  xGpioInitStruct.Mode = GPIO_MODE_AF_PP;
  xGpioInitStruct.Pull = GPIO_NOPULL;
  xGpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  xGpioInitStruct.Alternate = GPIO_AF5_SPI4;
  HAL_GPIO_Init(GPIOE, &xGpioInitStruct);
	
	// Config SPi interface
	__HAL_RCC_SPI4_CLK_ENABLE();
	hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW; //search
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE; //search
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; //search
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB; //search
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE; //search
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //search
  hspi4.Init.CRCPolynomial = 10; //search
  int error = HAL_SPI_Init(&hspi4);
  if(error==HAL_OK)
	{
		printf("SPI init succ %u\r\n", error);
	}
	else
	{
		printf("SPI init problem %u\r\n", error);
	}
	
	// SD card CS is PE4
	//__HAL_RCC_GPIOE_CLK_ENABLE();  // already enabled
	xGpioInitStruct.Pin = GPIO_PIN_4;
  xGpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  xGpioInitStruct.Pull = GPIO_NOPULL;
  xGpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &xGpioInitStruct);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
	
	
	//SD card config & init
	MX_FATFS_Init();
	HAL_Delay(1000); //a short delay is important to let the SD card settle
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t isButtonClicked = 0;
	//HAL_UART_Transmit(&xHUart1, "Start Program\n\r", 15, 1000);
  printf("Start Program\r\n");
	printf("------ SD card init section ------\r\n");
	// mount SD card
	FATFS xFatFs;
	FRESULT xFRes;
	xFRes = f_mount(&xFatFs, "", 1);
	if(xFRes != FR_OK)
	{
		printf("f_mount failed, error: %d\r\n", xFRes);
		while(1);
	}
	else
	{
		printf("f_mount succ\r\n");
	}
	//Let's get some statistics from the SD card
	DWORD free_clusters, free_sectors, total_sectors;
	FATFS* getFreeFs;
	xFRes = f_getfree("", &free_clusters, &getFreeFs);
	if (xFRes != FR_OK) {
		printf("f_getfree error (%d)\r\n", xFRes);
		while(1);
	}
	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;
	printf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

	// list all directories and files in SD card
	iListDirAndFile("", 0);
	
	// Create and Open new file in write mode (if file already existe, truncat it overwrite it)
	FIL xFil;
	const TCHAR pcFILE_NAME[] = "StmFile.txt"; // or use define like this #define pcFILE_NAME "StmFile.txt"
	// FA_CREATE_ALWAYS create new file, if file already existe, delete all data in file to overwrite it
	// FA_WRITE: open file in write access mode
	xFRes = f_open(&xFil, pcFILE_NAME, FA_CREATE_ALWAYS | FA_WRITE);
	if(xFRes != FR_OK)
	{
		printf("f_open %s error (%d)\r\n", pcFILE_NAME, xFRes);
		while(1);
	}
	printf("Successfuly open '%s' for writing\r\n", pcFILE_NAME);
	
	char pcData[100];
	UINT bytesWrote;
	//Copy in a string
	strncpy(pcData, "This is my first line in file\r\n", 31);
	xFRes = f_write(&xFil, pcData, 31, &bytesWrote);
	if(xFRes == FR_OK) {
		printf("Wrote %d bytes to '%s'!\r\n", bytesWrote, pcFILE_NAME);
	} else {
		printf("f_write error (%d)\r\n", xFRes);
	}
	
	char pcData2Write_2[] = "this is the second line and i'm trying to write anything to read it again!";
	xFRes = f_write(&xFil, pcData2Write_2, strlen(pcData2Write_2), &bytesWrote);
	if(xFRes == FR_OK) {
		printf("Wrote %d bytes to '%s'!\r\n", bytesWrote, pcFILE_NAME);
	} else {
		printf("f_write error (%d)\r\n", xFRes);
	}
	
	//after finish writing, close file
	f_close(&xFil);

	
	xFRes = f_open(&xFil, pcFILE_NAME, FA_READ);
	if (xFRes != FR_OK)
	{
		printf("f_open %s error (%i)\r\n", pcFILE_NAME, xFRes);
		while(1);
	}
	printf("Successfuly open '%s' for reading!\r\n", pcFILE_NAME);

	//Read 10 bytes from file
	BYTE bBuffer[10];

	// read all data in file (until the end of file EOF)
	// to make it easy we will use f_gets and read by 10 byte (char) untl the end of file
	printf("Data in %s:\r\n\r\n", pcFILE_NAME);
	do
	{
		if(f_gets((TCHAR*)bBuffer, 10, &xFil) != NULL)
		{
			printf("%s", bBuffer);
		}
		else // incase f_get return NULL, it can mean error or end of file
		{
			if(f_error(&xFil) != 0) // error was occured
			{
				printf("f_error\r\n");
			}
			if(f_eof(&xFil) != 0) // end of file was occured
			{
				printf("\r\n\r\nthis is the end of the file \r\n"); 
			}
			break;
		}
	}while(1);
	
	//after finish reading, close file
	f_close(&xFil);
	
	//We're done, so de-mount the drive
	printf("unmount SD Card\r\n");
	f_mount(NULL, "", 0);
	
	while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && isButtonClicked==0)
		{
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; // we divide by 1 to get 8Mhz in the ABP2 because we need SPI baudrate reachs 4Mbit in fast clk (https://01001000.xyz/2020-08-09-Tutorial-STM32CubeIDE-SD-card/)

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

// List all Directories and Files in Path
// Parameters:  pcPath (path to scan from), iNbrTabs (number of tabs to add in the print before dir or file name, to be easy to recognize the dir tree)
// return the result of the last used file function
// Note: in ffconf.h change the define _FS_LOCK to any max number of openned files that works for you, 
FRESULT iListDirAndFile(char *pcPath, int iNbrTabs)
{
	DIR xDir;
	FILINFO xFInfo;
	FRESULT xFRes;
	char pcNextPath[100];
	//char pcFullPath[100];
	xFRes = f_opendir(&xDir, pcPath);
	if(xFRes == FR_OK)
	{
		//printf("f_opendir %s succ\r\n", pcPath);
		// keep reading directories if SD card until no directory found
		while(1)
		{
			xFRes = f_readdir(&xDir, &xFInfo);
			if(xFRes == FR_OK)
			{
				//if end of directory exit loop
				if(xFInfo.fname[0]==0)
				{
					//printf("end of directory\r\n");
					f_closedir(&xDir);
					break;
				}
				// check if directory
				if(xFInfo.fattrib & AM_DIR)
				{
					sprintf(&pcNextPath[0], "%s\\%s", pcPath,xFInfo.fname);
					for(int i=0; i<iNbrTabs; i++)
						printf("	");
					printf("%s\r\n", xFInfo.fname);
					// List file and dir inside this dir (reccursivity)
					xFRes = iListDirAndFile(&pcNextPath[0], iNbrTabs+1);
					// if xFRes is not ok that mean not more file or directories in this directory
					if(xFRes != FR_OK)
					{
						printf("iListDirAndFile not ok (%d)\r\n", xFRes);
						f_closedir(&xDir);
						break;
					}
				}
				// if not directory then it's file
				else
				{
					for(int i=0; i<iNbrTabs; i++)
						printf("	");
					printf("%s\r\n", xFInfo.fname);
				}
			}
			else
			{
				f_closedir(&xDir);
				printf("f_readdir error (%d)\r\n", xFRes);
				break;
			}
		}
	}
	else
	{
		printf("f_opendir error (%d)\r\n", xFRes);
		while(1);
	}
	
	return xFRes;
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
