//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

#include "Osc.h"

using namespace Steinberg;

namespace MyCompanyName {
//------------------------------------------------------------------------
// FilterProcessor
//------------------------------------------------------------------------
FilterProcessor::FilterProcessor ():mOsc(44100,0.5)
{
	//--- set the wanted controller for our processor
	setControllerClass (kFilterControllerUID);
}

//------------------------------------------------------------------------
FilterProcessor::~FilterProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::process(Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

	if (data.inputParameterChanges)
	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
		for (int32 index = 0; index < numParamsChanged; index++)
		{
			if (auto* paramQueue = data.inputParameterChanges->getParameterData(index))
			{
				Vst::ParamValue value;
				int32 sampleOffset;
				int32 numPoints = paramQueue->getPointCount();
				switch (paramQueue->getParameterId())
				{
				case FilterParams::kParamGainId:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
						mGain = value;
					break;

				case FilterParams::kParamCutOffId:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
						mCutOff = value;
					break;
				}
			}
		}
	}

	if (data.numInputs == 0 || data.numSamples == 0){
		return kResultOk;
}
	//--- Here, you have to implement your processing
	int32 numChannels = data.inputs[0].numChannels;

	//---get audio buffers using helper-functions(vstaudioprocessoralgo.h)-------------
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
	void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

	// Here could check the silent flags
	if (data.inputs[0].silenceFlags != 0)
	{
		// mark output silence too
		data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		// the plug-in has to be sure that if it sets the flags silence that the output buffer are clear
		for (int32 i = 0; i < numChannels; i++)
		{
			// do not need to be cleared if the buffers are the same (in this case input buffer are
			 // already cleared by the host)
			if (in[i] != out[i])
			{
				memset(out[i], 0, sampleFramesSize);
			}
		}
		// nothing to do at this point
		return kResultOk;
	}
	// now we will produce the output
	// mark our outputs has not silent
	data.outputs[0].silenceFlags = 0;

	// for each channel (left and right)
	for (int32 i = 0; i < 1; i++)
	{
		int32 samples = data.numSamples;
		Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
		Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
		Vst::Sample32 tmp;
		// for each sample in this channel
		while (--samples >= 0)
		{
			// apply gain
			/*float a1 = mCutOff;
			float b0 = 1 - a1;
			float x = (*ptrIn++);
			float y = b0 * x + a1 * mY1;
			mY1 = y;
			(*ptrOut++) = y*mGain;*/

			(*ptrOut++)=mOsc.process(200+mCutOff*500);

			
		}


	}

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	mOsc = SineOsc(newSetup.sampleRate, 0.5);

	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API FilterProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
