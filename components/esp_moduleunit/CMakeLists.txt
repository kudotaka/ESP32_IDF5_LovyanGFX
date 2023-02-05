set(COMPONENT_SRCDIRS .)
set(COMPONENT_ADD_INCLUDEDIRS .)
set(COMPONENT_REQUIRES nvs_flash esp_wifi esp_timer driver LovyanGFX)


if(CONFIG_SOFTWARE_LGFX_MODEL_ILI9341_SPI)
    list(APPEND COMPONENT_SRCDIRS display)
    list(APPEND COMPONENT_ADD_INCLUDEDIRS display)
endif()

register_component()
