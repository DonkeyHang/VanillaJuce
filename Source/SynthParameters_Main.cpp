#include "SynthParameters.h"
#include "Synth.h"

// Names are symbolic names used to tag AudioParameter objects and XML attributes
// Labels are human-friendly identifiers for use in GUIs
const String SynthParameters_Main::masterLevel_Name = "masterLevel";
const String SynthParameters_Main::masterLevel_Label = TRANS("Master Volume");
const String SynthParameters_Main::pitchBendUpSemitones_Name = "pitchBendUpSemitones";
const String SynthParameters_Main::pitchBendUpSemitones_Label = TRANS("P.Bend up (semi)");
const String SynthParameters_Main::pitchBendDownSemitones_Name = "pitchBendDownSemitones";
const String SynthParameters_Main::pitchBendDownSemitones_Label = TRANS("P.Bend down (semi)");

SynthParameters_Main::SynthParameters_Main (Synth& s)
    : synth(s)
{
    // Set default values
    masterLevel = 0.15f;
    pitchBendUpSemitones = 2;
    pitchBendDownSemitones = 2;

    // Create parameter objects. The plugin processor will take ownership of these, so this
    // object need not worry about deleting them later.
    pMasterLevel_Param = new AudioParameterFloat(masterLevel_Name, masterLevel_Label, 0.0f, 1.0f, masterLevel);
    pPitchBendUpSemitones_Param = new AudioParameterInt(pitchBendUpSemitones_Name, pitchBendUpSemitones_Label, 0, 12, pitchBendUpSemitones);
    pPitchBendDownSemitones_Param = new AudioParameterInt(pitchBendDownSemitones_Name, pitchBendDownSemitones_Label, 0, 12, pitchBendDownSemitones);
}

void SynthParameters_Main::AttachControls(Slider* pMasterLevelSlider,
                                            Slider* pPitchBendDownSemitonesSlider,
                                            Slider* pPitchBendUpSemitonesSlider)
{
    pMasterLevel_Slider = pMasterLevelSlider;
    pPitchBendDownSemitones_Slider = pPitchBendDownSemitonesSlider;
    pPitchBendUpSemitones_Slider = pPitchBendUpSemitonesSlider;
}

void SynthParameters_Main::UpdateWorkingValuesFromPluginParameters()
{
    masterLevel = *pMasterLevel_Param;
    pitchBendUpSemitones = pPitchBendUpSemitones_Param->get();
    pitchBendDownSemitones = pPitchBendDownSemitones_Param->get();
}

void SynthParameters_Main::UpdateControlsFromWorkingValues()
{
    pMasterLevel_Slider->setValue(10.0 * masterLevel);
    pPitchBendDownSemitones_Slider->setValue(pitchBendUpSemitones);
    pPitchBendUpSemitones_Slider->setValue(pitchBendDownSemitones);
}

void SynthParameters_Main::sliderValueChanged(Slider* slider)
{
    float newValue = (float)slider->getValue();
    if (slider == pMasterLevel_Slider) *pMasterLevel_Param = 0.1f * newValue;
    else if (slider == pPitchBendDownSemitones_Slider) *pPitchBendUpSemitones_Param = (int)newValue;
    else if (slider == pPitchBendUpSemitones_Slider) *pPitchBendDownSemitones_Param = (int)newValue;
    synth.soundParameterChanged();
}

void SynthParameters_Main::sliderDragStarted(Slider* slider)
{
    if (slider == pMasterLevel_Slider) pMasterLevel_Param->beginChangeGesture();
    else if (slider == pPitchBendDownSemitones_Slider) pPitchBendUpSemitones_Param->beginChangeGesture();
    else if (slider == pPitchBendUpSemitones_Slider) pPitchBendDownSemitones_Param->beginChangeGesture();
}

void SynthParameters_Main::sliderDragEnded(Slider* slider)
{
    if (slider == pMasterLevel_Slider) pMasterLevel_Param->endChangeGesture();
    else if (slider == pPitchBendDownSemitones_Slider) pPitchBendUpSemitones_Param->endChangeGesture();
    else if (slider == pPitchBendUpSemitones_Slider) pPitchBendDownSemitones_Param->endChangeGesture();
}

void SynthParameters_Main::putToXml(XmlElement& xml)
{
    xml.setAttribute(masterLevel_Name, masterLevel);
    xml.setAttribute(pitchBendUpSemitones_Name, pitchBendUpSemitones);
    xml.setAttribute(pitchBendDownSemitones_Name, pitchBendDownSemitones);
}

void SynthParameters_Main::getFromXml(XmlElement* pXml)
{
    *pMasterLevel_Param = (float)(pXml->getDoubleAttribute(masterLevel_Name));
    *pPitchBendUpSemitones_Param = pXml->getIntAttribute(pitchBendUpSemitones_Name);
    *pPitchBendDownSemitones_Param = pXml->getIntAttribute(pitchBendDownSemitones_Name);
}
