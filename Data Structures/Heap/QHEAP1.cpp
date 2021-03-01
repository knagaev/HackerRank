#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main()
{
    int n;
    cin >> n;

    vector<int> heap;
    set<int> items;

    int op, x;
    for (int i = 0; i < n; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            {
                cin >> x;
                auto it = items.find(x);
                if (it != end(items))
                    break;

                heap.push_back(x);
                push_heap(begin(heap), end(heap),
                    [](const auto& lhs, const auto& rhs) { return lhs > rhs; });
                items.insert(x);
            }
            break;
        case 2:
            cin >> x;
            items.erase(x);
            break;
        case 3:
            {
              auto minElement = *begin(heap);
              auto it = items.find(minElement);
              while (it == end(items))
              {
                  pop_heap(begin(heap), end(heap),
                      [](const auto& lhs, const auto& rhs) { return lhs > rhs; });
                  heap.pop_back();
                  minElement = *begin(heap);
                  it = items.find(minElement);
              }
              cout << minElement << endl;
            }
            break;
        default:
            break;
        }

    }
    return 0;
}
