#include "SynthVoice.h"
#include <cmath>

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        // shifting up
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        // shifting down
        pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        // shifting up
        return pitchBend * mainParams.pitchBendUpSemitones * 100;
    }
    else
    {
        // shifting down
        return pitchBend * mainParams.pitchBendDownSemitones * 100;
    }
}

static double noteHz(int midiNoteNumber, double centsOffset)
{
    double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= std::pow(2.0, centsOffset / 1200);
    return hertz;
}

SynthVoice::SynthVoice(SynthParameters_Main& mp, SynthParameters_Osc& op, SynthParameters_AmpEG& aegp)
    : SynthesiserVoice()
    , mainParams(mp)
    , oscParams(op)
    , ampEgParams(aegp)
    , noteVelocity(0.0f)
    , pitchBend(0.0f)
    , osc1Level(0.0f)
    , osc2Level(0.0f)
    , tailOff(false)
{
}

// Set up voice according to current sound parameters and pitch bend
void SynthVoice::setup (bool pitchBendOnly)
{
    double sampleRateHz = getSampleRate();
    int midiNote = getCurrentlyPlayingNote();

    float masterLevel = float(noteVelocity * mainParams.masterLevel);
    double pbCents = pitchBendCents();

    double cyclesPerSecond = noteHz(midiNote + oscParams.pitchOffsetSemitones1, oscParams.detuneOffsetCents1 + pbCents);
    double cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc1.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        osc1.setWaveform(oscParams.waveform1);
        osc1Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc1Level.setValue(float(oscParams.oscBlend * masterLevel));
    }

    cyclesPerSecond = noteHz(midiNote + oscParams.pitchOffsetSemitones2, oscParams.detuneOffsetCents2 + pbCents);
    cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc2.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        osc2.setWaveform(oscParams.waveform2);
        osc2Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc2Level.setValue(float((1.0 - oscParams.oscBlend) * masterLevel));
    }

    if (!pitchBendOnly)
    {
        ampEG.attackSeconds = ampEgParams.attackTimeSeconds;
        ampEG.decaySeconds = ampEgParams.decayTimeSeconds;
        ampEG.sustainLevel = ampEgParams.sustainLevel;
        ampEG.releaseSeconds = ampEgParams.releaseTimeSeconds;
    }
}

void SynthVoice::soundParameterChanged()
{
    setup(false);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    ignoreUnused(midiNoteNumber);    // accessible as SynthesiserVoice::getCurrentlyPlayingNote()
    ignoreUnused(sound);

    tailOff = false;
    noteVelocity = velocity;

    double sampleRateHz = getSampleRate();
    setPitchBend(currentPitchWheelPosition);

    setup(false);
    ampEG.start(sampleRateHz);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    ignoreUnused(velocity);

    if (allowTailOff & !tailOff)
    {
        tailOff = true;
        ampEG.release();
    }
    else
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newValue)
{
    setPitchBend(newValue);
    setup(true);
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue)
{
    // nothing yet
    ignoreUnused(controllerNumber);
    ignoreUnused(newValue);
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        if (!ampEG.isRunning())
        {
            clearCurrentNote();
            break;
        }
        float aeg = ampEG.getSample();
        float osc = osc1.getSample() * osc1Level.getNextValue() + osc2.getSample() * osc2Level.getNextValue();
        float sample = aeg * osc;
        outputBuffer.addSample(0, startSample, sample);
        outputBuffer.addSample(1, startSample, sample);
        ++startSample;
    }
}
