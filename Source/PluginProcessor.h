#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"
#include "Synth.h"
#include "SynthSound.h"

class VanillaJuceAudioProcessor
    : public AudioProcessor
    , public ChangeBroadcaster
{
public:
    VanillaJuceAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setParameter(int parameterIndex, float newValue) override;

public:
    SynthParameters_Main mainParams;
    SynthParameters_Osc oscParams;
    SynthParameters_AmpEG ampEgParams;

private:
    static const int kNumberOfVoices = 16;

    Synth synth;
    String programName;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VanillaJuceAudioProcessor)
};
