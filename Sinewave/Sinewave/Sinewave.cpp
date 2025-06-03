#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  /* pi */
using namespace std;


double osc(double freq, double amp, double time) {
	double angle = fmod(2 * M_PI * freq * time, 2 * M_PI); //phase
	return amp * cos(angle);
}

int main() {

	const int N = 44100; // size/ sample rate, remember nyquist (highest frequency) is half sample rate
	const double Ts = 1 / 44100.0; // sampling period/ 1 second
	
	
	array<double, N> wave;

	for (int i = 0; i < N; i++) {
		double t = i * Ts; // current time
		
		wave[i] = osc(300, 0.5, t);
	}
}