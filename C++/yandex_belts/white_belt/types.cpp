#include <iostream>
#include <string>

using namespace std;

int main()
{
    string x = "abc", y = "aaaabc";
    if (x < y)
    {
        cout << "less\n";
    }
    else
    {
        cout << "not less\n";
    }

    return 0;
}