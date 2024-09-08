#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange()
{
	
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this == &other)
		return *this;
	this -> info = other.info;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	
}

bool	BitcoinExchange::validateInputTxtFile(std::string &fileName)
{
	std::ifstream file(fileName.c_str()); //입력 받은 파일 이름에 대해서 스트림 개방
	std::string line;

	if (!file.is_open()) //파일 열어보기
	{
		std::cerr << "[ERROR] Can not open Inputfile" << std::endl;
		return false;
	}
	getline(file, line); //한줄 읽고
	if (line != "date | value") //타이틀 검사
	{
		std::cerr << "[ERROR] Invalid Title" << std::endl;
        return false;
	}
	while (getline(file, line)) {
        // 공백을 기준으로 날짜와 값을 나누기 위한 처리
        std::istringstream ss(line);
        std::string date, pipe;
        
        // "date | value" 형태가 맞는지 확인
        if (!getline(ss, date, ' ') || !getline(ss, pipe, ' ')) {
            std::cerr << "[ERROR] Bad input format" << std::endl;
            return false;
        }

        // 파이프("|") 기호가 있는지 확인
        if (pipe != "|") {
            std::cerr << "[ERROR] Missing separator" << std::endl;
            return false;
        }

        // 값 부분을 파싱
        double value;
        ss >> value;
        
        // 날짜와 값의 유효성 체크
        if (!validateDate(date)) {
            std::cerr << "[ERROR] Invalid date => " << date << std::endl;
            return false;
        }

        if (validateValue(ss.str()) && (value < 0 || value > 1000)) {
            std::cerr << "[ERROR] Invalid value" << std::endl;
            return false;
        }

		printResult(date, value);
    }

    return true; // 파일을 성공적으로 검증한 경우 true 반환
}
bool	BitcoinExchange::validateCsvFile()
{
	std::ifstream dataBase("data.csv"); //data.csv 파일 열기
	std::string line;
	size_t separator;

	if (!dataBase.is_open()) //열 수 있는지 확인 (파일이 없거나, 권한이 없거나..)
	{
		std::cerr << "[ERROR] Can not open data.csv" << std::endl;
		return false;
	}
	if (getline(dataBase, line).eof()) //한 줄 읽기, 타이틀 나올 것
	{
		std::cerr << "[ERROR] Empty csv file" << std::endl; 
		return false;
	}

    if (line != "date,exchange_rate")
    {
        std::cerr << "[ERROR] Invalid csv Title" << std::endl;
        return false;
    }

    while (getline(dataBase, line)) 
    {
		separator = line.find(','); //컴마의 위치 인덱스 반환
		std::string date = line.substr(0, separator); //컴마 전까지 짜르기
		if (validateDate(date) == false) //날짜 검증
		{
			std::cerr << "[ERROR] invalid date format" << std::endl;
			return false;
		}
		std::string value = line.substr(separator + 1); // ~부터 끝까지 반환
		if (validateValue(value) == false) //value 검증
		{
			std::cerr << "[ERROR] invalid value format" << std::endl;
			return false;
		}
		info[date] = std::strtod(value.c_str(), NULL);//날짜랑 밸류 묶어서 맵으로 넣는과정
    }
	return true;

}

void BitcoinExchange::csvToMap(std::stringstream &line)
{
	bool isKey = true;
	std::string key;
	std::string token;
	double		value;
	std::map<std::string, double> temp;
	

	while (getline(line, token, ',')) 
	{
		if (isKey)
		{
			key = token;
			isKey = false;
		}
		else
		{
			value = atof(token.c_str());
			isKey = true;
		}

	}
	this -> info.insert(std::make_pair(key, value));
};

bool BitcoinExchange::validateDate(std::string s)
{	
	int year, month, day;
	bool isLeap;
	std::string dateSplit;
	std::istringstream date(s);

	if (s.length() != 10)
		return false;
	while(getline(date, dateSplit, '-')) {
		
		std::istringstream(dateSplit) >> year;
		if (year < 1000 || year > 9999)
			return false;
		getline(date, dateSplit, '-');	
		std::istringstream(dateSplit) >> month;
		if (month < 1 || month > 12)
			return false;
		getline(date, dateSplit, '-');
		std::istringstream(dateSplit) >> day;
		
		if (day < 1 || day > 31)
			return false;
		if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
			return false;
		if (month == 2)
		{
			isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
			if ((isLeap && day > 29) || (!isLeap && day > 28))
        		return false;
		}
    }
	return true;
}

bool BitcoinExchange::validateValue(std::string s)
{
	if (s.length() > 10 && std::strtoll(s.c_str(), 0, 0) > 2147483647)
	{
		std::cerr << "[ERROR] overflow" << std::endl;
		return false;
	}
	for (size_t i = 0; i < s.length(); i++)
	{
		if ((!isdigit(s[i]) && s[i] != '.'))
		{
			std::cerr << "[ERROR] invalid value args";
			return false;
		}
	}
	double value = std::strtod(s.c_str(), NULL);
	if (s.c_str() == NULL)
		return false;
	if (value < 0)
		return false;        
	return true;
}

void BitcoinExchange::printResult(std::string date, float value)
{
	double res = 0;
	std::map<std::string, float>::const_iterator iter;

	iter = this -> info.find(date);
	if (iter != info.end())
		res = (iter->second) * value;
	else {
		iter = info.lower_bound(date);
		if (iter == info.begin()) {
			std::cout << "Error : invalid date" << std::endl;
			return;
		}
		--iter;
		res = (iter->second) * value;
	}
	std::cout << date << " => " << value << " = " << res << std::endl;
}

void BitcoinExchange::excute(std::string &file)
{
	if (validateCsvFile() == false)
		return ;
	if (validateInputTxtFile(file) == false)
		return;
}