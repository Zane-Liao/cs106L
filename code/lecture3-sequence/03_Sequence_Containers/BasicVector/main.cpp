#include <vector>
#include <string>
#include <iostream>
using std::vector;  using std::string;
using std::cout;    using std::endl;

void printVec(const vector<string>& v) {
    cout << "{";
    for(auto elem : v) {
        cout << elem << " ";
    }
    cout << "}" << endl;
}

int main() {
    
    return 0;
}
