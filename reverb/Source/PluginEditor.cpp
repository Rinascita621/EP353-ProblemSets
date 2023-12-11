/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{ 
    setSize (900, 300);
    
    //set the basic config for sliders
    decay.setSliderStyle(juce::Slider::Rotary);
    decay.setRange(0.0, 5.0, 0.01);
    decay.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
    decay.setPopupDisplayEnabled(true, true, this, 2000);
    decay.setTextValueSuffix(" Decay");
    decay.setValue(1.5f);
    decay.setBounds(100, 100, 90, 100);
    
    size.setSliderStyle(juce::Slider::Rotary);
    size.setRange(0.0, 100.0, 1.0);
    size.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
    size.setPopupDisplayEnabled(true, true, this, 2000);
    size.setTextValueSuffix(" Size");
    size.setValue(50.0f);
    size.setBounds(300, 100, 90, 100);
    
    width.setSliderStyle(juce::Slider::Rotary);
    width.setRange(0.0, 1.0, 0.01);
    width.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
    width.setPopupDisplayEnabled(true, true, this, 2000);
    width.setTextValueSuffix(" Width");
    width.setValue(0.5f);
    width.setBounds(500, 100, 90, 100);
    
    drywet.setSliderStyle(juce::Slider::Rotary);
    drywet.setRange(0.0, 100.0, 1.0);
    drywet.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 0);
    drywet.setPopupDisplayEnabled(true, true, this, 2000);
    drywet.setTextValueSuffix(" Dry/Wet");
    drywet.setValue(50.0);
    drywet.setBounds(700, 100, 90, 100);
    
    // Attach the slider to the processor's parameter
//    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "DryWet", drywet);

    
    //add listeners to the slider
    decay.addListener(this);
    size.addListener(this);
    width.addListener(this);
    drywet.addListener(this);
    
    //add sliders to the editor
    addAndMakeVisible(decay);
    addAndMakeVisible(size);
    addAndMakeVisible(width);
    addAndMakeVisible(drywet);
}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::darkgreen);
    
    
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void ReverbAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
     
}

