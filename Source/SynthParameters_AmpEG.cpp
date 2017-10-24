#include "SynthParameters.h"
#include "Synth.h"

// Names are symbolic names used to tag AudioParameter objects and XML attributes
// Labels are human-friendly identifiers for use in GUIs
const String SynthParameters_AmpEG::attack_Name = "attack";
const String SynthParameters_AmpEG::attack_Label = TRANS("Attack Time (sec)");
const String SynthParameters_AmpEG::decay_Name = "decay";
const String SynthParameters_AmpEG::decay_Label = TRANS("Decay Time (sec)");
const String SynthParameters_AmpEG::sustain_Name = "sustain";
const String SynthParameters_AmpEG::sustain_Label = TRANS("Sustain Level (%)");
const String SynthParameters_AmpEG::release_Name = "release";
const String SynthParameters_AmpEG::release_Label = TRANS("Release Time (sec)");

SynthParameters_AmpEG::SynthParameters_AmpEG (Synth& s)
    : synth(s)
{
    // Set default values
    attackTimeSeconds = 0.1f;
    decayTimeSeconds = 0.1f;
    sustainLevel = 0.8f;
    releaseTimeSeconds = 0.5f;

    // Create parameter objects. The plugin processor will take ownership of these, so this
    // object need not worry about deleting them later.
    pAttack_Param = new AudioParameterFloat(attack_Name, attack_Label, 0.0f, 10.0f, attackTimeSeconds);
    pDecay_Param = new AudioParameterFloat(decay_Name, decay_Label, 0.0f, 10.0f, decayTimeSeconds);
    pSustain_Param = new AudioParameterFloat(sustain_Name, sustain_Label, 0.0f, 1.0f, sustainLevel);
    pRelease_Param = new AudioParameterFloat(release_Name, release_Label, 0.0f, 10.0f, releaseTimeSeconds);
}

void SynthParameters_AmpEG::AttachControls(
    Slider* pAttackSlider,
    Slider* pDecaySlider,
    Slider* pSustainSlider,
    Slider* pReleaseSlider)
{
    pAttack_Slider = pAttackSlider;
    pDecay_Slider = pDecaySlider;
    pSustain_Slider = pSustainSlider;
    pRelease_Slider = pReleaseSlider;
}

void SynthParameters_AmpEG::UpdateWorkingValuesFromPluginParameters()
{
    attackTimeSeconds = *pAttack_Param;
    decayTimeSeconds = *pDecay_Param;
    sustainLevel = *pSustain_Param;
    releaseTimeSeconds = *pRelease_Param;
}

void SynthParameters_AmpEG::UpdateControlsFromWorkingValues()
{
    pAttack_Slider->setValue(attackTimeSeconds);
    pDecay_Slider->setValue(decayTimeSeconds);
    pSustain_Slider->setValue(100.0f * sustainLevel);
    pRelease_Slider->setValue(releaseTimeSeconds);
}

void SynthParameters_AmpEG::sliderValueChanged(Slider* slider)
{
    float newValue = (float)slider->getValue();
    if (slider == pAttack_Slider) *pAttack_Param = newValue;
    else if (slider == pDecay_Slider) *pDecay_Param = newValue;
    else if (slider == pSustain_Slider) *pSustain_Param = 0.01f * newValue;
    else if (slider == pRelease_Slider) *pRelease_Param = newValue;
    synth.soundParameterChanged();
}

void SynthParameters_AmpEG::sliderDragStarted(Slider* slider)
{
    if (slider == pAttack_Slider) pAttack_Param->beginChangeGesture();
    else if (slider == pDecay_Slider) pDecay_Param->beginChangeGesture();
    else if (slider == pSustain_Slider) pSustain_Param->beginChangeGesture();
    else if (slider == pRelease_Slider) pRelease_Param->beginChangeGesture();
}

void SynthParameters_AmpEG::sliderDragEnded(Slider* slider)
{
    if (slider == pAttack_Slider) pAttack_Param->endChangeGesture();
    else if (slider == pDecay_Slider) pDecay_Param->endChangeGesture();
    else if (slider == pSustain_Slider) pSustain_Param->endChangeGesture();
    else if (slider == pRelease_Slider) pRelease_Param->endChangeGesture();
}

void SynthParameters_AmpEG::putToXml(XmlElement& xml)
{
    xml.setAttribute(attack_Name, attackTimeSeconds);
    xml.setAttribute(decay_Name, decayTimeSeconds);
    xml.setAttribute(sustain_Name, sustainLevel);
    xml.setAttribute(release_Name, releaseTimeSeconds);
}

void SynthParameters_AmpEG::getFromXml(XmlElement* pXml)
{
    *pAttack_Param = (float)pXml->getDoubleAttribute(attack_Name);
    *pDecay_Param = (float)pXml->getDoubleAttribute(decay_Name);
    *pSustain_Param = (float)(pXml->getDoubleAttribute(sustain_Name));
    *pRelease_Param = (float)(pXml->getDoubleAttribute(release_Name));
}
