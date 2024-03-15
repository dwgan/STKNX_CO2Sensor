/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_TlState.h
* �ļ���ʶ����
* ����ժҪ��knx transport layer state machine header file.
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


#ifndef _KNX_TLSTATE_H_
#define _KNX_TLSTATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define the tl style.1/2/3 */
#define KNX_TL_STYLE               3
#define TL_STYLE1                  1
#define TL_STYLE2                  2
#define TL_STYLE3                  3

/* TL state machine definition. */
#define KNX_TL_CNECT_CLOSED        0    /* there is no connection.                 */
#define KNX_TL_CNECT_IDLE          1    /* there is a connection open and idle.    */
#define KNX_TL_CNECT_WAIT          2    /* Waiting for a T_ACK after sending data. */
#define KNX_TL_CNECT_CNECTING      3    /* Only for client.                        */

#define KNX_TL_REPT_MAX_CUNT       3    /* max. count for TL repititions. */

#define KNX_TL_SEQ_ADD_1           0x04   /* sequence No. + 1.    */
#define KNX_TL_SEQ_MASK            0x3C   /* sequence No.'s Mask. */

#define KNX_TL_REP_FLAG            0x8000 /* repeat send flag.                  */
#define KNX_TL_ACK_OVERTIME        3000   /* 3000ms-3s for ack overtime.        */
#define KNX_TL_CNECT_OVERTIME      6000   /* 6000ms-3s for connection overtime. */

/****************************************************
*   �ṹ����T_KNXTL_ATTR
*   ������  transport parameter connection parameter.
*   ������  see below.
*   ���ߣ�  Jackson
*   �޸ļ�¼��
*   2013-7-24  Jackson  �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucDevInfo;                                /* Bit0-3:the source device flag&No.Bit4-7:the destination device flag&No. */
    BYTE   ucMsgInfo;                                /* bit6-7:layer type.bit4-5:PortNo,bit0-3:connect channel No.              */
    BYTE   ucPoolId;                                 /* buffer pool used for connection frames. */
    BYTE   ucState;                                  /* connection's state.Closed/IDEL/Wait.    */
    BYTE   ucRxSeq;                                  /* receive sequence No.                    */
    BYTE   ucTxSeq;                                  /* transmit sequence No.                   */
    BYTE   ucRepCunt;                                /* the counter of repetition.              */
    WORD16 wParterAddr;                              /* remote device's address.                */
    WORD32 wTimeCnect;                               /* connection time for over time.          */
    WORD32 wTimeAck;                                 /* start time for waiting ACK.             */
    BYTE   *pucTlCtlUp;                              /* buffer for Tl control up frames.        */
    BYTE   *pucTlCtlDwn;                             /* buffer for Tl control down frames.      */
    BYTE   *pucTlData;                               /* buffer for down frames.                 */
}T_KNXTL_CNECT_ATTR;


/**************************************************************************************************************
* �������ƣ�BOOL Knx_TlStatInit(BYTE ucPoolId)
* ����������KNX transport layer state initiation.
* ���������BYTE ucPoolId:pool for TL.
* ���������no.
* �� �� ֵ��TRUE or FLASE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_TlStatInit(VOID);

/**************************************************************************************************************
* �������ƣ�VOID Knx_TlCnect_Data(**pucUpFrame)
* ����������Connection data frames handling.
* ���������BYTE **pucUpFrame:frame buffer's pointer's pointer.
* ���������no.
* �� �� ֵ��no.
* ����˵����we will clear the buffer length if the buffer is not need to be handled anymore.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_TlCnect_Data(BYTE **pucUpFrame);

/**************************************************************************************************************
* �������ƣ�VOID Knx_TlCnect_Ctrl(**pucUpFrame)
* ����������Connection command handling.
* ���������BYTE **pucUpFrame:frame buffer's pointer's pointer.
* ���������no.
* �� �� ֵ��no.
* ����˵����we will clear the buffer length if the buffer is not need to be handled anymore.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_TlCnect_Ctrl(BYTE **pucUpFrame);

/**************************************************************************************************************
* �������ƣ�VOID KnxTlCnect_Ack(**pucUpFrame)
* ����������Connection ACK handling.
* ���������BYTE **pucUpFrame:frame buffer's pointer's pointer.
* ���������no.
* �� �� ֵ��no.
* ����˵����we will clear the buffer length if the buffer is not need to be handled anymore.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID KnxTlCnect_Ack(BYTE **pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BYTE *KnxTl_GetStUpFrame(VOID)
* ����������Getting the KNX TL state management up frames.
* ���������no.
* ���������no.
* �� �� ֵ��NULL    :no return buffer;
            Not Null:up frames buffer pointer.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE *KnxTl_GetStUpFrame(VOID);

/**************************************************************************************************************
* �������ƣ�VOID KnxTl_GetStDwnFrame(VOID)
* ����������Getting the KNX TL state management up frames.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID KnxTl_GetStDwnFrame(VOID);

/**************************************************************************************************************
* �������ƣ�BYTE KnxTl_GetTlState(VOID)
* ����������Getting the KNX TL state.
* ���������no.
* ���������no.
* �� �� ֵ��   KNX_TL_CNECT_CLOSED
                             KNX_TL_CNECT_IDLE
                             KNX_TL_CNECT_WAIT
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE KnxTl_GetTlState(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL KnxTl_IsWaiting(VOID)
* ����������KNX TL is in waiting.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE:TL is in waiting;
            FALSE:TL is not in waiting.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL KnxTl_IsWaiting(VOID);

/**************************************************************************************************************
* �������ƣ�BOOL KnxTl_Evt15Action(BYTE *pucBuffer)
* ����������Action of Knx Tl Event15.
* ���������BYTE *pucBuffer:frame buffer's pointer.
* ���������no.
* �� �� ֵ��TRUE or FLASE.
* ����˵����case ucstate == CLOSED,we do action0;
            case ucstate == IDLE,we do action7,ucstate = WAIT;
            case ucstate == WAIT,we do action11(do nothing).
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL KnxTl_Evt15Action(BYTE *pucBuffer);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_TLSTATE_H_ */



/* end of file. */


