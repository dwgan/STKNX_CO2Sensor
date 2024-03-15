/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�ctrl_service.h
* �ļ���ʶ����
* ����ժҪ�����ļ�Ϊ���ƽӿڲ㹫��ͷ�ļ����塣
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

#ifndef _CTRL_SERVICE_H_
#define _CTRL_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************TIMER define***********************/
#define SW_TIMER_MAX_NUM                    20       /* max. number of timer. */
/* working mode define. */
#define SW_TIMER_TM_MODE                    0        /* timer working mode.   */
#define SW_TIMER_COUNT_MODE                 1        /* counter working mode. */
#define SW_TIMER_PWM_MODE                   2        /* PWM working mode.     */
/* control the timer. */
#define SW_TIMER_STOP                       0        /* stop the timer.  */
#define SW_TIMER_START                      1        /* start the timer. */
#define SW_DISABLE_TIMER_INT                2        /* disable the interrupt of timer. */
#define SW_ENABLE_TIMER_INT                 3        /* enable the interrupt of timer.  */
/* time scale. */
#define SW_TIMER_MS                         0        /* timer is running in ms scale. */
#define SW_TIMER_US                         1        /* timer is running is us scale. */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA�ṹ����Timer��ʼ��/����ʱ�Ĳ������塣
* �����б�
           ������       ��������    ȡֵ��Χ                 ����   
  ------------------------------------------------------------------------------------------------------------------
  Input  pIntCallBackHandler                               �ص�������
  Input  ucPara[0]      BYTE      1-                       �豸ID��
  Input  ucPara[1]      BYTE      0-                       �����豸��
  Input  ucPara[2]      BYTE      0-4                      ����ģʽ
  Input                           SW_TIMER_TM_MODE
  Input                           SW_TIMER_COUNT_MODE
  Input                           SW_TIMER_PWM_MODE
  Input  ucPara[3]      BYTE      1-                       ��ʱ��ʱ�䳤��(ms/us)
  Input  ucPara[4]      BYTE      SW_TIMER_MS/SW_TIMER_US
 -------------------------------------------------------------------------------------------------
  Output no.
*******************************************************************************************************************/





/**********************����ԭ�Ͷ���******************************/

/**************************************************************************
* �������ƣ�WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* ������������ʱ���豸ע�ᡣ
* ���������T_REGISTED_DEVICE *ptRegDev�����ṹ���塣
* ����������ޡ�
* �� �� ֵ��SW_OK   ��ע��ɹ���
            SW_ERROR��ע��ʧ�ܣ�
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* �������ƣ�WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData)
* ����˵������ʱ����������ȡ�ӿڡ�
* ���������ucLogNo:device logical no.
            WORD32 *pdwData:pointer of return data.
* ���������WORD32 *pdwData:timer data.
* �� �� ֵ��SW_OK    ��successfully.
            SW_ERROR ��failed.
* ����˵������ȡ����ʱ���ļ��������ݡ�
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData);

/**************************************************************************
* �������ƣ�WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData)
* ����˵������ʱ������д�ӿڡ�
* ���������ucLogNo:device logical no.
            WORD32 dwData:pointer of return data.
* �����������
* �� �� ֵ: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* ����˵����д��ʱ���ļ�����ֵ��
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData);

/**************************************************************************
* �������ƣ�WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵������ʱ���豸���ƽӿڡ�
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara.
*              ucPara[0]      BYTE      SW_PERIPHERAL_TIMER      Timer type.  
*              ucPara[1]      BYTE      1                        timer logical number.
*              ucPara[2]      BYTE      control command.         timer control command.  
* ���������device dependent.
* �� �� ֵ: SW_OK   ��successfully.
            SW_ERROR��failed.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* �������ƣ�WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸��ʼ���ӿڡ�
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:device ID
                                    ->ucPara[1]:logical device No.
                                    ->ucPara[2]:working mode.
                                                SW_TIMER_TM_MODE
                                                SW_TIMER_COUNT_MODE
                                                SW_TIMER_PWM_MODE
* ���������no.
* �� �� ֵ: SW_OK   ��successfully.
            SW_ERROR��failed.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);


#ifdef __cplusplus
}
#endif

#endif /* _CTRL_SERVICE_H_ */




