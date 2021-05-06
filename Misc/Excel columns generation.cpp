
#include <iostream>

using namespace std;

string convert(int n, int base = 26)
{
    string result;

    auto i = n;
    while (i > 0) 
    {
        auto remainder = i % base;
        if (remainder == 0) remainder = base;
        
        result = (char)('@' + remainder) + result;

        i = (i - remainder) / base;
    };

    return result;
}

int main()
{
    for (int i = 1; i < 704; ++i)
        cout << i << ": " << convert(i) << endl;
    return 0;
}
