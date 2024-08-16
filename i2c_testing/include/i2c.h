#ifndef RX_I2C_H
#define RX_I2C_H

#include "stdio.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>



#define I2C_SDA_GPIO 32
#define I2C_SCL_GPIO 33
#define I2C_PORT -1 // I think this is fine to do

#define I2C_SENSOR_0_ADDR 0x60


int init_i2c();

// Do we ever need to write?
int i2c_write(uint8_t *data, uint8_t length);
int i2c_write_rec(uint8_t *d, uint8_t l, uint8_t *d2, uint8_t l2);
// would we ever read without write
// to make sure the register is correct?
int i2c_read(uint8_t *data, uint8_t length);
int i2c_config();



void test_i2c();
void init_test_i2c();

#endif



