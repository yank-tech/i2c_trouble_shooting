#include "i2c.h"
#include "vcnl_i2c.h"

void app_main() 
{
init_i2c();
test_i2c();
//vcnl_i2c_get_id();
vcnl_i2c_sensor_setup();
//vcnl_i2c_get_ps_data();
//vcnl_i2c_get_als_conf1();
while(1){
   vcnl_i2c_get_ps_data(); 
   vTaskDelay(100);
}

}