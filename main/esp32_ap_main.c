#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "soc/rtc_cntl_reg.h"

#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"

#include "user_wifi_ap.h"


void app_main()
{
	// 获取系统信息
    esp_chip_info_t chip_info;
	
    esp_chip_info( &chip_info );
	
	printf("========================================================\r\n");
	printf("[WIFI AP] Example : wifi set mode of soft-AP \r\n");
	printf("[WIFI AP] FLASH SIZE: %s  %d MB  \r\n", (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external",
													spi_flash_get_chip_size() / (1024 * 1024));
	printf("[WIFI AP] Free memory: %d bytes \r\n", esp_get_free_heap_size());

 
    nvs_flash_init();
	
    user_wifi_config_ap();
}
