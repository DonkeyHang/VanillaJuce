#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

VanillaJuceAudioProcessor::VanillaJuceAudioProcessor()
    : mainParams(synth)
    , oscParams(synth)
    , ampEgParams(synth)
{
    addParameter(mainParams.pMasterLevel_Param);
    addParameter(mainParams.pPitchBendUpSemitones_Param);
    addParameter(mainParams.pPitchBendDownSemitones_Param);

    addParameter(oscParams.pOscBlend_Param);
    addParameter(oscParams.pWaveform1_Param);
    addParameter(oscParams.pPitchOffsetSemitones1_Param);
    addParameter(oscParams.pDetuneOffsetCents1_Param);
    addParameter(oscParams.pWaveform2_Param);
    addParameter(oscParams.pPitchOffsetSemitones2_Param);
    addParameter(oscParams.pDetuneOffsetCents2_Param);

    addParameter(ampEgParams.pAttack_Param);
    addParameter(ampEgParams.pDecay_Param);
    addParameter(ampEgParams.pSustain_Param);
    addParameter(ampEgParams.pRelease_Param);

    synth.addSound(new SynthSound());
    for (int i = 0; i < kNumberOfVoices; ++i)
        synth.addVoice(new SynthVoice(mainParams, oscParams, ampEgParams));
}

const String VanillaJuceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VanillaJuceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VanillaJuceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double VanillaJuceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

const String VanillaJuceAudioProcessor::getProgramName (int index)
{
    ignoreUnused(index);

    return programName;
}

void VanillaJuceAudioProcessor::changeProgramName (int index, const String& newName)
{
    ignoreUnused(index);

    programName = newName;
    sendChangeMessage();
}

void VanillaJuceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);

    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void VanillaJuceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void VanillaJuceAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

bool VanillaJuceAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* VanillaJuceAudioProcessor::createEditor()
{
    VanillaJuceAudioProcessorEditor* pEditor = new VanillaJuceAudioProcessorEditor(*this);

    mainParams.UpdateControlsFromWorkingValues();
    oscParams.UpdateControlsFromWorkingValues();
    ampEgParams.UpdateControlsFromWorkingValues();

    return pEditor;
}

void VanillaJuceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml = XmlElement(JucePlugin_Name);
    xml.setAttribute("programName", programName);
    mainParams.putToXml(xml);
    oscParams.putToXml(xml);
    ampEgParams.putToXml(xml);
    copyXmlToBinary(xml, destData);
}

void VanillaJuceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> pXml = getXmlFromBinary(data, sizeInBytes);
    programName = pXml->getStringAttribute("programName");
    mainParams.getFromXml(pXml); mainParams.UpdateWorkingValuesFromPluginParameters();
    oscParams.getFromXml(pXml); oscParams.UpdateWorkingValuesFromPluginParameters();
    ampEgParams.getFromXml(pXml); ampEgParams.UpdateWorkingValuesFromPluginParameters();

    VanillaJuceAudioProcessorEditor* pEditor = (VanillaJuceAudioProcessorEditor*)getActiveEditor();
    if (pEditor)
    {
        mainParams.UpdateControlsFromWorkingValues();
        oscParams.UpdateControlsFromWorkingValues();
        ampEgParams.UpdateControlsFromWorkingValues();
    }

}

void VanillaJuceAudioProcessor::setParameter(int parameterIndex, float newValue)
{
    AudioProcessor::setParameter(parameterIndex, newValue);

    mainParams.UpdateWorkingValuesFromPluginParameters();
    oscParams.UpdateWorkingValuesFromPluginParameters();
    ampEgParams.UpdateWorkingValuesFromPluginParameters();

    VanillaJuceAudioProcessorEditor* pEditor = (VanillaJuceAudioProcessorEditor*)getActiveEditor();
    if (pEditor)
    {
        mainParams.UpdateControlsFromWorkingValues();
        oscParams.UpdateControlsFromWorkingValues();
        ampEgParams.UpdateControlsFromWorkingValues();
    }

    synth.soundParameterChanged();
}

// This creates new instances of the plugin.
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VanillaJuceAudioProcessor();
}
