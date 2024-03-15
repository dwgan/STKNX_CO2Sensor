/****************************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_InternalApp.h
* �ļ���ʶ����
* ����ժҪ��knx internal application source file header file.
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�
* ������ڣ�2013��7��24��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2013��7��24��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�
*        �޸����ݣ�������������.
*******************************************************************************************/


#ifndef _KNX_INTERNALAPP_H_
#define _KNX_INTERNALAPP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define APP_MAIN_FUNC               0xFA           /* application main function ID        */
#define APP_MAIN_INIT_FUNC          0xFB           /* application main init. function ID  */
#define APP_SAVE_FUNC               0xFC           /* application save function ID.       */

#define APP_HANDLER_MAIN            0x01           /* application entry */
#define APP_HANDLER_INIT            0x02           /* application initialize entry.    */
#define APP_HANDLER_SAVE            0x03           /* application save handling entry. */
#define APP_HANDLER_BUS_SAVE        0x04           /* application save handling when bus voltage down.  */
#define APP_HANDLER_POWER_SAVE      0x05           /* application save handling when power supply down. */
#define APP_HANDLER_WDG_RESET       0x06           /* application reset watchdog entry. */
#define APP_HANDLER_RESET_CPU       0x07           /* CPU reset entry.         */
#define APP_HANDLER_PRGM_LED_OFF    0x08           /* OFF program LED entry.   */
#define APP_HANDLER_PRGM_LED_ON     0x09           /* light program LED entry. */
#define APP_HANDLER_PRGM_KEY        0x0a           /* program key check entry. */
#define APP_HANDLER_BUS_POWER_CHECK 0x0b           /* bus power check entry.   */
#define APP_HANDLER_ADC_OP          0x0c           /* adc operation entry. */



/*****************************************************************************************************************
* �������ƣ�VOID Knx_UserAppHandler_Set(APP_HANDLER pfHandler,BYTE ucHandlerType)
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
* ���������no.
* �� �� ֵ��no.
* ����˵����application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  ����
********************************************************************************************************************/
VOID Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_BusSave(VOID)
* ����������the internal bus save entry used for calling user extenal bus save function when bus voltage down.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_BusSave(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_SupplySave(VOID)
* ����������the internal supply save entry used for calling user extenal supply save function when supply down.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_SupplySave(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_InteralApp_Main(VOID)
* ����������internal application entry,used to call the user registering extenal application entry.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_InteralApp_Main(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_InternalApp_Init(VOID)
* ����������the internal app init. entry used for calling user's application initializing function.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_InternalApp_Init(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_ResetDog(VOID)
* ����������the internal dog handle entry used for calling user's dog handler.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_ResetDog(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_ResetDev(VOID)
* ����������the internal device reset entry used for calling user's device reset function.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_ResetDev(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_PrgmLedOff(VOID)
* ����������the internal entry for switching off the program LED.it will call the user's program led handler.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOff(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_PrgmLedOn(VOID)
* ����������the internal entry for switching on the program LED.it will call the user's program led handler.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOn(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_PrgmKey(VOID)
* ����������the internal entry for check the program key.it will call the user's program key handler.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_PrgmKey(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_Internal_BusPowerCheck(VOID)
* ����������the internal entry for checking the bus power.it will call the user's bus power handler.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_Internal_BusPowerCheck(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_InternalApp_Save(VOID)
* ����������the internal entry for application save.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_InternalApp_Save(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_InternalApp_Entry(BYTE ucFuncId)
* ����������the internal application entry used to call different internal function.
* ���������BYTE ucFuncId:internal function ID.
                 APP_MAIN_FUNC      : internal application main function.
                 APP_MAIN_INIT_FUNC : internal application initializing function.
                 APP_SAVE_FUNC      : internal application save function.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_InternalApp_Entry(BYTE ucFuncId);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData)
* ����������the internal ADC operation entry for application.
* ���������BYTE ucChnl:channel no.
            BYTE ucCunt:sample count.
            WORD16 *pwData:return data pointer.
* ���������WORD16 *pwData:return data.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData);




#ifdef __cplusplus
}
#endif

#endif /* _KNX_INTERNALAPP_H_ */



/* end of file. */

