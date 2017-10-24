#include "GuiTabs.h"

GuiTabs::GuiTabs (SynthParameters_Main& mp, SynthParameters_Osc& op, SynthParameters_AmpEG& aegp)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (32);
    tabbedComponent->addTab(TRANS("Main"), Colours::lightgrey, pMainTab = new GuiMainTab(mp), true);
    tabbedComponent->addTab(TRANS("Osc"), Colours::lightgrey, pOscTab = new GuiOscTab(op), true);
    tabbedComponent->addTab(TRANS("AmpEG"), Colours::lightgrey, pAmpEgTab = new GuiEgTab(aegp), true);
    tabbedComponent->setCurrentTabIndex(0);
}

GuiTabs::~GuiTabs()
{
}

//==============================================================================
void GuiTabs::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void GuiTabs::resized()
{
    tabbedComponent->setBounds (0, 0, getWidth(), getWidth());
}

void GuiTabs::update()
{
    pMainTab->update();
    pOscTab->update();
    pAmpEgTab->update();
}
