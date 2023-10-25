This is a Datalogger project build with STM32F429 to collect Temperature measurement from SHT35 every second and save it in file in SD-card with an option to send the contient of this file through serial port UART

Hardware:
	+ STM32f429 
	+ SD-card adapter (SPI version) + 2GB SD-card 	
	+ SHT35 (temperature and humidity sensor)
	+ DS3231 (RTC)
	
software:
	+ Stm32Cube MX to create the project but with no configuration
	+ Keil uvision as development IDE

Libraries:
	+ FatFS library for the filesystem (SD card driver also provided by this library)
	
Drivers developed by me:
	+ SHT35 driver
	+ RTC driver
	+ Xmode (file send/receive protocol via UART, only receive section was developed)

How it workds:
	When device powerd on, at first it will initialize and configure the hardware and all drivers, then it will ask you if you want to change time, then it will display information about the SD card and create the datalogger file under the name "StmLog.txt"
 	then i will start collecting tempeture measurements from SHT35 every second (the 1 second period is triggered by an interruption from RTC) and save it in file, and if you want to display file contient through serial port, you just click the user button.
