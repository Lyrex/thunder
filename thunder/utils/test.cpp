#include <iostream>
#include <chrono>

#include "string.hpp"

int main( int, char** )
{
	const std::string test_1{ "cddcddecce" };

	std::vector<std::string> res;

	auto start_time = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < 1000; i++)
		res = thunder::utils::string::between(test_1, "c", "c", true, true);

	auto end_time = std::chrono::high_resolution_clock::now();
	
	std::cout << "Found " << res.size() << " elements!\n";
	for (auto& element : res)
		std::cout << element.c_str() << "\n";
	std::cout << "thunder::utils::string::between took " << std::chrono::duration_cast<std::chrono::milliseconds>( end_time - start_time ).count() << "ms" << std::endl;

	std::cin.get();

	return 0;
}
