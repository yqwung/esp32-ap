#ifndef __USER_WIFI_AP_H__
#define __USER_WIFI_AP_H__

#ifdef __cplusplus
extern "C" {
#endif


#define ESP32_AP_SSID           "espwifi"      // 设置wifi名
#define ESP32_AP_PASS           "esp123456"    // 设置的wifi 密码必须大于等于8个字符
#define ESP32_AP_CHANNEL        3              // 信道，中国一般是0~13
#define ESP32_MAX_CONN          3              // 最多有多少站点可以连接这个wifi(ESP32)，最大为4


void user_wifi_config_ap(void);


#ifdef __cplusplus
}
#endif

#endif /*#ifndef __USER_WIFI_AP_H__*/