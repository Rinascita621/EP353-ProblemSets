/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

void applyEnvelope(juce::AudioBuffer<float>& buffer, float attackPercentage);

int main(){
    
    //prompt for the output audio file
    std::cout<<"Enter the path for the audio file to save: "<< std::endl;
    std::string destfilepath;
    std::getline(std::cin, destfilepath);
    
    //create a file object from path
    juce::File destFile(destfilepath);
    
    //create audio format manager and register basic format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    //open the input wav file
    juce::File inputFile("sine.wav");
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(inputFile));
    
    if(!reader){
        std::cout<<"Failed to open the input file. "<< std::endl;
        return 1;
    }
    
    //create audio buffer to hold the sample
    juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));
    
    //read the sample into buffer
    reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
    
    //apply the linear AD envelope to the buffer
    applyEnvelope(buffer, 0.1f);
    
    //create writer for output audio file
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")->createWriterFor(new juce::FileOutputStream(destFile), reader->sampleRate, reader->numChannels, reader->bitsPerSample, {}, 0));
    
    if(writer)
    {
        //write the enveloped samples to the output file
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        std::cout<<"Failed to create a writer for the output file."<< std::endl;
    }
    return 0;
}

void applyEnvelope(juce::AudioBuffer<float>& buffer, float attackPercentage){
    int attackSamples = static_cast<int>(attackPercentage * buffer.getNumSamples());
    
    //apply attack phase
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
        float* channelData = buffer.getWritePointer(channel);
        for(int i = 0; i < attackSamples; ++i){
            float envelopeValue = i / static_cast<float>(attackSamples);
            channelData[i] *= envelopeValue;
        };
    }
    
    //apply decay phase
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
        float* channelData = buffer.getWritePointer(channel);
        for(int i = attackSamples; i < buffer.getNumSamples(); ++i){
            float envelopeValue = 1.0f - (i - attackSamples) * (1.0f / buffer.getNumSamples()-attackSamples);
            channelData[i] *= envelopeValue;
        }
    }
}
