#include "user_wifi_ap.h"

#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event_loop.h"


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) 
	{
		case SYSTEM_EVENT_AP_START:                         // wifi AP 开始
			printf("[WIFI AP] AP start event!\r\n");

			//ESP_LOGI(TAG, "station:"MACSTR" join,AID=%d\n",
			//MAC2STR(event->event_info.sta_connected.mac),
			//event->event_info.sta_connected.aid);
			//xEventGroupSetBits(udp_event_group, WIFI_CONNECTED_BIT);
			break;
		case SYSTEM_EVENT_AP_STACONNECTED:                  // 有站点（STA）连接上ESP32的AP
			printf("[WIFI AP] A station connected to ESP32 soft-AP!\r\n");
			//ESP_LOGI(TAG, "station:"MACSTR" join,AID=%d\n",
			//MAC2STR(event->event_info.sta_connected.mac),
			//event->event_info.sta_connected.aid);
			//xEventGroupSetBits(udp_event_group, WIFI_CONNECTED_BIT);
			break;
		case SYSTEM_EVENT_AP_STADISCONNECTED:               // 有站点（STA）与ESP32的AP断开连接
			printf("[WIFI AP] A station disconnected from ESP32 soft-AP!\r\n");
			//ESP_LOGI(TAG, "station:"MACSTR"leave,AID=%d\n",
			//MAC2STR(event->event_info.sta_disconnected.mac),
			//event->event_info.sta_disconnected.aid);
			//xEventGroupClearBits(udp_event_group, WIFI_CONNECTED_BIT);
			break;	
		default:
			break;
    }
	
    return ESP_OK;
}


void user_wifi_config_ap(void)
{
	printf("[WIFI AP] AP config start\r\n");
	printf("[WIFI AP] ESP32 soft-AP SSID: %s  PASSWORD: %s \r\n", ESP32_AP_SSID, ESP32_AP_PASS);
	
    tcpip_adapter_init();
	
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
	
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	
	wifi_config_t wifi_ap_config = 
	{
        .ap = 
		{
            .ssid = ESP32_AP_SSID,                 // ESP32 wifi soft-AP
			.password = ESP32_AP_PASS,             // wifi密码
            .ssid_len = strlen(ESP32_AP_SSID),
			.channel = ESP32_AP_CHANNEL,           // 信道
            .max_connection = ESP32_MAX_CONN,      // 能连接的设备数           
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_ap_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );	
}

