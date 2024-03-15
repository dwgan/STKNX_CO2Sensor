/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Knx_LoadCtrl.h
* �ļ���ʶ����
* ����ժҪ��KNX���ؿ���ͷ�ļ���
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


#ifndef _KNX_LOADCTRL_H_
#define _KNX_LOADCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif




/* Definition of load state machine */

/* The load states */
#define LOAD_STATE_UNLOADED            0x00    /* unloaded  */
#define LOAD_STATE_LOADED              0x01    /* loaded    */
#define LOAD_STATE_LOADING             0x02    /* loading   */
#define LOAD_STATE_ERROR               0x03    /* Load error*/
#define LOAD_STATE_UNLOADING           0x04    /* unloading */

/* The load events */
#define LOAD_EVENT_NONE                0x00    /* Nothing to do       */
#define LOAD_EVENT_START               0x01    /* Start to load       */
#define LOAD_EVENT_COMPLETE            0x02    /* Loading is complete */
#define LOAD_EVENT_SEGMENT             0x03    /* load segment        */
#define LOAD_EVENT_UNLOAD              0x04    /* Unload              */

/* The segment events */
#define SEG_EVENT_ALLOC                0x00    /* Allocation of abs. memory area       */
#define SEG_EVENT_STACK                0x01    /* Allocation of stack area (dummy)     */
#define SEG_EVENT_CONTROL              0x02    /* Set segment pointer (e.g. user main) */
#define SEG_EVENT_TASK_PTR             0x03    /* Set pointer to user init, save       */
#define SEG_EVENT_TASK_CONTROL1        0x04    /* Set user objects count and pointer   */
#define SEG_EVENT_TASK_CONTROL2        0x05    /* Set AL callback and CO pointer       */

/* Owner types of memory blocks used for memory control blocks MCB. */
#define OWNER_SYS                      0x00    /* Owner is system                      */
#define OWNER_ADDR                     0x01    /* Owner is address table               */
#define OWNER_ASSOC                    0x02    /* Owner is assiciation table           */
#define OWNER_APP                      0x03    /* Owner is application program         */
#define OWNER_PEI                      0x04    /* Owner is PEI program (only in 070x)  */
#define OWNER_ERROR_NONE               0x05    /* Error: Memory does not exist         */
#define OWNER_ERROR_MIXED              0x06    /* Error: Memory has not a unique owner */
#define OWNER_FREE                     0x07    /* Memory is not used                   */
#define OWNER_MAX_VALID                0x04    /* Max ID of a valid owner              */

#define FIRST_MCB_INDEX                0x00    /* First index for memory control records */
#define LAST_MCB_INDEX                 0x0B    /* Max number of memory control records   */
#define END_OF_MCB_INDEX               0xFF    /* Used as return value at end of MCB iteration */


/**************************************************************************************************************
* �������ƣ�BOOL Knx_LoadControl(BYTE* pucUpFrame,BYTE *pucDwFrame)
* ����������Handling the load control requests sent by property write to PID_LOAD_STATE_CONTROL Load state 
            machine according to AN080.
* ���������BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:down frame buffer's pointer.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_LoadControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_LoadStart(BYTE ucObjIndex)
* ����������This function handles the load start request.
* ���������BYTE ucObjIndex:object index.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_LoadStart(BYTE ucObjIndex);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_LoadComplete(BYTE ucObjIndex)
* ����������This function handles the load complete request.
* ���������BYTE ucObjIndex:object index.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_LoadComplete(BYTE ucObjIndex);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb)
* ����������This function retrieves the next memory control block beginning from the given index.
            This function may be used for an iteration through all MCBs.
* ���������BYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����The function does not check whether the returned block is valid.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* pMcb)
* ����������This function writes the MCB to the location given by nIndex.
* ���������BYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����The function does not check whether the returned block is valid.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* ptMcb);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum)
* ����������This function writes the checksum into the MCB given by ucIndex
* ���������BYTE ucIndex     :MCB index.
            WORD16 wChecksum : check sum.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����In the device model 070x, the memory checksums are stored in the corresponding MCB.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_LoadUnload(BYTE ucObjIndex)
* ����������This function handles the unload request
* ���������BYTE ucObjIndex : object index.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_LoadUnload(BYTE ucObjIndex);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_LoadSegment(BYTE* pucUpFrame)
* ����������This function handles the load segment requests.
* ���������BYTE* pucUpFrame : frame buffer pointer.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_LoadSegment(BYTE* pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_SegAllocation(BYTE *pucUpFrame)
* ����������This function handles the load segment request "Absolute Code/Data Allocation Record"
* ���������BYTE* pucUpFrame : frame buffer pointer.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_SegAllocation(BYTE *pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_SegControl(BYTE* pucUpFrame)
* ����������This function handles the load segment request "Segment Control Record".
* ���������BYTE* pucUpFrame : frame buffer pointer.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_SegControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_SegControl(BYTE* pucUpFrame)
* ����������This function handles the load segment request "Task Control Record-1".
* ���������BYTE* pucUpFrame : frame buffer pointer.
* ���������no.
* �� �� ֵ��TRUE or FALSE.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_SegTaskControl1(BYTE* pucUpFrame);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength)
* ����������return the owner of a given memory location in eeprom memory space.
* ���������BYTE* pucUpFrame : frame buffer pointer.
* ���������no.
* �� �� ֵ��ID.
* ����˵����Only unused blocks can be allocated.The maximum of MCBs are defined in LAST_MCB_INDEX
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb)
* ����������This function returns the owner of a given memory block in virtual memory space and retrieves the
            MCB data copied to pMcb.This pointer must point to a valid buffer with size of MCB.
* ���������WORD16 wAddr  : memory address.
            WORD16 wLength:memory length.
            T_KNXMEM_MCB *ptMcb:ginven MCB.
* ���������no.
* �� �� ֵ��ID.
* ����˵����The maximum of MCBs are defined in LAST_MCB_INDEX
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_CheckLoadStates(VOID)
* ����������This function checks whether the load states are ok.
* ���������no.
* ���������no.
* �� �� ֵ��ID.
* ����˵����It is called at startup an on disconnect.Never call this function during a download,because the 
            load states may be set to error.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_CheckLoadStates(VOID);

/**************************************************************************************************************
* �������ƣ�BYTE Knx_GetLoadState(BYTE ucObjIndex)
* ����������This function returns the load state of the given object.
* ���������no.
* ���������no.
* �� �� ֵ��load state.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BYTE Knx_GetLoadState(BYTE ucObjIndex);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState)
* ����������This function sets the load state of the given object.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FLASE.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState);

/**************************************************************************************************************
* �������ƣ�BOOL KnxLc_IsReadingAllowed(WORD16 wAddr, WORD16 wLength)
* ����������This function checks whether a read operation is allowed.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FLASE.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_IsReadingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength)
* ����������This function checks whether a write operation is allowed.
* ���������no.
* ���������no.
* �� �� ֵ��TRUE / FLASE.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* �������ƣ�BOOL Knx_GetRamAlloc(BYTE ucRamType, WORD16 *pwAddr, WORD16 *pwLength)
* ����������This function retrieves the start address and the size of the virtual RAM memory allocated via 
            load controls.
* ���������BYTE ucRamType : ram type.
            WORD16 *pwAddr : ram address.
            WORD16 *pwLength:ram length.
* ���������no.
* �� �� ֵ��TRUE / FLASE.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
***************************************************************************************************************/
BOOL Knx_GetRamAlloc(BYTE ucRamType, WORDPTR *pwAddr, WORD16 *pwLength);








#ifdef __cplusplus
}
#endif

#endif /* _KNX_LOADCTRL_H_ */



/* end of file */
