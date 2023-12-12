/*
  ==============================================================================
 This is a Reverb plugin using DSP module-reverb.The name is "NewPlugin" For this plugin, I'm using APVTS(AusioProcessorValueTreeState)
 to synchronized parameters with the host application that is loading this plugin and with plugin GUI. This reverb
 has 4 parameters, they are size, damp, width and dry/wet. And also you can bypass the reverb effect by ticking
 the bypass.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class NewPluginAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    NewPluginAudioProcessor();
    ~NewPluginAudioProcessor() override;

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
    
    //==============================================================================
    using APVTS = juce::AudioProcessorValueTreeState;
    static APVTS::ParameterLayout createParameterLayout();
    
    //declare APVTS function
    APVTS apvts{*this, nullptr, "Parameters", createParameterLayout()};
    
private:
    
    juce::AudioProcessorValueTreeState parameters;
    //==============================================================================
    //create pointer for parametes
    juce::AudioParameterFloat* size { nullptr };
    juce::AudioParameterFloat* width { nullptr };
    juce::AudioParameterFloat* damp { nullptr };
    juce::AudioParameterFloat* drywet { nullptr };
    juce::AudioParameterBool* bypassed { nullptr };
    
    juce::dsp::AudioBlock<float> block;
    
    //the function to get the value of these parameters
    void updateReverbParams();
    
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters params;
    
    juce::UndoManager undoManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewPluginAudioProcessor)
};
