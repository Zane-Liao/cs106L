
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

void streamTypeTests() {
   cout << "Strings work!" << endl;
   cout << 1729 << endl;
   cout << 3.14 << endl;
   cout << "Mixed types - " << 1123 << endl;
   cout << 23*2 << endl;
}

void streamType() {

}

int main() {
   streamTypeTests();
   string str = "This is The outputstream";
   cout << str << endl;
   ostringstream oss("Ito En Green Tea");
   return 0;
}
