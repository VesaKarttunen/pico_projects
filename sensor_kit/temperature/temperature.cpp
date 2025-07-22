//---------------------------------------------------------------------------------------------------------------------
// Temperature Measurement
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "temperature.hpp"

// Pico SDK
#include "hardware/adc.h"

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

// Pico's internal onboard temperature sensor in connected to ADC input 4
static constexpr unsigned f_onboard_sensor_adc_input = 4u;

// 12-bit Analog-to-Digital Converter (ADC) has 2^12 = 4096 distinct conversion levels.
// Note that there is one less (2^N -1) steps than there is ADC output values (0 - 4095)
static constexpr float f_count_adc_steps = 4095.0f;

// Max conversion range (ADC reference voltage) in Pico's PCB is 3.3 V
static constexpr float f_adc_voltage_ref_V = 3.3f;

// ADC step size is reference voltage devided by number of levels
static constexpr float f_adc_voltage_step_size_V = f_adc_voltage_ref_V / f_count_adc_steps;

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static float GetAdcVoltage_V()
{
    // ADC voltage is ADC output value times the voltage step size
    float adc_output_value = static_cast<float>(adc_read());
    float adc_voltage_V    = adc_output_value * f_adc_voltage_step_size_V;

    return adc_voltage_V;
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

void Temperature::Init()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(f_onboard_sensor_adc_input);
}

float Temperature::GetPcbTemperature_C()
{
    // Voltage is converted into temperature value using the temperature sensor's characteristics.
    // Pico's datasheet states that at 27 C temperature, the voltage is approximately 0.706V
    // and the voltage decreases by 1.721 mV for every degree Celsius increase in temperature.
    float temperature_C = 27.0f - ((GetAdcVoltage_V() - 0.706f) / 1.721e-3f);

    return temperature_C;
}
