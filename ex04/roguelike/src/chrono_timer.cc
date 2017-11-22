#include "utils/chrono_timer.h"

ChronoTimer::ChronoTimer(const std::string& name = "Unnamed") : name(name),	start(std::chrono::high_resolution_clock::now()) {}

ChronoTimer::~ChronoTimer() {
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
	std::cout << "Entity " << name << " died after " << elapsed.count() << " ms." << std::endl;
}

long long ChronoTimer::get_elapsed_time() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

std::chrono::high_resolution_clock::time_point ChronoTimer::get_current_time() const {
	return std::chrono::high_resolution_clock::now();
}

std::chrono::duration<long long> ChronoTimer::seconds(int seconds) const {
	return std::chrono::seconds(seconds);
}
std::chrono::duration<long int, std::ratio<1, 1000> > ChronoTimer::milliseconds(int milliseconds) const {
	return std::chrono::milliseconds(milliseconds);
}

void ChronoTimer::setTimerTo(long long elapsedTime) {
	auto diff = elapsedTime - this->get_elapsed_time();
	start += ChronoTimer::milliseconds(diff);
}

