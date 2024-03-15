/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Rec_Table.h
* �ļ���ʶ����
* ����ժҪ��record table header file.
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


#ifndef _REC_TABLE_H_
#define _REC_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif


/* record's status define. */
#define ID_RECORD_FREE                0xffff    /* Record is free and ready to be used      */
#define ID_RECORD_VALID               0x5555    /* The data that record contains is valid   */
#define ID_RECORD_INVALID             0xaaaa    /* The data that record contains is invalid */
#define ID_RCD_FREE_DATA              0xff
#define ID_RCD_INVALID_DATA           0xaa
#define ID_RCD_VALID_DATA             0x55

#define RCD_INVALID_INDEX             0
#define RCD_INVALID_ST_OFFSET         16

#define RCD_VALID_INDEX               8
#define RCD_VALID_ST_OFFSET           24

#define RCD_DATA_INDEX                0
#define RCD_DATA_OFFSET               8
#define RCD_ST_LENG                   16

/* system relating record type define. */
#define ID_REC_SYS                    0x01    /* One byte record used by system */
#define ID_REC_FLASH                  0x02    /* one byte used for flash status. */
/* application relatint record define. */
#define ID_REC_APP                    0x06    /* One byte Record used by application */

/* record table virtual space.1K bytes,8 bytes per record. */
#define RECORD_TABLE_BEG             VIR_BEG_REC_EE
#define RECTBL_FIRST_RECORD          RECORD_TABLE_BEG

#define RECORD_TABLE_END                   VIR_END_REC_EE
#define RECTBL_RECORD_LEN                  8
#define RECTBL_LAST_RECORD                 (RECORD_TABLE_END - RECTBL_RECORD_LEN + 1)
#define RECTBL_RECORD_CUNT                 ((RECORD_TABLE_END - RECORD_TABLE_BEG + 1)/RECTBL_RECORD_LEN)
#define BUILD_RECORD_ID(ucMainId,ucSubId)  (((ucMainId & 0x0F)<<8) | ucSubId)

#define GET_RECORD_MAIN_ID(ptRecord)   (((T_RECORD*)ptRecord)->ucMainId)
#define GET_RECORD_SUB_ID(ptRecord)    (((T_RECORD*)ptRecord)->ucSubId)
#define GET_RECORD_ID(ptRecord)        ((((T_RECORD*)ptRecord)->ucMainId << 8) + ((T_RECORD*)ptRecord)->ucSubId)

/****************************************************
*   �ṹ����T_RECORD
*   ������  record structure define of record table.
            every record has 6 data.
*   ������  
            BYTE ucMainId:4;           The main ID of record   
            BYTE ucReserved_0:4;       Only used by word record
            BYTE ucSubId;              The sub ID of record    
            BYTE aucResv[6];           reserve space.
            BYTE aucData[8];           Data bytes
            BYTE aucStatus[16];        The status of record,0-1 invalid,2-3 valid
*   �޸ļ�¼��
*   2013-7-24  Jackson  �����ṹ��
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucMainId:4;                     /* The main ID of record    */
    BYTE ucReserved_0:4;                 /* Only used by word record */
    BYTE ucSubId;                        /* The sub ID of record     */
    BYTE aucResv[6];                     /* reserve space.           */
    BYTE aucData[8];                     /* Data bytes               */
    BYTE aucStatus[RCD_ST_LENG];         /* The status of record     */
}T_RECORD;
#pragma pack()

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
VOID *RecTable_GetRecord(WORD16 wRecordId);

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
BOOL RecTable_SetRecord(VOID *ptRec2Write);

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
BOOL RecTable_DeleteRecord(WORD16 wRecordId);

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
BOOL RecTable_DeleteAppRecords(void);

/**************************************************************************
* �������ƣ�BYTE RecTable_GetByteIndex(BYTE ucBytePlace)
* ����˵����This function retrieves the byte index in a byte record for a 
            given ucBytePlace bit pattern.
* ���������BYTE ucBytePlace : data saving pattern.
* ���������no.
* �� �� ֵ: saving data index.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BYTE RecTable_GetByteIndex(BYTE ucBytePlace);

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
BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData);

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
BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData);

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
BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord);

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
BOOL RecTable_CleanUpTable(VOID);

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
BOOL RecTable_ClearTable(void);

/**************************************************************************
* �������ƣ�VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* ����˵����init recorder table operation.
* ���������BYTE ucDevNo     : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* ���������no.
* �� �� ֵ: no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize);






#ifdef __cplusplus
}
#endif

#endif /* _REC_TABLE_H_ */

/* end of file. */
