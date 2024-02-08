/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitCrusherAudioProcessorEditor::BitCrusherAudioProcessorEditor (BitCrusherAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    bitSlider.setRange(0.00001, 1000.0);
    bitSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    bitLabel.setText("Bit Reduction", juce::dontSendNotification);
    bitSlider.setValue(1000);
   
    bitSlider.addListener(this);

    sampleSlider.setRange(1, 1000);
    sampleSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    sampleSlider.setValue(100);

    sampleSlider.addListener(this);


    sampleLabel.setText("Sample Rate Reduction", juce::dontSendNotification);
    addAndMakeVisible(sampleLabel);
    addAndMakeVisible(sampleSlider);
    addAndMakeVisible(bitLabel);
    addAndMakeVisible(bitSlider);
    setSize (400, 300);

}

BitCrusherAudioProcessorEditor::~BitCrusherAudioProcessorEditor()
{
}

//==============================================================================
void BitCrusherAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BitCrusherAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    sampleLabel.setBounds(10, 10, 90, 20);
    sampleSlider.setBounds(100, 10, getWidth() - 110, 20);
    bitLabel.setBounds(10, 40, 90, 20);
    bitSlider.setBounds(100, 40, getWidth() - 110, 20);

}

void BitCrusherAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    if (slider == &sampleSlider)
        processor.getParameters()[0]->setValue(slider->getValue());
    else if (slider == &bitSlider)
        processor.getParameters()[1]->setValue(slider->getValue());
}
