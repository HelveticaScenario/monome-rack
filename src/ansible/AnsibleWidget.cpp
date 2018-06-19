#include "AnsibleWidget.hpp"
#include "AnsibleModule.hpp"
#include "MonomeWidgets.hpp"

using namespace rack;

AnsibleWidget::AnsibleWidget(AnsibleModule* module)
    : MonomeModuleBaseWidget(module)
{
    box.size = Vec(15 * 6, 380);

    {
        auto panel = new SVGPanel();
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/meadowphysics.svg")));
        panel->box.size = box.size;
        addChild(panel);
    }

    addChild(Widget::create<USBAJack>(Vec(10, 338)));

    addParam(ParamWidget::create<TL1105>(Vec(62, 336), module, AnsibleModule::BUTTON_PARAM, 0.0, 1.0, 0.0));
    // addParam(ParamWidget::create<MonomeKnob>(Vec(12, 232), module, AnsibleModule::CLOCK_PARAM, 0.0, 1.0, 0.5));

    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(2, 72), module, AnsibleModule::TRIG1_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(77, 72), module, AnsibleModule::TRIG2_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(2, 110), module, AnsibleModule::TRIG3_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(77, 110), module, AnsibleModule::TRIG4_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(2, 148), module, AnsibleModule::CV1_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(77, 148), module, AnsibleModule::CV2_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(2, 186), module, AnsibleModule::CV3_LIGHT));
    addChild(ModuleLightWidget::create<MediumLight<YellowLight>>(Vec(77, 186), module, AnsibleModule::CV4_LIGHT));

    addOutput(Port::create<PJ301MPort>(Vec(13, 54), Port::OUTPUT, module, AnsibleModule::TRIG1_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(50, 75), Port::OUTPUT, module, AnsibleModule::TRIG2_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(13, 92), Port::OUTPUT, module, AnsibleModule::TRIG3_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(50, 111), Port::OUTPUT, module, AnsibleModule::TRIG4_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(13, 130), Port::OUTPUT, module, AnsibleModule::CV1_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(50, 149), Port::OUTPUT, module, AnsibleModule::CV2_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(13, 168), Port::OUTPUT, module, AnsibleModule::CV3_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(50, 187), Port::OUTPUT, module, AnsibleModule::CV4_OUTPUT));
    addInput(Port::create<PJ301MPort>(Vec(13, 286), Port::INPUT, module, AnsibleModule::CLOCK_INPUT));
    addInput(Port::create<PJ301MPort>(Vec(50, 286), Port::INPUT, module, AnsibleModule::RESET_INPUT));
}

void AnsibleWidget::randomize()
{
}
