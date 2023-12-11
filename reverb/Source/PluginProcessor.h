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
class ReverbAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ReverbAudioProcessor();
    ~ReverbAudioProcessor() override;

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
    juce::AudioProcessorValueTreeState& parameters;
    
    //==============================================================================
    std::atomic<float>* sizeParameter;
    std::atomic<float>* widthParameter;
    std::atomic<float>* decayParameter;
    std::atomic<float>* drywetParameter;

private:
    class myFDNReverb
    {
    public:
        myFDNReverb(juce::AudioProcessorValueTreeState& state, int numdelayLines, float initialDelay) : numdelayLines(numdelayLines), decay(initialDelay), delayLines(numdelayLines, std::vector<float>(maxDelaylength, 0.0f)), readPointers(numdelayLines, 0), writePointers(numdelayLines, 0), parameters(state)
        {
            parameters = state;
            initializeMixmatrix();
        }
        void process(juce::dsp::AudioBlock<float>& block)
        {
            // Apply FDN processing
            for (int c = 0; c < numdelayLines; ++c)
            {
                float output = 0.0f;
                for (int i = 0; i < numdelayLines; ++i)
                {
                    output += mixmatrix[c][i] * delayLines[i][readPointers[i]];
                }

                delayLines[c][writePointers[c]] = feedbackGain * output;
                ++writePointers[c] %= maxDelaylength;
            }

            ++inputPointer %= maxDelaylength;
        }
        void prepare(const juce::dsp::ProcessSpec& spec);

    private:
        static const int maxDelaylength = 1024;
        static const float feedbackGain;

        int numdelayLines, decay;
        std::vector<std::vector<float>> delayLines;
        std::vector<std::vector<float>> mixmatrix;
        int inputPointer = 0;
        std::vector<int> readPointers;
        std::vector<int> writePointers;
        
        juce::AudioProcessorValueTreeState parameters;

        void initializeMixmatrix()
        {
            mixmatrix.resize(numdelayLines, std::vector<float>(numdelayLines, 0.0f));

                // Populate the mix matrix with coefficients
                for (int i = 0; i < numdelayLines; ++i)
                {
                    for (int j = 0; j < numdelayLines; ++j)
                    {
                        // Adjust these coefficients based on your desired reverb characteristics
                        mixmatrix[i][j] = 0.5f / static_cast<float>(numdelayLines);
                    }
                }
        }
    };

    myFDNReverb FDNreverb;
    
//    //==============================================================================
//    juce::AudioProcessorValueTreeState::SliderAttachment sizeAttachment;
//    juce::AudioProcessorValueTreeState::SliderAttachment widthAttachment;
//    juce::AudioProcessorValueTreeState::SliderAttachment decayAttachment;
//    juce::AudioProcessorValueTreeState::SliderAttachment drywetAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbAudioProcessor)
};
