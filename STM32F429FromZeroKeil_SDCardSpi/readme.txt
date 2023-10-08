The project will go step by step on how to use SD card using SPI-SDcard adapter

Note:
	+ i'm using the free version of the keil uvision so i had to use size optimizer in the compiler to stay under 32k firmware size
	+ increase your heap and stack (0x400, 0x600) to avoid any problems (STM32 was stop working after few seconds and sometimes act weird, if this happen, this is probably because of lack of memory)
	+ in ffconf.h change the define _FS_LOCK to any max number of openned files that works for you