/******************************************************************************
* 版权所有 (C)2013，Nanjing shufan Information technology Co.,Ltd.
*
* 文件名称：Knx_AppData.h
* 文件标识：无
* 内容摘要：本文件由用户来定义KNX协议栈中用户定义的数据。
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



#ifndef _APPLICATION_DATA_H_
#define _APPLICATION_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_ONOFF     0

/* modified by manufactor. */
#define KNX_APP_KEY0                      'S'                /* application recognizing key0. */
#define KNX_APP_KEY1                      'T'                /* application recognizing key1. */
#define APP_ID                            0xCC10             /* application ID. */
#define VALUE_FACTORY_ID                    0x01BF             /*  For ST(01bf)..   */

/* The real flash address used for saving data of knx protocol. it will be referenced in protocol code. */
#define KNX_API_S19_PARA_START            0x0800FFC0

/****** Do not change the next define. *******/
#define VALUE_FIRMWARE_VER                0x01
#define VALUE_MANUFACTURER_APP_VER        {GET_HIBYTE(VALUE_FACTORY_ID),GET_LOWBYTE(VALUE_FACTORY_ID),GET_HIBYTE(APP_ID),GET_LOWBYTE(APP_ID),VALUE_FIRMWARE_VER} /* B0-1:Manufactory Id,B2-3:application ID,B4:application version. */
#define VALUE_HAEDWARE_TYPE               {0x00,GET_HIBYTE(VALUE_FACTORY_ID),GET_LOWBYTE(VALUE_FACTORY_ID),0x00,GET_HIBYTE(APP_ID),GET_LOWBYTE(APP_ID)} /* manufactory define,B0-1:manufcatory ID,B2-5:Manu. defined. */
#define VALUE_PEI_APP_VER                 {0x00,0x00,0x00,0x00,0x00} /* No PEI program.this value descripts PEI program version. */
#define VALUE_SERIAL_NUMBER               {GET_HIBYTE(VALUE_FACTORY_ID),GET_LOWBYTE(VALUE_FACTORY_ID),2,0,1,5}
#define VALUE_ORDER_INFO                  {'D','e','m','o','D','e','v','i','c','e'}
#define VALUE_FACTOR_DATA                 {0xFF,0xFF,0xFF,0xFF}
#define VALUE_ROUTE_CUNT                  NL_ROUTING_COUNT
#define VALUE_MAX_APDU                    54                 /* this length shold be calculated by the supporting 
                                                                length of knx-chip(sub the length of knx frame header. */
#define VALUE_MAX_FRAME_LEN               63                 /* = (VALUE_MAX_APDU + POS_TPDU_APCI)Max. Frame length. */
#define VALUE_PEI_TYPE                    PEI_TYPE_0         /* defined in KNX definition files. */
#define APP_STACK_API_VERSION             1                  /* application api version.  */

/********************************************************
 Address table define and the associtation table define.
 The user should define the actual value according to the 
 actual application. 
*********************************************************/
#define MAX_ADDR_COUNT                    254        /* the max. group address count. < 255 */
#define MAX_ASSOC_COUNT                   254        /* the max. association count.  < 255  */
#define COMM_OBJECT_COUNT                 1         /* communication object count. < 255   */
#define COMM_OBJECT_MAX_COUNT             255        /* max. communication object count.    */
#define USER_OBJECT_COUNT                 1          /* EIB user's object count.            */
#define PROP_COUNT_OF_INTOB15             2          /* the number of properties of the object15. */

/* define Address table/association table/communication object talbe reference. */
#define APP_ADDR_TABLE_REF                VIR_ADDR_TABLE
#define APP_ASSOC_TABLE_REF               VIR_ASSOC_TABLE

/* system table size define. */
#define ADDR_TABLE_SIZE                   (1+(2*MAX_ADDR_COUNT))      /* address table length in bytes.     */
#define ASSOC_TABLE_SIZE                  (1+(2*MAX_ASSOC_COUNT))     /* association table length in bytes. */
#define COM_OBJ_TABLE_SIZE                (3+(COMM_OBJECT_COUNT*4))   /* communication object table length in bytes. */
#define USER_INTOBJ_TABLE_SIZE            (2*USER_OBJECT_COUNT)       /* user defining interface object table length. */
#define USER_INTOBJ15_DESC_SIZE           (1+PROP_COUNT_OF_INTOB15 * sizeof(T_KNXPROP_DESC)) /* user interface object15's description size. */
#define USER_INTOBJ15_VAL0_SIZE           (2)                         /* size of inter. obj. 15's value0. */

/******************* Application parameter size define,User define the next data ****************************/
/* input channel switch function parameter offset. */
#define IN1_SWFUNC_TYPE_OFFSET         0
#define IN2_SWFUNC_TYPE_OFFSET         1
#define IN3_SWFUNC_TYPE_OFFSET         2
#define IN4_SWFUNC_TYPE_OFFSET         3
/* input channel force function parameter offset.  */
#define IN1_FORCEFUNC_CTRL_OFFSET      4
#define IN2_FORCEFUNC_CTRL_OFFSET      5
#define IN3_FORCEFUNC_CTRL_OFFSET      6
#define IN4_FORCEFUNC_CTRL_OFFSET      7
/* input channel scene function parameter offset.  */
#define IN1_SCENEFUNC_CTRL_OFFSET      8
#define IN2_SCENEFUNC_CTRL_OFFSET      9
#define IN3_SCENEFUNC_CTRL_OFFSET      10
#define IN4_SCENEFUNC_CTRL_OFFSET      11
/* output channel function parameter offset. */
#define OUT1_FUNC_OFFSET               12
#define OUT2_FUNC_OFFSET               13
#define OUT3_FUNC_OFFSET               14
#define OUT4_FUNC_OFFSET               15
#define PARA_END_OFFSET                16  /* 1 is the length of the last parameter(1byte) */
/**** Don't change the name of the next macro define, just modify the value of it. */
#define APP_PARA_END_OFFSET               PARA_END_OFFSET
/********************************** parameter size define end *********************/

/*************************** application relative parameter area ***********************/ 
#define APP_MEM1_REF                      VIR_COMMOB_TABLE    /* Application memory1 start reference. */
#define APP_COM_OBJ_TABLE_REF             VIR_COMMOB_TABLE    /* communication object table start address. */

#define APP_PARA_AREA_REF                 (APP_COM_OBJ_TABLE_REF + COM_OBJ_TABLE_SIZE) /* application parameter start address. */
/* switch type parameter virtual address define. */
#define IN1_SWFUNC_TYPE_REF               (APP_PARA_AREA_REF + IN1_SWFUNC_TYPE_OFFSET)     /*  */
#define IN2_SWFUNC_TYPE_REF               (APP_PARA_AREA_REF + IN2_SWFUNC_TYPE_OFFSET)     /*  */
#define IN3_SWFUNC_TYPE_REF               (APP_PARA_AREA_REF + IN3_SWFUNC_TYPE_OFFSET)     /*  */
#define IN4_SWFUNC_TYPE_REF               (APP_PARA_AREA_REF + IN4_SWFUNC_TYPE_OFFSET)     /*  */
/* force control parameter virtual address define. */
#define IN1_FORCEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN1_FORCEFUNC_CTRL_OFFSET)  /*  */
#define IN2_FORCEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN2_FORCEFUNC_CTRL_OFFSET)  /*  */
#define IN3_FORCEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN3_FORCEFUNC_CTRL_OFFSET)  /*  */
#define IN4_FORCEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN4_FORCEFUNC_CTRL_OFFSET)  /*  */
/* scene control parameter virtual address define. */
#define IN1_SCENEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN1_SCENEFUNC_CTRL_OFFSET)  /*  */
#define IN2_SCENEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN2_SCENEFUNC_CTRL_OFFSET)  /*  */
#define IN3_SCENEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN3_SCENEFUNC_CTRL_OFFSET)  /*  */
#define IN4_SCENEFUNC_CTRL_REF            (APP_PARA_AREA_REF + IN4_SCENEFUNC_CTRL_OFFSET)  /*  */
/* output type parameter virtual address define. */
#define OUT1_FUNC_REF                     (APP_PARA_AREA_REF + OUT1_FUNC_OFFSET)  /*  */
#define OUT2_FUNC_REF                     (APP_PARA_AREA_REF + OUT2_FUNC_OFFSET)  /*  */
#define OUT3_FUNC_REF                     (APP_PARA_AREA_REF + OUT3_FUNC_OFFSET)  /*  */
#define OUT4_FUNC_REF                     (APP_PARA_AREA_REF + OUT4_FUNC_OFFSET)  /*  */

/***************************** application relative parameter area end ********************/

/* define user defining interface object address.If user want to add interface object,should add it here. */
#define USER_INTOBJ_TABLE_REF             (APP_PARA_AREA_REF + APP_PARA_END_OFFSET)            /* user defining interface object address table start address.  */
#define USER_INTOBJ15_DESC_RAW_REF        (USER_INTOBJ_TABLE_REF + USER_INTOBJ_TABLE_SIZE) 
#define USER_INTOBJ15_DESC_REF            (((USER_INTOBJ15_DESC_RAW_REF + MCU_SIZE - 1)>>(MCU_SIZE>>1))<<(MCU_SIZE>>1))            /* user defining interface object15's description address. 0x480c */
#define USER_INTOBJ15_VALUE0_REF          (USER_INTOBJ15_DESC_REF+ USER_INTOBJ15_DESC_SIZE)    /* user defining interface object15's first Prop. value address. */
/* user interface object area end. Don't change the macro name of it. */
#define USER_INTOBJ_DEFINE_END            (USER_INTOBJ15_VALUE0_REF + USER_INTOBJ15_VAL0_SIZE)

/* application program head description area. */
#define APP_HEADER_RAW_REF                 (USER_INTOBJ_DEFINE_END)   /* application description head raw address(not aligned).  */
#define APP_HEADER_MAIN_REF                (((APP_HEADER_RAW_REF + MCU_SIZE - 1)>>(MCU_SIZE>>1))<<(MCU_SIZE>>1)) /* application header begin address(aligned). */
#define APP_HEADER_KEY_REF                 (APP_HEADER_MAIN_REF)                         /*  */
#define APP_HEADER_STACK_TYPE_REF          (APP_HEADER_MAIN_REF + POS_APP_STACK_TYPE)    /*  */
#define APP_HEADER_COTABLE_REF             (APP_HEADER_MAIN_REF + POS_APP_CO_TAB_REF)    /*  */
#define APP_HEADER_STACK_VER_REF           (APP_HEADER_MAIN_REF + POS_APP_STACK_VERSION) /*  */
#define APP_MEM1_END_REF                   (APP_HEADER_MAIN_REF + APP_MAIN_SIZE - 1)     /* application memory end address.  */
#define APP_MEM1_SIZE                      (APP_MEM1_END_REF - APP_MEM1_REF +1)          /* total application memory size. */

/* Communication object RAM define.this define follows the communication define. */
/* Virtual RAM for application.It is ajustable according to the application. */
#define APP_RAM_BEGIN                     BEG_USER_RAM  /* virtual RAM,managed by MCB.   */
#define APP_RAM_SIZE                      256           /* RAM size used for application */

/* define memory for communcation object value. */
#define VALUE_REF_CO0                     (APP_RAM_BEGIN+0)                  /* Data pointer for CO #0 offset 1byte */
#define RAM_FLAGS_REF                     (APP_RAM_BEGIN+1)                 /* Start of co ram flags  */

/* CRC check of application memory is mandory. */
#define APP_MEM1_CRC                      (TRUE)

/* Application memory 2 area define.User adjust it's define accord to the application. */
#define APP_MEM2_REF                      (((APP_MEM1_END_REF + 1 + MCU_SIZE - 1)>>(MCU_SIZE>>1))<<(MCU_SIZE>>1))     /* application memory2 start. */
#define APP_MEM2_SIZE                     64                                 /* application memory2 size = total size of scence parameter area. */
#define APP_MEM2_ACC                      ACC_PAR                            /* application memory2 access level. */
#define APP_MEM2_CRC                      (FALSE)                            /* application memory2 CRC disable.  */

/* parameter of application memory2. */
#define CH_MEM_SCENE_SIZE                 16
#define CH1_MEM_SCENES                    (APP_MEM2_REF)
#define CH1_MEM_SCEMES_SIZE               16
#define CH2_MEM_SCENES                    (CH1_MEM_SCENES + CH_MEM_SCENE_SIZE)/*  */
#define CH2_MEM_SCENES_SIZE               16
#define CH3_MEM_SCENES                    (CH2_MEM_SCENES + CH_MEM_SCENE_SIZE)
#define CH3_MEM_SCENES_SIZE               16
#define CH4_MEM_SCENES                    (CH3_MEM_SCENES + CH_MEM_SCENE_SIZE)
#define CH4_MEM_SCENES_SIZE               16
/* define the end of memory2. */
#define APP_MEM_WRITE_BLOCKED             (APP_MEM2_REF + APP_MEM2_SIZE - 1)
#define APP_MEM_END                       APP_MEM_WRITE_BLOCKED




/****************************************************
*   结构名：T_0705_USER_OBJ15
*   描述：  Mask 0705's user interface object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  caoxw  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[PROP_COUNT_OF_INTOB15];
}T_0705_USER_OBJ15;

/**********************************************************************************************
*   结构名：T_COMOBJ_DESC
*   描述：  Mask 0705's communication object description. 
*   参数：  
            BYTE aucValRamRef[2] : Com. Obj. value's RAM reference. [0]:high byte,[1]:low byte.
            BYTE ucComObjCfg     : Com. Obj.'s configure byte.
            BYTE ucComObjType    : Com. Obj.'s data type.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
***********************************************************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucValRamRef[2];    /* Com. Obj. value's RAM reference. [0]:high byte,[1]:low byte.*/
    BYTE ucComObjCfg;        /* Com. Obj.'s configure byte.                                 */
    BYTE ucComObjType;       /* Com. Obj.'s data type.                                      */
}T_COMOBJ_DESC;
#pragma pack()

/****************************************************************************************
*   结构名：T_COMOBJ_TABLE
*   描述：  Mask 0705's communication object table. 
*   参数：  
            BYTE ucComObjCunt          : communication object count.
            BYTE aucRamFlagRef[2]      : flag RAM's reference.[0]:high byte,[1]:low byte.
            T_COMOBJ_DESC tComObjDesc[255]: communication object description array.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
*****************************************************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucComObjCunt;                            /* communication object count.                      */
    BYTE aucRamFlagRef[2];                        /* flag RAM's reference.[0]:high byte,[1]:low byte. */
    T_COMOBJ_DESC tComObjDesc[COMM_OBJECT_COUNT]; /* communication object description array.          */
}T_COMOBJ_TABLE;
#pragma pack()

#if(DEBUG_ONOFF)
VOID Application_Para_Debug(VOID);
#endif




#ifdef __cplusplus
}
#endif

#endif /* _APPLICATION_DATA_H_ */



/* End of file. */


