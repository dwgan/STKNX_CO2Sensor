#ifndef _SERIAL_PROC_H_
#define _SERIAL_PROC_H_

#include "stdint.h"
#include "demo_app.h"


uint8_t serialProc_TxData(uint8_t *pBuffer,uint8_t pSize);
void serialProc_Routine(KEYINPUT_STATUS *keystatus);
void serialProc_ByteRecv(uint8_t nByte);
void UART_ReceiveData_ApplicationProcess(uint8_t newdata);

#endif