#pragma once

#include <algorithm>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> info;
		bool	validateInputTxtFile(std::string &fileName);
		bool	validateCsvFile();
		bool 	validateDate(std::string s);
		bool	validateValue(std::string s);
		void 	csvToMap(std::stringstream &line);
		void	printResult(std::string date, float value);

	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void	excute(std::string &file);
		
};