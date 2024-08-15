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

#define I2C_SENSOR_0_ADDR 0x40
#define I2C_SENSOR_1_ADDR 0x41
#define I2C_SENSOR_2_ADDR 0x42
#define I2C_SENSOR_3_ADDR 0x43
#define I2C_SENSOR_5_ADDR 0x45



#define I2C_REG_CONFIG 0x00
#define I2C_REG_SHUNT_V 0x01
#define I2C_REG_BUS_V 0x02
#define I2C_REG_POWER 0x03
#define I2C_REG_CURRENT 0x04
#define I2C_REG_CALIBRATION 0x05
#define I2C_REG_MASK 0x06
#define I2C_REG_ALERT 0x07
#define I2C_REG_MANUFACTURE_ID 0xFE
#define I2C_REG_DIE_ID 0xFF

// need to confirm this
#define I2C_CAL_VAL 1

// then the config val

#define I2C_SENSOR_0_CONFIG 1319



typedef enum {SENSOR_0, SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_5} i2c_sensor;
typedef enum {BUS_V, SHUNT_V, CURRENT_mA, POWER_mW} i2c_req;


int init_i2c();

// Do we ever need to write?
int i2c_write();
// would we ever read without write
// to make sure the register is correct?
int i2c_read();
int i2c_config();


int i2c_get_value(i2c_sensor sensor, i2c_req req, double *ret);

void test_i2c();
void init_test_i2c();

uint16_t cal_sensor(double rshunt, double max_expect, i2c_sensor sensor);
#endif



