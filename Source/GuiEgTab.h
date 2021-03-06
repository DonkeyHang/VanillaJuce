#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class GuiEgTab  : public Component,
                  public SliderListener
{
public:
    GuiEgTab (SynthSound* pSynthSound);

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    void notify();

private:
    SynthSound* pSound;

    Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    Slider attackSlider, decaySlider, sustainSlider, releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiEgTab)
};
