// Own
#include "temperature.hpp"

// Pico-SDK
#include "hardware/adc.h"

void Temperature::Init()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

float Temperature::GetPcbTemperature_C()
{
    // 12-bit conversion = 4096 steps
    // And max conversion range is 3.3 V
    float conversion_factor = 3.3f / 4096.0f;
    float adc_voltage_V     = static_cast<float>(adc_read()) * conversion_factor;
    float temperature_C     = 27.0f - ((adc_voltage_V - 0.706f) / 0.001721f);

    return temperature_C;
}
