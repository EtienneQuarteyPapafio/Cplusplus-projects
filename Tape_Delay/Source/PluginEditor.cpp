/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Tape_DelayAudioProcessorEditor::Tape_DelayAudioProcessorEditor(Tape_DelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), timeAttachement(p.state, "time", timeSlider),ageAttachment(p.state,"age",ageSlider),mixAttachment(p.state,"mix",mixSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    mixSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    timeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    ageSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

    for (auto* slider : {&mixSlider,&ageSlider,&timeSlider})
    {
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 30);
        addAndMakeVisible(slider);
    }

    setSize (400, 300);
}

Tape_DelayAudioProcessorEditor::~Tape_DelayAudioProcessorEditor()
{
}

//==============================================================================
void Tape_DelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));


    //g.setColour(juce::Colours::silver);

    juce::ColourGradient gradient((juce::Colours::silver), 0, 0,
        (juce::Colours::darkgrey), 400, 100,
        1);

    g.setGradientFill(gradient);

    g.fillRect(0, 0, 400, 400);

    //                 x y width height

    g.setColour (juce::Colours::black);
    g.fillRect(5, 25, 390, 2);

    g.setColour(juce::Colours::black);

    g.setFont (25.0f);
    g.drawFittedText ("RE-20", getLocalBounds(), juce::Justification::topLeft, 10);
    g.drawFittedText("Space Echo", getLocalBounds(), juce::Justification::topRight, 10);

    g.setColour(juce::Colours::darkolivegreen);

    g.fillRect(10, 50, 380, 200);

    g.setColour(juce::Colours::darkgreen);

    g.fillRect(15, 55, 370, 150);

    g.setColour(juce::Colours::black);

    g.setFont(25.0f);

    g.drawFittedText("Mix", getLocalBounds(), juce::Justification::centredTop,10);

    g.drawFittedText("Age", getLocalBounds(), juce::Justification::bottomLeft, 10);

    g.drawFittedText("Time", getLocalBounds(), juce::Justification::bottomRight, 10);


}

void Tape_DelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    juce::Rectangle<int>bounds = getLocalBounds();
    int margin = 20;

    juce::Rectangle<int> mixBounds = bounds.removeFromTop(getWidth() / 3);
    mixSlider.setBounds(mixBounds.reduced(margin));

    juce::Rectangle<int> knobsBounds = bounds.removeFromTop(getHeight() / 2);

    juce::Rectangle<int> ageBounds = knobsBounds.removeFromLeft (knobsBounds.getWidth() / 2);
    ageSlider.setBounds(ageBounds.reduced(margin));

    

    juce::Rectangle<int> timeBounds = knobsBounds.removeFromLeft(knobsBounds.getWidth());
    timeSlider.setBounds(timeBounds.reduced(margin));

    
}
