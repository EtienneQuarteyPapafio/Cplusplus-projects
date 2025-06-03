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



int64_t WavtoBuffer(wav_hdr wavHeader) {

		//Read the data

		uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;
		//Number of bytes per sample
		uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample;
		//How many samples are in the wav file?

		int64_t wavSoundData1 = bytesPerSample * numSamples; //Find right Buffer size.

		cout << "Buffer size is " << wavSoundData1 << endl;

		vector<int8_t> buffer(wavSoundData1);

		return wavSoundData1;

	}






int main(int argc, char* argv[])
{
	wav_hdr wavHeader;

	string fileName;

	string wavAppend = ".wav";

	//creates a object type of wav_hdr, named wavHeader
	int headerSize = sizeof(wav_hdr), filelength = 0; //creates three int variables

	cout << "Enter wav name"<<endl;

	cin >> fileName;

	string firstfile = fileName + wavAppend;

	const char* filePath; //creates a constant pointer to the file path of the directory which cant be changed

	cout << "\nreading files" << endl;

	filePath = firstfile.c_str();

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


	if (bytesRead > 0)
	{
		cout << "DATA OF " << firstfile << endl;

		//Read the data

		uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;
		//Number of bytes per sample
		uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample;
		//How many samples are in the wav file?

		int64_t wavSoundData1 = WavtoBuffer(wavHeader);


		cout<< "Buffer size is " << wavSoundData1 << endl;

		vector<int8_t> buffer(wavSoundData1);

		wavFile.read(reinterpret_cast<char*>(buffer.data()), numSamples * bytesPerSample); //num of samples is the index,data is bytes 


		wavFile.close();

		


		return 0;
	}
}
