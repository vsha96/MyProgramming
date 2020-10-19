#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s = "abcdef";
    for (char c: s) {
        cout << c << ' ';
    }
    cout << '\n';

    vector<int> nums = {1, 5, 5, 5, 3, 4, 1};
    for (int n: nums) {
        cout << n << ' ';
    }
    cout << '\n';

    sort(begin(nums), end(nums));
    for (int x: nums) {
        cout << x << " ";
    }
    cout << '\n';
    
    cout << "There are " << count(begin(nums), end(nums), 5) << " fives\n";

    return 0;

}