#include <stm32f4xx.h>
#include <stdbool.h>

typedef enum
{
	enXMODEM_RECEIVE_PACKET_EOF,	// end of file reached
	enXMODEM_RECEIVE_PACKET_EOB,	// end of buffer
	enXMODEM_RECEIVE_PACKET_CANCELED,
	enXMODEM_RECEIVE_PACKET_TIMEOUT, // didn't receive xmodem cmd
	enXMODEM_RECEIVE_PACKET_ERROR_SIZE, // error, buffer size too small (less than 128 bytes)
	enXMODEM_RECEIVE_PACKET_ERROR // error in received packages
} t_enXmodemReceivePacketResult;

extern UART_HandleTypeDef huart1;

//t_enXmodemReceivePacketResult XMODEM_ReceiveFileInPackages(int8_t *pBuffer, uint16_t u16PackagesSize, uint16_t* pu16ReceivedBytes_out);
t_enXmodemReceivePacketResult XMODEM_ReceiveFileInPackages(int8_t *pBuffer, uint16_t u16PackagesSize, uint32_t u32Timeout_s, uint16_t* pu16ReceivedBytes_out);