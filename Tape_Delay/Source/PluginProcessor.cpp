/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>


//==============================================================================
Tape_DelayAudioProcessor::Tape_DelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
#endif
    ),


    state(*this, nullptr, "STATE", {
    std::make_unique<juce::AudioParameterFloat>("mix", "Dry / Wet", 0.0f, 1.0f, 0.5f), //adding mix for dry an wet signal

    std::make_unique < juce::AudioParameterInt>("time", "Ms", 50, 1200, 600), //adding delay time

    std::make_unique<juce::AudioParameterInt>("age", "Age", 1, 3, 2) }) //adding feedback

    // param type , (name, id, min, max, default)
   
{
}

Tape_DelayAudioProcessor::~Tape_DelayAudioProcessor()
{
}

//==============================================================================
const juce::String Tape_DelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Tape_DelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Tape_DelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Tape_DelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Tape_DelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Tape_DelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Tape_DelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Tape_DelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Tape_DelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Tape_DelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Tape_DelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    this->sampleRate = sampleRate;



    for (int i = 0;i < 2;++i) {

        mBuffer[i] = RingBuffer(sampleRate);
        Osc[i] = SineOsc(sampleRate);
        mod[i] = RingBuffer(sampleRate);
        LP[i] = Filter(sampleRate); 
}
    
}

void Tape_DelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

    for(int i=0;i<2;++i)
    { 
     mBuffer[i].clear();
}}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Tape_DelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Tape_DelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    


   


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        
        float mix = state.getRawParameterValue("mix")->load();

       

        int age = state.getRawParameterValue("age")->load();

        
        
        

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            
            int time = state.getRawParameterValue("time")->load();

            float dry = channelData[i];



             /*float dry1=LP[channel].read(dry);

            mBuffer[channel].write(dry1);

            mBuffer[channel].write(dry);

            float delay = mBuffer[channel].read(time);

            float osc = Osc[channel].process(age);

            mod[channel].write(delay);

            float modified = mod[channel].read(osc);

            channelData[i] = (dry * (1 - mix)) + (modified * mix);*/



            mBuffer[channel].write(dry);


            float delay = mBuffer[channel].readInterp(time);

            float out= (dry * (1 - mix)) + (delay * mix);

            mBuffer[channel].write(out);

            channelData[i] = out;
           
            
            
            
            

           


            
        }
        
        
    }
}

//==============================================================================
bool Tape_DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Tape_DelayAudioProcessor::createEditor()
{
    return new Tape_DelayAudioProcessorEditor (*this);

    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Tape_DelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    if (auto xmlState = state.copyState().createXml())
        copyXmlToBinary(*xmlState, destData);
}

void Tape_DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        state.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Tape_DelayAudioProcessor();
}
