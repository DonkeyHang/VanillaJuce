#include "GuiMainTab.h"

GuiMainTab::GuiMainTab (SynthParameters_Main& mp)
    : mainParams(mp)
    , masterLevelLabel(SynthParameters_Main::masterLevel_Name, SynthParameters_Main::masterLevel_Label)
    , pbUpLabel(SynthParameters_Main::pitchBendUpSemitones_Name, SynthParameters_Main::pitchBendUpSemitones_Label)
    , pbDownLabel(SynthParameters_Main::pitchBendDownSemitones_Name, SynthParameters_Main::pitchBendDownSemitones_Label)
{
    auto initLabel = [this](Label& label)
    {
        addAndMakeVisible(label);
        label.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
        label.setJustificationType(Justification::centredRight);
        label.setEditable(false, false, false);
        label.setColour(TextEditor::textColourId, Colours::black);
        label.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    };

    initLabel(masterLevelLabel);
    initLabel(pbUpLabel);
    initLabel(pbDownLabel);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(&mainParams);
    };

    initSlider(masterLevelSlider); masterLevelSlider.setRange(0, 10, 0);
    initSlider(pbUpSlider); pbUpSlider.setRange(0, 12, 1);
    initSlider(pbDownSlider); pbDownSlider.setRange(0, 12, 1);

    mainParams.AttachControls(&masterLevelSlider, &pbUpSlider, &pbDownSlider);
    mainParams.UpdateControlsFromWorkingValues();
}

void GuiMainTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiMainTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int sliderWidth = 420;
    const int controlHeight = 24;
    const int gapHeight = 8;

    int top = 20;
    masterLevelLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    masterLevelSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + 5 * gapHeight;
    pbUpLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbUpSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    pbDownLabel.setBounds(labelLeft, top, labelWidth, controlHeight);
    pbDownSlider.setBounds(controlLeft, top, sliderWidth, controlHeight);
}
