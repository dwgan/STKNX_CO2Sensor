/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�common_media.h
* �ļ���ʶ����
* ����ժҪ�����ļ�ΪǶ��ʽϵͳ����������塣
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


#ifndef _COMMON_MEDIA_H_
#define _COMMON_MEDIA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SW_MEDIA_DEV_MAX_NUM     2      /* max. number of media devices. */

#ifndef FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE       2      /* 2bytes(word16) */
#endif

/* media operation mode. */
#define SW_MEDIA_ERASE           0      /* erase the media from given address.         */
#define SW_MEDIA_BYTE            1      /* operate the media according to a byte.      */
#define SW_MEDIA_WORD            2      /* operate the media according to a word.      */
#define SW_MEDIA_LWORD           3      /* operate the media according to a long word. */
#define SW_MEDIA_LLWORD          4      /* operate the media according to 2 long word. */
#define SW_MEDIA_READ            5      /* read byte from the given address.           */

#define FLASH_BUF_ADDRESS_ALIGNMENT(x)  ((BYTE*)((((WORDPTR)(x))+MCU_SIZE-1) & (~(MCU_SIZE-1))))  /* align the address of the buffer. */
#define FLASH_BUF_SIZE_ALIGNMENT(x)     (((x)+MCU_SIZE-1) & (~(MCU_SIZE-1)))                      /* align the size of the buffer.    */

/**************************************************************************
* �������ƣ�WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
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
WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* �������ƣ�WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp)
* ����˵����interface for reading media.
* ���������T_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->dwDestAddr : the destination address.
* ���������T_DATA_OPERARTION *ptDataOp
                               ->wDataLength:length of read data in byte..
* �� �� ֵ��SW_OK    ���ɹ�
            SW_ERROR ������
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp);

/*********************************************************************************************
* �������ƣ� WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack)
* ���������� this function is called to initialize the given media device.
* ��������� BYTE ucLogNo : media device's logical No.
* ��������� No.
* �� �� ֵ�� SW_OK :successfully.
             SW_ERR:failed.
 ����˵����  
* �޸�����        �汾��     �޸���          �޸�����
* --------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����
**********************************************************************************************/
extern WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack);

/**************************************************************************
* �������ƣ�WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp)
* ����˵����ͨѶ�㷢�����ݽӿڡ�
* ���������T_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->wDataLength:length of data in byte.
                               ->dwDestAddr : the destination address.
* �����������
* �� �� ֵ: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
extern WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* �������ƣ� WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* ���������� �洢������������豸ע����ڡ�
* ��������� T_REGISTED_DEVICE *ptRegDev:input device parameter.
                                    ->ucAppType:interface type
                                                   SW_SAVE_INTERFACE
                                    ->ucDevId  :device type 
                                                   SW_SVMWDIA_EEPROM
                                                   SW_SVMEDIA_FRAM
                                                   SW_SVMEDIA_FLASH
                                    ->ucLogDevNo:logical device No.
                                    ->ucDevNo   :physical device No.
                                    ->ptDevOp   :device operation handler.
                                    ->pfCallBack:device's call back handler.
* ��������� no.
* �� �� ֵ�� SW_ERR:ע��ʧ��
             SW_OK :ע��ɹ�
  ����˵���� 
* �޸�����        �汾��     �޸���          �޸�����
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        ����  
**************************************************************************/
WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev);

#if(FLASH_PAGE_SIZE != 0)

/*****************************************************************************************************
* Function        : VOID API_Common_Media_Init(VOID)
* Description     : initialize common media.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID API_Common_Media_Init(VOID);

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo)
* Description     : flush the data in buffer to the flash media.
* Input parameter : ucDevNo   : logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing buffered byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo);

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer)
* Description     : read a byte data from Flash.
* Input parameter : dwAddr    : real address of the destination.
                    pucBuffer : data buffer pointer for saving.
                    ucDevNo   : logical device no.
* Output parameter: *pucBuffer: output data.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for reading byte data of FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer);

/**********************************************************************************************************
* function name   : WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt)
* Description     : write wCunt bytes to Flash buffer(not the practical media).
* Input parameter : dwAddr   : real address of the destination.
                    *pucData : written data.
                    ucDevNo  : logical device no.
                    wCunt    : byte's counts.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************************/
WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt);

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData)
* Description     : write a byte data to Flash buffer(not the practical media).
* Input parameter : dwAddr : real address of the destination.
                    ucData : written data.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData);

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr)
* Description     : erase a sector of flash media.
* Input parameter : dwAddr : real address of the sector.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr);

#endif /* #if(FLASH_PAGE_SIZE != 0) */


#endif /* _COMMON_MEDIA_H_ */

/* End of common_driver.h */

