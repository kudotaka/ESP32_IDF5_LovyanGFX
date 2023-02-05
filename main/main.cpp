#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#if ( CONFIG_SOFTWARE_LGFX_MODEL_ILI9341_SPI )
#include "esp_moduleunit.h"
#endif


static const char *TAG = "MY-MAIN";

extern "C" { void app_main(); }


//=================================================

void app_main() {
    ESP_LOGI(TAG, "app_main() start.");
//    esp_log_level_set("*", ESP_LOG_ERROR);
//    esp_log_level_set("wifi", ESP_LOG_INFO);
//    esp_log_level_set("gpio", ESP_LOG_INFO);
    esp_log_level_set("MY-MAIN", ESP_LOG_INFO);
    esp_log_level_set("MY-UI", ESP_LOG_INFO);
    esp_log_level_set("MY-WIFI", ESP_LOG_INFO);

#ifdef CONFIG_SOFTWARE_LGFX_MODEL_ILI9341_SPI
    Ui_Init();
#endif

}