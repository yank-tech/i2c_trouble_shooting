
#include "i2c.h"


// keeping new driver
// Emphasis that the driver was changed manually
// Will need to make sure it is updated in the docker container
// gonna need sensor names
i2c_master_dev_handle_t sensor_handle_0;

i2c_master_bus_handle_t bus_handle;

double sensor_0_cur_div = -1;


double sensor_0_pwr_mul = -1;

short i2c_connected = 1;



int i2c_config()
{
    return 0;
}


int init_i2c()
{

    // init i2c bus
i2c_master_bus_config_t i2c_mst_config = 
    {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_PORT,
    .scl_io_num = I2C_SCL_GPIO,
    .sda_io_num = I2C_SDA_GPIO,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
    
    };

// probably need a better checking system since
// I think this one just aborts if there is a non ESP-OK
ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

i2c_device_config_t sensor_0_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = I2C_SENSOR_0_ADDR,
    .scl_speed_hz = 100000,
};


//get devices
i2c_master_bus_add_device(bus_handle, &sensor_0_cfg, &sensor_handle_0);

// now should be all set up for i2c

i2c_connected = 1;
return i2c_connected;

}

int i2c_write(uint8_t *data, uint8_t length)
{
    i2c_master_transmit(sensor_handle_0, data, length, 10);
    return 0;
}

int i2c_write_rec(uint8_t *data_send, uint8_t data_send_length, uint8_t *data_rec, uint8_t data_rec_length)
{
    //printf("data send is %x\n", *data_send);
    //printf("current data is %x, %x\n", data_rec[0], data_rec[1]);
    i2c_master_transmit_receive(sensor_handle_0, data_send, data_send_length, data_rec, data_rec_length, 10);
    return 0;
}

int i2c_read(uint8_t *data, uint8_t length)
{
    i2c_master_receive(sensor_handle_0, data, length, 10);
    return 0;
}


void test_i2c()
{
    ESP_ERROR_CHECK(i2c_master_probe(bus_handle, I2C_SENSOR_0_ADDR, 100));
}



/*


void init_test_i2c()
{

    // init i2c bus
i2c_master_bus_config_t i2c_mst_config = 
    {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_PORT,
    .scl_io_num = I2C_SCL_GPIO,
    .sda_io_num = I2C_SDA_GPIO,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
    
    };

// probably need a better checking system since
// I think this one just aborts if there is a non ESP-OK
ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

i2c_device_config_t main_sensor_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = I2C_SENSOR_0_ADDR,
    .scl_speed_hz = 100000,
};

i2c_master_bus_add_device(bus_handle, &sensor_0_cfg, &sensor_handle_0);

i2c_config();
}

*/

