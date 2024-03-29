#include <iostream> // for cin, cout
#include <sstream> // for stringstream
#include <chrono> // for *fancy* timers
#include <iomanip> // for manipulators
#include <fstream> // for file streams
#include <vector> // for vector
// #include <stream>

/* Lecture 1 Code, by Avery Wang, Jan. 9, 2020 */

using namespace std;

int stringToInteger(const string& s);
void stringToIntegerTest();
int mindlessWork();
void bufferedExperiment(ostream& oss);
int endlEachTime();
int endlAtEnd();
void badWelcomeProgram();
void printStateBits(const istream& iss);
std::vector<string> stringSplit(const string& str);
void manipulatorFun();
void printEndTime(const string& input);


// During lecture, fill in this main function
// Follow along, type in some code, and
// try experimenting with anything you can think of
// did something unexpected happen? Ask!
int main() {

    /* Uncomment these to play with them */
    // stringToIntegerTest();
    // bufferedExperiment();

    int a = endlEachTime();
    int b = endlAtEnd();
    cout << "endl each time: " << a << endl;
    cout << "endl at end: " << b << endl;

    // badWelcomeProgram();

    return 0;
}

// you haven't learned about const or the ampersand
// but that's fine, just pretend it's just a string
// converts the string to an integer
// if the string is not an integer, then throws an exception
int stringToInteger(const string& s) {
    istringstream iss(s);

    int result;
    if (!(iss >> result))
        throw std::domain_error("stringToInteger: no valid integer at beginning found");

    char remain;
    if (iss >> remain)
        throw std::domain_error("stringToInteger: can't have characters after the int");
    return result;
}

// Call this function to test your stringToInteger function
// ignore how it is implemented - you'll learn about this next week.
void stringToIntegerTest() {
    while (true) {
        cout << "Type in an integer: ";
        string s;
        if (!getline(cin, s)) throw std::domain_error("getline failed");
        cout << "You typed in: " << s << "\n";
        int result = stringToInteger(s);
        cout << "As an integer, this is: " << result << "\n";
        cout << "Half of that is: " << result/2 << "\n";
    }

}

// the purpose of this function is to
// experiment with cout vs. cerr
// which are both types of ostreams
// we covered this optional topic at the end of lecture
void bufferedExperiment(ostream& oss) {
    oss << "CS";
    mindlessWork();

    oss << "106";
    mindlessWork();

    oss << flush;
    mindlessWork();

    oss << "L";
    mindlessWork();

    oss << endl;
    mindlessWork();
}

// This is how I feel about my classes this quarter
// This function acts as a pause so you can more clearly see the interesting
// parts around this call, such as the buffering above.
// This is probably a life lesson about mindless work.
int mindlessWork() {
    double sum = 0;
    for (int i = 0; i < 400000000; ++i) {
        sum += i/999959;
        // large prime number so compiler can't optimize :)
    }
    return sum;
}

// Prints the first 100 integers including an endl at the end of each line
// Returns the duration it took.
// Optional topic covered at end of lecture.
int endlEachTime() {
    auto startMove = std::chrono::high_resolution_clock::now(); // records start time

    for (int i = 0; i < 10000; ++i) {
        cout << i << endl;
    }

    auto stopMove = std::chrono::high_resolution_clock::now(); // records end time
    // don't worry too much about this syntax, you can google it easily
    // in fact, that's exactly what I did
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

// Prints the first 100 integers including only a newline character after each line
// Returns the duration it took.
// Optional topic covered at end of lecture
int endlAtEnd() {
    auto startMove = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000; ++i) {
        cout << i << '\n';
    }
    cout << flush;

    auto stopMove = std::chrono::high_resolution_clock::now();
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

// This is a bad program, and is how most C++ beginners get themselves into
// trouble (so don't use it in CS 106B!)
// WE DID NOT GET TO THIS IN LECTURE, WILL BEGIN LECTURE 3 WITH THIS
void badWelcomeProgram() {
    string name, response;
    int age;

    cout << "What is your name? "; // sidenote: no flush needed! why?
    cin >> name;

    cout << "What is your age? ";
    cin >> age;

    cout << "Hello " << name << " (age " << age << ")" << '\n';

    cout << "Do you want to try again? ";
    cin >> response;

    cout << "You said: " << response << endl;
}

// Takes in any istream and prints the state bits

void printStateBits(const istream& iss) {
    cout << "State bits: ";

    /*
     *
     * Quick syntax lesson (Keith will teach this too!)
     * TERNARY OPERATOR
     * The following are equivalent:
     * [boolean] ? [statement 1] : [statement 2]
     *
     * if (boolean) {
     *     statement1
     * } else {
     *     statement2
     * }
     *
     * Many people (understandably) hate it, but it makes some expressions super short.
     *
     * int i = 0;
     * if (x > 100) i = 3;
     * else i = 5
     *
     * can replaced by...
     *
     * int i = (x > 100) ? 3 : 5;
     *
     */

    cout << (iss.good() ? "G" : "-");
    cout << (iss.fail() ? "F" : "-");
    cout << (iss.eof() ? "E" : "-");
    cout << (iss.bad() ? "B" : "-");
    cout << '\n';
    cout << "-----------" << '\n';
    // automatically flushed! why?
}

// splits a string with whitespace separated tokens
// into a vector of tokens
std::vector<string> stringSplit(const string& str) {
    std::vector<string> tokens;
    // to add a token to tokens, use tokens.push_back(token);
    return tokens;
}

// some fun with manipulators
// we're not gonna spend too much time on these
// just google them and find the one you wnat to use
void manipulatorFun() {
    cout << "[" << std::setw(10) << "Ito" << "]";
    cout << "[" << std::left << std::setw(10) << "Ito" << "]";
    cout << "[" << std::left << std::setfill('-')
         << std::setw(10) << "Ito" << "]";

}

// Given a start time and a duration,
// calculate the end time.
// Assume correct formatting of string.

// input string: “1:30 PM \n 1 hour 20 minute”
// console string: “2:50 PM”

// Common bug: "1:30 PM \n 0 hour 30 minute"
// should print "2:00 PM", not "2:0 PM"
// Hint: use manipulators
void printEndTime(const string& input) {
    // you fill this out!
}





