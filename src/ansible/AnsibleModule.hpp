#include "MonomeModuleBase.hpp"

#pragma once

struct AnsibleModule : MonomeModuleBase
{
    enum ParamIds
    {
        CLOCK_PARAM,
        RESET_PARAM,
        BUTTON_PARAM,
        NUM_PARAMS
    };

    enum InputIds
    {
        CLOCK_INPUT,
        RESET_INPUT,
        NUM_INPUTS
    };

    enum OutputIds
    {
        TRIG1_OUTPUT,
        TRIG2_OUTPUT,
        TRIG3_OUTPUT,
        TRIG4_OUTPUT,
        CV1_OUTPUT,
        CV2_OUTPUT,
        CV3_OUTPUT,
        CV4_OUTPUT,
        NUM_OUTPUTS
    };

    enum LightIds
    {
        MODE_LIGHT,
        TRIG1_LIGHT,
        TRIG2_LIGHT,
        TRIG3_LIGHT,
        TRIG4_LIGHT,
        CV1_LIGHT,
        CV2_LIGHT,
        CV3_LIGHT,
        CV4_LIGHT,
        NUM_LIGHTS
    };

    AnsibleModule();
    void processInputs() override;
    void processOutputs() override;
};