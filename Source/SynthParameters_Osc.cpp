#include "SynthParameters.h"
#include "Synth.h"

// Names are symbolic names used to tag AudioParameter objects and XML attributes
// Labels are human-friendly identifiers for use in GUIs
const String SynthParameters_Osc::waveform1_Name = "osc1Waveform";
const String SynthParameters_Osc::waveform1_Label = TRANS("Osc1 Waveform");
const String SynthParameters_Osc::waveform2_Name = "osc2Waveform";
const String SynthParameters_Osc::waveform2_Label = TRANS("Osc2 Waveform");
const String SynthParameters_Osc::pitchOffsetSemitones1_Name = "osc1PitchOffsetSemitones";
const String SynthParameters_Osc::pitchOffsetSemitones1_Label = TRANS("Pitch (semitones)");
const String SynthParameters_Osc::pitchOffsetSemitones2_Name = "osc2PitchOffsetSemitones";
const String SynthParameters_Osc::pitchOffsetSemitones2_Label = TRANS("Pitch (semitones)");
const String SynthParameters_Osc::detuneOffsetCents1_Name = "osc1DetuneOffsetCents";
const String SynthParameters_Osc::detuneOffsetCents1_Label = TRANS("Detune (cents)");
const String SynthParameters_Osc::detuneOffsetCents2_Name = "osc2DetuneOffsetCents";
const String SynthParameters_Osc::detuneOffsetCents2_Label = TRANS("Detune (cents)");
const String SynthParameters_Osc::oscBlend_Name = "oscBlend";
const String SynthParameters_Osc::oscBlend_Label = TRANS("Blend");

SynthParameters_Osc::SynthParameters_Osc (Synth& s)
    : synth(s)
{
    // Set default values
    waveform1.setToDefault();
    pitchOffsetSemitones1 = 0;
    detuneOffsetCents1 = 0.0f;
    waveform2.setToDefault();
    pitchOffsetSemitones2 = 0;
    detuneOffsetCents2 = 0.0f;
    oscBlend = 0.5f;

    // Create parameter objects. The plugin processor will take ownership of these, so this
    // object need not worry about deleting them later.
    pWaveform1_Param = new AudioParameterChoice(waveform1_Name, waveform1_Label, SynthWaveform::names, 0);
    pWaveform2_Param = new AudioParameterChoice(waveform2_Name, waveform2_Label, SynthWaveform::names, 0);
    pPitchOffsetSemitones1_Param = new AudioParameterInt(pitchOffsetSemitones1_Name, pitchOffsetSemitones1_Label, -24, 24, pitchOffsetSemitones1);
    pPitchOffsetSemitones2_Param = new AudioParameterInt(pitchOffsetSemitones2_Name, pitchOffsetSemitones2_Label, -24, 24, pitchOffsetSemitones2);
    pDetuneOffsetCents1_Param = new AudioParameterFloat(detuneOffsetCents1_Name, detuneOffsetCents1_Label, -50.0f, 50.0f, detuneOffsetCents1);
    pDetuneOffsetCents2_Param = new AudioParameterFloat(detuneOffsetCents2_Name, detuneOffsetCents2_Label, -50.0f, 50.0f, detuneOffsetCents2);
    pOscBlend_Param = new AudioParameterFloat(oscBlend_Name, oscBlend_Label, 0.0f, 1.0f, oscBlend);
}

void SynthParameters_Osc::AttachControls(
    ComboBox* pWaveform1Combo, ComboBox* pWaveform2Combo,
    Slider* pPitchOffsetSemitones1Slider, Slider* pPitchOffsetSemitones2Slider,
    Slider* pDetuneOffsetCents1Slider, Slider* pDetuneOffsetCents2Slider,
    Slider* pOscBlendSlider)
{
    pWaveform1_Combo = pWaveform1Combo;
    pWaveform2_Combo = pWaveform2Combo;
    pPitchOffsetSemitones1_Slider = pPitchOffsetSemitones1Slider;
    pPitchOffsetSemitones2_Slider = pPitchOffsetSemitones2Slider;
    pDetuneOffsetCents1_Slider = pDetuneOffsetCents1Slider;
    pDetuneOffsetCents2_Slider = pDetuneOffsetCents2Slider;
    pOscBlend_Slider = pOscBlendSlider;
}

void SynthParameters_Osc::UpdateWorkingValuesFromPluginParameters()
{
    waveform1.setFromName(pWaveform1_Param->getCurrentChoiceName());
    waveform2.setFromName(pWaveform2_Param->getCurrentChoiceName());
    pitchOffsetSemitones1 = pPitchOffsetSemitones1_Param->get();
    pitchOffsetSemitones2 = pPitchOffsetSemitones2_Param->get();
    detuneOffsetCents1 = *pDetuneOffsetCents1_Param;
    detuneOffsetCents2 = *pDetuneOffsetCents2_Param;
    oscBlend = *pOscBlend_Param;
}

void SynthParameters_Osc::UpdateControlsFromWorkingValues()
{
    waveform1.toComboBox(*pWaveform1_Combo);
    waveform2.toComboBox(*pWaveform2_Combo);
    pPitchOffsetSemitones1_Slider->setValue(pitchOffsetSemitones1);
    pPitchOffsetSemitones2_Slider->setValue(pitchOffsetSemitones2);
    pDetuneOffsetCents1_Slider->setValue(detuneOffsetCents1);
    pDetuneOffsetCents2_Slider->setValue(detuneOffsetCents2);
    pOscBlend_Slider->setValue(100.0 * oscBlend);
}

void SynthParameters_Osc::comboBoxChanged(ComboBox* combo)
{
    if (combo == pWaveform1_Combo)
    {
        pWaveform1_Param->beginChangeGesture();
        *pWaveform1_Param = combo->getSelectedItemIndex();
        pWaveform1_Param->endChangeGesture();
    }
    else
    {
        pWaveform2_Param->beginChangeGesture();
        *pWaveform2_Param = combo->getSelectedItemIndex();
        pWaveform2_Param->endChangeGesture();
    }
    synth.soundParameterChanged();
}

void SynthParameters_Osc::sliderValueChanged(Slider* slider)
{
    float newValue = (float)slider->getValue();
    if (slider == pPitchOffsetSemitones1_Slider) *pPitchOffsetSemitones1_Param = (int)newValue;
    else if (slider == pPitchOffsetSemitones2_Slider) *pPitchOffsetSemitones2_Param = (int)newValue;
    else if (slider == pDetuneOffsetCents1_Slider) *pDetuneOffsetCents1_Param = newValue;
    else if (slider == pDetuneOffsetCents2_Slider) *pDetuneOffsetCents2_Param = newValue;
    else if (slider == pOscBlend_Slider) *pOscBlend_Param = 0.01f * newValue;
    synth.soundParameterChanged();
}

void SynthParameters_Osc::sliderDragStarted(Slider* slider)
{
    if (slider == pPitchOffsetSemitones1_Slider) pPitchOffsetSemitones1_Param->beginChangeGesture();
    else if (slider == pPitchOffsetSemitones2_Slider) pPitchOffsetSemitones2_Param->beginChangeGesture();
    else if (slider == pDetuneOffsetCents1_Slider) pDetuneOffsetCents1_Param->beginChangeGesture();
    else if (slider == pDetuneOffsetCents2_Slider) pDetuneOffsetCents2_Param->beginChangeGesture();
    else if (slider == pOscBlend_Slider) pOscBlend_Param->beginChangeGesture();
}

void SynthParameters_Osc::sliderDragEnded(Slider* slider)
{
    if (slider == pPitchOffsetSemitones1_Slider) pPitchOffsetSemitones1_Param->endChangeGesture();
    else if (slider == pPitchOffsetSemitones2_Slider) pPitchOffsetSemitones2_Param->endChangeGesture();
    else if (slider == pDetuneOffsetCents1_Slider) pDetuneOffsetCents1_Param->endChangeGesture();
    else if (slider == pDetuneOffsetCents2_Slider) pDetuneOffsetCents2_Param->endChangeGesture();
    else if (slider == pOscBlend_Slider) pOscBlend_Param->endChangeGesture();
}

void SynthParameters_Osc::putToXml(XmlElement& xml)
{
    xml.setAttribute(waveform1_Name, waveform1.name());
    xml.setAttribute(waveform2_Name, waveform2.name());
    xml.setAttribute(pitchOffsetSemitones1_Name, pitchOffsetSemitones1);
    xml.setAttribute(pitchOffsetSemitones2_Name, pitchOffsetSemitones2);
    xml.setAttribute(detuneOffsetCents1_Name, detuneOffsetCents1);
    xml.setAttribute(detuneOffsetCents2_Name, detuneOffsetCents2);
    xml.setAttribute(oscBlend_Name, oscBlend);
}

void SynthParameters_Osc::getFromXml(XmlElement* pXml)
{
    SynthWaveform wf;
    wf.setFromName(pXml->getStringAttribute(waveform1_Name));
    *pWaveform1_Param = wf.getIndex();
    wf.setFromName(pXml->getStringAttribute(waveform2_Name));
    *pWaveform2_Param = wf.getIndex();
    *pPitchOffsetSemitones1_Param = pXml->getIntAttribute(pitchOffsetSemitones1_Name);
    *pPitchOffsetSemitones2_Param = pXml->getIntAttribute(pitchOffsetSemitones2_Name);
    *pDetuneOffsetCents1_Param = (float)(pXml->getDoubleAttribute(detuneOffsetCents1_Name));
    *pDetuneOffsetCents2_Param = (float)(pXml->getDoubleAttribute(detuneOffsetCents2_Name));
    *pOscBlend_Param = (float)(pXml->getDoubleAttribute(oscBlend_Name));
}
