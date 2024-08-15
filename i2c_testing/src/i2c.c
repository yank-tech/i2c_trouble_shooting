
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



uint16_t cal_sensor(double rshunt, double max_expect, i2c_sensor sensor)
{

    uint8_t cal_reg = I2C_REG_CALIBRATION;
    uint8_t data[3];
    double cur_lsb = max_expect/(32768);
    uint16_t cal_val = (uint16_t) (.00512/(cur_lsb * rshunt));
    i2c_master_dev_handle_t dev_handle;


    double cur_div = .001 / cur_lsb;
    double pwr_mul = 1000.0 * 25.0 * cur_lsb;
    switch(sensor)
    {
        case SENSOR_0:
        sensor_0_cur_div = cur_div;
        sensor_0_pwr_mul = pwr_mul;
        dev_handle = sensor_handle_0;
        break;
        default:
        return 0;
    } 

    data[0] = cal_reg;
    data[1] = cal_val >> 8;
    data[2] = cal_val & 255;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, &data[0], 3, 1000));
    return cal_val;
}

int i2c_get_value(i2c_sensor sensor, i2c_req req, double *ret)
{
    if (i2c_connected != 1)
    {
        return -1;
    }
    i2c_master_dev_handle_t dev_handle;
    double cur_div = -1;
    double pwr_mul = -1;
    switch(sensor)
    {
        case(SENSOR_0):
        dev_handle = sensor_handle_0;
        cur_div = sensor_0_cur_div;
        pwr_mul = sensor_0_pwr_mul;
        break;
        default:
        return -1;
    }

    uint8_t req_reg;
    switch(req)
    {
        case(BUS_V):
        req_reg = I2C_REG_BUS_V;
        break;
        case(SHUNT_V):
        req_reg = I2C_REG_SHUNT_V;
        break;
        case(CURRENT_mA):
        req_reg = I2C_REG_CURRENT;
        break;
        case(POWER_mW):
        req_reg = I2C_REG_POWER;
        break;
        default:
        return -1;
    }


    // might have to play with timeout


    uint8_t r[2];
    uint16_t tmp_val;
    esp_err_t error = i2c_master_transmit_receive(dev_handle, &req_reg, 1, (uint8_t*) &r[0], 2, 1000);
    if(error != ESP_OK)
    {
        printf("I2C did not read correctly\n");
        return -1;
    }

    tmp_val = (r[0] << 8) + r[1];

    switch(req)
    {
        case(BUS_V):
        *ret = tmp_val * .00125;
        break;
        case(SHUNT_V):
        // can also have a correction factor
        *ret = ((int16_t) tmp_val) * .0025;
        break;
        case(CURRENT_mA):
        printf("tmp val is %u\n", tmp_val);
        printf("cur_div is %f\n", cur_div);
        printf("tmp_val as an int is %d\n", (int16_t) tmp_val);
        *ret = ((int16_t) tmp_val) / cur_div;
        printf("ret in current is %f\n", *ret);
        break;
        case(POWER_mW):
        // have to figure out power multiplier
        *ret = tmp_val * pwr_mul;
        break;
        default:
        return -1;
    }

    //turn tmp_val into correct based on scaling

    //printf("I2C value is %u\n", *ret);
    return 0;
    // do I need to wait for i2c transactions to be done?
    // either before or after

    // could also register callback functions instead of doing
    // what i am doing now

}




int i2c_config()
{

    // really need to double check all of this
    // to check if it is working

    cal_sensor(.009, 8, SENSOR_0);


    uint8_t data[3];
    uint8_t cal_reg = I2C_REG_CONFIG;
    uint16_t cal_val = I2C_SENSOR_0_CONFIG;
    data[0] = cal_reg;
    data[1] = cal_val >> 8;
    data[2] = cal_val & 255;
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_handle_0, &data[0], 3, 1000));
   /*
uint8_t reg = I2C_REG_DIE_ID;
    uint16_t ret = 0;
i2c_master_transmit_receive(main_sensor_handle, &reg, 1, (uint8_t*) &ret, 2, 1000);
    printf("ret is %u\n", ret);
   */ 
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

