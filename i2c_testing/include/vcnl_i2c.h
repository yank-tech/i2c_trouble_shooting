#ifndef VCNL_I2C
#define VCNL_I2C
#include "i2c.h"




#define ALS_CONF_CC 0x00
#define ALS_THDH 0x01


int vcnl_i2c_write(uint8_t command_code, uint8_t lower_byte, uint8_t upper_byte);
int vcnl_i2c_read(uint8_t cc, uint8_t *data);
int vcnl_i2c_get_id();





#endif