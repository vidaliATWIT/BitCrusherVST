/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/

class BitCrush_Parameter : public juce::AudioProcessorParameter
{
public:

    float defaultValue{ 0 };
    float currentValue{ 0 };
    juce::String name;

    float getValue() const override
    {
        return currentValue;
    }

    void setValue(float newValue) override
    {
        currentValue = newValue;
    }

    float getDefaultValue() const override
    {
        return defaultValue;
    }

    juce::String getName(int maximumStringLength) const override
    {
        return name;
    }

    juce::String getLabel() const override
    {
        return getName(10);
    }

    float getValueForText(const juce::String& text) const override
    {
        return 1;
    }
};


class BitCrusherAudioProcessor : public juce::AudioProcessor
{
    juce::AudioBuffer<float> noiseBuffer, currentOutputBuffer;
    BitCrush_Parameter* rateRedux;
    BitCrush_Parameter* bitRedux;
public:
    //==============================================================================
    BitCrusherAudioProcessor();
    ~BitCrusherAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    juce::AudioDeviceManager deviceManager;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrusherAudioProcessor)
    

};
