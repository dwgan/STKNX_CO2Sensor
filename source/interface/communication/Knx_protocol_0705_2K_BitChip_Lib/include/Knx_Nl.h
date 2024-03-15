/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_Nl.h
* �ļ���ʶ����
* ����ժҪ��knx ip network layer header file.
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


#ifndef _KNX_NL_H_
#define _KNX_NL_H_

#ifdef __cplusplus
extern "C" {
#endif


#define NPDU_CLR_HOP_COUNT        0x8F           /* clear the hop count.        */
#define NPDU_MAX_HOP_COUNT        0x60           /* Max. hop count.             */
#define NPDU_ESC_HOP_COUNT        0x70           /* No blocking hop count.      */
#define NPDU_HOP_COUNT_MASK       0x70           /* Mask for getting hop count. */


/**************************************************************************************************************
* �������ƣ�VOID Knx_NlUp(BYTE **pucUpFrame)
* ����������KNX network up frame handle��
* ���������BYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* ���������no.
* �� �� ֵ��no.
* ����˵����if there is a wrong in the buffer,we set the length to 0.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_NlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* �������ƣ�VOID Knx_NlDown(BYTE **pucDownFrame)
* ����������KNX network down frame handle��
* ���������BYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* ���������no.
* �� �� ֵ��no.
* ����˵����if there is a wrong in the buffer,we set the length to 0.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID Knx_NlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_NL_H_ */



/* end of file. */


