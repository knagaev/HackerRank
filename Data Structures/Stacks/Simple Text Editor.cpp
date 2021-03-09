#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    stack<string> operations;
    string st;

    int n;
    cin >> n;

    int op;
    string opArg;

    for (int i = 0; i < n; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> opArg;
            operations.push(st);
            st += opArg;
            break;
        case 2:
            cin >> opArg;
            operations.push(st);
            st.erase(st.length() - stoi(opArg));
            break;
        case 3:
            cin >> opArg;
            cout << st[stoi(opArg) - 1] << endl;
            break;
        case 4:
            st = operations.top();
            operations.pop();
            break;
        default:
            break;
        }
    }

    return 0;
}
