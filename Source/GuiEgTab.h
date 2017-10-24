#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class GuiEgTab  : public Component
{
public:
    GuiEgTab (SynthParameters_AmpEG& aegp);

    void paint (Graphics& g) override;
    void resized() override;

    void update() { ampEgParams.UpdateControlsFromWorkingValues(); }

private:
    SynthParameters_AmpEG& ampEgParams;

    Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    Slider attackSlider, decaySlider, sustainSlider, releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiEgTab)
};
