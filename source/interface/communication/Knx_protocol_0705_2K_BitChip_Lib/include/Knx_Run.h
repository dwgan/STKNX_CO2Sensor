/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_Run.h
* �ļ���ʶ����
* ����ժҪ�����ļ�ΪKNXЭ��ջ״̬����ͷ�ļ���
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
******************************************************************************/



#ifndef _KNX_RUN_H_
#define _KNX_RUN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Run status machine define */
#define RUNSTATE_HALTED             0x00    /* The application is halted (e.g. no app loaded) */
#define RUNSTATE_RUNNING            0x01    /* The application is running                     */
#define RUNSTATE_READY              0x02    /* The application is ready to start (after reset)*/
#define RUNSTATE_TERMINATED         0x03    /* The application is stopped by external request */

/* Not extern (via property read) because only the low byte will be returned */
#define RUNSTATE_FLAG_SAVE_SUPPLY    0x40    /* A comming up power fail has been detected */
#define RUNSTATE_FLAG_SAVE_BUS       0x80    /* A comming up power fail has been detected */
#define RUNSTATE_MASK_EXT            0x0F    /* Mask to get the external run state  */
#define RUNSTATE_MASK_SAVE           0xF0    /* Mask to get the save flags in state */

/* Defines for run control commands (defined by KNX) */
#define RUNCONTROL_NO_OPERATION       0x00    /* No operation */
#define RUNCONTROL_RESTART            0x01    /* Request to start application */
#define RUNCONTROL_STOP               0x02    /* Request to stop application  */
/* Defines for run control commands (only used internally) */
#define RUNCONTROL_HALT               0xFF    /* Request to halt application */

/* Definitions for start delay */
#define START_DELAY_CONST            1700    /* Time constant in ms for application start   */
#define START_DELAY_MULT                5    /* Time mulitplier in ms for application start */
#define RUN_RESET_FLG                0x55
#define RUN_RESET_WAIT_TIM           40




/**************************************************************************************************************
* �������ƣ�BOOL Knx_StartRunApplication(VOID)
* ����������This function initializes the application.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_StartRunApplication(VOID);

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
VOID Knx_SetRunState(BYTE ucControl);

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
BYTE Knx_GetRunStateEx(VOID);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetRunState(VOID)
* ����������This function get the run state(without save flags).
* ���������no.
* ���������no.
* �� �� ֵ��run state without save flags.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE Knx_GetRunState(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);
* ����������calling a function in application.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);

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
VOID Knx_RunProcess(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_CheckRunConditions(VOID)
* ����������Checking whether the system is ready to start the application program.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_CheckRunConditions(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_RunOnBusPowerFail(VOID)
* ����������if bus power failed this function will be called.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_RunOnBusPowerFail(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_RunOnSupplyPowerFail(VOID)
* ����������supply power failed should call this function.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_RunOnSupplyPowerFail(VOID);

/****************************************************************************************************************
* Function: VOID KnxRun_SetResetCmd(VOID)
* Descrip.: reset device.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxRun_SetResetCmd(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _KNX_RUN_H_ */



/* end of file. */



