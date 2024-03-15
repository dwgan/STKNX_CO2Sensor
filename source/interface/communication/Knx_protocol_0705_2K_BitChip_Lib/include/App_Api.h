/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�App_Api.h
* �ļ���ʶ����
* ����ժҪ��Knx application API header file.
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�Jackson
* ������ڣ�2014��3��18��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2014��3��18��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�Jackson
*        �޸����ݣ������ļ�
******************************************************************************/


#ifndef _APP_API_H_
#define _APP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define KNX_API_START_VIR_ADDR         0x0800FE80


/*****************************************************************************************************************
* �������ƣ�VOID API_Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType)
* ����������application set handler relate to the device design.
* ���������APP_HANDLER pfHandler:application handler.
            BYTE ucHandlerType   :handler type.
                 APP_HANDLER_MAIN            0x01           application entry
                 APP_HANDLER_INIT            0x02           application initialize entry.
                 APP_HANDLER_SAVE            0x03           application save handling entry.
                 APP_HANDLER_BUS_SAVE        0x04           application save handling when bus voltage down.
                 APP_HANDLER_POWER_SAVE      0x05           application save handling when power supply down.
                 APP_HANDLER_WDG_RESET       0x06           application reset watchdog entry.
                 APP_HANDLER_RESET_CPU       0x07           CPU reset entry.
                 APP_HANDLER_PRGM_LED_OFF    0x08           OFF program LED entry.
                 APP_HANDLER_PRGM_LED_ON     0x09           light program LED entry.
                 APP_HANDLER_PRGM_KEY        0x0a           program key check entry.
                 APP_HANDLER_BUS_POWER_CHECK 0x0b           bus power check entry.
                 APP_HANDLER_ADC_OP          0x0c           adc operation entry. 
* ���������no.
* �� �� ֵ��no.
* ����˵����application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  ����
********************************************************************************************************************/
extern VOID (*const API_Knx_UserAppHandler_Set)(VOID *pfHandler,BYTE ucHandlerType);

/****************************************/
/**************** Knx time op. ************/
/****************************************/

/**************************************************************************
* �������ƣ�VOID API_KnxTm_TimerInit(BYTE ucDevNo)
* ����������KNX��ʱ����ʼ���ӿڣ���ʱ��1ms��
* ���������BYTE ucDevNo:device logical number.
* ���������no.
* �� �� ֵ��no.
* ����˵����ͨ��api�ṩ���ⲿʹ�á���ʱ������ͨ��ע�᷽ʽע�ᵽKNX��ʱ������
            ���й�����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      ���� 
**************************************************************************/
extern VOID (*const API_KnxTm_TimerInit)(BYTE ucDevNo);

/**************************************************************************
* �������ƣ�WORD32 API_KnxTm_GetTimeMs(VOID)
* ������������ȡ��ǰ��ʱ��������
* ��������� �ޡ�
* ��������� �ޡ�
* �� �� ֵ�� ��ǰ��������0-0xFFFFFFFF��
* ����˵���� ��
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      ���� 
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetTimeMs)(VOID);

/**************************************************************************
* �������ƣ�WORD32 API_KnxTm_GetDelayMs(WORD32 dwOldTime)
* ������������ȡ����ʱ�����ǰʱ���ʱ����룩��
* ��������� WORD16 wOldTime��������ʱ�䡣
* ��������� �ޡ�
* �� �� ֵ�� ʱ����룺0-0xFFFF��
* ����˵���� ��
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    ���� 
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetDelayMs)(WORD32 dwOldTime);

/**************************************************************************
* �������ƣ�VOID API_KnxTm_UpdateCycle(VOID)
* ���������� ��������ʱ��ͼ�����
* ��������� �ޡ�
* ��������� �ޡ�
* �� �� ֵ�� �ޡ�
* ����˵���� �ޡ�
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    ����
**************************************************************************/
extern VOID (*const API_KnxTm_UpdateCycle)(VOID);

/**************************************************************************
* �������ƣ�WORD16 API_KnxTm_GetCycleTimeMs(VOID)
* ���������� ��ȡѭ������ʱ�䣨���룩��
* ��������� �ޡ�
* ��������� �ޡ�
* �� �� ֵ�� ʱ��ֵ�����룬0~0xFFFF��
* ����˵���� ��Ҫ��ѭ���е���KnxTm_UpdateCycle��������ʱ�䡣
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        ����
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetCycleTimeMs)(VOID);

/**************************************************************************
* �������ƣ�WORD32 API_KnxTm_GetCycleCount(VOID)
* ���������� ��ȡѭ�����ڴ�����
* ��������� �ޡ�
* ��������� �ޡ�
* �� �� ֵ�� ѭ��������0~0xFFFF��
* ����˵���� ��Ҫ��ѭ���е���KnxTm_UpdateCycle�������¼�����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    ����
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetCycleCount)(VOID);


/****************************************/
/**************** Knx co. op. ************/
/****************************************/

/**************************************************************************************************************
* �������ƣ�BYTE API_KnxAl_GetCoBufferLength(BYTE ucCoNo)
* ����������This function retrieves the buffer length used by the given communication object.
* ���������BYTE ucCoNo :communication object No.
* ���������no.
* �� �� ֵ��buffer length.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetCoBufferLength)(BYTE ucCoNo);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* ����������This function is used by application to retrieve the value of the given communication object.
* ���������BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* ���������BYTE *pucBuffer :communication object data.
* �� �� ֵ��TRUE / FALSE.
* ����˵����This function will be a API function used by the application.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_GetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* ����������This function is used by application to set the value of the given communication object.
* ���������BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����(1)This function will be a API function used by the application.
            (2)To initiate a transmission of the new value KnxAl_RequestValueWrite(para) has to be called in addition.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_SetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_GetUpdatedCo(BYTE *pucCoNo)
* ����������This function is used by the application to retrieve the number of the next communication object
            updated by external event.
* ���������BYTE *pucCoNo:Co.objet No pointer.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_GetUpdatedCo)(BYTE *pucCoNo);

/**************************************************************************************************************
* �������ƣ�BYTE API_KnxAl_GetRamFlags(BYTE ucCoNo)
* ����������This function is used by application to retrieve the status of the given communication object.
* ���������BYTE ucCoNo     :communication object No.
* ���������no.
* �� �� ֵ��BYTE : the status of the communication object.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetRamFlags)(BYTE ucCoNo);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags)
* ����������This function is used by application to set the status of the given communication object.
* ���������BYTE ucCoNo     :communication object No.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_SetRamFlags)(BYTE ucCoNo, BYTE ucFlags);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_RequestValueWrite(BYTE ucCoNo)
* ����������This function initiates a value write request on the given communication object.
* ���������BYTE ucCoNo:Co.objet No.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����The system will transmitts the current value of the given communication object.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_RequestValueWrite)(BYTE ucCoNo);

/**************************************************************************************************************
* �������ƣ�BOOL API_KnxAl_RequestValueRead(BYTE ucCoNo)
* ����������This function initiates a value read request on the given communication object.
* ���������BYTE ucCoNo:Co.objet No.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����Attention: The response by remote device can only be received if the "Update on response" flag is set
            for this communication object.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_RequestValueRead)(BYTE ucCoNo);

/**************************************************************************************************************
* �������ƣ�VOID Knx_AlMgmInit(VOID)
* ����������KNX application layer management initialize��
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_AlMgmInit)(VOID);

/****************************************/
/*********** Knx memory data op. **********/
/****************************************/

/**************************************************************************************************************
* �������ƣ�VOID KnxMem_Init(VOID)
* ����������This function does the initialisation of the internal variables.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_KnxMem_Init)(VOID);

/**************************************************************************
* �������ƣ�BYTE API_KnxMem_GetByte(WORDPTR dwAddr)
* ����������get a byte data from the given virtual address.
* ���������WORDPTR dwAddr:source address.
* ���������no.
* �� �� ֵ��memory data.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BYTE (*const API_KnxMem_GetByte)(WORDPTR dwAddr);

/**************************************************************************
* �������ƣ�WORD16 API_KnxMem_GetWord(WORDPTR dwAddrHi)
* ����������This function reads one word from virtual memory area.
* ���������WORDPTR dwAddr:source address.
* ���������no.
* �� �� ֵ��memory data.
* ����˵����The requested word in virtual memory is assumed to have the 
            hibyte at address dwAddrHi and the lobyte at dwAddrHi+1
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD16 (*const API_KnxMem_GetWord)(WORDPTR dwAddrHi);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
* ����������get a byte data from the given virtual address.
* ���������WORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* ���������BYTE *pucData : destination data.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_ReadByte)(WORDPTR dwAddr, BYTE *pucData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
* ����������This function writes one byte to virtual memory area.
* ���������WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_WriteByte)(WORDPTR dwAddr,BYTE ucData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
* ����������This function writes one word to virtual memory area.
* ���������WORDPTR dwAddrHi:destination high address.
            WORD16 wData    :source data.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_WriteWord)(WORDPTR dwAddrHi, WORD16 wData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
* ����������This function writes ucCount bytes to virtual memory area.
* ���������WORDPTR dwAddr:destination high address.
            BYTE *pucData :source data.
            BYTE ucCount  :byte count.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_WriteData)(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteFinished(VOID)
* ����������This function is called to force writing data to the flash.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_WriteFinished)(VOID);

/**********************************************************************************
* �������ƣ�BYTE API_KnxMem_GetCoCount(VOID)
* ����������This function returns the number of communication objects.
* ���������WORD16 wPhysAddr : physical address.
* ���������no.
* �� �� ֵ��BYTE :communication object number.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
extern BYTE (*const API_KnxMem_GetCoCount)(VOID);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* ����������This function writes the checksum for the given memory block.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_SetChecksum)(BYTE ucObjIndex);

/**********************************************************************************
* �������ƣ�BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* ����������This function may be called by application to set some system parameters.
* ���������BYTE ucItem : system parameter id.
                          PARID_RESTART_COUNT
                          PARID_ROUTING_COUNT
                          PARID_DEL_USER_MSG
                          PARID_TELRATE_LIMIT
            BYTE ucValue: 
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
extern BOOL (*const API_KnxMem_SetParam)(BYTE ucItem, BYTE ucValue);

/**************************************************************************
* �������ƣ�VOID KnxMem_MediaRecoveDefault(VOID)
* ����������This function sets the parameter area in flash to the default.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����this function will be called at the start.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern VOID (*const API_KnxMem_MediaRecoveDefault)(VOID);

/**********************************************************************************
* �������ƣ�WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* ����������This function retrieves the virtual address of the buffer of the given 
            communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��WORDPTR :communication object's value reference(Virtual).
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
extern WORDPTR (*const API_KnxMem_GetCoValueRef)(BYTE ucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetCoValueType(BYTE nCoNo)
* ����������This function returns the value type of the given communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��BYTE :communication object's value type.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
extern BYTE (*const API_KnxMem_GetCoValueType)(BYTE ucCoNo);

/**************************************************************************************************************
* �������ƣ�BYTE API_KnxAl_GetCoBufferLength(BYTE ucCoNo)
* ����������This function retrieves the buffer length used by the given communication object.
* ���������BYTE ucCoNo :communication object No.
* ���������no.
* �� �� ֵ��buffer length.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetCoBufLength)(BYTE ucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
* ����������returns the configuration flags of the given communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��BYTE :communication object's configuration.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
extern BYTE (*const API_KnxMem_GetCoConfigByte)(BYTE ucCoNo);

/**************************************************************************
* �������ƣ�BOOL KnxMem_InitMedia(VOID)
* ����������This function is called by main at the begin.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_KnxMem_InitMedia)(BYTE ucDevNo);

/**************************************************************************************************************
* �������ƣ�BOOL KnxMem_VirRamInit(VOID)
* ����������This function initialize the virtual RAM.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BOOL (*const API_KnxMem_VirRamInit)(VOID);


/****************************************/
/*********** Knx program led&key op. **********/
/****************************************/

/**************************************************************************************************************
* �������ƣ�VOID Knx_GetProgKey(VOID)
* ����������checks the KNX key state and stores it.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����it should be called periodically.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_GetProgKey)(VOID);

/**************************************************************************************************************
* �������ƣ�BYTE API_Knx_GetPrgLedState(VOID)
* ����������retrieves the current state of the programming LED.
* ���������no.
* ���������BYTE ucState.
* �� �� ֵ��KNX_PRGLED_OFF / KNX_PRGLED_ON
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BYTE (*const API_Knx_GetPrgLedState)(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_SetPrgLed(VOID)
* ����������sets the state of the KNX programing LED according to the state in g_ucProgramState.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����it should be called periodically.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_SetPrgLed)(VOID);


/**************************************************************************************************************
* �������ƣ�VOID API_Knx_SetPrgLedState(BYTE ucState)
* ����������set the program LED state to g_ucProgramState.
* ���������BYTE ucState.
                                     KNX_PRGLED_OFF
                                     KNX_PRGLED_ON
                                     KNX_PRGLED_BLINK_SLOW
                                     KNX_PRGLED_BLINK_FAST
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_SetPrgLedState)(BYTE ucState);

/**************************************************************************
* �������ƣ�VOID *RecTable_GetRecord(WORD16 wRecordId)
* ����˵����This function searches the requested control record in the 
            record table.
* ���������WORD16 wRecordId : record id.
* ���������no.
* �� �� ֵ: record pointer.
* ����˵����Attention:the return pointer is physicall address.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern VOID *(*const API_RecTable_GetRecord)(WORD16 wRecordId);

/**************************************************************************
* �������ƣ�BOOL RecTable_SetRecord(VOID *ptRec2Write)
* ����˵����This function searches the record with the given ID 
            in the record table.If possible (only 1->0 to write)
            overwrite this record.else mark found record as invalid
            and use the next free record.
* ���������VOID *ptRec2Write : record.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_SetRecord)(VOID *ptRec2Write);

/**************************************************************************
* �������ƣ�BOOL RecTable_DeleteRecord(WORD16 wRecordId)
* ����˵����This function searches the requested control record in the 
            record table and mark it as invalid.
* ���������WORD16 wRecordId : record id.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_DeleteRecord)(WORD16 wRecordId);

/**************************************************************************
* �������ƣ�BOOL RecTable_DeleteAppRecords(void)
* ����˵����This function searches all control records used by the application
            process in the record table and mark them as invalid.
* ���������no.
* ���������no.
* �� �� ֵ: TRUE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_DeleteAppRecords)(void);

/**************************************************************************
* �������ƣ�BYTE RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* ����˵����This function initializes rectalbe.
* ���������BYTE ucBytePlace : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* ���������no.
* �� �� ֵ: saving data index.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern VOID (*const API_RecTable_OpInit)(BYTE ucDevNo,BYTE ucWrtSize);

/**************************************************************************
* �������ƣ�BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData)
* ����˵����reading one data byte to pucData from a record's data area.
* ���������WORD16 wRecordID : record ID.
            BYTE *pucData    : return data's pointer.
* ���������BYTE *pucData    : return data.
* �� �� ֵ: TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_GetByte)(WORD16 wRecordID, BYTE *pucData);

/**************************************************************************
* �������ƣ�BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData)
* ����˵����This function writes one data byte ucData to OneByteRecord with 
            wRecordID. modify it, else it creates new record.
* ���������WORD16 wRecordID : record ID.
            BYTE ucData      : input data byte.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_SetByte)(WORD16 wRecordID, BYTE ucData);

/**************************************************************************
* �������ƣ�BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord)
* ����˵����This function is used by cleanup to free dirty memory in one 
            byte and one word records.
* ���������T_RECORD *ptRecord : record.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����we only use byte mode to save the data.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_CleanUpRecord)(T_RECORD *ptRecord);

/**************************************************************************
* �������ƣ�BOOL RecTable_CleanUpTable(VOID)
* ����˵����This function copys all valid records to RAM, erases Record table 
            write back the valid records.
* ���������no.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����This function can not be called during running.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_CleanUpTable)(VOID);

/**************************************************************************
* �������ƣ�BOOL RecTable_ClearTable(void)
* ����˵����This function erases the complete record table.
* ���������no.
* ���������no.
* �� �� ֵ: TRUE / FALSE.
* ����˵����This function can not be called during running.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern BOOL (*const API_RecTable_ClearTable)(void);

/**************************************************************************************************************
* �������ƣ�VOID Knx_SetRunState(BYTE ucControl)
* ����������This function set the run state.
* ���������BYTE ucControl:run control byte.
                 RUNCONTROL_NO_OPERATION
                 RUNCONTROL_RESTART
                 RUNCONTROL_STOP
                 RUNCONTROL_HALT
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_SetRunState)(BYTE ucControl);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetRunStateEx(VOID)
* ����������This function get the run state(with save flags).
* ���������no.
* ���������no.
* �� �� ֵ��run state with save flags.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern BYTE (*const API_Knx_GetRunStateEx)(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_RunProcess(VOID)
* ����������managing the application precess.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����It will be called periodically.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_RunProcess)(VOID);

/*******************************************************************************************
* �������ƣ�WORD32 KnxLl_DevReg(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum)
* ��������������·��ע���豸���豸�߼��Ŵ�0��ʼ���������ע�ᡣ
* ���������BYTE ucLogNo:device's logical No.
            BYTE ucPhyNo:device's physical No.
            WORD16 wRxBufNum:buffer count for receiving.it should be bigger than 0.
            WORD16 wTxBufNum:buffer count for transmitting.it should be bigger than 0.
* ���������
* �� �� ֵ��SW_OK ��ע��ɹ���
            SW_ERR��ע��ʧ�ܣ�
* ����˵����(1)the device logical No. should begin with 0.
            (2)the device should be registered in sequence.
            (3)wBufferNum should set according to the resource of CPU.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
*********************************************************************************************/
extern WORD32 (*const API_KnxLl_DevReg)(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum);

/**************************************************************************************************************
* �������ƣ�VOID Knx_MsgInit(VOID)
* ����������KNX message handler initialization.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_MsgInit)(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_MsgProcess(VOID)
* ����������KNX��Ϣ��������ڡ�
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
extern VOID (*const API_Knx_MsgProcess)(VOID);

/**************************************************************************
* �������ƣ� WORD32 KnxLl_Init(BYTE ucBufferNum,BYTE ucBufferSize)
* ���������� initialize the link device.
* ��������� 
* ��������� 
* �� �� ֵ�� SW_OK �������ɹ�
             SW_ERR������ʧ��
* ����˵���� 
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 (*const API_KnxLl_Init)(BYTE ucBufferNum,BYTE ucBufferSize);


/****************************************/
/*********** system memory op. **********/
/****************************************/

extern VOID *(*const API_malloc)(unsigned short wLen);

extern VOID (*const API_free)(void *p);

extern VOID *(*const API_realloc)(void *p,unsigned short wLen);

extern VOID (*const API_memset)(void *p,unsigned char byte,unsigned short wLen);






#ifdef __cplusplus
}
#endif

#endif /* _APP_API_H_ */

/* end of file. */

