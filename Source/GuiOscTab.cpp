#include "GuiOscTab.h"

GuiOscTab::GuiOscTab (SynthParameters_Osc& op)
    : oscParams(op)
    , wfLabel1(SynthParameters_Osc::waveform1_Name, SynthParameters_Osc::waveform1_Label)
    , semiLabel1(SynthParameters_Osc::pitchOffsetSemitones1_Name, SynthParameters_Osc::pitchOffsetSemitones1_Label)
    , detuneLabel1(SynthParameters_Osc::detuneOffsetCents1_Name, SynthParameters_Osc::detuneOffsetCents1_Label)
    , wfLabel2(SynthParameters_Osc::waveform2_Name, SynthParameters_Osc::waveform2_Label)
    , semiLabel2(SynthParameters_Osc::pitchOffsetSemitones2_Name, SynthParameters_Osc::pitchOffsetSemitones2_Label)
    , detuneLabel2(SynthParameters_Osc::detuneOffsetCents2_Name, SynthParameters_Osc::detuneOffsetCents2_Label)
    , oscBlendLabel(SynthParameters_Osc::oscBlend_Name, SynthParameters_Osc::oscBlend_Label)
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

    initLabel(wfLabel1);
    initLabel(semiLabel1);
    initLabel(detuneLabel1);
    initLabel(wfLabel2);
    initLabel(semiLabel2);
    initLabel(detuneLabel2);
    initLabel(oscBlendLabel);
    oscBlendLabel.setJustificationType(Justification::centredLeft);

    auto initCombo = [this](ComboBox& combo)
    {
        addAndMakeVisible(combo);
        combo.setEditableText(false);
        combo.setJustificationType(Justification::centredLeft);
        combo.setTextWhenNothingSelected("");
        combo.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
        combo.addListener(&oscParams);
    };

    initCombo(waveformCB1); 
    SynthWaveform::setupComboBox(waveformCB1);
    waveformCB1.addListener(&oscParams);
    initCombo(waveformCB2);
    SynthWaveform::setupComboBox(waveformCB2);
    waveformCB2.addListener(&oscParams);

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 20);
        slider.addListener(&oscParams);
    };

    initSlider(semiSlider1); semiSlider1.setRange(-24, 24, 1);
    initSlider(detuneSlider1); detuneSlider1.setRange(-50, 50, 0);
    initSlider(semiSlider2); semiSlider2.setRange(-24, 24, 1);
    initSlider(detuneSlider2); detuneSlider2.setRange(-50, 50, 0);

    addAndMakeVisible(oscBlendSlider);
    oscBlendSlider.setRange(0, 100, 1);
    oscBlendSlider.setSliderStyle(Slider::LinearVertical);
    oscBlendSlider.setTextBoxStyle(Slider::TextBoxRight, false, 40, 20);
    oscBlendSlider.addListener(&oscParams);

    oscParams.AttachControls(&waveformCB1, &waveformCB2, &semiSlider1, &semiSlider2, &detuneSlider1, &detuneSlider2, &oscBlendSlider);
    oscParams.UpdateControlsFromWorkingValues();
}

void GuiOscTab::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiOscTab::resized()
{
    const int labelLeft = 16;
    const int controlLeft = 144;
    const int labelWidth = 120;
    const int cboxWidth = 150;
    const int sliderWidth = 344;
    const int controlHeight = 24;
    const int gapHeight = 8;
    const int blendSliderLeft = 500;
    const int blendSliderWidth = 80;
    const int blendSliderHeight = 200;

    int top = 20;
    wfLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    waveformCB1.setBounds (controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    semiSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel1.setBounds (labelLeft, top, labelWidth, controlHeight);
    detuneSlider1.setBounds (controlLeft, top, sliderWidth, controlHeight);

    top += controlHeight + 5 * gapHeight;
    wfLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    waveformCB2.setBounds(controlLeft, top, cboxWidth, controlHeight);
    top += controlHeight + gapHeight;
    semiLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    semiSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);
    top += controlHeight + gapHeight;
    detuneLabel2.setBounds(labelLeft, top, labelWidth, controlHeight);
    detuneSlider2.setBounds(controlLeft, top, sliderWidth, controlHeight);

    top = 20;
    oscBlendLabel.setBounds(blendSliderLeft, top, labelWidth, controlHeight);
    top += controlHeight;
    oscBlendSlider.setBounds(blendSliderLeft, top, blendSliderWidth, blendSliderHeight);
}
