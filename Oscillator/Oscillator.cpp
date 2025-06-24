// Oscillator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//This program creates an oscillator for use in DSP

//A sinusoid is expressed as x(t)=Amplitude*Cosine(radian*time+initial phase)

//x(t)=Acos(2*pi*frequency+phase)

#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  //defines pi
using namespace std;

class SineOsc {
public:
	SineOsc(double sampleRate, double amplitude)
	{
		mTs = 1 / sampleRate;
		mAmp = amplitude;
	}
	double process(double freq) {
		double newPhase = mPhase + freq * 2 * M_PI * mTs;
		mPhase = fmod(newPhase, 2 * M_PI);
		return mAmp * cos(mPhase);
	}
private:
	double mTs;
	double mAmp;
	double mPhase;
};

int main() {
	const int N = 44100; // size
	const double Ts = 1 / 44100.0; // sampling period
	double freq = 100; // frequency
	const double A = 0.5; // amplitude

	double Fs = freq;

	array<double, N> wave;

	SineOsc sine(freq, A);

	for (int i = 0; i < N; i++) {
		wave[i] = sine.process(freq);
		freq = freq + 0.1;
	}

}
