#pragma once

#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  /* pi */
namespace MyCompanyName {

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
		double mTs{0};
		double mAmp{0};
		double mPhase{0};
	};

}
