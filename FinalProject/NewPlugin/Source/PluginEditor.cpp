/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//======================= =======================================================
NewPluginAudioProcessorEditor::NewPluginAudioProcessorEditor (NewPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 500);
    
    //initialize the slider
    sizeSlider.setRange(0.0f, 100.0f, 1.0f);
    sizeSlider.setSliderStyle(juce::Slider::Rotary);
    sizeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 20, 10);
    sizeSlider.setTextValueSuffix(" Size");
    sizeSlider.setValue(100.0f);
    sizeSlider.setEnabled(true);
    sizeSlider.setBounds(100, 50, 20, getHeight() - 60);
    
    widthSlider.setRange(0.0f, 100.0f, 1.0f);
    widthSlider.setSliderStyle(juce::Slider::Rotary);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 20, 10);
    widthSlider.setTextValueSuffix(" Width");
    widthSlider.setValue(100.0f);
    widthSlider.setEnabled(true);
    widthSlider.setBounds(300, 50, 20, getHeight() - 60);
    
    dampSlider.setRange(0.0f, 100.0f, 1.0f);
    dampSlider.setSliderStyle(juce::Slider::Rotary);
    dampSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 20, 10);
    dampSlider.setTextValueSuffix(" Damp");
    dampSlider.setValue(100.0f);
    dampSlider.setEnabled(true);
    dampSlider.setBounds(500, 50, 20, getHeight() - 60);
    
    drywetSlider.setRange(0.0f, 100.0f, 1.0f);
    drywetSlider.setSliderStyle(juce::Slider::Rotary);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 20, 10);
    drywetSlider.setTextValueSuffix(" Dry/Wet");
    drywetSlider.setValue(100.0f);
    drywetSlider.setEnabled(true);
    drywetSlider.setBounds(700, 50, 20, getHeight() - 60);
    
    addAndMakeVisible(&sizeSlider);
    addAndMakeVisible(&widthSlider);
    addAndMakeVisible(&dampSlider);
    addAndMakeVisible(&drywetSlider);
}

NewPluginAudioProcessorEditor::~NewPluginAudioProcessorEditor()
{
}

//==============================================================================
void NewPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void NewPluginAudioProcessorEditor::resized()
{
    //...
}
