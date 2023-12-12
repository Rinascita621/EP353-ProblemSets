/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewPluginAudioProcessorEditor (NewPluginAudioProcessor&);
    ~NewPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    NewPluginAudioProcessor& audioProcessor;
    
    //==============================================================================
    //initialize the slider and label
    juce::Slider sizeSlider;
    juce::Slider widthSlider;
    juce::Slider dampSlider;
    juce::Slider drywetSlider;
    juce::Label sizeLabel;
    juce::Label widthLabel;
    juce::Label dampLabel;
    juce::Label drywetLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewPluginAudioProcessorEditor)
};
