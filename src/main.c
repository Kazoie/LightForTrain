#include "esp_common.h"
#include "freertos/task.h"
#include "gpio.h"
 
/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;
 
        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;
 
        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;
 
        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;
 
        default:
            rf_cal_sec = 0;
            break;
    }
 
    return rf_cal_sec;
}
 
void task_blink(void* ignore) // blind of the 4 color (Red/Blue/Yellow/Green)
{
    GPIO_AS_OUTPUT(GPIO_Pin_5);
    GPIO_AS_OUTPUT(GPIO_Pin_4);
    GPIO_AS_OUTPUT(GPIO_Pin_0);
    GPIO_AS_OUTPUT(GPIO_Pin_2);

        // PIN 5 : BLUE
        // PIN 4 : RED
        // PIN 0 : YELLOW
        // PIN 2 : GREEN
    while(true) {
        //blue
        GPIO_OUTPUT(GPIO_Pin_5, 1);
        vTaskDelay(2000/portTICK_RATE_MS);
    	GPIO_OUTPUT(GPIO_Pin_5, 0);
        
        //red
        GPIO_OUTPUT(GPIO_Pin_4, 1);
        vTaskDelay(2000/portTICK_RATE_MS);
    	GPIO_OUTPUT(GPIO_Pin_4, 0);
        
        //yellow
        GPIO_OUTPUT(GPIO_Pin_0, 1);
        vTaskDelay(2000/portTICK_RATE_MS);
    	GPIO_OUTPUT(GPIO_Pin_0, 0);
       
        //green
        GPIO_OUTPUT(GPIO_Pin_2, 1);
        vTaskDelay(2000/portTICK_RATE_MS);
    	GPIO_OUTPUT(GPIO_Pin_2, 0);

        //5seconds
        //all led
        int i = 0;
        while( i < 5) {
        GPIO_OUTPUT(GPIO_Pin_5, 0);
        GPIO_OUTPUT(GPIO_Pin_4, 0);
        GPIO_OUTPUT(GPIO_Pin_0, 0);
        GPIO_OUTPUT(GPIO_Pin_2, 0);
        vTaskDelay(1000/portTICK_RATE_MS);

        if (i%2 == 0) {
            GPIO_OUTPUT(GPIO_Pin_5, 1);
            GPIO_OUTPUT(GPIO_Pin_0, 1);
        }
        if (i%2 == 1) {
            GPIO_OUTPUT(GPIO_Pin_4, 1);
            GPIO_OUTPUT(GPIO_Pin_2, 1);
        }
        vTaskDelay(1000/portTICK_RATE_MS);
        i++;
        }

        GPIO_OUTPUT(GPIO_Pin_5, 0);
        GPIO_OUTPUT(GPIO_Pin_4, 0);
        GPIO_OUTPUT(GPIO_Pin_0, 0);
        GPIO_OUTPUT(GPIO_Pin_2, 0);
    }
    vTaskDelete(NULL);
}


void task_house(void* ignore) // Blind of the white LED for house (5 -> 1,30 x2 | 6 -> 1,30)
{
     GPIO_AS_OUTPUT(GPIO_Pin_0);
     GPIO_AS_OUTPUT(GPIO_Pin_14);
     GPIO_AS_OUTPUT(GPIO_Pin_2);
     GPIO_AS_OUTPUT(GPIO_Pin_4);
     GPIO_AS_OUTPUT(GPIO_Pin_5);

     while (true){
        GPIO_OUTPUT(GPIO_Pin_0, 0);
        GPIO_OUTPUT(GPIO_Pin_14, 0);
        GPIO_OUTPUT(GPIO_Pin_2, 0);
        GPIO_OUTPUT(GPIO_Pin_4, 0);
        GPIO_OUTPUT(GPIO_Pin_5, 0);
        vTaskDelay(1000/portTICK_RATE_MS);
        GPIO_OUTPUT(GPIO_Pin_0, 1);
        GPIO_OUTPUT(GPIO_Pin_14, 1);
        GPIO_OUTPUT(GPIO_Pin_2, 1);
        GPIO_OUTPUT(GPIO_Pin_4, 1);
        GPIO_OUTPUT(GPIO_Pin_5, 1);
        vTaskDelay(1000/portTICK_RATE_MS);
        GPIO_OUTPUT(GPIO_Pin_0, 0);
        GPIO_OUTPUT(GPIO_Pin_14, 0);
        GPIO_OUTPUT(GPIO_Pin_2, 0);
        GPIO_OUTPUT(GPIO_Pin_4, 0);
        GPIO_OUTPUT(GPIO_Pin_5, 0);

     }
    vTaskDelete(NULL);
}
 
/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    //xTaskCreate(&task_blink, "startup", 2048, NULL, 1, NULL);
    xTaskCreate(&task_house, "startup", 2048, NULL, 1, NULL);
}