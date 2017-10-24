#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class GuiOscTab : public Component
{
public:
    GuiOscTab (SynthParameters_Osc& op);

    void paint (Graphics& g) override;
    void resized() override;

    void update() { oscParams.UpdateControlsFromWorkingValues(); }

private:
    SynthParameters_Osc& oscParams;

    Label wfLabel1, semiLabel1, detuneLabel1;
    ComboBox waveformCB1;
    Slider semiSlider1, detuneSlider1;
    Label wfLabel2, semiLabel2, detuneLabel2;
    ComboBox waveformCB2;
    Slider semiSlider2, detuneSlider2;
    Label oscBlendLabel;
    Slider oscBlendSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiOscTab)
};
