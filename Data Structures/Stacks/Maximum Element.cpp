#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    
    vector<int> stack;

    int n;
    cin >> n;

    int op, x;
    for (int i = 0; i < n; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> x;
            if (stack.empty())
                stack.push_back(x);
            else
                stack.push_back(max(x, stack.back()));
            break;
        case 2:
            if (!stack.empty())
                stack.pop_back();
            break;
        case 3:
            cout << stack.back() << endl;
            break;
        default:
            break;
        }
    }


    return 0;
}
