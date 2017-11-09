#pragma once

#include <string>
#include <chrono>
#include <iostream>

class ChronoTimer {
	const std::string name;
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
  public:
    explicit ChronoTimer(const std::string& name = "Unnamed")
		: name(name),
		start(std::chrono::high_resolution_clock::now()) {
	}
	~ChronoTimer() {
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
		std::cout << "Entity " << name << " died after " << elapsed.count() << " ms." << std::endl;
	}

	long long get_elapsed_time() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	}

	std::chrono::high_resolution_clock::time_point get_current_time() const{
		return std::chrono::high_resolution_clock::now();
	}

    std::chrono::duration<long long> one_second() const {
		return std::chrono::seconds(1);
	}
};
