#include <iostream>
#include <string>
#include <fstream> //needs to be here to open files for input and output
#include <cstdint>
#include <vector>

#include "WavHeader.h"

using namespace std;
using std::fstream;
using std::ifstream;
using std::ofstream;

// Function prototypes
int getFileSize(ifstream& inFile);

// find the file size

int getFileSize(ifstream& inFile)
{
	inFile.seekg(0, ios::end); //moves the get pointer to the end of the file
	int fileSize = inFile.tellg(); //gets size of current position
	inFile.seekg(0, ios::beg); //moves pointer back to beginning
	return fileSize;
}

int main(int argc, char* argv[])
{
	wav_hdr wavHeader;
	wav_hdr wavHeader2;


	//creates a object type of wav_hdr, named wavHeader
	int headerSize = sizeof(wav_hdr), filelength, filelength2 = 0; //creates three int variables

	const char* filePath; //creates a constant pointer to the file path of the directory which cant be changed
	const char* filePath2{}; //creates a constant to the second file path
	const char* filePath3{}; //creates a constant to the third file path



	string firstfile = "C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Audio_mix/1kHz.wav";
	string secondfile = "C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Audio_mix/10kHz.wav";
	string newfile = "C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Audio_mix/amen+sine.wav";


	cout << "\nreading files" << endl;

	filePath = firstfile.c_str();

	filePath2 = secondfile.c_str();

	filePath3 = newfile.c_str();

	//cout << filePath << ", " << filePath2 << endl;


	ifstream wavFile(filePath, ios::binary);

	
	



	if (!wavFile)
	{
		cerr << "Unable to open wave file: " << filePath << endl; //checks to make sure pointer is pointing to a file if not outputs standard error
		return 1;
	}

	//Read the first header


	wavFile.read(reinterpret_cast<char*>(&wavHeader), headerSize);

	filelength = getFileSize(wavFile);

	int bytesRead = filelength;


	cout << "Header Read " << bytesRead << " bytes." << endl;




	if (bytesRead > 0)
	{
		cout << "DATA OF " << firstfile << endl;

		//Read the data
		uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;
		//Number of bytes per sample
		uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample;
		//How many samples are in the wav file?

		int64_t wavSoundData1 = bytesPerSample * numSamples;

		cout << wavSoundData1<<endl;

		int64_t wavSoundData2 = bytesPerSample * numSamples;
		int64_t wavSoundData3 = bytesPerSample * numSamples;

		double fileSizeMB = static_cast<double>(filelength) / (1024 * 1024);
		double fileSizeKB = static_cast<double>(filelength) / 1024;

		cout << "File is " << filelength << " bytes" << endl;
		cout << "File is " << fileSizeKB << " kilobytes" << endl;
		cout << "File is " << fileSizeMB << " megabytes" << endl;
		cout << "Riff header is " << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
		cout << "Wave header is " << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
		cout << "FMT " << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
		cout << "Data size " << wavHeader.ChunkSize << endl;

		//Display sampling rate from header

		cout << "Sampling Rate " << wavHeader.SamplesPerSec << endl;
		cout << "Number of bits used " << wavHeader.bitsPerSample << endl;
		cout << "number of channels " << wavHeader.NumOfChan << endl;
		cout << "number of bytes per sec " << wavHeader.bytesPerSec << endl;
		cout << "data length " << wavHeader.Subchunk2Size << endl;
		cout << "audio format " << wavHeader.AudioFormat << endl;

		cout << "block align " << wavHeader.blockAlign << endl;
		cout << "Data string " << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;

		uint64_t maxSamples = wavHeader.Subchunk2Size / (wavHeader.bitsPerSample / 8);

		cout << "Maximum number of samples: " << maxSamples << endl;

		

		vector<int8_t> buffer(wavSoundData1);
		vector<int8_t> buffer2(wavSoundData2);
		vector<int8_t> buffer3(wavSoundData3);

		//reading Wavfile 2 


		ifstream wavFile2(filePath2, ios::binary);

		filelength2 = getFileSize(wavFile2);


		wavFile2.read(reinterpret_cast<char*>(&wavHeader2), headerSize);

		cout << "----------------------------------------------\n" << endl;
		cout << "DATA OF " << filePath2 << endl;

		//Read the data
		uint16_t bytesPerSample2 = wavHeader2.bitsPerSample / 8;
		//Number of bytes per sample
		uint64_t numSamples2 = wavHeader2.ChunkSize / bytesPerSample2;
		//How many samples are in the wav file?





		double fileSize2MB = static_cast<double>(filelength2) / (1024 * 1024);
		double fileSize2KB = static_cast<double>(filelength2) / 1024;

		cout << "File is " << filelength2 << " bytes" << endl;
		cout << "File is " << fileSize2KB << " kilobytes" << endl;
		cout << "File is " << fileSize2MB << " megabytes" << endl;
		cout << "Riff header is " << wavHeader2.RIFF[0] << wavHeader2.RIFF[1] << wavHeader2.RIFF[2] << wavHeader2.RIFF[3] << endl;
		cout << "Wave header is " << wavHeader2.WAVE[0] << wavHeader2.WAVE[1] << wavHeader2.WAVE[2] << wavHeader2.WAVE[3] << endl;
		cout << "FMT " << wavHeader2.fmt[0] << wavHeader2.fmt[1] << wavHeader2.fmt[2] << wavHeader2.fmt[3] << endl;
		cout << "Data size " << wavHeader2.ChunkSize << endl;

		//Display sampling rate from header

		cout << "Sampling Rate " << wavHeader2.SamplesPerSec << endl;
		cout << "Number of bits used " << wavHeader2.bitsPerSample << endl;
		cout << "number of channels " << wavHeader2.NumOfChan << endl;
		cout << "number of bytes per sec " << wavHeader2.bytesPerSec << endl;
		cout << "data length " << wavHeader2.Subchunk2Size << endl;
		cout << "audio format " << wavHeader2.AudioFormat << endl;

		cout << "block align " << wavHeader2.blockAlign << endl;
		cout << "Data string " << wavHeader2.Subchunk2ID[0] << wavHeader2.Subchunk2ID[1] << wavHeader2.Subchunk2ID[2] << wavHeader2.Subchunk2ID[3] << endl;

		uint64_t maxSamples2 = wavHeader2.Subchunk2Size / (wavHeader2.bitsPerSample / 8);

		cout << "Maximum number of samples: " << maxSamples2 << endl;


		//Creating the mixed file

		

		cout << filelength << " FL1\n" << filelength2 << " FL2 " << endl;

	

		ofstream wavFile3(filePath3, ios::binary);

		uint64_t currentSample = 0;
		uint64_t remainingSamples;

		

		//use smaller file for writing


		

		

			// Reset file pointer to the beginning of the original audio data

			//wavFile.seekg(headerSize);

			remainingSamples = maxSamples;


			wavFile.read(reinterpret_cast<char*>(buffer.data()), numSamples* bytesPerSample);

			wavFile2.read(reinterpret_cast<char*>(buffer2.data()), numSamples* bytesPerSample);


			for (int i = 0; i < (numSamples*bytesPerSample); i++)
			{
				buffer3[i] = (buffer[i] * 0.5) + (buffer2[i] * 0.5);
			}

			wavFile3.write(reinterpret_cast<char*>(&wavHeader), headerSize);

			wavFile3.write(reinterpret_cast<char*>(buffer3.data()), numSamples * bytesPerSample);


			wavFile.close();
			wavFile2.close();
			wavFile3.close();


		return 0;
	}
}


