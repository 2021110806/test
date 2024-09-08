#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "[ERROR] Invalid usage" << std::endl;
		return 1;
	}
	RPN rpn;
	rpn.play(argv[1]);
	return 0;
}