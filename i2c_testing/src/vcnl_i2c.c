#include "vcnl_i2c.h"



int vcnl_i2c_get_als_conf1()
{
    uint8_t data[2] = {2,2};
    vcnl_i2c_read(0x00, &data[0]);

    printf("data is %x, %x\n", data[0], data[1]);
    return 0;
}

int vcnl_i2c_sensor_setup()
{
    //PROXIMITY SENSOR CONFIG
    vcnl_i2c_write(CMD_PS_CONF1_2, PS_CONF1, PS_CONF2);
    vcnl_i2c_write(CMD_PS_CONF3_MS, PS_CONF3, PS_MS);

    return 0;
}


int vcnl_i2c_get_ps_data()
{
    uint8_t data[2] = {2,2};
    uint16_t ps1_data;
    double ps1_mm;
    vcnl_i2c_read(0x08, &data[0]);
    ps1_data = *((uint16_t*)data);
    ps1_mm = 300-((0.004577637)*ps1_data);
    printf("data is %x, %x\n", data[0], data[1]);
    printf("converted data is %x\n", ps1_data);
    printf("data in [mm] is %f\n", ps1_mm);
    return 0;
}


int vcnl_i2c_get_id()
{
    uint8_t data[2] = {1,1};
    vcnl_i2c_read(0x0E, &data[0]);

    printf("data is %x, %x\n", data[0], data[1]);
    return 0;
}

int vcnl_i2c_write(uint8_t cc, uint8_t lower_byte, uint8_t upper_byte)
{
    uint8_t buf[3];
    buf[0] = cc;
    buf[1] = lower_byte;
    buf[2] = upper_byte;
    i2c_write(&buf[0], 3);

    return 0;

}


int vcnl_i2c_read(uint8_t cc, uint8_t *data)
{
    i2c_write_rec(&cc, 1, data, 2);
   
    return 0;
}