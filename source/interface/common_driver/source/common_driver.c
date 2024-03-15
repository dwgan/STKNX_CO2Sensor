/******************************************************************************
* ��Ȩ���� (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�common_driver.c
* �ļ���ʶ����
* ����ժҪ���ṩ��������Ӧ����ڵĽӿڲ��ļ���Ϊ��Ҫͳһ������豸
            �����ṩͳһ�������ڡ�
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





#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "common_driver.h"
#include "mem_malloc.h"

/* Common device. */
static BYTE               g_ucComDevNum = 0;
static T_REGISTED_DEVICE *gt_CommonDev[SW_COMMON_DEV_MAX_NUM] = {NULL,NULL,NULL,NULL};

/**************************************************************************
* �������ƣ�WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* ���������� ͨ���豸���ơ�
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* �� �� ֵ�� SW_OK�� �ɹ�
             SW_ERR��ʧ��
* ����˵���� 
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ���� 
**************************************************************************/
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    BYTE   ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptDev=NULL;
    
    /* �����Ȳ����Ƕ����ָ������顣 */
    {
        ucIndex = ptPara->ucPara[1];
        if(ucIndex < SW_COMMON_DEV_MAX_NUM)
        {
            ptDev             = gt_CommonDev[ucIndex];
            ptPara->ucPara[1] = ptDev->ucDevNo;
            /* if(ptDev->ptDevOp->pfDrvCtrl) */
            {
                dwRes = ptDev->ptDevOp->pfDrvCtrl(ptPara);
            }
            ptPara->ucPara[1] = ucIndex;
        }
    }
    
    return dwRes;
}

/**************************************************************************
* �������ƣ� void API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* ���������� ͨ����������豸ע����ڡ�
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* �� �� ֵ�� SW_ERR:ע��ʧ��
             SW_OK :ע��ɹ�
  ����˵���� �����м���ע�ắ����SPIģ��ע�ᵽ�м�㡣
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE ucIndex;
    T_REGISTED_DEVICE *ptRegDevice = NULL;
    
    if((ptRegDev) && (g_ucComDevNum < SW_COMMON_DEV_MAX_NUM))
    {
        /* Ӧ���豸���߼������� */
        ucIndex = ptRegDev->ucLogDevNo;
        if(NULL==gt_CommonDev[ucIndex])
        {
            /* ���豸��û�б�ע�ᡣ */
            ptRegDevice = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptRegDevice)
            {
                ptRegDevice->ucAppType  = ptRegDev->ucAppType;
                ptRegDevice->ucDevId    = ptRegDev->ucDevId;
                ptRegDevice->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptRegDevice->ucDevNo    = ptRegDev->ucDevNo;
                ptRegDevice->ptDevOp    = ptRegDev->ptDevOp;
                gt_CommonDev[ucIndex]   = ptRegDevice;
                g_ucComDevNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

/**************************************************************************
* �������ƣ� WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* ���������� ͨ��������ĳ�ʼ���ӿڡ�
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* ���������T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* �� �� ֵ�� SW_OK :��ʼ���ɹ�
             SW_ERR:��ʼ��ʧ��
 ����˵����  ���˼·�ϣ�Ҫ��ע����Դ���豸���ٵ��øýӿڡ�
             �ýӿ�ͨ�����ø����豸ע��Ľӿ��ٽ�����������
             ����ʼ����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����
**************************************************************************/
WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
{
    WORD32 dwRes;
    BYTE ucIndex;
    T_REGISTED_DEVICE *ptRegDevice = NULL;
    
    /* if(ptInitPara) */
    {
        ucIndex = ptInitPara->ucPara[1];
        if(ucIndex < SW_COMMON_DEV_MAX_NUM)
        {
            ptRegDevice = gt_CommonDev[ucIndex];
            if(ptRegDevice)
            {
                /* ��ʼ������Σ�ͨ��Control�ӿڽ������á� */
                dwRes = ptRegDevice->ptDevOp->pfDrvInit(ptInitPara);
                if(SW_ERR==dwRes)
                {
                    return dwRes;
                }
            }
        }
    }
    
    return dwRes;
}



/* End of common_driver.c */

