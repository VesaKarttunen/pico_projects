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
    // 12-bit Analog-to-Digital Converter (ADC) has 2^12 = 4096 distinct conversion levels.
    // Note that there is one less (2^N -1) steps than there is ADC output values (0 - 4095)
    float count_adc_steps = 4095.0f;

    // Max conversion range (ADC reference voltage) in Pico's PCB is 3.3 V
    float adc_voltage_ref_V = 3.3f;

    // ADC step size is reference voltage devided by number of levels
    float adc_voltage_step_size_V = adc_voltage_ref_V / count_adc_steps;

    // ADC voltage is ADC output value times the voltage step size
    float adc_voltage_V = static_cast<float>(adc_read()) * adc_voltage_step_size_V;

    // Voltage is converted into temperature reading using the temperature sensor's characteristics.
    // Pico's datasheet states that at 27 C temperature, the voltage is approximately 0.706V
    // and the voltage decreases by 1.721 mV for every degree Celsius increase in temperature.
    float temperature_C = 27.0f - ((adc_voltage_V - 0.706f) / 1.721e-3f);

    return temperature_C;
}
