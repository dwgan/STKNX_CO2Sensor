/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_Prop.h
* �ļ���ʶ����
* ����ժҪ�����ļ�ΪKNX���״̬���塣
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



#ifndef _KNX_PROGRAM_H_
#define _KNX_PROGRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* KNX programming key */
#define    KNX_PRG_KEY_OFF                    0x00                /* Key was not pressed            */
#define    KNX_PRG_KEY_NEW                    0x10                /* Key was just pressed           */
#define    KNX_PRG_KEY_ON                     0x20                /* Key was pressed long enough    */
#define    KNX_PRG_KEY_PRESSED                0x80                /* Key actually pressed           */
#define    KNX_PRG_KEY_MASK                   0x30                /* Key state without pressed flag */
#define    KNX_PRG_KEY_MASK_EX                0xF0                /* Key state with pressed flag    */

#define    KNX_KEY_TIME                       50                  /* Debounce time before pressed short */

/* KNX programming led  */
#define    KNX_PRGLED_OFF                     0x00                /* LED is switched off      */
#define    KNX_PRGLED_ON                      0x01                /* LED is switched on       */
#define    KNX_PRGLED_BLINK_SLOW              0x02                /* LED is blinking slow     */
#define    KNX_PRGLED_BLINK_FAST              0x03                /* LED is blinking fast     */
#define    KNX_PRGLED_MASK                    0x03                /* Mask to access LED flags */

#define    TIME_EXP_BLINK_SLOW                9                   /* Blinking time is 2^exp: here 512 ms */
#define    TIME_EXP_BLINK_FAST                6                   /* Blinking time is 2^exp: here  64 ms */



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
VOID Knx_GetProgKey(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_SetPrgLed(VOID)
* ����������sets the state of the KNX learning LED according to the state in g_ucProgramState.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����it should be called periodically.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_SetPrgLed(VOID);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetPrgLedState(VOID)
* ����������retrieves the current state of the programming LED.
* ���������BYTE ucState.
* ���������no.
* �� �� ֵ��KNX_PRGLED_OFF / KNX_PRGLED_ON
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE Knx_GetPrgLedState(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_SetPrgLedState(BYTE ucState)
* ����������set the program LED state.
* ���������BYTE ucState.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_SetPrgLedState(BYTE ucState);













#ifdef __cplusplus
}
#endif

#endif /* _KNX_PROGRAM_H_ */



/* End of file. */

