/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�boardctrl.h
* �ļ���ʶ����
* ����ժҪ�����ļ�Ϊ��Ʒ������������ͷ�ļ���
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

#ifndef _BOARDCTRL_H_
#define _BOARDCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEFINE_AUTO_SER_SERIAL_NUMBER         0
  
/* do not modify the name of the follow macro. */
#define CLK0_FREQ_HZ                          16000000
#define STM32G070_MCUID_START                 (0x1FFF7590)

#ifndef MCU_SIZE
    #define MCU_SIZE 4                        /* 4 bytes */
#endif

#ifndef FLASH_PAGE_SIZE
    #define FLASH_PAGE_SIZE                   2048
#endif

#ifdef FLASH_WRT_SIZE
    #undef  FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE                    8
#else
    #define FLASH_WRT_SIZE                    8
#endif

/* redefine  the RxTx buffer pool size. */
#ifdef TOTAL_BUFFER_SIZE
    #undef  TOTAL_BUFFER_SIZE
#endif
#define TOTAL_BUFFER_SIZE               1288                                        /* 5 rx buffer,5 tx buffer.256 bytes for rx,128 bytes for tx. */
#define RX_BUFFER_NUMBER                5                                           /* rx buffer number. */
#define TX_BUFFER_NUMBER                5                                           /* tx buffer number. */
#define TX_PHY_BUFFER_SIZE              32                                          /* physical data buffer size. */

#define DEV_KEY_ON                      0
#define DEV_KEY_DEBOUNC_TIM             100
#define DEV_KEY_LONG_PRESS_TIM          300
  
/* Pin state define */
#define PIN_LOW_STATE                   0       /* Pin is Low voltage  */
#define PIN_HIGH_STATE                  1       /* Pin is High voltage */

/* key press state machine. */
#define KEY_PRESS_NONE  0x00
#define KEY_PRESS_ST    0x01
#define KEY_PRESS_CONF  0x02
#define KEY_PRESS_REL   0x03

#define KEY1_ST_MASK    0xfc
#define KEY2_ST_MASK    0xf3
#define KEY3_ST_MASK    0xcf
#define KEY4_ST_MASK    0x3f

/* KNX power check. */
#define PIN_SAVE_SIGNAL                 (0 == GET_GPIO_PORT_DATA(C,13))              /* power down. */
/* KNX programming key */
#define KNX_KEY_PORT                    (0 == GET_GPIO_PORT_DATA(B,10))             /* knx programming key. */
/* KNX programming led */
#define SET_KNX_LED_ON                  SET_GPIO_PORT(B,12)                          /* Switch LED off */
#define SET_KNX_LED_OFF                 CLR_GPIO_PORT(B,12)                          /* Switch LED on  */  

#define SET_RUN_LED_ON                 SET_GPIO_PORT(A,5)
#define SET_RUN_LED_OFF                  CLR_GPIO_PORT(A,5)

#define MASTER_RESET_TIME               3000                                        /* do master reset time.default 3s. */
/* device no define. */
#define AD_LOGIC_NO                     0                                           /* AD's logical No. */
#define AD_PHYSICAL_NO                  0                                           /* AD's physical No. */
#define TIMER_LOGIC_NO                  0                                           /* Timer logical No.  */
#define TIMER_PHYSICAL_NO               0                                           /* Timer physical No. */
#define FLASH_LOGIC_NO                  0                                           /* Flash logical No.  */
#define FLASH_PHYSICAL_NO               0                                           /* Flash physical No. */
#define KNX_CHIP_LOGIC_NO               0
#define KNX_CHIP_PH_NO                  0


/*************************************************************************
* �������ƣ�VOID BoardCtrl_Init(VOID) 
* ����˵�����豸������ʼ����
* �����������
* �����������
* �� �� ֵ����
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
VOID BoardCtrl_Init(VOID);

/*************************************************************************
* �������ƣ�BOOL Board_PrgmLed_On(VOID)
* ����˵�������ָʾ����
* �����������
* �����������
* �� �� ֵ����
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL Board_PrgmLed_On(VOID);

/*************************************************************************
* �������ƣ�BOOL Board_PrgmLed_Off(VOID)
* ����˵�������ָʾ����
* �����������
* �����������
* �� �� ֵ����
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL Board_PrgmLed_Off(VOID);

/*************************************************************************
* �������ƣ�BOOL Board_PrgmKey_Handle(VOID)
* ����˵������̰�ť״̬�ж�
* �����������
* �����������
* �� �� ֵ����
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL Board_PrgmKey_Handle(VOID);

/*************************************************************************
* �������ƣ�BOOL Board_SavePin_Check(VOID)
* ����˵�����ж����ߵ���ܽ��Ƿ��е��硣
* �����������
* �����������
* �� �� ֵ��TRUE:�������ߵ���
                          FALSE:û�����ߵ���
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL Board_SavePin_Check(VOID);

/*************************************************************************
* �������ƣ�BOOL Board_CheckMasterReset(VOID)
* ����˵��������Ƿ���Ҫ�����ϵ�ָ�Ĭ�����á�
* �����������
* �����������
* �� �� ֵ��TRUE:Ҫ�ָ�
                          FALSE:��Ҫ�ָ�
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
**************************************************************************/
BOOL Board_CheckMasterReset(VOID);

/*****************************************************************************************************
* Function        : VOID BrdCtrl_KeyCheck(VOID)
* Description     : check the key input.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
*             K1	PIO0_0     0 is pressed. 1 is released.
*             K2	PIO0_1
*             K15	PIO0_15
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID BrdCtrl_KeyCheck(VOID);

/**************************************************************************
* �������ƣ� Set_Output(BYTE ucChnlNo, BYTE ucOnOff)
* ���������� ��������Ĺܽ�״̬��
* ��������� BYTE ucChnlNo           ���ͨ���ţ���1��ʼ
                                     OUTPUT_CHANNLE_1
                                     OUTPUT_CHANNLE_2
                                     OUTPUT_CHANNLE_3
             BYTE ucOnOff            ����ָ��
                                     OUTPUT_LED_OFF  LED����
                                     OUTPUT_LED_ON   LED����
* ��������� ��      
* �� �� ֵ�� ��
* ����˵���� LED����״̬����Ӳ����ƽ����޸�
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
void Set_Output(BYTE ucChnlNo, BYTE ucOnOff);

/***************************************************************************************
* �������ƣ�BOOL VOID BoardCtrl_Set(VOID)
* ����˵����set device working parameters.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
****************************************************************************************/
VOID BoardCtrl_Set(VOID);

/*****************************************************************************************************
* Function        : BYTE Get_Input(BYTE ucChnlNo)
* Description     : return key status.
* Input parameter : BYTE ucChnlNo : channel No.
* Output parameter: No.
* Return          : key status.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
BYTE Get_Input(BYTE ucChnlNo);

#ifdef __cplusplus
}
#endif

#endif /* _BOARDCTRL_H_ */




