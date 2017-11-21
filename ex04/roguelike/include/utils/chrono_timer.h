#ifndef ROGUELIKE_CCHRONO_UTILS_H_
#define ROGUELIKE_CCHRONO_UTILS_H_

#include <string>
#include <chrono>
#include <iostream>

class ChronoTimer {
	const std::string name;
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
  public:
	  ChronoTimer(const std::string& name);
	  ~ChronoTimer();
	  long long get_elapsed_time() const;

	  std::chrono::high_resolution_clock::time_point get_current_time() const;
	  std::chrono::duration<long long> seconds(int seconds) const;
	  std::chrono::duration<long int, std::ratio<1, 1000> > milliseconds(int milliseconds) const;
};

#endif //ROGUELIKE_CCHRONO_UTILS_H_