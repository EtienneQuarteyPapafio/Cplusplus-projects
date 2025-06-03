/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <vector>

# define M_PI           3.14159265358979323846  /* pi */

class SineOsc {
public:
    SineOsc(double sampleRate)
    {
        mTs = 1.0 / sampleRate;

    }

    SineOsc() {
    }

    float process(int age) {

        float rate=1.5; //fixed rate

        if (age == 1) {
             depth= 5; } //25+-5

        if (age == 2) {
             depth = 10;// delay range of 25+-10
        }
        if (age == 3) {
             depth = 15; //gives delay range of 25+-15
        }
        //amplitude of effect
        
        double newPhase = (mPhase + rate * 2 * M_PI * mTs);
        mPhase = fmod(newPhase, 2 * M_PI);
        return depth * cos(mPhase)+25; //centre line 
    }
private:
    double mTs;
    double mPhase = 0;
    float depth;
};


class Filter {

public: Filter()=default;
    
    Filter(double sampleRate)
{

if (sampleRate <= 0) { sampleRate = 44100.0; }

    this->sampleRate = sampleRate;

 //equation here

    //butter worth implemented as biquad

    //y(z)=b0x[n]+b1x[n-1]+b2x[n-2]-a1y[n-1]-a2y[n-2]

    
    x=std::vector<float> (3,0.0f);

    y = std::vector<float>(3, 0.0f);//stores elements of vector, initialises all elements of vector to 0

    float c = 1 / tan(M_PI * cutoff / sampleRate);

    b0 = 1 / (1 + sqrt(2) * c + pow(c, 2)); //co-efficient pole 1

    b1 = 2 * b0;

    b2 = b0;

    a1 = 2*b0*(1-(pow(c, 2)));
    a2 = b0 * (1 - sqrt(2) * c + pow(c, 2));

    
    
    //process

    

}
      float read(float value) {

          x[2] = x[1];
          x[1] = x[0];
          
          x[0] = value;
          
          
          
          y[2] = y[1];
          y[1] = y[0];
          y[0] = b0 * x[0];
          
          y[0] = b0 * x[0] + b1 * x[1] + b2 * x[2] - a1 * y[1] - a2 * y[2];

          return y[0];

      }
private:
   

    std::vector<float> x;

    std::vector<float> y;

    double sampleRate = 44100.0;

    float b0, b1, b2, a1, a2;
    int cutoff = 18000;

    
};

class RingBuffer {
public:
    RingBuffer() = default;
    
    
    
    RingBuffer(double sampleRate) {
      

        if (sampleRate <= 0) { sampleRate = 44100.0; }

        this->sampleRate = sampleRate;

        size = static_cast<int>(sampleRate * maxDelay); //converts to milliseconds and to int

        mBuffer = std::vector<float>(size, 0.0f);//stores elements of vector, initialises all elements of vector to 0
        mWritePos = mBuffer.size()-1; //write pos

      
        

    }

    float read(int delay) {
        
        delay = delay * sampleRate / 1000;

        delay = std::min(delay, (int)(mBuffer.size() - 1)); //zero is a place

        int index = mWritePos - delay;
        

         if (index<0){
             index+=mBuffer.size();

            
         }


        

         return mBuffer[index];

    }
    void write(float val) {

        
            mBuffer[mWritePos] = val;
            mWritePos = (mWritePos + 1) % mBuffer.size();

        
       
    
    }

    void clear() {
        std::fill(mBuffer.begin(), mBuffer.end(), 0.0f);
        

    }
   

     float readInterp(int delay) {
       
        int samples = delay;

        float v1 = read(samples);
        float v2 = read(samples+1);
        
        float frac = delay-samples;

        return v1 + frac * (v2 - v1);

        
    }

private:
    std::vector<float> mBuffer;
    

    int mWritePos;

    double sampleRate;

    int size;

    float maxDelay = 1.2;

};







//==============================================================================
/**
*/
class Tape_DelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Tape_DelayAudioProcessor();
    ~Tape_DelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;







    juce::AudioProcessorValueTreeState state;

   

private:
    //==============================================================================

    double sampleRate;
    RingBuffer mBuffer[2];
    RingBuffer mod[2];
    SineOsc Osc[2];
    Filter LP[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tape_DelayAudioProcessor)
};
