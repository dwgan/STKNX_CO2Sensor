/*****************************************************************************************
* Copy right (C) for *********** company.(2016)
*
* File Name        : Stm32G0xxx_uart.h
*
* File Description : header file for the driver of stm32G0xxx cpu's uart.
*
* Other Description: this file realizes the driver of Stm32G0xx uart.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
*****************************************************************************************/


#ifndef _STM32G0XXX_UART_H_
#define _STM32G0XXX_UART_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_UART_DEVICE_NUM                 (4)                                /* Max number of uart device   */

/* Interrupt reason data field position definition */
#define UART_INT_DATA_LEN_POS               (0)                                /* Field of data length        */
#define UART_INT_RX_DATA_POS                (1)                                /* Field of received data      */

/* Uart parameter data field position definition   */
#define UART_DEVICE_ID                      (0)                                /* Field of device type ID     */
#define UART_DEV_NO                         (1)                                /* Field of device No.         */
#define UART_OPERATION_CMD                  (2)                                /* Field of operation command  */
#define UART_BIT_MODE                       (3)                                /* Field of bit mode setting   */
#define UART_COMM_STAT                      (3)                                /* Field of Rx/Tx status       */
#define UART_STOP_BIT_MODE                  (4)                                /* Field of stop mode setting  */
#define UART_PARITY_MODE                    (5)                                /* Field of parity setting     */
#define UART_BAUD_MODE                      (6)                                /* Field of baud rate          */

/* Uart number */
#define UART_1                              (0)
#define UART_2                              (1)
#define UART_3                              (2)
#define UART_4                              (3)

/* Uart base addresses */
#define UART1_BASE                          ((T_UART_MEM_MAP)0x40013800u)      /* Address of base register for Uart1 */
#define UART2_BASE                          ((T_UART_MEM_MAP)0x40004400u)      /* Address of base register for Uart2 */
#define UART3_BASE                          ((T_UART_MEM_MAP)0x40004800u)      /* Address of base register for Uart3 */
#define UART4_BASE                          ((T_UART_MEM_MAP)0x40004C00u)      /* Address of base register for Uart4 */
#define UART5_BASE                          ((T_UART_MEM_MAP)0x40005000u)      /* Address of base register for Uart5 */

/* Uart Register accessors */
#define UARTX_SR(base)                      ((base)->SR)                       /* Address of Status Register    */
#define UARTX_DR(base)                      ((base)->DR)                       /* Address of Data Register      */
#define UARTX_BRR(base)                     ((base)->BRR)                      /* Address of Baud Rate Register */
#define UARTX_CR1(base)                     ((base)->CR1)                      /* Address of Control Register 1 */
#define UARTX_CR2(base)                     ((base)->CR2)                      /* Address of Control Register 1 */
#define UARTX_CR3(base)                     ((base)->CR3)                      /* Address of Control Register 1 */
#define UARTX_RTOR(base)                    ((base)->RTOR)                     /* Address of RTOR               */
#define UARTX_RQR(base)                     ((base)->RQR)                      /* Address of RQR                */
#define UARTX_ICR(base)                     ((base)->ICR)                      /* Address of interrupt clear register. */
#define UARTX_TDR(base)                     ((base)->TDR)                      /* Address of transmit register.        */

#define  USART_CR2_STOP_ONE_BIT              (0x00000000u)                     /* 0x00000000 */
#define  USART_CR2_STOP_HALF_BIT             (0x00001000u)                     /* 0x00001000 */
#define  USART_CR2_STOP_TWO_BIT              (0x00002000u)                     /* 0x00002000 */
#define  USART_CR2_STOP_ONE_HALF_BIT         (0x00003000u)                     /* 0x00003000 */

/******************  Bit definition for USART_BRR register  *******************/
#define  USART_BRR_DIV_FRACTION              ((uint16_t)0x000F)                /*!< Fraction of USARTDIV */
#define  USART_BRR_DIV_MANTISSA              ((uint16_t)0xFFF0)                /*!< Mantissa of USARTDIV */

/*******************  Bit definition for USART_RQR register  ******************/
#define  USART_RQR_ABRRQ                     ((uint16_t)0x0001)                /*!< Auto-Baud Rate Request */
#define  USART_RQR_SBKRQ                     ((uint16_t)0x0002)                /*!< Send Break Request */
#define  USART_RQR_MMRQ                      ((uint16_t)0x0004)                /*!< Mute Mode Request */
#define  USART_RQR_RXFRQ                     ((uint16_t)0x0008)                /*!< Receive Data flush Request */
#define  USART_RQR_TXFRQ                     ((uint16_t)0x0010)                /*!< Transmit data flush Request */

/*******************  Bit definition for USART_ISR register  ******************/
#define  USART_SR_PE                         ((uint32_t)0x00000001)            /*!< Parity Error */
#define  USART_SR_FE                         ((uint32_t)0x00000002)            /*!< Framing Error */
#define  USART_SR_NE                         ((uint32_t)0x00000004)            /*!< Noise detected Flag */
#define  USART_SR_ORE                        ((uint32_t)0x00000008)            /*!< OverRun Error */
#define  USART_SR_IDLE                       ((uint32_t)0x00000010)            /*!< IDLE line detected */
#define  USART_SR_RXNE                       ((uint32_t)0x00000020)            /*!< Read Data Register Not Empty */
#define  USART_SR_TC                         ((uint32_t)0x00000040)            /*!< Transmission Complete */
#define  USART_SR_TXE                        ((uint32_t)0x00000080)            /*!< Transmit Data Register Empty */
#define  USART_SR_LBD                        ((uint32_t)0x00000100)            /*!< LIN Break Detection Flag */
#define  USART_SR_CTSIF                      ((uint32_t)0x00000200)            /*!< CTS interrupt flag */
#define  USART_SR_CTS                        ((uint32_t)0x00000400)            /*!< CTS flag */
#define  USART_SR_RTOF                       ((uint32_t)0x00000800)            /*!< Receiver Time Out */
#define  USART_SR_EOBF                       ((uint32_t)0x00001000)            /*!< End Of Block Flag */
#define  USART_SR_ABRE                       ((uint32_t)0x00004000)            /*!< Auto-Baud Rate Error */
#define  USART_SR_ABRF                       ((uint32_t)0x00008000)            /*!< Auto-Baud Rate Flag */
#define  USART_SR_BUSY                       ((uint32_t)0x00010000)            /*!< Busy Flag */
#define  USART_SR_CMF                        ((uint32_t)0x00020000)            /*!< Character Match Flag */
#define  USART_SR_SBKF                       ((uint32_t)0x00040000)            /*!< Send Break Flag */
#define  USART_SR_RWU                        ((uint32_t)0x00080000)            /*!< Receive Wake Up from mute mode Flag */
#define  USART_SR_WUF                        ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Flag */
#define  USART_SR_TEACK                      ((uint32_t)0x00200000)            /*!< Transmit Enable Acknowledge Flag */
#define  USART_SR_REACK                      ((uint32_t)0x00400000)            /*!< Receive Enable Acknowledge Flag */
#define  USART_SR_ERR_MASK                   ((uint32_t)0x0000000F)            /* All kinds of error */

/* Data structure definition */
/****************************************************
*   Structure£º  T_UART_MEM_MAP
*   Description£ºMemory map of uart registers.
*   Parameter:
    WORD32 CR1;           USART Control register 1,                 Address offset: 0x00 
    WORD32 CR2;           USART Control register 2,                 Address offset: 0x04 
    WORD32 CR3;           USART Control register 3,                 Address offset: 0x08
    WORD16 BRR;           USART Baud rate register,                 Address offset: 0x0C
    WORD16 RESERVED1;     Reserved, 0x0E
    WORD16 GTPR;          USART Guard time and prescaler register,  Address offset: 0x10
    WORD16 RESERVED2;     Reserved, 0x12
    WORD32 RTOR;          USART Receiver Time Out register,         Address offset: 0x14  
    WORD16 RQR;           USART Request register,                   Address offset: 0x18
    WORD16 RESERVED3;     Reserved, 0x1A
    WORD32 SR;            USART Interrupt and status register,      Address offset: 0x1C
    WORD32 ICR;           USART Interrupt flag Clear register,      Address offset: 0x20
    WORD16 DR;            USART Receive Data register,              Address offset: 0x24
    WORD16 RESERVED4;     Reserved, 0x26
    WORD16 TDR;           USART Transmit Data register,             Address offset: 0x28
    WORD16 RESERVED5;     Reserved, 0x2A
*   Authour£º    Danny
*   Modify record:
*   Date:  2020-5-14 creat.
****************************************************/
typedef struct
{
    WORD32 CR1;          /*!< USART Control register 1,                 Address offset: 0x00 */ 
    WORD32 CR2;          /*!< USART Control register 2,                 Address offset: 0x04 */ 
    WORD32 CR3;          /*!< USART Control register 3,                 Address offset: 0x08 */
    WORD16 BRR;          /*!< USART Baud rate register,                 Address offset: 0x0C */
    WORD16 RESERVED1;    /*!< Reserved, 0x0E                                                 */  
    WORD16 GTPR;         /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
    WORD16 RESERVED2;    /*!< Reserved, 0x12                                                 */
    WORD32 RTOR;         /*!< USART Receiver Time Out register,         Address offset: 0x14 */  
    WORD16 RQR;          /*!< USART Request register,                   Address offset: 0x18 */
    WORD16 RESERVED3;    /*!< Reserved, 0x1A                                                 */
    WORD32 SR;           /*!< USART Interrupt and status register,      Address offset: 0x1C */
    WORD32 ICR;          /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
    WORD16 DR;           /*!< USART Receive Data register,              Address offset: 0x24 */
    WORD16 RESERVED4;    /*!< Reserved, 0x26                                                 */
    WORD16 TDR;          /*!< USART Transmit Data register,             Address offset: 0x28 */
    WORD16 RESERVED5;    /*!< Reserved, 0x2A                                                 */
}volatile *T_UART_MEM_MAP;


/* Declaration of functions */
/**************************************************************************
* Funciton: void Uart_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register Uart
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void Uart_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara);


/**************************************************************************
* Funciton: void Uart1_isr(void)
* Descrip.: interrupt process function of uart1
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart1_isr(void);

/**************************************************************************
* Funciton: void Uart2_isr(void)
* Descrip.: interrupt process function of uart2
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart2_isr(void);

/**************************************************************************
* Funciton: void Uart3_isr(void)
* Descrip.: interrupt process function of uart3
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart3_isr(void);


/**************************************************************************
* Funciton: void Uart4_isr(void)
* Descrip.: interrupt process function of uart4
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart4_isr(void);




#ifdef __cplusplus
}
#endif

#endif /* _STM32G0XXX_UART_H_ */



