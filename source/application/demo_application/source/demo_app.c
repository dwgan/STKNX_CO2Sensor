/******************************************************************************
* ��Ȩ���� (C)2013��**************��˾
*
* �ļ����ƣ�demo_app.c
* �ļ���ʶ����
* ����ժҪ��demo application for education.
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

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "app_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "Rec_Table.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "Application.h"
#include "Knx_AlApp.h"
#include "demo_app.h"
#include "App_Api.h"
#include "boardctrl.h"
#include "co2_sensor.h"


BYTE CO2value[2],ucPara,CO2updateflag;

 

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void)
{
       
   ; 

}

/**************************************************************************
* �������ƣ� VOID Demo_App_Forced_Run(BYTE ucInputNo)
* ���������� handle the force function happening on the input channel.
* ��������� BYTE ucInputNo : the NO. of the input channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Forced_Run(BYTE ucInputNo)
{
   ;
}

/**************************************************************************
* �������ƣ� VOID Demo_App_Scene_Run(BYTE ucInputNo)
* ���������� handle the scene function happening on the input channel.
* ��������� BYTE ucInputNo : the NO. of the input channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Scene_Run(BYTE ucInputNo)
{
   ;
}

/**************************************************************************
* �������ƣ� VOID Demo_App_Switch_Run(BYTE ucInputNo)
* ���������� handle key input function.
* ��������� BYTE ucInputNo : the NO. of the input channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Switch_Run(BYTE ucInputNo)
{
   ;
}

/**************************************************************************
* �������ƣ� void Demo_App_Out_Run(BYTE ucOutputNo)
* ���������� handle output function.
* ��������� BYTE ucOutputNo : the NO. of the output channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Out_Run(BYTE ucOutputNo)
{
   ;
}

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
uint16_t int32_to_custom_float16(int32_t int32) ;
void Demo_App_Run(void)
{

    BYTE sensorvalue[4];
        
    if(co2_sensor_knx_bus.co2_valueflag== 1)
    {
        *(WORD32*)sensorvalue=(WORD32)co2_sensor_knx_bus.co2_value*100;
        DataConvert_Int32ToFloat(sensorvalue);
        API_KnxAl_SetCoValue(CO2_VALUE_CO,&sensorvalue[0]);
              /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite(CO2_VALUE_CO); 

        co2_sensor_knx_bus.co2_valueflag= 0;
    }
    co2_sensor_Loop();
}


/******************************************************************
The following function was used to convert 2 bytes float data to short
 currently only processed postive date

*******************************************************************/
void DataConvert_FloatToInt(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;

    indexnumer = ((pData[0] & 0x78)>>3);
    converrvalue = ((pData[0] & 0x07)<<8) + pData[1] ;

    for(;indexnumer>=1;indexnumer--)
    {
        converrvalue = converrvalue * 2;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)((converrvalue >>8) & 0xff);
}


/******************************************************************
The following function was used to convert short to 2 bytes float data 
 currently only processed postive date

*******************************************************************/
void DataConvert_IntToFloat(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;

    converrvalue = (pData[0] <<8) + pData[1] ;
    indexnumer = 0;


    for(;converrvalue> 0x7ff;)
    {
        converrvalue = converrvalue /2;
        indexnumer++;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)(((converrvalue >>8) & 0xff)|(indexnumer << 3));
}

void DataConvert_Int32ToFloat( BYTE *pData )
{
    WORD32 converrvalue;
    BYTE indexnumer;

    converrvalue = ( pData[3] << 24 ) + ( pData[2] << 16 ) + ( pData[1] << 8 ) + pData[0];
    indexnumer = 0;


    for( ; converrvalue > 0x7ff; )
    {
        converrvalue = converrvalue / 2;
        indexnumer++;
    }
    pData[1] = ( BYTE )( converrvalue & 0xff );
    pData[0] = ( BYTE )( ( ( converrvalue >> 8 ) & 0xff ) | ( indexnumer << 3 ) );
}

/**
 * @description: swap big-endian or little-endian to another type
 * @param {none} 
 * @return: none
 * @date 2023/9/2
 * example: swapEndian(&value16, sizeof(value16));
 */
void swapEndian(void* data, size_t size)
{
    uint8_t* byteData = (uint8_t*)data;
    uint8_t temp;
    
    for (size_t i = 0; i < size / 2; ++i)
    {
        temp = byteData[i];
        byteData[i] = byteData[size - 1 - i];
        byteData[size - 1 - i] = temp;
    }
}

uint16_t int32_to_custom_float16(int32_t int32) {
    uint16_t f16 = 0;
    uint32_t absVal, tempVal;
    int32_t exp = 0;
    uint32_t sign = 0;

    // ������λ����ȡ����ֵ
    if (int32 < 0) {
        sign = 1;
        absVal = -int32; // ����Ǹ�����ȡ����1�õ�����ֵ
    } else {
        absVal = int32;
    }

    // ������������������0��ֱ�ӷ���0
    if (absVal == 0) return 0;

    // ����ָ����β��
    tempVal = absVal;
    while (tempVal > 0) {
        tempVal >>= 1;
        exp++;
    }

    // ����β������Ӧ11λ�ռ�
    // exp-1��Ϊָ���Ǵ����λ1��ʼ����ģ��������absVal��1����2^0����expӦ����0
    int shiftAmount = exp - 12;
    uint32_t mantissa = (shiftAmount > 0) ? (absVal >> shiftAmount) : (absVal << -shiftAmount);

    // ��ϳ�16λ������
    // ����ָ����Χ������Ӧ4λָ��λ
    if (exp > 15) {
        exp = 15;
    } else if (exp < 1) {
        exp = 1; // ����ֵ����Сָ��
    }

    f16 = (sign << 15) | ((exp & 0xF) << 11) | (mantissa & 0x7FF);

    return f16;
}


u32_t GetSystemTime_ms(void)
{

    return(API_KnxTm_GetTimeMs());
}


/* end of file. */

