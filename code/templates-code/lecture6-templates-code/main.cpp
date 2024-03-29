/*
 * Final lecture code for lecture 7 - templates.
 *
 * Avery Wang - last updated 1/25/2020
 */

#include <iostream> // for cin, cout
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <typeinfo> // for typeid
#include <type_traits>
#include "templates.h" // I defined everything you don't care about (yet) in here.
using namespace std;



template <typename T>
pair<T, T> my_minmax(T a, T b) {
    if (a < b) return {a, b};
    else return {b, a};
}

template <typename T>
void printMinAndMax(T min, T max) {
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << endl;
}

template <typename T>
T getTypeValue() {
    while (true) {
        // typeid is my imperfect way of printing the name of T.
        cout << "Enter a " << typeid(T).name() << ": ";

        string line; T result; char extra;
        if (!getline(cin, line))
            throw domain_error("Unable to get line from cin.");
        istringstream iss(line);
        if (iss >> result && !(iss >> extra)) return result;
        cout << "Invalid format." << endl;
    }
}

void getTypeTest() {
    int val0 = getTypeValue<int>();
    double val1 = getTypeValue<double>();
    Time val2 = getTypeValue<Time>();
    // Time only works because we have overloaded << for a Time struct.

    cout << val0 << endl;
    cout << val1 << endl;
    cout << val2 << endl;
}

template <typename InputIt, typename DataType>
int countOccurences(InputIt begin, InputIt end, const DataType& val) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter == val) ++count;
    }
    return count;
}


void conceptLifting() {
    // Count how many times 3 appears in a vector<int>.
    vector<int> v1{3, 3, 4, 4, 1, 3};
    int times1 = countOccurences(v1.begin(), v1.end(), 3);
    cout << "v1 contains " << times1 << " copies of 3" << endl;

    // Count how many times 4.7 appears in a list<double>.
    list<double> v2{2.3, 4.6667, 4.6666667, 4.7, 4.7, 7.4};
    int times2 = countOccurences(v2.begin(), v2.end(), 4.7);
    cout << "v2 contains " << times2 << " copies of 4.7" << endl;

    // Count how many times ‘X’ appears in a string.
    string quadratic = "AX^2 + BX + C = 0";
    int times3 = countOccurences(quadratic.begin(), quadratic.end(), 'X');
    cout << "quadratic contains " << times3 << " copies of X" << endl;

    // Count how many times ‘X’ appears in a deque<char>.
    deque<char> quadraticDeque{'A', 'X', '^', '2', '+', 'B', 'X', '+', 'C'};
    int times4 = countOccurences(quadraticDeque.begin(), quadraticDeque.end(), 'X');
    cout << "quadraticDeque contains " << times4 << " copies of X" << endl;

    // Count how many times 5 appears in the second half of a vector<int>.
    vector<int> phoneNumber{5, 5, 5, 8, 2, 6, 5, 5, 3, 5};
    int times5 = countOccurences(phoneNumber.begin() + phoneNumber.size()/2,
                                 phoneNumber.end(), 5);
    cout << "quadraticDeque contains " << times5 << " copies of X" << endl;

    // Count how many elements in the second half of a vector<int> are at most 5.
    // We can't do this yet, because that requires us to change the
    // *iter == val condition. But we will be able to next time!
}

//// SFINAE demonstration
template <typename T>
auto printSize(const T& a) -> decltype(a.size()) {
    cout << "printing with size member function: ";
    cout << a.size() << endl;

    return a.size();
}

template <typename T>
auto printSize(const T& a) -> decltype(-a) {
    cout << "printing with negative numeric function: ";
    cout << -a << endl;

    return -a;
}

template <typename T>
auto printSize(const T& a) -> decltype(a->size()) {
    cout << "printing with pointer function: ";
    cout << a->size() << endl;

    return a->size();
}

// given two vectors, finds the first mismatching pairs of elements, and returns {true, pair1, pair2}
// if there is no mismatch, then returns {false, ??, ??}
// assumes second vector is at least as long as the first
tuple<bool, int, int> my_mismatch(const vector<int>& vec1,
                               const vector<int>& vec2) {
    size_t i = 0;
    while (i < vec1.size() && vec1[i] == vec2[i]){
        ++i;
    }
    if (i == vec1.size()) return {false, 0, 0};
    else return {true, vec1[i], vec2[i]};
}

// Returns the first mismatching pair of elements from two ranges:
// one defined by [first1, last1) and another defined by [first2,last2).
// we can implicitly calculate last2 = first2 + (last1 - first1).
// if there is no mismatch, returns {last1, last2}
template <typename InputIt1, typename InputIt2>
pair<InputIt1, InputIt2> my_mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    // FILL THIS IN!
    return {first1, first2};
}



int main() {
    auto [min1, max1] = my_minmax(string("Avery"), string("Anna"));
    printMinAndMax(min1, max1);
    getTypeTest();
    conceptLifting();

    // FOURTH PART OF LECTURE (SFINAE)
    vector<int> testVector{1, 2, 3};
    printSize(testVector); 		// calls first overload
    printSize(testVector[1]);	// calls second overload
    printSize(&testVector);		// calls third overload
    // printSize(nullptr);	    // compiler error

    // HOMEWORK CHALLENGE
    vector<int> testVec1 {1, 2, 3, 4, 5, 6, 7};
    vector<int> testVec2 {1, 2, 3, 4, 7, 6, 7};
    deque<int> testDeq1 {1, 2, 3, 4, 5, 6, 7};
    deque<int> testDeq2 {1, 2, 3, 4, 7, 6, 7};

    auto[no_match1, first1, second1] = my_mismatch(testVec1, testVec2);
    cout << no_match1 << " " << first1 << " " << second1 << endl;

    auto[no_match2, first2, second2] = my_mismatch(testVec1, testVec1);
    cout << no_match2 << " " << first2 << " " << second2 << endl;
    // write your own test cases for your template function
}
