#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the runningMedian function below.
 */
vector<double> runningMedian(vector<int> a) 
{
    vector<double> result;

    if (a.empty()) return result;

    vector<int> lowPart;
    vector<int> highPart;

    lowPart.push_back(*cbegin(a));
    result.push_back(static_cast<double>(lowPart[0]));

    for (auto cit = next(cbegin(a)); cit != cend(a); ++cit)
    {
        auto item = *cit;

        double median = 0.;
        if (lowPart.size() == highPart.size())
        {
            if (item <= highPart[0])
            {
                lowPart.push_back(item);
                push_heap(begin(lowPart), end(lowPart));
            }
            else
            {
                highPart.push_back(item);
                push_heap(begin(highPart), end(highPart), [](const auto& lhs, const auto& rhs) { return lhs > rhs; });

                pop_heap(begin(highPart), end(highPart), [](const auto& lhs, const auto& rhs) { return lhs > rhs; });
                auto minInHigh = highPart.back();
                highPart.pop_back();

                lowPart.push_back(minInHigh);
                push_heap(begin(lowPart), end(lowPart));
            }
            median = lowPart[0];
        }
        else
        {
            if (highPart.empty() || item <= highPart[0])
            {
                lowPart.push_back(item);
                push_heap(begin(lowPart), end(lowPart));

                pop_heap(begin(lowPart), end(lowPart));
                auto maxInLow = lowPart.back();
                lowPart.pop_back();

                highPart.push_back(maxInLow);
                push_heap(begin(highPart), end(highPart), [](const auto& lhs, const auto& rhs) { return lhs > rhs; });
            }
            else
            {
                highPart.push_back(item);
                push_heap(begin(highPart), end(highPart), [](const auto& lhs, const auto& rhs) { return lhs > rhs; });
            }
            median = (static_cast<double>(lowPart[0]) + highPart[0]) / 2.;
        }

        result.push_back(median);
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
