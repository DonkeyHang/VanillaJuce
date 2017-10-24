#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"
#include "GuiMainTab.h"
#include "GuiOscTab.h"
#include "GuiEgTab.h"

class GuiTabs  : public Component
{
public:
    GuiTabs (SynthParameters_Main& mp, SynthParameters_Osc& op, SynthParameters_AmpEG& aegp);
    ~GuiTabs();

    void paint (Graphics& g) override;
    void resized() override;

    void update();

private:
    ScopedPointer<TabbedComponent> tabbedComponent;
    GuiMainTab* pMainTab;
    GuiOscTab* pOscTab;
    GuiEgTab* pAmpEgTab;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiTabs)
};
