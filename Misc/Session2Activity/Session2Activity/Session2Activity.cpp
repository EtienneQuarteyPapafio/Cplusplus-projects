// Session2Activity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <fstream> //needs to be here to open files for input and output
#include <cstdint>
#include <vector>
#include <math.h>

class SineOsc {
public:
	SineOsc(double sampleRate, double amplitude, double phase) {
		mTs = 1 / sampleRate;
		mAmp = amplitude;
		mPhase = phase;
	}
	double process(double freq) {
		double newPhase = mPhase + freq * 2 * M_PI * mTs;
		mPhase = fmod(newPhase, 2 * M_PI);
		return mAmp * (mPhase);
	}
private:
	double mTs;
	double mAmp;
	double mPhase;
};




typedef struct WAV_HEADER
{
	/* RIFF Chunk Descriptor */
	uint8_t RIFF[4]; // RIFF Header Magic header
	uint32_t ChunkSize; // RIFF Chunk Size
	uint8_t WAVE[4]; // WAVE Header

	/* "fmt" sub-chunk */
	uint8_t fmt[4]; // FMT header
	uint32_t Subchunk1Size; // Size of the fmt chunk
	uint16_t AudioFormat; // Audio format 1 = PCM, 6 = mulaw, 7 = alaw, 257 = IBM Mu - Law, 258 = IBM A - Law, 259 = ADPCM

	uint16_t NumOfChan; // Number of channels 1=Mono 2 = Stereo
	uint32_t SampleRate; // Sampling Frequency in Hz

	uint32_t byteRate; // bytes per second
	uint16_t blockAlign; // 2=16-bit mono, 4=16-bit stereo

	uint16_t bitsPerSample; // Number of bits per sample
	/* "data" sub-chunk */
	uint8_t Subchunk2ID[4]; // "data" string
	uint32_t Subchunk2Size; // Sampled data length

} wav_hdr; //stores all the info about the WAV 

using namespace std;

using std::fstream;
using std::ofstream;

int main(int argc, char* argv[])
{

	

	wav_hdr wavHeader;

	//creates a object type of wav_hdr, named wavHeader
	 //creates three int variables

	const char* filePath; //creates a constant pointer to the file path of the directory which cant be changed
	
	string firstfile = "C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Session2Activity/1kHz.wav";

	filePath = firstfile.c_str();

		

		wavHeader.RIFF[0] = 'R';
		wavHeader.RIFF[1] = 'I';
		wavHeader.RIFF[2] = 'F';
		wavHeader.RIFF[3] = 'F';

		


		wavHeader.WAVE[0] = 'W';
		wavHeader.WAVE[1] = 'A';
		wavHeader.WAVE[2] = 'V';
		wavHeader.WAVE[3] = 'E';

		

		wavHeader.fmt[0] = 'f';
		wavHeader.fmt[1] = 'm';
		wavHeader.fmt[2] = 't';
		wavHeader.fmt[3] = ' ';

		
		

		wavHeader.Subchunk1Size=16;
	
		wavHeader.AudioFormat = 1;

		wavHeader.NumOfChan=1;

		wavHeader.SampleRate = 44100;

		wavHeader.byteRate=(44100*16*1)/8;

		wavHeader.blockAlign=2;

		wavHeader.bitsPerSample=16;

		wavHeader.Subchunk2ID[0] = 'd';
		wavHeader.Subchunk2ID[1] = 'a';
		wavHeader.Subchunk2ID[2] = 't';
		wavHeader.Subchunk2ID[3] = 'a';

		int seconds = 4;

		wavHeader.Subchunk2Size = ((wavHeader.SampleRate*seconds)*wavHeader.NumOfChan * wavHeader.bitsPerSample) / 8;

		wavHeader.ChunkSize = wavHeader.Subchunk2Size + 36;


		//Read the data
		uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;
		//Number of bytes per sample
		uint64_t numSamples = wavHeader.Subchunk2Size / bytesPerSample;
		//How many samples are in the wav file?


		uint64_t wavSoundData1 = numSamples * bytesPerSample;

		vector<uint16_t> buffer(numSamples);

		ofstream wavFile(filePath, ios::binary);

		if (!wavFile) {
			cerr << "Error" << endl;
			return 1;
		}


		
		SineOsc sineWave(44100, 1, 0);
	

		double frequency = 500;
	

		

		for (size_t i = 0; i < numSamples; i++) {
			double t = static_cast<double>(i) / wavHeader.SampleRate;
			double result = sineWave.process(frequency);
	

			int16_t sample = static_cast<int16_t>(result);
			buffer[i] = sample;
			
		}


	/*	std::vector<double> y(buffer.size());
		double a1 = -0.99;
		double b0 = 1 - std::abs(a1);

		y[0] = b0 * buffer[0];
		for (int n = 1; n < buffer.size(); n++) {
			y[n] = b0 * buffer[n] - a1 * y[n - 1];
		}*/





		int headerSize = sizeof(wav_hdr);


		//sine 300 0.5 0.3 out.wav


		wavFile.write(reinterpret_cast<char*>(&wavHeader), headerSize);


		wavFile.write(reinterpret_cast<char*>(buffer.data()), numSamples * bytesPerSample);

		
		wavFile.close();

		return 0;
	}
