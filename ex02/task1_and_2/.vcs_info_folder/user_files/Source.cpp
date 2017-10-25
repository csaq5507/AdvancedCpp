#include <iostream>
#include "backup_builder.h"


int main(int argv, char** args) {
	
	fs::path path = fs::current_path();
    backup_builder b(path);
    fs::path file_to_copy = "Source.cpp";
    b.initial_copy(file_to_copy);

	return 0;
}
