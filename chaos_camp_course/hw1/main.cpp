#include <iostream> 
#include <thread>
#include <condition_variable>
#include <math.h>

// https://github.com/ToruNiina/pnm
#include "pnm.hpp"

#define PROGRESS_BAR_LENGTH 40

int num_threads;
int img_size;
int img_width, img_height;
int batch_size;

int num_steps;

// all threads
std::thread **threads;

// an counter to check if all threads are ready and waiting
int waiting_threads_count;
// a condition variable for the main thread to be notidfied for ready and waiting threads
std::condition_variable main_cv;
std::mutex main_condition_mutex;

std::condition_variable threads_cv;
std::mutex threads_condition_mutex;

// determines if the worker threads should work or exit when woken by threads_cv
int running;
int current_step;

// a mutex for output
std::mutex out_mutex;

// the two buffers;
pnm::image<pnm::bit_pixel> img_1;
pnm::image<pnm::bit_pixel> img_2;

// standard double buffer pointers
auto* front_buff = &img_1;
auto* back_buff  = &img_2;

void worker(int thread_index) {
	// calcuate the batch of pixels the current thread has to process
	int min_index = thread_index * batch_size;
	int max_index = std::min((thread_index + 1) * batch_size, img_size - 1);

	for(int thread_step = 0; running; ++thread_step) {
		for(int i = min_index; i < max_index; ++i) {
			// compute the pixel coordinates
			int y = i / img_width;
			int x = i % img_width;

			// get the current pixel
			bool curr = front_buff->at(x, y).value;

			// check all neighbours
			int count = 0;
			if(x + 1 <  img_width                       ) count += front_buff->at(x + 1, y    ).value; // right
			if(                      y + 1 <  img_height) count += front_buff->at(x    , y + 1).value; // left
			if(x - 1 >= 0                               ) count += front_buff->at(x - 1, y    ).value; // down
			if(                      y - 1 >= 0         ) count += front_buff->at(x    , y - 1).value; // up
			if(x + 1 <  img_width && y + 1 <  img_height) count += front_buff->at(x + 1, y + 1).value; // down right
			if(x + 1 <  img_width && y - 1 >= 0         ) count += front_buff->at(x + 1, y - 1).value; // down left
			if(x - 1 >= 0         && y + 1 <  img_height) count += front_buff->at(x - 1, y + 1).value; // up right
			if(x - 1 >= 0         && y - 1 >= 0         ) count += front_buff->at(x - 1, y - 1).value; // up left

			// modify the result according to the rules
			if(curr) {
				if(count < 2 || count > 3) {
					curr = false;
				}
			} else { 
				if(count == 3) {
					curr = true;
				}
			}

			// write to the back buffer
			back_buff->raw_access(i) = curr;
		}

		// finished current work, so declare ready
		main_condition_mutex.lock();
		waiting_threads_count ++;
		main_condition_mutex.unlock();

		main_cv.notify_one();

		// wait for the main thread to signal that the thread should continue
		std::unique_lock<std::mutex> lk(threads_condition_mutex);
		threads_cv.wait(lk, [&] () {
			return thread_step < current_step;
		});
	}
}

// print for debugging purposes
void print_buffers() {
	out_mutex.lock();
	for(int y = 0; y < (int) front_buff->y_size(); ++y) {
		for(int x = 0; x < (int) front_buff->x_size(); ++x) {
			std::cout << ((*front_buff)[y][x].value ? "##" : "  ");
		}
		std::cout << std::endl; 
	}

	for(int y = 0; y < (int) front_buff->y_size(); ++y) {
		for(int x = 0; x < (int) front_buff->x_size(); ++x) {
			std::cout << ((*back_buff)[y][x].value ? "##" : "  ");
		}
		std::cout << std::endl; 
	}

	out_mutex.unlock();
}


int main(int argc, char** argv) {

	std::string in_file;
	std::string out_file;

	num_threads = std::thread::hardware_concurrency();
	int max_threads = num_threads;

	num_steps = 1;
	current_step = 0;
	if(argc < 3) {
		std::cerr << "insufficient number of arguments." << std::endl;
		exit(1);
	} else {
		in_file = argv[1];
		out_file = argv[2];
		if(argc >= 4) {
			try {
				num_steps = std::stoi(argv[3]);
			} catch(...) {
				std::cerr << "number of steps must be an integer." << std::endl;
				exit(1);
			}
			if(num_steps < 1) {
				std::cerr << "numver of steps must be at least 1." << std::endl;
				exit(1);
			}

			if(argc == 5) {
				try {
					num_threads = std::stoi(argv[4]);
				} catch(...) {
					std::cerr << "number of threads must be an integer." << std::endl;
					exit(1);
				}

				if(num_threads < 1) {
					std::cerr << "cannot use less than 1 thread!" << std::endl;
					exit(1);
				} else if(num_threads > max_threads) {
					std::cerr << "cannot use more than the max number of cores on this system: " << max_threads << std::endl;
					exit(1);
				}
			}
		}
	} 

	img_1 = pnm::read_pbm(in_file);
	img_2 = pnm::image<pnm::bit_pixel>(img_1.width(), img_1.height());

	img_width  = img_1.width();
	img_height = img_1.height();

	img_size = img_width * img_height;
	batch_size = (num_threads == 1) ? img_size : img_size / (num_threads-1);

	std::cout << std::fixed << std::setprecision(2);

	//std::cout << "image size: " << img_size << ", threads: " << num_threads << ", batch size: " << batch_size << std::endl;

	running = 1;
	threads = (std::thread**)malloc(sizeof(std::thread*) * num_threads);
	for(int i = 0; i < num_threads; i++) {
		threads[i] = new std::thread(worker, i);
	}

	int percent = num_steps / 100.;

	// one step is already done, so start at 1
	// the last iteration is only for telling the workers to stop with the last notify, but does an unneeded buffer swap
	for(int i = 1; i <= num_steps; i ++) {
		// wait for all the threads to finish (all threads increment waiting_threads_count)
		std::unique_lock<std::mutex> lk(main_condition_mutex);
		main_cv.wait(lk, [] () {
			return waiting_threads_count == num_threads;
		});

		// reset the count
		waiting_threads_count = 0;
		lk.unlock();

		if(percent == 0 || i % percent == 0) {
			double progress = i / (double)num_steps;
			out_mutex.lock();
			std::cout << "\r[";
			for(int j = 0; j < PROGRESS_BAR_LENGTH; ++j ) {
				std::cout << (progress * PROGRESS_BAR_LENGTH > j ? "#" : " "); 
			}
			std::cout << "]" << progress * 100 << "\%" << std::flush;
			out_mutex.unlock();
		}


		//sleep(1);

		// swap the buffers
		std::swap(front_buff, back_buff);

		threads_condition_mutex.lock();
		// in the last iteration running = 0
		running = (i != num_steps);
		// next frame is ready to be computed, so increment the counter
		++current_step;
		threads_condition_mutex.unlock();

		// wake up the threads to do work or exit
		threads_cv.notify_all();
	}


	// swap the buffers one additional time to neutralize the bonus swap that is done in the cycle
	std::swap(front_buff, back_buff);
	//print_buffers();

	// join all threads
	for(int i = 0; i < num_threads; i++) {
		threads[i]->join();
	}

	// write to output file
	pnm::write(out_file, *back_buff, pnm::format::ascii);

	std::cout << std::endl;


	// destroy threads and the array holding them
	for(int i = 0; i < num_threads; ++i) {
		delete threads[i];
	}
	delete threads;


	return 0;
}
