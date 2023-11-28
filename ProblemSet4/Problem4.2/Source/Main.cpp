/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

const float kSampleRate = 44100.0f;
const float ksec = 1.0f;
const float kNumFrames = kSampleRate * ksec;
const int knumChannels = 2;
const float kFrequency = 440.0f;
const float kAmplitude = 1.0f;
const float knumHarmonic = 16;
//==============================================================================
int main ()
{
    //ask user enter the path of triangle wave
    std::cout <<"Enter the path for saving the triangle wave. "<< std::endl;
    std::string path;
    std:getline(std::cin, path);
    
    //create a file object from path
    juce::File file(path);
     
    //create audio format manager and register the wav format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    //create a buffer to hold the samples
    juce::AudioBuffer<float> buffer(knumChannels, kNumFrames);
    buffer.clear();
                 
    //compute triangle wave
    for(int channel = 0; channel < knumChannels; channel++)
    {
        float *channelData = buffer.getWritePointer(channel);
        for(int sample = 0; sample < kNumFrames; sample++)
        {
            for(int harmonic = 1; harmonic <= knumHarmonic * 2; harmonic+=4)
            {
                float value = 0.0f;
                value += kAmplitude / (harmonic * harmonic) * std :: sin(2.0 * M_PI * (kFrequency * harmonic / kSampleRate) * sample);
                channelData[sample] = value;
            }
        }
    }
    
    //write it to the file
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")->createWriterFor(new juce::FileOutputStream(file), kSampleRate, knumChannels, 16, {}, 0));
    
    if(writer)
    {
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        std::cout <<"Failed to write."<< std::endl;
    }
    

    return 0;
}
