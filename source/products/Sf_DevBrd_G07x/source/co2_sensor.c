#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "sw_common.h"
#include "boardctrl.h"
#include "SerialProc.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "co2_sensor.h"
#include "main.h" 

co2_sensor_knx_bus_t co2_sensor_knx_bus;

static uint16_t crc_table[256] =
{
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
};


// Compute CRC-16/MODBUS
uint16_t compute_crc( uint8_t *data, size_t length )
{
    uint16_t crc = CRC_INIT;
    while ( length-- )
    {
        uint8_t tableIndex = ( crc ^ *data++ ) & 0xFF;
        crc = crc_table[tableIndex] ^ ( crc >> 8 );
    }
    return crc; // In some cases, you might want to swap the bytes of the result.
}

static BYTE temp_init[][7] =
{
    {0xFE, 0x2B, 0x0E, 0x04, 0x00, 0x67, 0x33},
    {0xFE, 0x2B, 0x0E, 0x04, 0x01, 0xA6, 0xF3},
    {0xFE, 0x44, 0x00, 0x28, 0x08, 0x06, 0xE2},
    {0xFE, 0x44, 0x00, 0x06, 0x04, 0x1B, 0x47},
    {0xFE, 0x44, 0x00, 0x0E, 0x02, 0x9C, 0x85},
    {0xFE, 0x44, 0x00, 0x10, 0x02, 0x95, 0x25},
    {0xFE, 0x44, 0x00, 0x14, 0x01, 0xD7, 0xE4},
    {0xFE, 0x44, 0x00, 0x1C, 0x04, 0x10, 0x27},
    {0xFE, 0x44, 0x00, 0x20, 0x01, 0xC1, 0x24},
    {0xFE, 0x44, 0x00, 0x23, 0x01, 0xC1, 0xD4},
    {0xFE, 0x44, 0x00, 0x28, 0x08, 0x06, 0xE2},
    {0xFE, 0x44, 0x00, 0x30, 0x10, 0x0C, 0xE8},
    {0xFE, 0x44, 0x00, 0x40, 0x10, 0x29, 0x28},
    {0xFE, 0x44, 0x00, 0x50, 0x10, 0x24, 0xE8},
    {0xFE, 0x44, 0x00, 0x60, 0x01, 0xF0, 0xE4},
    {0xFE, 0x44, 0x00, 0x62, 0x03, 0x70, 0x45},
    {0xFE, 0x44, 0x00, 0x69, 0x02, 0xB6, 0xB5},
    {0xFE, 0x44, 0x00, 0x70, 0x02, 0xBD, 0x25},
    {0xFE, 0x44, 0x00, 0x74, 0x02, 0xBF, 0xE5},
    {0xFE, 0x44, 0x00, 0x78, 0x05, 0xFB, 0x27},
    {0xFE, 0x44, 0x00, 0x80, 0x0E, 0xF9, 0x20},
    {0xFE, 0x44, 0x00, 0x92, 0x0A, 0xF4, 0x43}
};

BOOL co2_sensor_init()
{
    static uint8_t dat_init_pos = 0;
    USART_SendStringData( temp_init[dat_init_pos++], 7 );

    if ( dat_init_pos == 22 )
        return TRUE;
    else
        return FALSE;
}


#define TEMP_LEN 1
#define CMD_LEN 8
uint8_t dat_rcv_pos = 0;
static BYTE temp_send[][CMD_LEN] =
{
//    {0xFE, 0x44, 0x00, 0x1F, 0x01, 0xD0, 0xD4},
//    {0xFE, 0x44, 0x00, 0x06, 0x04, 0x1B, 0x47},
//    {0xFE, 0x44, 0x00, 0x0E, 0x02, 0x9C, 0x85},
//    {0xFE, 0x44, 0x00, 0x10, 0x02, 0x95, 0x25},
//    {0xFE, 0x44, 0x00, 0x14, 0x01, 0xD7, 0xE4},
//    {0xFE, 0x44, 0x00, 0x1C, 0x03, 0x51, 0xE5},
//    {0xFE, 0x44, 0x00, 0x28, 0x04, 0x06, 0xE7},
//    {0xFE, 0x44, 0x00, 0x60, 0x01, 0xF0, 0xE4},
//    {0xFE, 0x44, 0x00, 0x69, 0x02, 0xB6, 0xB5},
//    {0xFE, 0x44, 0x00, 0x74, 0x02, 0xBF, 0xE5}
    {0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5}
//    {0xFE, 0x04, 0x00, 0x04, 0x00, 0x01, 0xD5, 0xC5}
};
static BYTE temp_rcv[TEMP_LEN][9] = {0};
static void co2_value_request()
{
    USART_SendStringData(temp_send[0], CMD_LEN);
}

static void TaskRun()
{
    co2_value_request();
}

BYTE seneair_rcv_done = 0;
static uint8_t seneairBuff[COMMAND_LEN] = {0};
void seneair_decoder( uint8_t nByte )
{
    static uint8_t pos = 0;
    static uint8_t data_len = 0;
    if ( pos == 0 )
    {
        if ( nByte == 0xfe )
        {
            seneairBuff[pos++] = nByte;
        }
    }
    else if ( pos == 1 )
    {
        if ( nByte == 0x44 || nByte == 0x04 )
        {
            seneairBuff[pos++] = nByte;
        }
        else
        {
            pos = 0;
        }
    }
    else if ( pos == 2 )
    {
        seneairBuff[pos++] = nByte;
        data_len = nByte + 5;
    }
    else
    {
        seneairBuff[pos] = nByte;
        if ( pos < data_len - 1 )
        {
            pos ++;
        }
        else
        {
            pos = 0;
            seneair_rcv_done = 1;
            memcpy( temp_rcv[dat_rcv_pos], seneairBuff, 9 );
            if ( dat_rcv_pos < TEMP_LEN - 1 )
            {
                dat_rcv_pos++;
            }
            else
            {
                dat_rcv_pos = 0;
            }
        }
    }
}


/**
 * @description: EventProcess
 * @param {type}
 * @return: none
 */
static void EventProcess()
{
    if ( seneair_rcv_done )
    {
        WORD16 crc = compute_crc( temp_rcv[0], 3 + * ( temp_rcv[0] + 2 ) );
        if ( ( crc & 0xff ) == *( temp_rcv[0] + * ( temp_rcv[0] + 2 ) + 3 ) && ( crc >> 8 & 0xff ) == *( temp_rcv[0] + * ( temp_rcv[0] + 2 ) + 4 ) )
        {
            co2_sensor_knx_bus.co2_value = (((WORD16)*(temp_rcv[0]+3) << 8) & 0xff00) | ((WORD16)*(temp_rcv[0]+4) & 0xff);
            co2_sensor_knx_bus.co2_valueflag = 1;
        }
        seneair_rcv_done = 0;
        memset( temp_rcv[0], 0, sizeof( temp_rcv[0] ) );
    }
}

/**
 * @description: Main loop of the HMI system and logic control, this function
    should be called per ms.
 * @param {type} receive byte
 * @return: none
 */
void co2_sensor_Loop()
{
    static WORD32 TimesMsRef;

    static BYTE InitFlag = FALSE;
    
    if ( !InitFlag )
    {
        if ( API_KnxTm_GetDelayMs( TimesMsRef ) >= INIT_PERIOD )
        {
            TimesMsRef = API_KnxTm_GetTimeMs();
            InitFlag = co2_sensor_init();
        }
    }
    else
    {
        if ( API_KnxTm_GetDelayMs( TimesMsRef ) >= LOOP_PERIOD )
        {
            TimesMsRef = API_KnxTm_GetTimeMs();

            TaskRun();
            EventProcess();
        }
    }    
}
