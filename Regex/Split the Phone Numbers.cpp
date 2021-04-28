#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <list>
#include <regex>
#include <sstream>

using namespace std;


string convert(string src)
{
    const regex re("(\\d+)[- ](\\d+)[- ](\\d+)");
    smatch cm;

    ostringstream ss;
    if (regex_match(src, cm, re))
    {
        ss << "CountryCode=" << cm[1] << ",LocalAreaCode=" << cm[2] << ",Number=" << cm[3];
    }

    return ss.str();
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        string src;
        getline(cin, src);

        cout << convert(src) << endl;
    }

    return 0;
}
