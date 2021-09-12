#include <SDL.h>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>

// This is a simple audio synthesizer
// has no keyboard input... maybe some day...
// 14.4.2021

using namespace std;

float PI = 3.14159265359;

struct MyAudioEngine {

	SDL_AudioSpec spec{};
	float pitch = 110;
	float volume = 0.05;
	long long time = 0;

	MyAudioEngine() {
		spec.freq = 96000;
		spec.format = AUDIO_F32SYS;
		spec.channels = 1;
		spec.samples = 4096;
		spec.userdata = this;
		spec.callback = 
			[] (void * param, Uint8* stream, int len) {
			((MyAudioEngine*) param)->callback((float*) stream, len / sizeof(float));
		};
		auto dev = SDL_OpenAudioDevice(nullptr, 0, &spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
		SDL_PauseAudioDevice(dev, 0);
	}

	float square_wave(double val) {
		return int(val) % 2 == 0. ? -0.5f : 0.5f;
	}
	
	float sine_wave(double val) {
		return sin(val * 2 * PI);
	}
	
	float triangle_wave(double val) {
		return asin(sine_wave(val));
	}
	
	float distorted_wave(double val) {
		float a = triangle_wave(val);
	
		float drive = 1;
		float blend = 0.1;
		
		a *= drive;
		return clamp((((2. / PI) * atan(a)) * blend) + (a * (1. / blend)) / 2, -0.5, 0.5);

	}

	float wave(long long time, int freq, int type) {
		double val = time * freq * 2 / 1e9;
		switch(type) {
			case 0: return sine_wave(val);
			case 1: return square_wave(val);
			case 2: return triangle_wave(val);
			case 3: return distorted_wave(val);
			default: return 0;
		}
	}
	
	int note_counter = 0;
	void callback(float* target, int num_samples) {
		//auto begin = chrono::high_resolution_clock::system_clock::now();
		//time = chrono::duration_cast<chrono::nanoseconds>(begin.time_since_epoch()).count();
		
		//const int song[] = {-5, -4, 2, -5, -4, 3, -5, -4, 4, -5, -4, 3, -5, -4, 2, 2, -5, -4, 2, -5, -4, 3, -5, -4, 4, -5, -4, 3, -5, -4, 2, 2, -5, -4, 2, -5, -4, 3, -5, -4, 4, -5, -4, 3, -5, -4, 2, 2, -5, -4, 2, -5, -4, 3, -5, -4, -2, -3, -5, -2, -3, -5, -2, -3, -5};

		
		//const int song[] = {-5, -5, 7, -5, -5, 5, -5, -5, 3, -5, -5, 1, -5, -5, 2, 3, -5, -5, 7, -5, -5, 5, -5, -5, 3, -5, -5, 1, 1};

		const int song[] = {-4, -2, -10, -2, 1, 3, 4, 3, 1, -2, -10, -10, -4, 1, -2, -10, -10};
		
		int note = song[note_counter % (sizeof(song) / sizeof(int))];

		long long time_per_sample = 1e9 / spec.freq;
		//cout << time / 1e9 * 110 << endl;

		for(int position = 0; position < num_samples; ++ position) {
			float sample = wave(time + position * time_per_sample, 110 * exp2(note / 12.), 3);
			if(note == -10) sample = 0;

			sample *= volume;
			target[position] = sample;
		}
		time += num_samples * time_per_sample;
		note_counter = time / 1e9 * 4;
	}
};


int main() {

	SDL_InitSubSystem(SDL_INIT_AUDIO);
	MyAudioEngine beeper;

	for(;;) {
		SDL_Delay(500);
	}
}
