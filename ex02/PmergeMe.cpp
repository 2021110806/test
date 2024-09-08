#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    oddVector = -1;
    oddDeque = -1;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void) other;
    return *this;
}

PmergeMe::~PmergeMe()
{

}

void	PmergeMe::sort(int argc, char **argv )
{
	if (!PmergeMe::validateUserInput(argc, argv))
        return ;
	PmergeMe::printBeforeSorting();
	PmergeMe::sortVector();
	PmergeMe::sortDeque();
}

void    PmergeMe::printBeforeSorting(void)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < inputVector.size(); i++)
    {
        std::cout << inputVector[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

template<typename T>
void    PmergeMe::printAfterSorting(clock_t start, const T& seq, std::string type)
{
    clock_t end = clock();
    double timePassedMs = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "After : ";
    for (size_t i = 0; i < seq.size(); i ++)
    {
        std::cout << seq[i] << " ";
    }
    std::cout << "\nTime to process a range of " << seq.size()  << " elements with " << type << " : " << timePassedMs << "ms" << std::endl;
}

bool    PmergeMe::validateUserInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        int length = std::strlen(argv[i]);
        for (int j = 0; j < length; j++)
        {
            if (!std::isdigit(argv[i][j]))
            {
                std::cout << "[ERROR] invalid argument" << std::endl;
                return false;
            }
        }
        if (std::strlen(argv[i]) > 10 || std::atoll(argv[i]) > 2147483647)
        {
            std::cout << "[ERROR] overflow" << std::endl;
            return false;
        }
        int num = atoi(argv[i]);
        if (num < 0)
        {
            std::cout << "[ERROR] cannot process negative number" << std::endl;
            return false;
        }
        std::vector<int>::iterator it;
        it = std::find(inputVector.begin(), inputVector.end(), num);
        if (it != inputVector.end())
        {
            std::cout << "[ERROR] cannot insert duplicate number" << std::endl;
            return false;
        }
        inputVector.push_back(num);
        inputDeque.push_back(num);
    }
        return true;
    }
    

template<typename T>
int PmergeMe::binarySearch(T& container, int target, int begin, int end)
{
	int mid;

	while (begin <= end)
	{
		mid = begin + (end - begin) / 2;
		if (target == container.at(mid))
			return (mid);

		if (target > container.at(mid))
			begin = mid + 1;
		else
			end = mid - 1;
	}
	if (target > container.at(mid))
		return (mid + 1);
	else
		return (mid);
}

int PmergeMe::getJacobsthal(int n)
{
    if (n== 0)
		return (0);
    if (n == 1)
		return (1);

    int prev1 = 0;
    int prev2 = 1;
    int current = 0;

    for (int i = 2; i <= n; ++i)
	{
        current = prev1 + 2 * prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return current;
}

void	PmergeMe::sortVector( void )
{
	clock_t start = clock();
	size_t	size = inputVector.size();
	if (size == 1)  
    {
        mainVector.push_back(inputVector[0]);
        PmergeMe::printAfterSorting(start, mainVector, "vector");
        return;
    }
	if (size % 2 == 1) 
	{
		oddVector = inputVector.back();
		inputVector.pop_back();
	}

	for (size_t i = 0; i < size - 1; i += 2) {
		
		if (inputVector[i] < inputVector[i + 1]) {
			
			mainVector.push_back(inputVector[i + 1]);
			subVector.push_back(inputVector[i]);
		} else {
			
			mainVector.push_back(inputVector[i]);
			subVector.push_back(inputVector[i + 1]);
		}
	}
	PmergeMe::mergeSort(mainVector, 0, mainVector.size() - 1);
    PmergeMe::mergeSort(subVector, 0, subVector.size() - 1);;
	mainVector.insert(mainVector.begin(), subVector[0]);
	PmergeMe::insertNumbersVector();
	PmergeMe::printAfterSorting(start, mainVector, "vector");
}


void	PmergeMe::sortDeque( void )
{
	clock_t start = clock();
	size_t	size = inputDeque.size();
	
    if (size == 1)  
    {
        mainDeque.push_back(inputDeque[0]);
        PmergeMe::printAfterSorting(start, mainDeque, "deque");
        return;
    }
	if (size % 2 == 1)
	{
		oddDeque = inputDeque.back();
		inputDeque.pop_back();
	}
	for (size_t i = 0; i < size - 1; i += 2) {

		if (inputDeque[i] < inputDeque[i + 1]) {
			mainDeque.push_back(inputDeque[i + 1]);
			subDeque.push_back(inputDeque[i]);
		} else {

			mainDeque.push_back(inputDeque[i]);
			subDeque.push_back(inputDeque[i + 1]);
		}
	}
	
	mergeSort(mainDeque, 0, mainDeque.size() - 1);
    mergeSort(subDeque, 0, subDeque.size() - 1);
	mainDeque.push_front(subDeque[0]);
	insertNumbersDeque();
	printAfterSorting(start, mainDeque, "deque");
}

template <typename T>
void PmergeMe::mergeSort( T& vector, int start, int end )
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    PmergeMe::mergeSort(vector, start, mid);
    PmergeMe::mergeSort(vector, mid + 1, end);

    std::vector<int> sorted;

    int left = start;
    int right = mid + 1;

    while (left <= mid && right <= end)
	{
        if (vector[left] <= vector[right]) {
            sorted.push_back(vector[left]);
            left++;
        } else {
            sorted.push_back(vector[right]);
            right++;
        }
    }
    while (left <= mid)
	{
        sorted.push_back(vector[left]);
        left++;
    }
    while (right <= end)
	{
        sorted.push_back(vector[right]);
        right++;
    }
    for (int i = start; i <= end; i++)
        vector[i] = sorted[i - start];
}

template<typename T>
void PmergeMe::jacobsthalInsertSequence(size_t maxSize, T& jacobsthalSequence)
{
	size_t	jacobIndex;
	int		index;

	index = 3;
	while ((jacobIndex = PmergeMe::getJacobsthal(index)) < maxSize) 
	{
		jacobsthalSequence.push_back(jacobIndex); 
		index++;
	}
}

void PmergeMe::getSubvectorInsertionPosition( void )
{
    if (this->subVector.empty())
        return;
    PmergeMe::jacobsthalInsertSequence(subVector.size(), this -> jacobsthalVectorSequence); 
    size_t lastPos = 1;
    size_t val = 1;
    for (size_t i = 0; i < this -> jacobsthalVectorSequence.size(); i++) 
    {
        val = jacobsthalVectorSequence.at(i); 
        subVectorInsertionPosition.push_back(val);

        size_t pos = val - 1; 
        while (pos > lastPos)
        {
            subVectorInsertionPosition.push_back(pos);
            pos--;
        }
        lastPos = val;
    }

    while (val++ < subVector.size()) 
        subVectorInsertionPosition.push_back(val);
}

void PmergeMe::insertNumbersVector( void )
{
	std::vector<int>::iterator	it;
    size_t	addCount = 0;

    PmergeMe::getSubvectorInsertionPosition();
	for (it = subVectorInsertionPosition.begin(); it < subVectorInsertionPosition.end(); it++)
    {
        int nbr = subVector.at(*it - 1); 
        size_t endPos = *it + addCount; 
        size_t pos = PmergeMe::binarySearch(mainVector, nbr, 0, endPos); 
        mainVector.insert(mainVector.begin() + pos, nbr); 
		addCount++;
    }
    if (oddVector != -1)
    {
        size_t nbr = oddVector;
        size_t pos = PmergeMe::binarySearch(mainVector, nbr, 0, mainVector.size() - 1);
        mainVector.insert(mainVector.begin() + pos, nbr);
    }
}

void PmergeMe::getSubDequeInsertionPosition( void )
{
	if (subDeque.empty())
		return;

	PmergeMe::jacobsthalInsertSequence(subDeque.size(), this -> jacobsthalDequeSequence);
	size_t lastPos = 1;
	size_t val = 1;

	while (!jacobsthalDequeSequence.empty())
	{
		val = jacobsthalDequeSequence.front();

		jacobsthalDequeSequence.pop_front();
		subDequeInsertionPosition.push_back(val);

		size_t pos = val - 1;
		while (pos > lastPos)
		{
			subDequeInsertionPosition.push_back(pos);
			pos--;
		}
		lastPos = val;
	}
	while (val++ < subDeque.size())
	    subDequeInsertionPosition.push_back(val);
}

void PmergeMe::insertNumbersDeque( void )
{
	std::deque<int>::iterator it;
	size_t addCount = 0;

	PmergeMe::getSubDequeInsertionPosition();
    std::cout << std::endl;
	for (it = subDequeInsertionPosition.begin(); it < subDequeInsertionPosition.end(); it++)
	{
		int n = subDeque.at(*it - 1);
		size_t endPos = *it + addCount;
		size_t pos = PmergeMe::binarySearch(mainDeque, n, 0, endPos);
		mainDeque.insert(mainDeque.begin() + pos, n);
		addCount++;
	}
	if (oddDeque != -1)
	{
		size_t nbr = oddDeque;
		size_t pos = PmergeMe::binarySearch(mainDeque, nbr, 0, mainDeque.size() - 1);
		mainDeque.insert(mainDeque.begin() + pos, nbr);
	}
}