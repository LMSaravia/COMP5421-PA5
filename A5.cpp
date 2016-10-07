#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*Prints the elements of a Container*/
template <class Container> // Container must provide input iterator (at least)
void print(const Container & c, const string & message = "")
{
	if (!message.empty()) cout << message << ": ";
	//using valType = declType(*c.begin()); // ok
	using valType = typename Container::value_type; // ok, too
	ostream_iterator<valType> osItr(cout, " "); // an iterator to write to cout
	copy(c.begin(), c.end(), osItr); // print
	cout << endl;
}

// Answer to q1
/* Returns random integer between min and max.
Uses std::rand to generate random integers
*/
int random(int min, int max)
{
	// use std::swap() to swap min and max if max < min
	if (max < min)
	{
		swap(min, max);
	}
	// return a random integer between min and max, inclusive
	int range{ max - min };
	return min + rand() % range;
}

// Answer to q2
class Random
{
public:
	Random() = default;
	Random(const Random &) = default;
	Random & operator=(const Random &) = default;
	~Random() = default;
	int operator()(int min, int max) const
	{
		return random(min, max);
	}
};

// Answer to q3
auto randomLambda = [](int min, int max) {return random(min, max); };

// Ref to q11
auto times10 = [](const int &i) {return i * 10; };

// Ref to q14
auto isEven = [](const int &i) {return (i % 2) == 0; };

// Answer to q15
template<class Iterator>
pair<Iterator, bool> secondMax(Iterator start, Iterator finish)
{
	if (start == finish) // range is empty
		return make_pair(finish, false);
	auto largestIt = start;	// point to the largest
	auto secondLargestIt = start; // point to second largest
	auto scanIt = start; // iterates through all items in container
	while (scanIt != finish)
	{
		if (*scanIt > *largestIt)
		{
			secondLargestIt = largestIt;
			largestIt = scanIt;
		}
		else if (*secondLargestIt < *scanIt && *scanIt < *largestIt)
		{
			secondLargestIt = scanIt;
		}
		else if (largestIt == secondLargestIt && *scanIt < *largestIt)
		{
			secondLargestIt = scanIt;
		}
		++scanIt;
	}
	return make_pair(secondLargestIt, largestIt != secondLargestIt);
}

// Answer to q16
auto isAlpha = [](const char & c) { return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); };
char alphaToLowercase (char c)
{ 
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');
	else
		return c;
}
bool IsPalindrome(const string & phrase)
{
	string temp;
	// remove non-alphabetic chars
	remove_copy_if(begin(phrase), end(phrase), inserter(temp, begin(temp)), isAlpha); 
	// temp to lowercase
	transform(begin(temp), end(temp), begin(temp), alphaToLowercase);
	auto middleIt = begin(temp);
	advance(middleIt, temp.length() / 2); // move iterator to temp's half position
	// return if right half reflects on left half
	return equal(begin(temp), middleIt, rbegin(temp)); 
}

// Answer to q17
void wordIndex()
{
	map<string, set<int>> wordIndexMap;
	string word;
	int lineNum{ 1 }; // starts from first line
	while (cin >> word)
	{
		// add word to map and insert lineNum in word's set (if new word/lineNum)
		wordIndexMap[word].insert(lineNum); 
		if (cin.get() == '\n') // increases lineNum when \n is found.
			++lineNum;
	}
	for (const auto & w : wordIndexMap) // for each word
	{
		cout << w.first << " ";
		for (const auto & l : w.second) // display all line numbers
		{
			cout << l << " ";
		}
		cout << endl;
	}
}


int main()
{
	// Test print()
	//set<int> intset = { 11, 2, 43, 5, 76, 19, 21 };
	//print(intset);
	//print(intset, "a set of integers");

	srand(53); // seeds the random number generator rand() in <cstdlib>.
				// Will generate same seq. of numbers every time the program runs

	// Answer to q1 test (function random)
	cout << left << setw(4) << "1)";
	cout << random(1, 49) << endl;

	//Answer to q2 test (class Random)
	cout << setw (4) << "2)";
	Random luckyNumber;
	cout << luckyNumber(1, 49); // an integer between 1 and 49 inclusive
	cout << endl;

	//Answer to q3 test (lambda expression randomLambda)
	cout << setw(4) << "3)";
	cout << randomLambda(1, 49);
	cout << endl;

	// Answer to q4
	cout << setw(4) << "4)";
	vector<int> va(10);
	auto random_1_5 = bind(random, 1, 5); // function takes no arguments (binds random to parameters 1, 5)
	generate_n(begin(va), 10, random_1_5);
	print(va, "va");
	
	// Answer to q5
	cout << setw(4) << "5)";
	vector<int> vb;
	copy(begin(va), end(va), back_inserter(vb));
	print(vb, "vb");

	// Answer to q6
	cout << setw(4) << "6)";
	copy(begin(va), end(va), inserter(vb, begin(vb)));
	print(vb, "vb after insertion");

	// Answer to q7
	cout << setw(4) << "7)";
	set<int> sa(begin(vb), end(vb));
	print(sa, "sa");

	// Answer to q8
	cout << setw(4) << "8)";
	set<int, greater<int>> sb(begin(vb), end(vb));
	print(sb, "sb");

	// Answer to q9
	cout << setw(4) << "9)";
	multiset<int> msa(begin(vb), end(vb));
	print(msa, "msa");

	// Answer to q10
	multiset<int, greater<int>> msb(begin(vb), end(vb));
	cout << setw(4) << "10)";
	print(msb, "msb");

	// Answer to q11
	cout << setw(4) << "11)";
	multiset<int> msc;
	transform(begin(msa), end(msa), inserter(msc, begin(msc)), times10);
	print(msc, "msc");

	// Answer to q12
	cout << "12)" << endl;
	pair<multiset<int>::iterator, multiset<int>::iterator> bounds;
	for (int i = 1; i <= 5; i++)
	{
		bounds = equal_range(begin(msc), end(msc), i * 10);
		cout << setw(4) << "" << "counted " 
			<< distance(bounds.first, bounds.second) << " " << i * 10 << "'s" << endl;
	}
	
	// Answer to q13
	cout << setw(4) << "13)";
	int sum{ 0 };
	sum = accumulate(lower_bound(begin(msc), end(msc), 15), upper_bound(begin(msc), end(msc), 35), sum);
	cout << "Sum of values between 15 and 35 in msc is: " << sum << endl;

	// Answer to q14
	cout << setw(4) << "14)";
	int count{ count_if(begin(vb), end(vb), isEven) };
	cout <<"Number of even elements in vb: " << count << endl;

	// Test answer to q15
	cout << setw(4) << "15)";
	vector<int> int_vec{ 1, 1, 5, 5, 7, 7 };
	print(int_vec, "int_vec");
	// pair<vector<int>::iterator, bool> // return type, let's use auto
	auto ret_val = secondMax(int_vec.begin(), int_vec.end());
	if (ret_val.second)
	{
		cout << "The second largest element in int_vec is "
			<< *ret_val.first << endl;
	}
	else
	{
		if (ret_val.first == int_vec.end())
			cout << "List empty, no elements\n";
		else
			cout << "Container's elements are all equal to "
			<< *ret_val.first << endl;
	}		

	// Test answer to q16
	cout << "16) " << endl;
	string str_cat = string("Was it a car or a cat I saw?");
	string str_kat = string("Was it a car or a kat I saw?");
	bool is_str_cat = IsPalindrome(str_cat);
	bool is_str_kat = IsPalindrome(str_kat);
	cout << "the phrase \"" + str_cat + "\" is " +
		(is_str_cat ? "" : "not ") + "a palindrome\n";
	cout << "the phrase \"" + str_kat + "\" is " +
		(is_str_kat ? "" : "not ") + "a palindrome\n";

	// Test answer to q17
	cout << "17) " << endl;
	wordIndex();

	return 0;
}