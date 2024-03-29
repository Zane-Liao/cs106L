#include <iostream>
#include <set>

using std::cout;    using std::endl;
using std::set;

int main() {
    // We first populate this set of integers with the numbers from 0 to 9,
    // inclusive.
    set<int> integers;
    for (int i = 0; i < 10; ++i) {
        integers.insert(i);
    }

    // Now, we iterate through the container and print each element one at a time.
    // We do this using an iterator object which starts at the container's
    // beginning. We keep looping as long as we haven't hit the end of the
    // container yet. Inside the loop, we ask for the current value (*itr), and
    // then instruct the iterator to move to the next location (++itr).

    // Alternative #1:
//    set<int>::iterator iter = integers.begin();
//    while (iter != integers.end()) {
//        cout << *iter << endl;
//        ++iter;
//    }
//    cout << endl;

    // Alternative #2:
//    for (auto iter = integers.begin(); iter != integers.end(); ++iter) {
//        cout << *iter << endl;
//    }

    // Most commonly used:
    // (We'll see where iterators are most useful later on)
    for (int elem : integers) {
        cout << elem << endl;
    }

    return 0;
}
