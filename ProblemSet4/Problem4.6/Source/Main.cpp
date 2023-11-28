/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

// Function prototypes
int readSoundFile(juce::AudioBuffer<float>& buffer);
int writeSoundFile(juce::AudioBuffer<float>& buffer, float sampleRate);
void process(juce::AudioBuffer<float>& buffer, int keepBits);
short keep_bits_from_16(short input, int keepBits);

//==============================================================================
int main()
{
    // Read the source file into a buffer for processing
    juce::AudioBuffer<float> buffer;
    if (!readSoundFile(buffer)) return 1;

    // Create a buffer for processing audio data
    int keepBits;
    std::cout << "Enter the number of bits to keep (1-16): ";
    std::cin >> keepBits;

    if (keepBits < 1 || keepBits > 16)
    {
        std::cout << "Invalid number of bits. Must be in the range of 1 to 16." << std::endl;
        return 1;
    }

    process(buffer, keepBits);

    // Write the processed audio data to a sound file
    if (writeSoundFile(buffer, buffer.getNumSamples())) return 1;
}

void process(juce::AudioBuffer<float>& buffer, int keepBits)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float currentSample = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, static_cast<float>(keep_bits_from_16(static_cast<short>(currentSample * 32767.0f), keepBits)) / 32767.0f);
        }
    }
}

int readSoundFile(juce::AudioBuffer<float>& buffer)
{
//    // Prompt for the input file path
//    std::cout << "Enter the path to the wave file to process: ";
//    std::string filePath;
//    std::getline(std::cin, filePath);
//    juce::File file(filePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    //open the input file
    juce::File file("sine.wav");
    
    //create unique reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    
    // Check if the reader was created
    if (reader)
    {
        // Set the size of buffer
        buffer.setSize(reader->numChannels, static_cast<int>(reader->lengthInSamples));

        // Read the samples from the file into the buffer
        bool success = reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Return 0 if reading was successful
        if (success) return 0;

        std::cout << "Failed to copy samples into the buffer from the source wave file." << std::endl;
        return 1;
    }

    std::cout << "Failed to read the source wave file." << std::endl;
    return 1;
}

int writeSoundFile(juce::AudioBuffer<float>& buffer, float sampleRate)
{
//    // Prompt for the output file path
//    std::cout << "Enter the path to the AIFF file to save: ";
//    std::string filePath;
//    std::getline(std::cin, filePath);
//    juce::File file(filePath);

    // Create an audio format manager and register AIFF format
    juce::AudioFormatManager formatManager;
    formatManager.registerFormat(new juce::AiffAudioFormat(), true);
    
    //save the output file
    juce::File outputfile("reduct.aiff");

    // Create a unique_ptr for the writer (AIFF format)
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("aiff")
        ->createWriterFor(new juce::FileOutputStream(outputfile),
            sampleRate,
            buffer.getNumChannels(),
            24,
            {},
            0));

    // Check if the writer was created
    if (writer)
    {
        // Write the samples to the output file
        bool success = writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        if (success) return 0;

        std::cout << "Failed to write samples into the buffer to the destination AIFF file." << std::endl;
        return 1;
    }

    std::cout << "Failed to create a writer for the destination file." << std::endl;
    return 1;
}

short keep_bits_from_16(short input, int keepBits)
{
    return (input & (-1 << (16 - keepBits)));
}
