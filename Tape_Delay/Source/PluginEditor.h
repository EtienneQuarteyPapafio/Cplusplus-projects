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
class Tape_DelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Tape_DelayAudioProcessorEditor (Tape_DelayAudioProcessor&);
    ~Tape_DelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Tape_DelayAudioProcessor& audioProcessor;

    juce::Slider mixSlider, timeSlider, ageSlider;

    juce::AudioProcessorValueTreeState::SliderAttachment timeAttachement, ageAttachment, mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tape_DelayAudioProcessorEditor)
};
