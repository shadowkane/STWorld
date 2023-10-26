A simple bootloader project, user can upload his firmware in bin format through UART communication using Xmode as a file transfer protocol.
Hardware:
	+ STM32F429
	+ UART to USB cable (like FTDI converter)

Program and IDE:
	+ Keil uvision
	+ TeraTerm (or any other Serial port interface that supports Xmode protocol)

How it works:
	Connect PC with your STM32F429 via serial port (FTDI) using Pin9 and Pin10 (USART1), turn on STM32 and press user button under 10 seconds duration otherwise the bootloader will run the installed application
	Use TeraTerm to upload your firmware. when it's done, it will jump directly to the new firmware.

Scoop inside bootloader firmware:
	Application firmware will be saved in flash memory starting in address 0x08020000, 2 sectors are reserved for the application (sector 5 and 6, total size is 256KB)
	at startup, user have 10 seconds to click user butter if he need to upload firmware (you can change this to wait for command from UART)
	since max playload size in 128 Byte, a buffer of 200 Byte is used to hold those data (packages) and save them in falsh memory directly

Application firmware requirements:
	+ it should be in bin format
	+ make sure the start address is "0x08020000" and flash size if 256 Kbyte
	+ also in system_stm32_f4xx.c uncomment the USER_VECT_TAB_ADDRESS macro and change VECT_TAB_OFFSET to 0x00020000U