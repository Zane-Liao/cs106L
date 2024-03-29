#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  ostringstream oss("Ito En Green Tea ");
/*  cout << oss.str() << endl;
  oss << 16.9 << string(" Ounce ");
  cout << oss.str() << endl;
  oss << "(Pack of " << 12 << ")" << endl;
  cout << oss.str() << endl;
  istringstream iss(oss.str());
  double amount;
  string unit;
  iss >> amount >> unit;
  cout << "...as: " << amount/3 << " " << unit << "\n";
*/
  oss << 16.9;
  fpos pos = oss.tellp() + streamoff(3);
  oss.seekp(pos);
  oss << "Black";

  cout << oss.str() << endl;
  ostringstream oss_numbers("1 2 3 4 5", ostringstream::ate);
  cout << oss_numbers.str() << endl;
  oss_numbers << " 6" << " 7" << endl;
  cout << oss_numbers.str() << endl;

  return 0;
}
