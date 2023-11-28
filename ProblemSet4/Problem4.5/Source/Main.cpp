/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

// Function prototypes
int readSoundFile(juce::AudioBuffer<float>* buffer);
int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate);
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer);

// Constants
const float kThreshold = 0.02f; // Noise Gate Threshold

//==============================================================================
int main()
{
    // Read the source file into a buffer for processing
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = readSoundFile(&inBuffer);
    if (!sampleRate) return 1;

    // Create a buffer for processing audio data
    juce::AudioBuffer<float> outBuffer(inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // Process the audio data with noise gate
    process(inBuffer, &outBuffer);

    // Write the processed audio data to a sound file
    if (writeSoundFile(outBuffer, sampleRate)) return 1;
}

void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
    {
        const float* channelReadData = inBuffer.getReadPointer(channel);
        float* channelWriteData = outBuffer->getWritePointer(channel);

        for (int sample = 0; sample < inBuffer.getNumSamples(); ++sample)
        {
            // Apply noise gate
            if (std::abs(channelReadData[sample]) > kThreshold)
            {
                channelWriteData[sample] = channelReadData[sample];
            }
            else
            {
                // If the sample is below the threshold, set it to zero (mute)
                channelWriteData[sample] = 0.0f;
            }
        }
    }
}

int readSoundFile(juce::AudioBuffer<float>* buffer)
{
    // Prompt for the input file path
    std::cout << "Enter the path to the wave file to process: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file(filePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    // Check if the reader was created
    if (reader)
    {
        // Set the size of the buffer
        buffer->setSize(reader->numChannels, static_cast<int>(reader->lengthInSamples));

        // Read the samples from the file into the buffer
        bool success = reader->read(buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Return the sample rate if reading was successful
        if (success) return reader->sampleRate;

        std::cout << "Failed to copy samples into the buffer from the source wave file." << std::endl;
        return 0;
    }

    std::cout << "Failed to read the source wave file." << std::endl;
    return 0;
}

int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate)
{
    // Prompt for the output file path
    std::cout << "Enter the path to the wave file to save: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file(filePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the writer (WAV format)
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
        ->createWriterFor(new juce::FileOutputStream(file),
            sampleRate,
            buffer.getNumChannels(),
            16,
            {},
            0));

    // Check if the writer was created
    if (writer)
    {
        // Write the mixed samples to the output file
        bool success = writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        if (success) return 0;

        std::cout << "Failed to write samples into the buffer to the destination wave file." << std::endl;
        return 1;
    }

    std::cout << "Failed to create a writer for the destination file." << std::endl;
    return 1;
}
