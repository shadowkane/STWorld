/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \file
 *
 * Implementation of XMODEM transfer protocols
 *
 */
 
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "xmodem.h"
#include <stm32f4xx.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/** The definitions are followed by the X/Ymodem protocol */
#define XMDM_SOH     0x01 /**< Start of heading */
#define XMDM_EOT     0x04 /**< End of text */
#define XMDM_ACK     0x06 /**< Acknowledge  */
#define XMDM_NAK     0x15 /**< negative acknowledge */
#define XMDM_CAN     0x18 /**< Cancel */
#define XMDM_ESC     0x1b /**< Escape */

#define CRC16POLY   0x1021  /**< CRC 16 polynom */
#define PKTLEN_128  128     /**< Packet length */

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** Xmodem transfer error indicator */
int8_t cRrror;
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
 /**
 * \brief Transmit the character through xmodem protocol.
 *
 * \param ucChar  Character to be transmitted.
 */
static void XMODEM_PutChar(uint8_t ucChar)
{
	HAL_UART_Transmit(&huart1, &ucChar, 1, 30000);
}

/**
 * \brief Get the character through xmodem protocol.
 *
 * \return The character received
 */
static uint8_t XMODEM_GetChar(void)
{
	uint8_t c;
	
	HAL_UART_Receive(&huart1, &c, 1, 30000);
	
	return c;
}

/**
 * \brief Get the character through xmodem protocol.
 *
 * \param u32Timeout_ms  max time to wait for data (in ms).
 *
 * \return The character received
 */
static uint8_t XMODEM_GetCharWithTimeout(uint32_t u32Timeout_ms)
{
	uint8_t c;
	
	HAL_UART_Receive(&huart1, &c, 1, u32Timeout_ms);
	
	return c;
}

/**
 * \brief Get calculated crc value for xmodem transfer
 *
 * \param ucChar  The CRC original character.
 * \param uwCrc Calculated CRC value.
 * \return Calculated CRC value.
 */
static uint16_t XMODEM_GetCrc(int8_t ucChar, uint16_t uwCrc)
{

    uint16_t uwCmpt;

    uwCrc = uwCrc ^ (int32_t) ucChar << 8;

    for (uwCmpt= 0; uwCmpt < 8; uwCmpt++)
    {
      if (uwCrc & 0x8000)
          uwCrc = uwCrc << 1 ^ CRC16POLY;
      else
          uwCrc = uwCrc << 1;
    }

    return (uwCrc & 0xFFFF);
}

/**
 * \brief Get bytes through xmodem protocol.
 *
 * \param pData  Pointer to the data buffer.
 * \param dwLength Length of data expected.
 * \return Bytes received
 */
static uint16_t XMODEM_Getbytes(int8_t *pData, uint32_t dwLength)
{
    uint16_t uwCrc = 0;
    uint32_t dwCpt;
    int8_t cChar;

    for (dwCpt = 0; dwCpt < dwLength; ++dwCpt)
    {
        cChar = XMODEM_GetChar();

        if (cRrror)
            return 1;

        uwCrc = XMODEM_GetCrc(cChar,uwCrc);

        *pData++ = cChar;
    }

    return uwCrc;
}

/**
 * \brief Get a packet through xmodem protocol
 *
 * \param pData  Pointer to the data buffer.
 * \param ucSno  Sequnce number.
 * \return 0 for sucess and other value for xmodem error
 */
static int32_t XMODEM_GetPacket(int8_t *pData, uint8_t ucSno)
{
		//(package number (2 bytes) + data (128 bytes) + CRC(2 bytes))
    uint8_t  cpSeq[2];
    uint16_t  uwCrc, uwXcrc;

    XMODEM_Getbytes((int8_t *)cpSeq, 2);

    uwXcrc = XMODEM_Getbytes(pData,PKTLEN_128);

    if(cRrror)
        return (-1);

    /* An "endian independent way to combine the CRC bytes. */
    uwCrc  = (unsigned short)XMODEM_GetChar() << 8;
    uwCrc += (unsigned short)XMODEM_GetChar();

    if(cRrror == 1)
        return (-1);

    if ((uwCrc != uwXcrc) || (cpSeq[0] != ucSno) || (cpSeq[1] != (uint8_t) ((~(uint32_t)ucSno)&0xff)))
    {
        XMODEM_PutChar(XMDM_CAN);
        return(-1);
    }

    return(0);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
 /**
 * \brief Receive the files through xmodem protocol
 *
 * \param pBuffer  Pointer to received buffers
 * \return 0 for sucess and other value for xmodem error
 */
//uint32_t XMODEM_ReceiveFile(int8_t *pBuffer, uint16_t u16BufferSize, bool* bIsEOF)
//{
//    int32_t wTimeout;
//    int8_t cChar;
//    int32_t wDone;
//    uint8_t ucSno = 0x01;
//    uint32_t dwWavSize = 0;
//		bool bSkipFirstGetChar;
//    /* Wait and put 'C' till start xmodem transfer */
//    while(1)
//    {
//        XMODEM_PutChar('C');

//       if(HAL_UART_Receive(&huart1, &cChar, 1, 10000) == HAL_OK)
//			 {
//				 bSkipFirstGetChar = true;
//				 break;
//			 }
//    }

//    /* Begin to receive the data */
//    cRrror = 0;
//    wDone = 0;
//    while(wDone == 0) 
//    {
//				if(bSkipFirstGetChar==false)
//				{
//					cChar = (int8_t)XMODEM_GetChar();
//				}
//				else
//				{
//					bSkipFirstGetChar = false;
//				}
//        if(cRrror)
//            return 0;

//        switch(cChar) 
//        {   
//            /* Start of transfer */
//            case XMDM_SOH:
//                wDone = XMODEM_GetPacket(pBuffer+dwWavSize, ucSno);
//                if(cRrror)
//                    return 0;

//                if (wDone == 0) 
//                {
//                    ucSno++;
//                    dwWavSize += PKTLEN_128;
//                }

//                XMODEM_PutChar(XMDM_ACK);
//								if(dwWavSize>=u16BufferSize)
//								{
//									*bIsEOF = false;
//									wDone = dwWavSize;
//								}
//								break;

//            /* End of transfer */
//            case XMDM_EOT:
//                XMODEM_PutChar(XMDM_ACK);
//                wDone = dwWavSize;
//								*bIsEOF = true;
//                break;

//            case XMDM_CAN:
//            case XMDM_ESC:
//            default:
//                wDone = -1;
//                break;
//        }
//    }
//    return dwWavSize;
//}


//bool bIsFirstPacketReceived;
//uint8_t ucSno = 0x01;
//bool bIsResponseSent = true;
//t_enXmodemReceivePacketResult XMODEM_ReceiveFileInPackages(int8_t *pBuffer, uint16_t u16PackagesSize, uint16_t* pu16ReceivedBytes_out)
//{
//	t_enXmodemReceivePacketResult enRet;
//	int8_t cChar;
//	int32_t wDone;
//	
//	HAL_StatusTypeDef xHalStatus;
//	/* Begin to receive the data */
//	wDone = 0;
//	*pu16ReceivedBytes_out = 0;
//	uint8_t u8TimeoutCounter = 0;
//	
//	while(wDone == 0) 
//	{
//		if(bIsFirstPacketReceived==false)
//		{
//			u8TimeoutCounter++;
////				if(u8TimeoutCounter>=u8Timeout_s)
////				{
////					break;
////				}
//			XMODEM_PutChar('C');
//		}
//		if(bIsResponseSent == false)
//		{
//			XMODEM_PutChar(XMDM_ACK);
//			//XMODEM_PutChar('C');
//			bIsResponseSent = true;
//		}
//		XMODEM_PutChar(XMDM_ACK);
//		xHalStatus = HAL_UART_Receive(&huart1, (uint8_t*)&cChar, 1, 5000);
//		if(xHalStatus == HAL_TIMEOUT)
//		{
//			enRet = enXMODEM_RECEIVE_PACKET_TIMEOUT;
//			// if time's out, send "C" to attempt to start start the communication between sender and Receiver (in xModem protocol, receiver should start communcation by sending "C" or NAK)
////			if(bIsFirstPacketReceived==false)
////			{
////				u8TimeoutCounter++;
//////				if(u8TimeoutCounter>=u8Timeout_s)
//////				{
//////					break;
//////				}
////				XMODEM_PutChar('C');
////			}
////			else
//			if(bIsFirstPacketReceived==true)
//			{
//				bIsFirstPacketReceived = false;
//				ucSno = 0x01;
//				break; // exit while(wDone == 0)
//			}
//		}
//		else if(xHalStatus == HAL_OK)
//		{
//			switch(cChar) 
//			{   
//				/* Start of transfer */
//				case XMDM_SOH:
//					wDone = XMODEM_GetPacket(pBuffer+(*pu16ReceivedBytes_out), ucSno);
//					if(wDone != 0)
//					{
//						enRet = enXMODEM_RECEIVE_PACKET_ERROR;
//						bIsFirstPacketReceived = false;
//						ucSno = 0x01;
//					}
//					else 
//					{
//						ucSno++;
//						*pu16ReceivedBytes_out += PKTLEN_128;
//						if(*pu16ReceivedBytes_out>=u16PackagesSize)
//						{
//							enRet = enXMODEM_RECEIVE_PACKET_EOP;
//							wDone = -1;
//						}
//						bIsFirstPacketReceived = true;
//						bIsResponseSent = false;
//						//XMODEM_PutChar(XMDM_ACK);
//					}
//					break;

//				/* End of transfer */
//				case XMDM_EOT:
//					enRet = enXMODEM_RECEIVE_PACKET_EOF;
//					bIsFirstPacketReceived = false;
//					ucSno = 0x01;
//					wDone = 1;
//					XMODEM_PutChar(XMDM_ACK);
//					bIsResponseSent = true;
//					break;

//				case XMDM_CAN:
//				case XMDM_ESC:
//				default:
//					enRet = enXMODEM_RECEIVE_PACKET_ERROR;
//					bIsFirstPacketReceived = false;
//					wDone = -1;
//					break;
//			}
//		}
//		else 
//		{
//			enRet = enXMODEM_RECEIVE_PACKET_ERROR;
//			bIsFirstPacketReceived = false;
//			ucSno = 0x01;
//			break; // exit while(wDone == 0)
//		}
//	}
//	
//	return enRet;
//}

static uint8_t u8PackageNumber = 1;

t_enXmodemReceivePacketResult XMODEM_ReceiveFileInPackages(int8_t *pBuffer, uint16_t u16PackagesSize, uint32_t u32Timeout_s, uint16_t* pu16ReceivedBytes_out)
{
	t_enXmodemReceivePacketResult enRet;
	bool bStopReading;
	uint8_t u8XmodemPackageHeader;
	HAL_StatusTypeDef xHalStatus;
	uint8_t u8TimeoutCounter;
	
	bStopReading = false;
	u8TimeoutCounter = 1;
	*pu16ReceivedBytes_out = 0;
	
	if(u16PackagesSize<PKTLEN_128)
	{
		enRet = enXMODEM_RECEIVE_PACKET_ERROR_SIZE;
		bStopReading = true;
	}
	
	while(!bStopReading)
	{
		// sender will start send file unless we initiate the communcation by sending "C"
		// initate communication only at the start (mean, don't send 'C' while receiving packages)
		// u8PackageNumber = 1 mean, we are waiting for the first package from sender
		if(u8PackageNumber == 1)
		{
			XMODEM_PutChar('C');
		}
		// incase this this is not the start of file receiving process (if package number is not the first one, then we are in the middle of receiving file)
		// for optimization purposes we will send the ACK msg to sender here, this way will  make sure the sender won't start sending any further packages (stay in hold) until we are ready for the next package
		// we are ready for the next package when we finish storing the previous one or when we back to this function afte we exist it because of package size
		// the optimization is, we won't write this condition at the start of this function (before while(...)) and after receving package
		else
		{
			XMODEM_PutChar(XMDM_ACK);
		}
		// receive first byte of the packages (wait data for 5 seconds)
		xHalStatus = HAL_UART_Receive(&huart1, (uint8_t*)&u8XmodemPackageHeader, 1, 1000);
		// if successfully received data
		if(xHalStatus == HAL_OK)
		{
			// manage header
			switch(u8XmodemPackageHeader)
			{
				// start of package
				case XMDM_SOH:
					// receive rest of package 
					if(XMODEM_GetPacket(pBuffer+(*pu16ReceivedBytes_out), u8PackageNumber) == 0)
					{
						u8PackageNumber++;
						*pu16ReceivedBytes_out += PKTLEN_128;
						// if we have reached the max size we need to read, or no more space left in buffer for the next package, then pause fire receiving process and exit this function
						u16PackagesSize -= PKTLEN_128;
						if(u16PackagesSize<PKTLEN_128)
						{
							enRet = enXMODEM_RECEIVE_PACKET_EOB;
							bStopReading = true;
							// we will send the ACK message at the next function call
						}
						// we will send the ACK msg to sender at the next iteration
					}
					// error incase we didn't receive a package correctly
					// --todo--: attempt to receive again the same package (using package number), if still the package wasn't received correctly afte few attemps, declare it as error
					else
					{
						enRet = enXMODEM_RECEIVE_PACKET_ERROR;
						u8PackageNumber = 1;
						bStopReading = true;
					} 
					break;
				// end of text (or end of file)
				case XMDM_EOT:
					XMODEM_PutChar(XMDM_ACK);
					bStopReading = true;
					u8PackageNumber = 1;
					enRet = enXMODEM_RECEIVE_PACKET_EOF;
					break;
				// sending file been canceled
				case XMDM_CAN:
				case XMDM_ESC:
					// stop process and return sending file been canceled
					bStopReading = true;
					u8PackageNumber = 1;
					enRet = enXMODEM_RECEIVE_PACKET_CANCELED;
					break;
				// unknown header
				default:
					// stop process and return error
					bStopReading = true;
					u8PackageNumber = 1;
					enRet = enXMODEM_RECEIVE_PACKET_ERROR;
					break;
			}
		}
		// time out
		else if(xHalStatus == HAL_TIMEOUT)
		{
			u8TimeoutCounter++;
			if(u8TimeoutCounter > u32Timeout_s)
			{
				// stop process and return timeout
				bStopReading = true;
				u8PackageNumber = 1;
				enRet = enXMODEM_RECEIVE_PACKET_TIMEOUT;
			}
				
		}
		// other error
		else
		{
			// stop process and return error
			bStopReading = true;
			u8PackageNumber = 1;
			enRet = enXMODEM_RECEIVE_PACKET_ERROR;
		}
	}
	
	return enRet;
}