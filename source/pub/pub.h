/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�pub.h
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


#ifndef _PUB_H_
#define _PUB_H_

#ifdef __cplusplus
extern "C" {
#endif




    
/****************************** Ӧ�����Ͷ��� *************************************************/
#define SW_APP_KNX             (0x01)        /* KNXӦ��    */
#define SW_APP_KNX_IP          (0x02)        /* KNX IP     */
#define SW_APP_MODBUS          (0x03)        /* MODBUSӦ�� */
#define SW_APP_DLT645          (0x04)        /* Dlt645Ӧ�� */
#define SW_APP_SAVE_MEDIA      (0x05)        /* �洢Ӧ��   */


/****************************** �����ܲ㶨�� ***********************************************/
#define SW_INTERFACE_LAYER_NUM (0x06)        /* �ӿڲ����������������½ӿڲ㣬��Ҫ���Ĵζ��塣*/
#define SW_NA_INTERFACE        (0x00)        /* ���ò�     */
#define SW_SAVE_INTERFACE      (0x01)        /* �洢��     */
#define SW_COMM_INTERFACE      (0x02)        /* ͨѶ��     */
#define SW_MATH_INTERFACE      (0x03)        /* �����     */
#define SW_CONTROL_INTERFACE   (0x04)        /* ���Ʋ�     */
#define SW_DISPLAY_INTERFACE   (0x05)        /* ��ʾ��     */
#define SW_COMMON_DRIVER_LAYER (0x06)        /* ���������� */

/****************************** �ӿڲ�������ģʽ ********************************************/
#define SW_SVR_READ            (0x01)        /* ���ݶ�ȡ   */
#define SW_SVR_WRITE           (0x02)        /* ����д��   */

/************************* ͨ�ô����붨�� *******************************/

#define SW_ERRCODE_BASE           ( 0x00000000 )                                    /* ���������       */
#define SW_APP_ERRCODE_BASE       ( SW_ERRCODE_BASE + (0x01<<24) )                    /* Ӧ�ò��������� */
#define SW_INTERFACE_ERRCODE_BASE ( SW_ERRCODE_BASE + (0x02<<24) )                    /* �ӿڲ��������� */
#define SW_DRIVER_ERRCODE_BASE    ( SW_ERRCODE_BASE + (0x03<<24) )                    /* �������������� */

/************************* Ӧ�ò�����붨�� ****************************/
                          /* Ӧ�ò���ܴ�������� */
#define SW_APP_ENERGY_ERRCODE_BASE      ( SW_APP_ERRCODE_BASE + (1<<16) )            /* Ӧ�ò���������������� */
        #define SW_APP_ENERGY_DATA_ERR  ( SW_APP_ENERGY_ERRCODE_BASE + 1 )          /* �������ݳ���             */
        
                          /* Ӧ�ò�ͨѶ��������� */
#define SW_APP_COMM_ERRCODE_BASE        ( SW_APP_ERRCODE_BASE + (2<<16) )            /* Ӧ�ò�ͨѶ����������   */
        #define SW_APP_COMM_CHECK_ERR   ( SW_APP_COMM_ERRCODE_BASE + 1 )            /* ͨѶ���ݼ��ʧ��         */

/******* ���������붨�壬�����������а������ **************************/

/************************** ͨ�÷����붨�� ********************************/
#define SW_OK               ((WORD32)0x00000000)  /* �����ɹ� */
#define SW_ERR              ((WORD32)0xffffffff)  /* ����ʧ�� */
#define SW_INVALID_PARA     ((WORD32)0xfffffffe)  /* �Ƿ����� */
#define SW_NOT_SUPPORT      ((WORD32)0xfffffffd)  /* �Ƿ����� */

/******************************* ͨ�����ݽṹ���� ***************************/








#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H_ */

/* End-of-file */


