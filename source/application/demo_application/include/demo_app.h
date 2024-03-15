/******************************************************************************
* ��Ȩ���� (C)2013���Ͼ�******************** ���޹�˾��
*
* �ļ����ƣ�demo_app.h
* �ļ���ʶ����
* ����ժҪ��demo app header file.
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�    
* ������ڣ�2014��7��8��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2014��7��8��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�    
*        �޸����ݣ�������������.
******************************************************************************/

#ifndef _DEMO_APP_H_
#define _DEMO_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

  
#define OUTPUT_FLASH_TIME          500 /* 500 ms. */
#define INPUT_CHECK_TIME           50  /* 50ms    */
#define OUTPUT_FLASH_START         1
#define OUTPUT_FLASH_STOP          0


typedef struct
{
    BOOL   ucForced;               /* channel is in forced status. */
    BYTE   ucOldCoData;            /* previous data of co-obj.       */
    WORD32 dwStartTime;            /* input start time.            */
}T_INPUT_STATUS;

typedef struct
{
    BYTE    ucSwtCoNo;                   /* switch function com. NO. */
    BYTE    ucForceCoNo;                 /* force function com. No.  */
    BYTE    ucSceneCoNo;                 /* scene function  com. No. */
    T_INPUT_STATUS *pdwChnlParaRef;      /* channel ram data variable's address. */
    WORDPTR pdwSwtTypeRef;               /* switch type set address.   */
    WORDPTR pdwForceCtrlRef;             /* force control set address. */
    WORDPTR pdwSceneCtrlRef;             /* scene control set address. */
    WORDPTR pdwSceneDataRef;             /* scene data address.        */
}T_INPUT_CHANNEL;

typedef struct
{
    BYTE    ucOutCoNo;           /* output function com. NO. */
    BYTE    ucOutStCoNo;         /* output status com. NO.   */
    WORDPTR pdwOutTypeRef;       /* output type set address com. NO. */
}T_OUTPUT_CHANNEL;

typedef struct
{
    BYTE   ucOldSt;               /* the old status of output. */
    BYTE   ucFlashCtl;            /* control flash stop or  start. */
    WORD32 dwStartTime;           /* the action start time(ms). */
}T_OUTPUT_STATUS;



typedef struct
{
    BYTE   ReceivedFlag;
    WORD32 ReceivedTime;
    BYTE   ReceivedMessages[7];
}KEYINPUT_STATUS;

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void);

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Run(void);
void DataConvert_FloatToInt(BYTE *pData);
void DataConvert_IntToFloat(BYTE *pData);
void swapEndian(void* data, size_t size);
void DataConvert_Int32ToFloat( BYTE *pData );
u32_t GetSystemTime_ms(void);

#ifdef __cplusplus
}
#endif

#endif /* _DEMO_APP_H_ */






/* end of file. */
