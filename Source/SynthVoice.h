#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthOscillator.h"
#include "SynthEnvelopeGenerator.h"
#include "SynthParameters.h"
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
private:
    // encapsulated objects which generate/modify sound
    SynthOscillator osc1, osc2;
    SynthEnvelopeGenerator ampEG;

    // current sound parameters
    SynthParameters_Main& mainParams;
    SynthParameters_Osc& oscParams;
    SynthParameters_AmpEG& ampEgParams;

    // voice properties remembered from startNote() call
    float noteVelocity;

    // dynamic properties of this voice
    float pitchBend;    // converted to range [-1.0, +1.0]
    LinearSmoothedValue<float> osc1Level, osc2Level;
    bool tailOff;

public:
    SynthVoice(SynthParameters_Main& mp, SynthParameters_Osc& op, SynthParameters_AmpEG& aegp);

    bool canPlaySound(SynthesiserSound* sound) override
    { return dynamic_cast<SynthSound*> (sound) != nullptr; }

    void soundParameterChanged();

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

private:
    void setPitchBend(int pitchWheelPosition);
    float pitchBendCents();
    void setup(bool pitchBendOnly);
};
