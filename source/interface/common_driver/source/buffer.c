/******************************************************************************
* ��Ȩ���� (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�buffer.c
* �ļ���ʶ����
* ����ժҪ������������Դ�ļ�
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�     
* ������ڣ�2014��3��18��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2014��3��18��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�     
*        �޸����ݣ������ļ�
******************************************************************************/


#include "type_def.h"
#include "Pub.h"
#include "sw_common.h"
#include "boardcfg.h"
#include "Boardctrl.h"       /* it should be included before buffer.h for the TOTAL_BUFFER_SIZE definition. */
#include "buffer.h"
#include "mem_malloc.h"


static BYTE         sg_ucPoolInitFlg = 0;
static BYTE         sg_ucPoolIndex = 0;
static BYTE         sg_BufferPool[DATA_BUF_SIZE_ALIGNMENT(TOTAL_BUFFER_SIZE)];
static BYTE         *sg_pucBufferPool = NULL,*sg_pucFreePool = NULL;
static T_BUFFER_MGM *sg_patBufferMgm[MAX_BUFFER_POOL_NUM] = {NULL,NULL,NULL,NULL};



/**************************************************************************
* �������ƣ�VOID Buffer_Pool_Init(VOID)
* ������������ʼ��buffer�ء�
* �����������
* �����������
* �� �� ֵ����
* ����˵����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
VOID Buffer_Pool_Init(VOID)
{
    WORD16 wIndex;
    BYTE   *pucData;
    
    sg_ucPoolIndex   = 0;
    sg_pucBufferPool = DATA_BUF_ADDRESS_ALIGNMENT(sg_BufferPool);
    sg_pucFreePool   = sg_pucBufferPool;
    pucData          = sg_pucBufferPool;
    for(wIndex=0;wIndex<TOTAL_BUFFER_SIZE;wIndex++)
    {
        *(pucData+wIndex) = 0;
    }
    sg_ucPoolInitFlg = BUFFER_INIT_FLAG;
    
    return;
}

/**************************************************************************
* �������ƣ�BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
* ������������buffer�ܳ��з���һ��buffer�ӳأ��ӳصĴ�СΪbuffer���Ⱥ͸���
            �ĳ˻���
* ���������WORD16 wBufferSize : һ��buffer�Ĵ�С
            WORD16 wBufferNum  : buffer�ĸ���
* �����������
* �� �� ֵ��POOL_ID_NULL  : buffer�ӳط���ʧ��
                            ����Ϊ����ɹ����POOL ID,Pool ID < MAX_BUFFER_POOL_NUM
* ����˵����wBufferSize > sizeof(WORDPTR) + 1
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
{
    BYTE         *pucPoint;
    WORD16       wMemSize,wIndex;
    T_BUFFER_MGM *ptMgm;
    
    if(BUFFER_INIT_FLAG != sg_ucPoolInitFlg)
    {
        return POOL_ID_NULL;
    }
    
    wMemSize = wBufferSize * wBufferNum;
    if(((sg_pucFreePool + wMemSize) > (sg_pucBufferPool + TOTAL_BUFFER_SIZE))||\
       (sg_ucPoolIndex >= MAX_BUFFER_POOL_NUM)||(wBufferSize <= sizeof(T_BUFFER_HEADER)))
    {
        /* Not enough. */
        return POOL_ID_NULL;
    }
    ptMgm = mem_malloc(sizeof(T_BUFFER_MGM));
    if(NULL==ptMgm)
    {
        return POOL_ID_NULL;
    }
    sg_patBufferMgm[sg_ucPoolIndex] = ptMgm;
    ptMgm->ucUseFlg         = 0;
    ptMgm->pucPoolHeader    = sg_pucFreePool;
    ptMgm->pucBufferIn      = NULL;
    ptMgm->pucBufLastIn     = NULL;
    sg_ucPoolIndex++;
    pucPoint = sg_pucFreePool;
    for(wIndex=0;wIndex < wBufferNum;wIndex++)
    {
        if((wIndex + 1) == wBufferNum)
        {
            ptMgm->pucPoolEnd                      = pucPoint;
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = NULL;                 /* the final one's next is set to NULL. */
        }
        else
        {
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = pucPoint+wBufferSize; /* save the next buffer's address into the buffer's header. */
        }
        ((T_BUFFER_HEADER *)pucPoint)->ucPoolId = sg_ucPoolIndex;            /* save the pool ID. */
        pucPoint += wBufferSize;
    }
    sg_pucFreePool += wMemSize;                                    /* set the pool current free point. */
    
    return sg_ucPoolIndex;
}

/**************************************************************************
* �������ƣ�BYTE* Buffer_Alloc(BYTE ucPoolId)
* ������������buffer�ӳ��з���һ��buffer��
* ���������BYTE ucPoolId : pool Id.
* �����������
* �� �� ֵ��NULL  : buffer�ӳط���ʧ��
                    �������ɹ���bufferָ��
* ����˵����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
BYTE* Buffer_Alloc(BYTE ucPoolId)
{
    BYTE         *pucBuffer;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0 == ucPoolId))
    {
        return NULL;
    }

    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL == ptMgm->pucPoolHeader)
    {
        /* There is no buffer in pool. */
        return NULL;
    }

#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    pucBuffer            = ptMgm->pucPoolHeader;
    ptMgm->pucPoolHeader = ((T_BUFFER_HEADER *)pucBuffer)->pucNext;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    /* clear the buffer next chain link. */
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;

    return pucBuffer;
}

/**************************************************************************
* �������ƣ�BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
* �����������ͷ�һ��buffer��pool�С�
* ���������BYTE ucPoolId : pool Id.
            BYTE *pucBuffer:���ͷ�buffer.
* �����������
* �� �� ֵ��NULL  : buffer�ӳ��ͷ�ʧ��
                    �ͷųɹ��������ӳ���buffer
* ����˵�������ں������������£�����ֵ������Ϊbuffer�ص��׵�ַ���м��㡣
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
{
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }

    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;
    
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    if(NULL == ptMgm->pucPoolHeader)
    {
        ptMgm->pucPoolHeader = pucBuffer;
    }
    else
    {
        ((T_BUFFER_HEADER *)ptMgm->pucPoolEnd)->pucNext = pucBuffer;
    }
    ptMgm->pucPoolEnd = pucBuffer;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    return ptMgm->pucPoolHeader;
}

/**************************************************************************
* �������ƣ�BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* ������������buffer���в���һ��buffer��
* ���������BYTE ucPoolId : pool Id.
            BYTE *pucBuffer:insert buffer.
* �����������
* �� �� ֵ��NULL  : ����bufferʧ��
                    ����ɹ������ص�ǰbuffer����buffer��
* ����˵�������ں������������£�����ֵ������Ϊbuffer�����׵�ַ���м��㡣
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
{
    BYTE *pucBufEnd;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }
    
    /* we get the input buffer chain's end. */
    pucBufEnd = pucBuffer;
    while(((T_BUFFER_HEADER *)pucBufEnd)->pucNext != NULL)
    {
        /* it is a buffer chain. */
        pucBufEnd = ((T_BUFFER_HEADER *)pucBufEnd)->pucNext;
    }
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    if(NULL == ptMgm->pucBufferIn)
    {
        ptMgm->pucBufferIn  = pucBuffer;
        ptMgm->pucBufLastIn = pucBufEnd;
    }
    /* we use first in first out mode. */
    else
    {
        ((T_BUFFER_HEADER *)(ptMgm->pucBufLastIn))->pucNext = pucBuffer;
        ptMgm->pucBufLastIn                                 = pucBufEnd;
    }
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    return ptMgm->pucBufferIn;
}

/**************************************************************************
* �������ƣ�BYTE* Buffer_Get(BYTE ucPoolId)
* ������������buffer���е�һ��buffer��
* ���������BYTE ucPoolId : pool Id.
* �����������
* �� �� ֵ��NULL  : ��ȡbufferʧ��
                    ��ȡ�ɹ������ص�ǰbuffer��
* ����˵����
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
BYTE* Buffer_Get(BYTE ucPoolId)
{
    BYTE *pucResult = NULL;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId))
    {
        return NULL;
    }
    
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL != ptMgm->pucBufferIn)
    {
        pucResult = ptMgm->pucBufferIn;
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
        ptMgm->pucBufferIn = ((T_BUFFER_HEADER *)(ptMgm->pucBufferIn))->pucNext;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif
        ((T_BUFFER_HEADER *)pucResult)->pucNext = NULL;
    }

    return pucResult;
}



/* end of file. */

