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
class ReverbAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    ReverbAudioProcessorEditor (ReverbAudioProcessor&);
    ~ReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //The silder listener to the slider
    void sliderValueChanged(juce::Slider *slider) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbAudioProcessor& audioProcessor;
    
    
    juce::Slider decay;
    juce::Slider size;
    juce::Slider width;
    juce::Slider drywet;
    
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeAttachment;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
