/*
  ==============================================================================
 This is a Reverb plugin using DSP module-reverb. The name is "NewPlugin"For this plugin, I'm using APVTS(AusioProcessorValueTreeState)
 to synchronized parameters with the host application that is loading this plugin and with plugin GUI. This reverb
 has 4 parameters, they are size, damp, width and dry/wet. And also you can bypass the reverb effect by ticking
 the bypass.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout NewPluginAudioProcessor::createParameterLayout()
{
    APVTS::ParameterLayout layout;
    using namespace juce;
    
    //create the parameters for reverb
    layout.add(std::make_unique<juce::AudioParameterFloat>("Size", "size", NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 50.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("Width", "width", NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 20.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("Damp", "damp", NormalisableRange<float>(0.0f, 100.0f, 0.1f, 1.0f), 20.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("Dry/Wet", "drywet", NormalisableRange<float>(0.0f, 100.0f, 1.0f, 1.0f), 50.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("Bypassed", "bypassed", false));

    return layout;
}
//==============================================================================
NewPluginAudioProcessor::NewPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
parameters (*this, &undoManager, "Parameters", createParameterLayout())
{
    //cast parameters to correct type
    size = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("Size"));
    jassert(size != nullptr);
    
    width = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("Width"));
    jassert(width != nullptr);
    
    damp = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("Damp"));
    jassert(damp != nullptr);
    
    drywet = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("Dry/Wet"));
    jassert(drywet!= nullptr);
    
    bypassed = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("Bypassed"));
    jassert(bypassed != nullptr);
}

NewPluginAudioProcessor::~NewPluginAudioProcessor()
{
    
}

//==============================================================================
const juce::String NewPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //declare processor spec for passing the audio into reverb
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    reverb.prepare(spec);
}

void NewPluginAudioProcessor::updateReverbParams()
{
    //get the value of parameters
    params.roomSize = size-> get() * 0.01f;
    params.damping = damp->get() * 0.01f;
    params.wetLevel = drywet->get() * 0.01f;
    params.dryLevel = 1.0f - drywet->get() * 0.01f;
    params.width = width->get() * 0.01f;
    
    reverb.setParameters(params);
 }

void NewPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    updateReverbParams();
    
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> ctx (block); //replacing the original audio in the buffer with processed audio
    
    ctx.isBypassed = bypassed->get();
    
    reverb.process(ctx);
}

//==============================================================================
bool NewPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewPluginAudioProcessor::createEditor()
{
//    return new NewPluginAudioProcessorEditor (*this, undoManager);
      return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void NewPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // save the plugin state data using memory blcok function
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void NewPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //check if tree is pulled out, once it's valid, we can replace the plugin state appropriately
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if(tree.isValid())
        apvts.replaceState(tree);
     
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewPluginAudioProcessor();
}
