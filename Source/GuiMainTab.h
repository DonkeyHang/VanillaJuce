#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class GuiMainTab : public Component
{
public:
    GuiMainTab (SynthParameters_Main& mp);

    void paint (Graphics& g) override;
    void resized() override;

    void update() { mainParams.UpdateControlsFromWorkingValues(); }

private:
    SynthParameters_Main& mainParams;

    Label masterLevelLabel, pbUpLabel, pbDownLabel;
    Slider masterLevelSlider, pbUpSlider, pbDownSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMainTab)
};
