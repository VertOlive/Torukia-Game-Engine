#include "torukia.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
	Torukia::TorukiaEngineUnitTest test(300,300,600,300);
	std::cout << test << std::endl;

	test.run_tests();

	return 0;
}