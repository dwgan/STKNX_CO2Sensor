/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_Tl.h
* �ļ���ʶ����
* ����ժҪ��knx ip transport layer header file.
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


#ifndef _KNX_TL_H_
#define _KNX_TL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define TPDU type. */
#define KNX_TPDU_TYPE_MASK        0xC0   /* TPDU type mask.                     */
#define KNX_TPDU_TYPE_DATA        0x00   /* TPDU data type,P2P-cntless/Brd/Grp. */
#define KNX_TPDU_TYPE_CDATA       0x40   /* T_Connect_Data.                     */
#define KNX_TPDU_TYPE_CMD         0x80   /* Cnt/DisCnt command.                 */
#define KNX_TPDU_TYPE_ACK         0xC0   /* connection ACK.                     */
#define KNX_TPDU_TYPE_SEQU_NO     0xFC

/* define connection command. */
#define KNX_TPDU_CNECT_CMD        0x80   /* establish a connection command. */
#define KNX_TPDU_DISCNT_CMD       0x81   /* release a connection command.   */

/* define connection ACK. */
#define KNX_TPDU_ACK              0xC2   /* Positive connection ACK. */
#define KNX_TPDU_NACK             0xC3   /* Negative connection ACK. */

/* connection sequence mask. */
#define KNX_TPDU_SEQ_MASK         0x3C   /* connection sequence mask. */


/**************************************************************************************************************
* �������ƣ�VOID Knx_TlUp(BYTE **pucUpFrame)
* ����������KNX transport up frame handle��
* ���������BYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* ���������no.
* �� �� ֵ��no.
* ����˵����if there is a wrong in the buffer,we set the length to 0.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_TlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* �������ƣ�VOID Knx_TlDown(BYTE **pucDownFrame)
* ����������KNX transport down frame handle��
* ���������BYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* ���������no.
* �� �� ֵ��no.
* ����˵����if there is a wrong in the buffer,we set the length to 0.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_TlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_TL_H_ */



/* end of file. */


