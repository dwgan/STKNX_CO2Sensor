/*
 * @Author: 
 * @Date: 2021-06-10 22:52:57
 * @Description: add rx and tx function
 * @FilePath: 
 */ 

#include "type_def.h"
#include "SerialProc.h"
#include "stdint.h"
#include "string.h"
#include "demo_app.h"



#define FS_CHAR         0x7E
#define TSC_CHAR        0x7D
#define TE_CHAR         0x7F

#define HEADERINDEX         0X00
#define DATALENGHTINDEX     0X01
#define DATAINDEX           0X02
#define CHECKSUNINDEX       0X03



/*
import declear in serial phys c
*/
uint8_t mPlTxData[20+2];
uint8_t mPlTxDataSize;

typedef struct
{
  WORD32  timestamp;
  uint8_t nSize;
  uint8_t nData[20];
}tag_RTXStruct;


static tag_RTXStruct mRxBuffer[2];
//static tag_RTXStruct *mRxPointer;



//static uint8_t mTxBusy;

//static uint16_t mRxStamp;
//static uint8_t mRxSize;
//static uint8_t mRxBusy;
/**
 * @description: update receive pointer
 * @param {type} 
 * @return: 
  true:have free rx buffer
  false:no free rx buffer
 */
/*
uint8_t serialProc_UpdateRxPointer(void)
{
    if(mRxBuffer[0].nSize==0)
    {
      mRxPointer=&mRxBuffer[0];
    }
    else if(mRxBuffer[1].nSize==0)
    {
      mRxPointer=&mRxBuffer[1];
    }
    else
      return FALSE;
    return TRUE;
}

*/


void UART_ReceiveData_ApplicationProcess(uint8_t newdata)
{
	static unsigned char index = 0;
	static unsigned char i,datalength = 0;
	static unsigned char receiverdata[15],receiverindex,checksum;
	

	switch (index) 
	{
	    case HEADERINDEX:
	    {
			if (newdata == FS_CHAR)
			{
				index = DATALENGHTINDEX;
				receiverindex = 0;
			}			
	    }
		break;
		
		case DATALENGHTINDEX:
		{
		    datalength = newdata;
			index = DATAINDEX;		
		}
		break;
		
		case DATAINDEX:
		{ 
		    receiverdata[receiverindex++] = newdata;
			if(receiverindex >= datalength)
			{
				index = CHECKSUNINDEX;
			}
		}
		break;

		case CHECKSUNINDEX:	
		{
		    index = HEADERINDEX;
		    checksum = datalength;
			for(i= 0;i< datalength; i++ )
			{
                            checksum = checksum ^ receiverdata[i];
			}
			if(checksum == newdata)
			{
				if(mRxBuffer[0].nSize==0)
				{
				    for(i= 0;i< datalength;i++)
				    {
					    mRxBuffer[0].nData[i] =receiverdata[i];
				    }
					mRxBuffer[0].nSize = datalength;
					mRxBuffer[0].timestamp =  GetSystemTime_ms();
				}
				else if(mRxBuffer[1].nSize==0)
				{
				    for(i= 0;i< datalength ;i++)
				    {
					    mRxBuffer[1].nData[i] =receiverdata[i];
				    }
					mRxBuffer[1].nSize = datalength;
					mRxBuffer[1].timestamp = GetSystemTime_ms();
				}
				else
				{
                 ;
				}
			}
		}
		break;

		default:
			index = HEADERINDEX;
			break;

	}
}




/*
put into routine
*/
/**
 * @description: process rx buffer in routine
 * @param {type} stamp of this mcu
 * @return: none
 */
void serialProc_Routine(KEYINPUT_STATUS *keystatus)
{
    unsigned char i;
  if(mRxBuffer[0].nSize)
  {
     
      keystatus->ReceivedFlag = 1;
      keystatus->ReceivedTime = mRxBuffer[0].timestamp;
      for(i = 0; i< mRxBuffer[0].nSize;i++)
      {
          keystatus->ReceivedMessages[i] = mRxBuffer[0].nData[i] ;    
      }
	  mRxBuffer[0].nSize = 0 ;
  }
  else if((mRxBuffer[1].nSize))
  {

      keystatus->ReceivedFlag = 1;
      keystatus->ReceivedTime = mRxBuffer[0].timestamp;
      for(i = 0; i< mRxBuffer[0].nSize;i++)
      {
          keystatus->ReceivedMessages[i] = mRxBuffer[0].nData[i] ;    
      }
	  mRxBuffer[1].nSize = 0 ;
  }
  else
  {
      keystatus->ReceivedFlag = 0;
  }
}



