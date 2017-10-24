#include "GuiEgTab.h"

GuiEgTab::GuiEgTab (SynthParameters_AmpEG& aegp)
    : ampEgParams(aegp)
    , attackLabel(SynthParameters_AmpEG::attack_Name, SynthParameters_AmpEG::attack_Label)
    , decayLabel(SynthParameters_AmpEG::decay_Name, SynthParameters_AmpEG::decay_Label)
    , sustainLabel(SynthParameters_AmpEG::sustain_Name, SynthParameters_AmpEG::sustain_Label)
    , releaseLabel(SynthParameters_AmpEG::release_Name, SynthParameters_AmpEG::release_Label)
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        label.setJustificationType (Justification::centredRight);
        label.setEditable (false, false, false);
        label.setColour (TextEditor::textColourId, Colours::black);
        label.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    };

    initLabel(attackLabel);
    initLabel(decayLabel);
    initLabel(sustainLabel);
    initLabel(releaseLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle (Slider::LinearHorizontal);
        slider.setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
        slider.addListener(&ampEgParams);
    };

    initSlider(attackSlider); attackSlider.setRange (0, 10, 0);
    initSlider(decaySlider); decaySlider.setRange (0, 10, 0);
    initSlider(sustainSlider); sustainSlider.setRange (0, 100, 1);
    initSlider(releaseSlider); releaseSlider.setRange (0, 10, 0);

    ampEgParams.AttachControls(&attackSlider, &decaySlider, &sustainSlider, &releaseSlider);
    ampEgParams.UpdateControlsFromWorkingValues();
}

void GuiEgTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiEgTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    attackLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    attackSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    decayLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    decaySlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    sustainLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    sustainSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    releaseLabel.setBounds (labelLeft, top, labelWidth, controlHeight);
    releaseSlider.setBounds (controlLeft, top, sliderWidth, controlHeight);
}
