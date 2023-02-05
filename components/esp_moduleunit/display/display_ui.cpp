#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "display_ui.hpp"

#ifdef CONFIG_SOFTWARE_LGFX_MODEL_ILI9341_SPI
#include "LGFX_ESP32S3_SPI_ILI9341_XPT2046.hpp"
#endif

static const char *TAG = "MY-UI";

// 準備したクラスのインスタンスを作成します。
LGFX display;

TaskHandle_t xLcd_display;
static void lcd_display_task(void* pvParameters) {
  ESP_LOGI(TAG, "start lcd_display_task");

  display.init();
  display.setTextSize((std::max(display.width(), display.height()) + 255) >> 8);

  if (display.touch())
  {
    if (display.width() < display.height()) display.setRotation(display.getRotation() ^ 1);

    // 画面に案内文章を描画します。
    display.setTextDatum(textdatum_t::middle_center);
    display.drawString("touch the arrow marker.", display.width()>>1, display.height() >> 1);
    display.setTextDatum(textdatum_t::top_left);

    // タッチを使用する場合、キャリブレーションを行います。画面の四隅に表示される矢印の先端を順にタッチしてください。
    std::uint16_t fg = TFT_WHITE;
    std::uint16_t bg = TFT_BLACK;
    if (display.isEPD()) std::swap(fg, bg);
    display.calibrateTouch(nullptr, fg, bg, std::max(display.width(), display.height()) >> 3);

  }

  display.fillScreen(TFT_BLACK);

  uint32_t count = ~0;
  while(1) {
    display.startWrite();
    display.setRotation(++count & 7);
    display.setColorDepth((count & 8) ? 16 : 24);

    display.setTextColor(TFT_WHITE);
    display.drawNumber(display.getRotation(), 16, 0);

    display.setTextColor(0xFF0000U);
    display.drawString("R", 30, 16);
    display.setTextColor(0x00FF00U);
    display.drawString("G", 40, 16);
    display.setTextColor(0x0000FFU);
    display.drawString("B", 50, 16);

    display.drawRect(30,30,display.width()-60,display.height()-60,count*7);
    display.drawFastHLine(0, 0, 10);

    display.endWrite();

    int32_t x, y;
    if (display.getTouch(&x, &y)) {
      display.fillRect(x-2, y-2, 5, 5, count*7);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
  vTaskDelete(NULL); // Should never get to here...
}

void Ui_Init() {
    xTaskCreatePinnedToCore(&lcd_display_task, "lcd_display_task", 4096 * 1, NULL, 2, &xLcd_display, 1);
}
