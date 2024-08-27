#ifndef VCNL_I2C
#define VCNL_I2C
#include "i2c.h"




#define ALS_CONF_CC 0x00
#define ALS_THDH 0x01

#define PS_MIN_HYST 680
#define PS_MAX_HYST 700
#define CMD_PS_THDL                                 0x06
#define CMD_PS_THDH                                 0x07
#define CMD_PS1_DATA                                0x08
#define CMD_ALS_DATA                                0x0B
#define CMD_WHITE_DATA                              0x0C
#define CMD_ALS_CONF1_2                             0x00
#define CMD_PS_CONF1_2                              0x03
#define CMD_PS_CONF3_MS                             0x04

#define CMD_INT_FLAG                                0x0D

#define PS_THDL_M                                   0x00  //0x03  // THDL = 800
#define PS_THDL_L                                   0x00  //0x20
#define PS_THDH_M                                   0xFF  //0x03  // THDH = 1000
#define PS_THDH_L                                   0XFF //0xE8
//#define ALS_CONF1                                   0x12  // 50 ms intergration time, ALS enabled, dynamic range x2
//#define ALS_CONF2                                   0x00  // sensitivity x2, White enabled
#define PS_CONF1                                    0xFE  //0x3E  // PS enabled, PS interrupt persistence 4, 8T integration time
#define PS_CONF2                                    0x48  //0x10  // PS 16-bit output, PS interrupt dis-enabled, 
#define PS_CONF3                                    0x93  //0x0D  // PS 
#define PS_MS                                       0x07  // 200 mA LED_I current


int vcnl_i2c_write(uint8_t command_code, uint8_t lower_byte, uint8_t upper_byte);
int vcnl_i2c_read(uint8_t cc, uint8_t *data);
int vcnl_i2c_get_id();
int vcnl_i2c_get_ps_data();
int vcnl_i2c_get_als_conf1();
int vcnl_i2c_sensor_setup();



#endif