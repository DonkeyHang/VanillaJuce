#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthWaveform.h"

class Synth;

struct SynthParameters_Main : public Slider::Listener
{
    SynthParameters_Main(Synth& s);
    void AttachControls(Slider* pMasterLevelSlider,
        Slider* pPitchBendDownSemitonesSlider,
        Slider* pPitchBendUpSemitonesSlider);
    void UpdateWorkingValuesFromPluginParameters();
    void UpdateControlsFromWorkingValues();

    // Actual working parameter values
    float masterLevel;
    int pitchBendUpSemitones;
    int pitchBendDownSemitones;

    // Names are symbolic names used to tag AudioParameter objects and XML attributes
    // Labels are human-friendly identifiers for use in GUIs
    static const String masterLevel_Name, masterLevel_Label;
    static const String pitchBendUpSemitones_Name, pitchBendUpSemitones_Label;
    static const String pitchBendDownSemitones_Name, pitchBendDownSemitones_Label;

    // AudioParameter objects
    AudioParameterFloat* pMasterLevel_Param;
    AudioParameterInt* pPitchBendUpSemitones_Param;
    AudioParameterInt* pPitchBendDownSemitones_Param;

    // Slider::Listener methods
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

    // get/put XML
    void putToXml(XmlElement& xml);
    void getFromXml(XmlElement* xml);

private:
    // Reference back to Synth object, to allow change notifications
    Synth& synth;

    // References to controls linked to these parameters
    Slider* pMasterLevel_Slider;
    Slider* pPitchBendDownSemitones_Slider;
    Slider* pPitchBendUpSemitones_Slider;
};

struct SynthParameters_Osc : public ComboBox::Listener, public Slider::Listener
{
    SynthParameters_Osc(Synth& s);
    void AttachControls(ComboBox* pWaveform1Combo, ComboBox* pWaveform2Combo,
        Slider* pPitchOffsetSemitones1Slider, Slider* pPitchOffsetSemitones2Slider,
        Slider* pDetuneOffsetCents1Slider, Slider* pDetuneOffsetCents2Slider,
        Slider* pOscBlendSlider);
    void UpdateWorkingValuesFromPluginParameters();
    void UpdateControlsFromWorkingValues();

    // Actual working parameter values
    SynthWaveform waveform1, waveform2;
    int pitchOffsetSemitones1, pitchOffsetSemitones2;
    float detuneOffsetCents1, detuneOffsetCents2;
    float oscBlend;                        // [0.0, 1.0] relative osc1 level

    // Names are symbolic names used to tag AudioParameter objects and XML attributes
    // Labels are human-friendly identifiers for use in GUIs
    static const String waveform1_Name, waveform1_Label;
    static const String waveform2_Name, waveform2_Label;
    static const String pitchOffsetSemitones1_Name, pitchOffsetSemitones1_Label;
    static const String pitchOffsetSemitones2_Name, pitchOffsetSemitones2_Label;
    static const String detuneOffsetCents1_Name, detuneOffsetCents1_Label;
    static const String detuneOffsetCents2_Name, detuneOffsetCents2_Label;
    static const String oscBlend_Name, oscBlend_Label;

    // AudioParameter objects
    AudioParameterChoice *pWaveform1_Param, *pWaveform2_Param;
    AudioParameterInt *pPitchOffsetSemitones1_Param, *pPitchOffsetSemitones2_Param;
    AudioParameterFloat *pDetuneOffsetCents1_Param, *pDetuneOffsetCents2_Param;
    AudioParameterFloat* pOscBlend_Param;

    // ComboBox::Listener methods
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

    // Slider::Listener methods
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

    // get/put XML
    void putToXml(XmlElement& xml);
    void getFromXml(XmlElement* xml);

private:
    // Reference back to Synth object, to allow change notifications
    Synth& synth;

    // References to controls linked to these parameters
    ComboBox *pWaveform1_Combo, *pWaveform2_Combo;
    Slider *pPitchOffsetSemitones1_Slider, *pPitchOffsetSemitones2_Slider;
    Slider *pDetuneOffsetCents1_Slider, *pDetuneOffsetCents2_Slider;
    Slider* pOscBlend_Slider;
};

struct SynthParameters_AmpEG : public Slider::Listener
{
    SynthParameters_AmpEG(Synth& s);
    void AttachControls(Slider* pAttackSlider,
        Slider* pDecaySlider,
        Slider* pSustainSlider,
        Slider* pReleaseSlider);
    void UpdateWorkingValuesFromPluginParameters();
    void UpdateControlsFromWorkingValues();

    // Actual working parameter values
    float attackTimeSeconds;
    float decayTimeSeconds;
    float sustainLevel;               // [0.0, 1.0]
    float releaseTimeSeconds;

    // Names are symbolic names used to tag AudioParameter objects and XML attributes
    // Labels are human-friendly identifiers for use in GUIs
    static const String attack_Name, attack_Label;
    static const String decay_Name, decay_Label;
    static const String sustain_Name, sustain_Label;
    static const String release_Name, release_Label;

    // AudioParameter objects
    AudioParameterFloat* pAttack_Param;
    AudioParameterFloat* pDecay_Param;
    AudioParameterFloat* pSustain_Param;
    AudioParameterFloat* pRelease_Param;

    // Slider::Listener methods
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

    // get/put XML
    void putToXml(XmlElement& xml);
    void getFromXml(XmlElement* xml);

private:
    // Reference back to Synth object, to allow change notifications
    Synth& synth;

    // References to controls linked to these parameters
    Slider* pAttack_Slider;
    Slider* pDecay_Slider;
    Slider* pSustain_Slider;
    Slider* pRelease_Slider;
};
