/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Main.c
* 文件标识：无
* 内容摘要：KNX应用源主函数文件，应用入口。
* 其他说明：
* 当前版本：V1.00
* 作    者：      
* 完成日期：2013年7月24日
*    
* 修改记录1：
*        修改日期：2013年7月24日
*        版 本 号：V1.00
*        修 改 人：      
*        修改内容：新增公共定义.
******************************************************************************/



#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Hardware.h"
#include "boardctrl.h"
#include "Knx_Run.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "stm32g0xx_iwdg.h"

#include "stm32g0xx_ll_usart.h" 
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx.h"
#include "main.h"
#include "SerialProc.h"
#include "co2_sensor.h"

__IO uint8_t ubSend = 0;
uint8_t aStringToSend[] = "STM32G0xx USART LL API Example : TX in IT mode\r\nConfiguration UART 115200 bps, 8 data bit/1 stop bit/No parity/No HW flow control\r\n";
uint8_t ubSizeToSend = sizeof(aStringToSend);


/* Private function prototypes -----------------------------------------------*/
static void MX_USART2_UART_Init(void);

/**************************************************************************************************************
* 函数名称：void main(void)
* 功能描述：device software start entry.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
void main(void)
{
    system_base_clk();
    /* initializing productor board control . */
    BoardCtrl_Init();
    /* set the device working handler and parameters. */
    BoardCtrl_Set();
    
    /* Initialize all configured peripherals */
    MX_USART2_UART_Init();
    
  /* Polling USART initialisation */
    while ((!(LL_USART_IsActiveFlag_TEACK(USART2))) || (!(LL_USART_IsActiveFlag_REACK(USART2))))
    {
     }    
    /* Enable RXNE and Error interrupts */
    LL_USART_EnableIT_RXNE(USART2);
    LL_USART_EnableIT_ERROR(USART2);
    
      /* Start transfer only if not already ongoing */
//    if (ubSend == 0)
//    {
//    /* Start USART transmission : Will initiate TXE interrupt after TDR register is empty */
//        LL_USART_TransmitData8(USART2, aStringToSend[ubSend++]);
//
//    /* Enable TXE interrupt */
//       LL_USART_EnableIT_TXE(USART2);
//     }
    

    while(1)
    {
        /* renew the cycle time. */
        API_KnxTm_UpdateCycle();
        /* get the programming key state and store it. */
        API_Knx_GetProgKey();
        /* set the programming LED. */
        API_Knx_SetPrgLed();
        /* process messages. */
        if(API_Knx_GetRunStateEx() < RUNSTATE_FLAG_SAVE_SUPPLY)
        {
            /* knx messages handling. */
            API_Knx_MsgProcess();
        }
        /* Run status management. */
        API_Knx_RunProcess();
        /* wdg. */
        Stm32G0xx_Iwdg_Reset();
    }
}          


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_SYSCLK);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_IRQn, 0);
  NVIC_EnableIRQ(USART2_IRQn);

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV2;
  USART_InitStruct.BaudRate = 9600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART2, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART2, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART2);
  LL_USART_DisableDMADeactOnRxErr(USART2);
  LL_USART_ConfigAsyncMode(USART2);

  /* USER CODE BEGIN WKUPType USART2 */

  /* USER CODE END WKUPType USART2 */

  LL_USART_Enable(USART2);

  /* Polling USART2 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART2))) || (!(LL_USART_IsActiveFlag_REACK(USART2))))
  {
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}


/**
  * @brief  Function called for achieving next TX Byte sending
  * @param  None
  * @retval None
  */
void USART_TXEmpty_Callback(void)
{
  if (ubSend == (ubSizeToSend - 1))
  {
    /* Disable TXE interrupt */
    LL_USART_DisableIT_TXE(USART2);

    /* Enable TC interrupt */
    LL_USART_EnableIT_TC(USART2);
  }

  /* Fill TDR with a new char */
  LL_USART_TransmitData8(USART2, aStringToSend[ubSend++]);
}

void USART_SendStringData(unsigned char * datasource, unsigned char sendsize)
{
    unsigned char i;
    for(i =0 ;i < sendsize; i++)
    {
	    aStringToSend[i] = (datasource[i]);
    }
	ubSizeToSend = sendsize;
    ubSend = 0;
 
	/* Start USART transmission : Will initiate TXE interrupt after TDR register is empty */
    LL_USART_TransmitData8(USART2, aStringToSend[ubSend++]);

    /* Enable TXE interrupt */
     LL_USART_EnableIT_TXE(USART2);

}



/**
  * @brief  Function called at completion of last byte transmission
  * @param  None
  * @retval None
  */
void USART_CharTransmitComplete_Callback(void)
{
  if (ubSend == sizeof(aStringToSend))
  {
    ubSend = 0;

    /* Disable TC interrupt */
    LL_USART_DisableIT_TC(USART2);

    /* Turn LED4 On at end of transfer : Tx sequence completed successfully */
  //  LED_On();
  }
}

/**
  * @brief  Function called from USART IRQ Handler when RXNE flag is set
  *         Function is in charge of reading character received on USART RX line.
  * @param  None
  * @retval None
  */
void USART_CharReception_Callback(void)
{
  uint8_t received_char;

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  received_char = LL_USART_ReceiveData8(USART2);

  seneair_decoder(received_char);
//  UART_ReceiveData_ApplicationProcess(received_char);

  /* Echo received character on TX */
  LL_USART_TransmitData8(USART2, received_char);

}

/**
  * @brief  Function called in case of error detected in USART IT Handler
  * @param  None
  * @retval None
  */
void Error_Callback(void)
{
  __IO uint32_t isr_reg;

  /* Disable USARTx_IRQn */
  NVIC_DisableIRQ(USART2_IRQn);

  /* Error handling example :
    - Read USART ISR register to identify flag that leads to IT raising
    - Perform corresponding error handling treatment according to flag
  */
  isr_reg = LL_USART_ReadReg(USART2, ISR);
  if (isr_reg & LL_USART_ISR_NE)
  {
    /* case Noise Error flag is raised : ... */
   ;// LED_Blinking(LED_BLINK_FAST);
  }
  else
  {
    /* Unexpected IT source : Set LED to Blinking mode to indicate error occurs */
  ;//  LED_Blinking(LED_BLINK_ERROR);
  }
}


// End of Main.c

