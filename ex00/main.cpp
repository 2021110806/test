#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange btc;
	if (argc != 2)
	{
		std::cerr << "Usage : ./btc filename" << std::endl;
		return 1;
	}
	std::string str(argv[1]);
	btc.excute(str);
}