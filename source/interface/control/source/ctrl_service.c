/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�ctrl_service.c
* �ļ���ʶ����
* ����ժҪ�����ƽӿڲ�Դ�ļ���
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
#include "ctrl_service.h"
#include "mem_malloc.h"

/* timer control define */
static BYTE               sg_ucMaxTimerNum = 0;
static T_REGISTED_DEVICE  *sg_ptTimerDev[SW_TIMER_MAX_NUM] = \
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};           /* �ӿڲ��豸�� */
static BYTE sg_aucPhy2LogNo[SW_TIMER_MAX_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                       /* ���豸�����Ϊ������ӳ���豸���߼��š� */


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
extern WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE   ucIndex;
    T_REGISTED_DEVICE *ptListDev = NULL;
    
    /* we check the validity of the input parameter. */
    if((ptRegDev) && (SW_TIMER_MAX_NUM > sg_ucMaxTimerNum))
    {
        ucIndex = ptRegDev->ucLogDevNo;
        /* �豸�����߼������� */
        if(sg_ptTimerDev[ucIndex] == NULL)
        {
            /* ���߼����豸��ûע�� */
            ptListDev = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptListDev)
            {
                ptListDev->ucAppType  = ptRegDev->ucAppType;
                ptListDev->ucDevId    = ptRegDev->ucDevId;
                ptListDev->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptListDev->ucDevNo    = ptRegDev->ucDevNo;
                ptListDev->ptDevOp    = ptRegDev->ptDevOp;
                ptListDev->pfCallBack = NULL;
                sg_ptTimerDev[ucIndex]= ptListDev;
                /* save the device. */
                sg_aucPhy2LogNo[ptRegDev->ucDevNo] = ptRegDev->ucLogDevNo;
                sg_ucMaxTimerNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

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
extern WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData)
{
    BYTE aucData[4];
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    T_DATA_OPERARTION tDataOp;
    
    /* if(ptDataOp) */   /* �����ݲ����Ǹñ��� */
    {
        if(ucLogNo < SW_TIMER_MAX_NUM)
        {
            ptOperDev = sg_ptTimerDev[ucLogNo];
            if(ptOperDev)
            {
                tDataOp.ucDevNo   = ptOperDev->ucDevNo;   /* we change device's logic No. to device's physical No. */
                tDataOp.pucBuffer = aucData;              /* data buffer. */
                if(ptOperDev->ptDevOp->pfDrvRead)
                {
                    dwRes = ptOperDev->ptDevOp->pfDrvRead(&tDataOp);
                }
                if(SW_OK == dwRes)
                {
                    *pdwData = ((WORD32)aucData[3]<<24) | \
                               ((WORD32)aucData[2]<<16) | \
                               ((WORD32)aucData[1]<<8)  | \
                               (aucData[0]);
                }
            }
        }
    }
    
    return dwRes;
}

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
extern WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData)
{
    BYTE aucData[4];
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    T_DATA_OPERARTION tDataOp;
    
    /* if(ptDataOp) */   /* �����ݲ����Ǹñ��� */
    {
        if(ucLogNo < SW_TIMER_MAX_NUM)
        {
            ptOperDev = sg_ptTimerDev[ucLogNo];
            if(ptOperDev)
            {
                aucData[0] = (dwData & 0x000000ff);
                aucData[1] = (dwData & 0x0000ff00)>>8;
                aucData[2] = (dwData & 0x00ff0000)>>16;
                aucData[3] = (dwData & 0xff000000)>>24;
                tDataOp.ucDevNo   = ptOperDev->ucDevNo;   /* we change device's logic No. to device's physical No. */
                tDataOp.pucBuffer = aucData;              /* data buffer. */
                if(ptOperDev->ptDevOp->pfDrvWrite)
                {
                    dwRes = ptOperDev->ptDevOp->pfDrvWrite(&tDataOp);
                }
            }
        }
    }
    
    return dwRes;
}

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
extern WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
{
    BYTE   ucLogNo;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
        
    /* if(ptCtlPara) */
    {
        ucLogNo = ptCtlPara->ucPara[1];
        if(ucLogNo < SW_TIMER_MAX_NUM)
        {
            ptOperDev            = sg_ptTimerDev[ucLogNo];
            ptCtlPara->ucPara[0] = ptOperDev->ucDevId;
            ptCtlPara->ucPara[1] = ptOperDev->ucDevNo;
            if(ptOperDev->ptDevOp->pfDrvCtrl)
            {
                dwRes = ptOperDev->ptDevOp->pfDrvCtrl(ptCtlPara);
            }
            ptCtlPara->ucPara[1] = ucLogNo;
        }
    }
    
    return dwRes;
}

/**************************************************************************
* �������ƣ�VOID API_TimerDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
* ����˵�����豸��Ӧ�ûص���ڡ�
* ���������ptIntEvt->ucAppType : application type.
                      ucDevId   : device type.
                      ucDevNo   : physical No. of the device.
                      ucEvent   : event type.
                      ucBuffer  : parameter buffer.
* ���������
* �� �� ֵ: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
VOID API_TimerDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
{
    T_REGISTED_DEVICE *ptOperDev;
    
    ptOperDev         = sg_ptTimerDev[sg_aucPhy2LogNo[ptIntEvt->ucDevNo]];
    ptIntEvt->ucDevNo = ptOperDev->ucLogDevNo;              /* set the logical No. according to the physical No. */
    if(ptOperDev->pfCallBack)
    {
        ptOperDev->pfCallBack(ptIntEvt);
    }
    
    return;
}

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
                                    ->ucPara[3]:Timer scale(MS)./Counter/PWM parameter.
* ���������no.
* �� �� ֵ: SW_OK   ��successfully.
            SW_ERROR��failed.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    ucIndex = ptInitPara->ucPara[1];
    if(ucIndex < SW_TIMER_MAX_NUM)
    {
        /* get the registered device. */
        ptOperDev             = sg_ptTimerDev[ucIndex];
        /* hang the call back handler to the registered device. */
        ptOperDev->pfCallBack = ptInitPara->pIntCallBackHandler;
        /* change the input logical No to the device's physical No. */
        ptInitPara->ucPara[1] = ptOperDev->ucDevNo;
        if(ptInitPara->pIntCallBackHandler)
        {
            /* if there is a callback handler,we hang the common callback handler to the device driver. */
            ptInitPara->pIntCallBackHandler = API_TimerDrv_CallBack;
        }
        /* call the device's initialize handler. */
        if(ptOperDev->ptDevOp->pfDrvInit)
        {
            dwRes = ptOperDev->ptDevOp->pfDrvInit(ptInitPara);
        }
        /* recover the logical No. and callback handler. */
        ptInitPara->ucPara[1] = ucIndex;
        ptInitPara->pIntCallBackHandler = ptOperDev->pfCallBack;
    }
    
    return dwRes;
}



/** End-of-file */
