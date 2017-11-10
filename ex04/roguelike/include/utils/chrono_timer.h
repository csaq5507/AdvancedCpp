#ifndef ROGUELIKE_CCHRONO_UTILS_H_
#define ROGUELIKE_CCHRONO_UTILS_H_

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

    std::chrono::duration<long long> seconds(int seconds) const {
		return std::chrono::seconds(seconds);
	}

	std::chrono::duration<long int,std::ratio<1, 1000> > milliseconds(int milliseconds) const {
		return std::chrono::milliseconds(milliseconds);
	}
};

#endif //ROGUELIKE_CCHRONO_UTILS_H_