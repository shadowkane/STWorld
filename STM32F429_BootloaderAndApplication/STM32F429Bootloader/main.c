// Includes
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmodem.h"
#include "MY_FLASH.h"

//#include "stm32f4xx_hal_flash.h"
// typedefs

// Defines
/* Note:
*		Don't change Application flash memory information randomly, read reference manual of your STM32 MCU, make sure to use a free and valid space memory,
*		it's better to start your application section from the start of a free sector to avoid any further complications
*/
#define APPLICATION_FLASH_MEMORY_START_ADDR		0x08020000
#define APPLICATION_FLASH_MEMORY_SIZE					256
#define APPLICATION_FLASH_MEMORY_START_SECTOR	5
#define APPLICATION_FLASH_MEMORY_NBR_SECTOR		2
#define BUFFER_SIZE	200// must be more than 128
#define FMK_DOWNLOAD_BUTTON_MAX_TIMEOUT_100MS	100 //10 seconds

// Prototypes
void vClockConfig(void);
void vGpioConfig(void);
void vUartInit(void);
void SysTick_Handler(void);

// Variables
UART_HandleTypeDef huart1;
uint8_t pBuffer[BUFFER_SIZE];
uint8_t pFileExample[46000];
//uint8_t __frmk_region_start__ __attribute__((section("UNINIT_FIXED_LOC")));
//const uint8_t* pu8Frmk = &__frmk_region_start__;
bool bIsEOF;
int i;
uint32_t u32ApplicationFlashMemoryIndex = 0;
bool bStop = false;
uint16_t u16ReceivedBytes;
uint8_t u8FmkDownloadButtonTimeout_100ms;

int main(void)
{
	// board init and config
	HAL_Init();
	vClockConfig();
	vGpioConfig();
	vUartInit();
	//HAL_UART_Transmit(&huart1, "Start Bootloader from keil\r\n", 1, 30000);
	printf("Start Bootloader from keil\r\n");
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_Delay(1000);

	u8FmkDownloadButtonTimeout_100ms=0;
	bool bStartFmkDownload = false;
	do
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			// exit loop if buttn clicked
			printf("user button clicked\r\n");
			bStartFmkDownload = true;
			break;
		}
		HAL_Delay(100);
		u8FmkDownloadButtonTimeout_100ms++;
	}while(u8FmkDownloadButtonTimeout_100ms<FMK_DOWNLOAD_BUTTON_MAX_TIMEOUT_100MS); // exit loop after timeout (this also mean not button was clicked)


	MY_FLASH_SetSectorAddrs(APPLICATION_FLASH_MEMORY_START_SECTOR, APPLICATION_FLASH_MEMORY_NBR_SECTOR, APPLICATION_FLASH_MEMORY_START_ADDR);
	if(bStartFmkDownload)
	{
		printf("Start Firmwork uploading ...\r\n");
		do
		{
			HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13); // just a visual indicator
			switch(XMODEM_ReceiveFileInPackages(&(pBuffer[0]), BUFFER_SIZE, 10, &u16ReceivedBytes))
			{
				case enXMODEM_RECEIVE_PACKET_EOB:
					#ifdef XMODE_TEST
					memcpy(pFileExample+u32ApplicationFlashMemoryIndex, pBuffer, u16ReceivedBytes);
					#else
					// write in application section in flash memeory
					MY_FLASH_StreamWriteN(u32ApplicationFlashMemoryIndex, pBuffer, u16ReceivedBytes, DATA_TYPE_8);
					#endif
					u32ApplicationFlashMemoryIndex+=u16ReceivedBytes;
					
					break;
				case enXMODEM_RECEIVE_PACKET_EOF:
					#ifdef XMODE_TEST
					memcpy(pFileExample+u32ApplicationFlashMemoryIndex, pBuffer, u16ReceivedBytes);
					printf("nbr data received from xmodem:%d\r\n", x);
					for(i=0; i<u32ApplicationFlashMemoryIndex; i++)
					{
						printf("%c ", pFileExample[i]);
					}
					printf("\r\n");
					printf("end of file\r\n");
					#else
					// write in application section in flash memeory
					MY_FLASH_StreamWriteN(u32ApplicationFlashMemoryIndex, pBuffer, u16ReceivedBytes, DATA_TYPE_8);
					#endif
					u32ApplicationFlashMemoryIndex+=u16ReceivedBytes;
					printf("File received successfully\r\n");
					bStop = true;
					break;
				case enXMODEM_RECEIVE_PACKET_TIMEOUT:
					// check if timeout come from waiting for start sending file
					printf("wait again\r\n");
					break;
				case enXMODEM_RECEIVE_PACKET_ERROR_SIZE:
					printf("Buffer size not enough for 1 packet\r\n");
					bStop = true;
					break;
				case enXMODEM_RECEIVE_PACKET_CANCELED:
					printf("Sender cancel sending file\r\n");
					bStop = true;
					break;
				case enXMODEM_RECEIVE_PACKET_ERROR:
					bStop = true;
					break;
				default:
					break;
			}
		}while(!bStop);
		// incase we have use MY_FLASH_StreamWriteN(...) function, we need to close it 
		MY_FLASH_CloseStreamWriteN();
	}
	// clear indicators
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	
	// jump to Application section
	MY_FLASH_ReadN(0, &(pBuffer[0]), 1, DATA_TYPE_8);
	if(pBuffer[0] != (uint8_t)0xFF)
	{
		//--TODO--: DeInit everything so the application do the its init
		printf("Start Application\r\n");
		HAL_Delay(1000);
		void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*) (APPLICATION_FLASH_MEMORY_START_ADDR + 4U)));
		app_reset_handler();
	}
	// if no application is available, run main loop
	// main loop
	printf("Start Main loop\r\n");
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);// toggle red led for problem indication (no application is runnin)
		HAL_Delay(1000);
	}
}

void vClockConfig(void)
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
    while(1); // error
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
    while(1); // error
  }
}

void vGpioConfig(void)
{
	GPIO_InitTypeDef xGpioInitStruct;
	
	// clock config
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	
	
	// config LED3 and LED4 (green/red led)
	xGpioInitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
	xGpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG ,&xGpioInitStruct);
	// user button
	xGpioInitStruct.Pin = GPIO_PIN_0;
	xGpioInitStruct.Mode = GPIO_MODE_INPUT;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &xGpioInitStruct);
	// USART 1
	xGpioInitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	xGpioInitStruct.Mode = GPIO_MODE_AF_PP;
	xGpioInitStruct.Pull = GPIO_NOPULL;
	xGpioInitStruct.Alternate = GPIO_AF7_USART1;
	xGpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &xGpioInitStruct);
	
	
	// Init State
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET); // turn Green led off
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET); // turn red led off
}

void vUartInit(void)
{
	// config USART1
	__HAL_RCC_USART1_CLK_ENABLE();
	huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
    while(1);
  }
}

FILE __stdout;
FILE __stdin;
int fputc(int c, FILE * stream)
{
	HAL_UART_Transmit(&huart1, (uint8_t *) &c, 1, 30000);
	return c; //return the character written to denote a successfull write
}

int fgetc(FILE * stream)
{
	char c;
	HAL_UART_Receive(&huart1, (uint8_t *) &c, 1, 30000);
	return c; //return the character
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}