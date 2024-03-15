/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_Mem.h
* �ļ���ʶ����
* ����ժҪ��Э��memory����ͷ�ļ���
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


#ifndef _KNX_MEM_H_
#define _KNX_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Flash state define.we use these defines to check if the system start the first time. */
#define VIR_MEM_STATE_CLEAR          0xFF    /* State after erasing                 */
#define VIR_MEM_STATE_NEW            0xFE    /* State after loading EEPROM via JTAG */
#define VIR_MEM_STATE_OK             0xFC    /* State after KnxMem_InitEeprom()     */
#define VIR_MEM_STATE_WRITING        0xF0    /* Data writing is in progress         */
#define VIR_MEM_STATE_ERROR          0x00    /* Used for return value               */

#define NOT_PROGRAMMING              0x00    /* No programming in progress          */
#define ADDR_IN_PROG_AREA            0x01    /* Programming in progress but address in prog. area */
#define ADDR_OUT_OF_PROG_AREA        0x02    /* Programming in progress and address out of prog. area.*/
#define ADDR_OUT_OF_EEPROM           0x03    /* Error: Address is not valid eeprom space              */

#define GET_FLASH_PAGE(dwAddr)       (GET_REAL_OF_VIR(dwAddr)&(~(FLASH_PAGE_SIZE-1)))


/* Defines for communication object descriptor tabe.*/
#define COTAB_POS_COUNT              0    /* The count of communication objects */
#define COTAB_POS_RAMFLAGS_REF       1    /* The pointer to RAM flags (2 bytes) */
#define COTAB_POS_FIRSTVAL_REF       3    /* Start of the first object desc.    */

/* Defines for a single communication object descriptor */
#define CO_POS_VALUE_REF             0    /* The value pointer of the co (2 bytes)    */
#define CO_POS_CONFIG                2    /* The config byte of the co                */
#define CO_POS_TYPE                  3    /* The type byte of the co                  */
#define CO_DESC_SIZE                 4    /* The count of bytes for one co descriptor */

/* define for set parameter by user. */
#define PARID_RESTART_COUNT            0         /* Parameter ID for restart count (BIM112) */
#define PARID_ROUTING_COUNT            1         /* Parameter ID for routing count (BIM112) */
#define PARID_DEL_USER_MSG             11        /* Parameter ID for delete user messages   */
#define PARID_TELRATE_LIMIT            12        /* Parameter ID for tel. limitation rate   */

/****************************************************
*   �ṹ����T_RAM_DESC
*   ������  KNX virtual RAM discription structure.
*   ������  
            WORD16  wStart         Start of the block in virtual address space
            WORD16  wLength        Length of the block in bytes
            BYTE    *pucData       Pointer to block in physical address space
*   ���ߣ�  Jackson
*   �޸ļ�¼��
*   2013-7-24  Jackson  �����ṹ��
****************************************************/
typedef struct
{
    WORDPTR wStart;         /* Start of the block in virtual address space */
    WORD16  wLength;        /* Length of the block in bytes */
    BYTE    *pucData;       /* Pointer to block in physical address space */
}T_RAM_DESC;


/**************************************************************************
* �������ƣ�BYTE API_KnxMem_GetByte(WORDPTR dwAddr)
* ����������get a byte data from the given virtual address.
* ���������WORDPTR dwAddr:source address.
* ���������no.
* �� �� ֵ��memory data.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BYTE KnxMem_GetByte(WORDPTR dwAddr);

/**************************************************************************
* �������ƣ�WORD16 API_KnxMem_GetWord(WORDPTR dwAddrHi)
* ����������This function reads one word from virtual memory area.
* ���������WORDPTR dwAddr:source address.
* ���������no.
* �� �� ֵ��memory data.
* ����˵����The requested word in virtual memory is assumed to have the 
            hibyte at address dwAddrHi and the lobyte at dwAddrHi+1
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
WORD16 KnxMem_GetWord(WORDPTR dwAddrHi);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
* ����������get a byte data from the given virtual address.
* ���������WORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* ���������BYTE *pucData : destination data.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
* ����������This function writes one byte to virtual memory area.
* ���������WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
* ����������This function writes one word to virtual memory area.
* ���������WORDPTR dwAddrHi:destination high address.
            WORD16 wData    :source data.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
* ����������This function writes ucCount bytes to virtual memory area.
* ���������WORDPTR dwAddr:destination high address.
            BYTE *pucData :source data.
            BYTE ucCount  :byte count.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_WriteFinished(VOID)
* ����������This function is called to force writing data to the flash.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_WriteFinished(VOID);

/**********************************************************************************
* �������ƣ�BYTE API_KnxMem_GetCoCount(VOID)
* ����������This function returns the number of communication objects.
* ���������WORD16 wPhysAddr : physical address.
* ���������no.
* �� �� ֵ��BYTE :communication object number.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetCoCount(VOID);

/**************************************************************************
* �������ƣ�BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* ����������This function writes the checksum for the given memory block.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_SetChecksum(BYTE ucObjIndex);

/**********************************************************************************
* �������ƣ�BOOL API_KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* ����������This function may be called by application to set some system parameters.
* ���������BYTE ucItem : communication object N.
            BYTE ucValue: 
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue);

/**************************************************************************
* �������ƣ�VOID KnxMem_MediaRecoveDefault(VOID)
* ����������This function clears the parameter area in flash.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����this function will be called at the start.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
VOID KnxMem_MediaRecoveDefault(VOID);

/**********************************************************************************
* �������ƣ�WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* ����������This function retrieves the virtual address of the buffer of the given 
            communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��WORDPTR :communication object's value reference(Virtual).
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetCoValueType(BYTE nCoNo)
* ����������This function returns the value type of the given communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��BYTE :communication object's value type.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetCoValueType(BYTE ucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
* ����������returns the configuration flags of the given communication object.
* ���������BYTE ucCoNo : number of communication object.
* ���������no.
* �� �� ֵ��BYTE :communication object's configuration.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo);

/**************************************************************************
* �������ƣ�BOOL KnxMem_InitMedia(BYTE ucDevNo)
* ����������This function is called by main at the begin.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_InitMedia(BYTE ucDevNo);

/**************************************************************************************************************
* �������ƣ�BOOL KnxMem_VirRamInit(VOID)
* ����������This function initialize the virtual RAM.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL KnxMem_VirRamInit(VOID);

/**************************************************************************************************************
* �������ƣ�VOID KnxMem_Init(VOID)
* ����������This function does the initialisation of the internal variables.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
VOID KnxMem_Init(VOID);

/**************************************************************************
* �������ƣ�BYTE KnxMem_GetByte(WORDPTR dwAddr)
* ����������This function reads one byte from virtual memory as well as from
            physical memory.
* ���������WORDPTR dwAddr:source address.
* ���������no.
* �� �� ֵ��memory data.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BYTE KnxMem_GetByteEx(WORDPTR dwAddr);

/**********************************************************************************
* �������ƣ�BYTE* KnxMem_GetCoRamFlags(VOID)
* ����������This function returns the pointer to the communication objects RAM flags.
* ���������WORD16 wPhysAddr : physical address.
* ���������no.
* �� �� ֵ��BYTE *:physical address of RAM.
* ����˵����The pointer returned by this function is valid in the physical address 
            space of the controller
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE* KnxMem_GetCoRamFlags(VOID);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetSendConnNo(BYTE ucCoNo)
* ����������This function is used by sending communication object to retrieve the 
            sending connection number.
* ���������BYTE ucCoNo : communication object N.
* ���������no.
* �� �� ֵ��BYTE : connection number(Grp. index).
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetSendConnNo(BYTE ucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetAssocCount(VOID)
* ����������This function returns the count of associations defined in virtual ROM 
            area.
* ���������no.
* ���������no.
* �� �� ֵ��BYTE : associations count.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetAssocCount(VOID);

/**********************************************************************************
* �������ƣ�BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo)
* ����������This function retrieves an association given by index.
* ���������BYTE ucIndex    : association index.
* ���������BYTE *pucConnNo : connection number.
            BYTE *pucCoNo   : communication object No.
* �� �� ֵ��BYTE : associations count.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetAlTelRateLimit(void)
* ����������This function retrieves the current telegram rate limitation rate.
* ���������no. 
* ���������no.
* �� �� ֵ��hop count.
* ����˵����Value definition: Telegram rate whithin 17s, 0x00,if limitation is off
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetAlTelRateLimit(void);

/**************************************************************************
* �������ƣ�BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* ����������This function sets the physical address of the device.
* ���������WORD16 wPhysAddr : physical address.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr);

/**************************************************************************
* �������ƣ�BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData)
* ����������This function writes one byte to virtual media area.
* ���������WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData);

/**********************************************************************************
* �������ƣ�BOOL KnxMem_GetDelUserMsg(void)
* ����������This function retrieves whether automated deleting of user messages is enabled.
* ���������no. 
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BOOL KnxMem_GetDelUserMsg(void);

/**********************************************************************************
* �������ƣ�BYTE KnxMem_GetNlRoutingCount(VOID)
* ����������This function retrieves the current routing count.
* ���������no. 
* ���������no.
* �� �� ֵ��hop count.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetNlRoutingCount(VOID);

/**************************************************************************
* �������ƣ�BOOL KnxMem_CheckChecksum(VOID)
* ����������This function checks the checksum(s) of the data in EEPROM area.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL KnxMem_CheckChecksum(VOID);

/**********************************************************************************
* �������ƣ�BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* ����������This function returns the connection number of the given group address.
* ���������WORD16 wPhysAddr : physical address.
* ���������no.
* �� �� ֵ��TRUE / FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***********************************************************************************/
BYTE KnxMem_GetConnNo(WORD16 wGrpAddr);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_MEM_H_ */


/* end of file. */

