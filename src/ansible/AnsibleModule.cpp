#include "AnsibleModule.hpp"
#include "MonomeWidgets.hpp"

AnsibleModule::AnsibleModule()
    : MonomeModuleBase(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS)
{
    firmware.load("ansible");
    firmware.init();
}

void AnsibleModule::processInputs()
{
    // // Convert clock input jack to GPIO signals for normal connection and value
    // bool clockNormal = !inputs[CLOCK_INPUT].active;
    // if (clockNormal != firmware.getGPIO(B09))
    // {
    //     firmware.setGPIO(B09, clockNormal);
    //     firmware.triggerInterrupt(1);
    // }
    // bool externalClock = inputs[CLOCK_INPUT].value > 0;
    // if (externalClock != firmware.getGPIO(B08))
    // {
    //     firmware.setGPIO(B08, externalClock);
    //     firmware.triggerInterrupt(2);
    // }
    // bool frontButton = params[BUTTON_PARAM].value == 0;
    // if (frontButton != firmware.getGPIO(NMI))
    // {
    //     firmware.setGPIO(NMI, frontButton);
    //     firmware.triggerInterrupt(3);
    // }

    // // Convert knob float parameters to 12-bit ADC values
    // firmware.setADC(0, params[CLOCK_PARAM].value * 0xFFF);
    // firmware.setADC(1, params[PARAM_PARAM].value * 0xFFF);
}

void AnsibleModule::processOutputs()
{

    // // Update lights from GPIO
    // lights[CV1_LIGHT].value = firmware.getDAC(2) / 65536.0;
    // lights[CV2_LIGHT].value = firmware.getDAC(3) / 65536.0;
    // lights[CV3_LIGHT].value = firmware.getDAC(0) / 65536.0;
    // lights[POS_LIGHT].value = firmware.getDAC(1) / 65536.0;
    // lights[EDGE_LIGHT].setBrightnessSmooth(firmware.getGPIO(B00));

    // // Update output jacks from GPIO & DAC
    // outputs[CV1_OUTPUT].value = 10.0 * firmware.getDAC(2) / 65536.0;
    // outputs[CV2_OUTPUT].value = 10.0 * firmware.getDAC(3) / 65536.0;
    // outputs[CV3_OUTPUT].value = 10.0 * firmware.getDAC(0) / 65536.0;
    // outputs[POS_OUTPUT].value = 10.0 * firmware.getDAC(1) / 65536.0;
    // outputs[EDGE_OUTPUT].value = firmware.getGPIO(B00) * 8.0;
}
