#include "vcnl_i2c.h"



int vcnl_i2c_get_id()
{
    uint8_t data[2];
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
    i2c_write(&cc, 1);
    i2c_read(data, 2);
    return 0;
}