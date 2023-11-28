/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

int main()
{
    std::cout <<"Enter the path to the source audio file: "<< std::endl;
    std::string sourcefilepath;
    std::getline(std::cin, sourcefilepath);
    
    std::cout <<"Enter the path to the reverse audio file: "<< std::endl;
    std::string destfilepath;
    std::getline(std::cin, destfilepath);
    
    //create a file object from the path
    juce::File sourcefile(sourcefilepath);
    juce::File destfile(destfilepath);
    
    //create an audio format manage and register the wave format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    //create a reader for the wave file
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(sourcefile));
    
    if(reader)
    {
        //create the buffer to hold the samples
        juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));
        
        //read the sample into the buffer
        reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        
        //iterate over each audio channel in the buffer
        for(int channel = 0; channel < reader->numChannels; channel++)
        {
            //reverse the audio data for current channel
            std::reverse(buffer.getWritePointer(channel), buffer.getWritePointer(channel) + reader->lengthInSamples);
        }
        
        //create unique pointer for the writer
        std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")->createWriterFor(new juce::FileOutputStream(destfile), reader->sampleRate, reader->numChannels, reader->bitsPerSample, {}, 0));
        
        if(writer)
        {
            //write a reversed sample to destination file
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
            std::cout <<"Reversed file saved to: "<< destfile.getFullPathName()<<std::endl;
        }
        else
        {
            std::cout <<"Failed to reverse."<< std::endl;
        }
    }
    
    return 0;
}
