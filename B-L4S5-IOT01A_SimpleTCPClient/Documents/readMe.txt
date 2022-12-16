This is a very basic project in which i demonstrate how to use the onboard WIFI chip "SM43362" in the STM32 Discovery Kit (B-L4S5I-IOT01A) to send and receive messages from server via TCP/IP protocol.
obviously the board will act as a TCP client, also, this project could be made using different libraries  such-as netif, nettcp libraries you can find in the ST community.

The goal of this project is:
	* how to integrate and use the Wifi library in the "STM32CubeL4" package with a new project, so you don't have to use the sample in that library or any other library
	* import only what you need
	* the changes you need to made and why to make your project work

the files of the Wifi library are not placed in one directory like the LWIP and other library, so this is the list of files you only need to import and you are free to place them where you want, in may project i have the structure:
	Core\
		Inc\
			es_wifi_conf.h
			es_wifi_io.h
		Src\
			es_wifi_io.c

	\Drivers\BSP\
		Components\
			es_wifi\
				es_wifi.c
				es_wifi.h
	Middlewares\Third_Party\
		Wifi\
			wifi.c
			wifi.h
	
es_wifi => handle AT cmds (send/receive) to/from the Wifi module (driver)

es_wifi_io => the IO porting of the communication between MCU and Wifi module (init/deinit and send/receive using SPI communication) (it requires the es_wifi_conf and also each board has its own configuration this why it's in the core folder) 

wifi => Provide functions to connect to router,or act as AP, scan wifi and get information for wifi module etc (require es_wifi and es_wifi_io and it's a link between the application layer and the driver this why it's in the middleware folder)

other libraries like net (includes netif nettcp etc) can be used and it will use this wifi library to support a TCP UDP IPv4 and other protocols better, but wifi has a basic function to use TCP/IP protocol which is only wht we need for this basic project.

changes you need to made in your project:
	The communication between the MCU and the Wifi module is via SPI3 (C10, c11, c12) and it's already configured in the es_wifi file so you don't need to do the configuration again in the main file, so if you used the default configuration when you generated the project from cubeMX, make sure to not configure the SPI3.
also don't configure B13 (Wifi module wake-up cmd), E1(data ready from the Wifi module), E8 (wifi module reset cmd), E0 (Wifi module CS).

	The Wifi library need some interruption handler so you need to import those 2 functions in your main.c file:
 
```
extern  SPI_HandleTypeDef hspi; //this variable is declared in the es_wifi_io you need to called in main file.

// this callback is for the data ready from the wifi module
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
	case (GPIO_PIN_1):
	{
		SPI_WIFI_ISR();
		break;
	}

    default:
    {
      break;
    }
  }
}

// SPI3 Interruption request handler for the Wifi module (send/receive AT cmd via SPI)
void SPI3_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hspi);
}
```
 and import those lines in your stm32l4xx_it.c file:



```
// for the data ready from the wifi module
void EXTI1_IRQHandler(void)
{
 HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
```

if you are going to use this project and test it you need to:
	* set your router configuration (SSID, password, Encryption type)
	* set the server IP address and Port (you can install a TCP server in your PC and use it's IP address)
	
how the project works:
	1- initialize the Wifi module
	2- gather some information from the Wifi module (print version and MAC@)
	3- connect to router
	4- create socket (TCP type)
	5- connect to server
	6- send message to server
	7- white for messages from a server and print them


You will notice i have added other libraries but those for temperature module, and also the project is made using the cubeMX and everything is in default configuration,

Good luck
