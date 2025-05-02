#include "SDUpdater.h"
#include <M5StackUpdater.h>

SPIClass SPI2;

void SDU_lobby_cardputer()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;

  M5Cardputer.begin(cfg, true);
  SPI2.begin(
      M5.getPin(m5::pin_name_t::sd_spi_sclk),
      M5.getPin(m5::pin_name_t::sd_spi_miso),
      M5.getPin(m5::pin_name_t::sd_spi_mosi),
      M5.getPin(m5::pin_name_t::sd_spi_ss));

  while (false == SD.begin(M5.getPin(m5::pin_name_t::sd_spi_ss), SPI2))
  {
    delay(500);
  }
  M5Cardputer.update();

  if (M5Cardputer.Keyboard.isKeyPressed('a'))
  {
    updateFromFS(SD, "/menu.bin");
    ESP.restart();
  }
}
