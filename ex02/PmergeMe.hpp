#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstddef>
#include <cstring>
#include <cstdlib> 

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void			sort(int argc, char **argv );

	private:
		std::vector<int> inputVector;
		std::deque<int>	 inputDeque;
		std::vector<int> mainVector;
		std::vector<int> subVector;
		std::vector<int> subVectorInsertionPosition;
		std::vector<int> jacobsthalVectorSequence;
		std::deque<int> jacobsthalDequeSequence;;
		std::deque<int>	subDequeInsertionPosition;
		std::deque<int> mainDeque;
		std::deque<int> subDeque;
		int				oddVector;
		int				oddDeque;
		bool			validateUserInput(int argc, char **argv);
		int 			getJacobsthal(int n);
		template <typename T>
		void 			mergeSort(T& vector, int start, int end );
		void			getSubvectorInsertionPosition( void );
		void			getSubDequeInsertionPosition( void );
		void			insertNumbersDeque( void );
		void			printBeforeSorting(void);
		template<typename T>
		void    		printAfterSorting(clock_t start, const T& seq, std::string type);
		void			sortVector( void );
		void			sortDeque( void );
		void			insertNumbersVector( void );
		void    		printBeforeSotring(void);
		template<typename T>
		void 			jacobsthalInsertSequence(size_t maxSize, T& jacobsthakSequence);
		template<typename T>
		int 			binarySearch(T& container, int target, int begin, int end);

};



#endif