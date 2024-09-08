#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe pmerge;
	if (argc == 1)
	{
		std::cout << "[ERROR] minimum 2 args is needed...." << std::endl;
		return 1;
	}
	pmerge.sort(argc, argv);
	return 0;
}