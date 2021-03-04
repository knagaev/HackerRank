#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the minimumAverage function below.
 */
long long minimumAverage(vector<vector<int>> customers) 
{
    vector<vector<int>> sortedCustomers(customers);

    sort(begin(sortedCustomers), end(sortedCustomers),
        [](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; });

    vector<vector<int>> priorityQueue{*begin(sortedCustomers)};
    
    auto itNextCustomer = next(begin(sortedCustomers));
    long long currentTime = 0;

    long long averageSum = 0;
    while (!priorityQueue.empty())
    {
        pop_heap(begin(priorityQueue), end(priorityQueue),
            [](const auto& lhs, const auto& rhs) { return lhs[1] > rhs[1]; });
        auto currentCustomer = priorityQueue.back();
        priorityQueue.pop_back();

        currentTime = max(currentTime, static_cast<long long>(currentCustomer[0])) + currentCustomer[1];
        auto test = itNextCustomer != end(sortedCustomers);
        while (
            itNextCustomer != end(sortedCustomers) && 
            ((*itNextCustomer)[0] < currentTime || priorityQueue.empty())
        )
        {
            priorityQueue.push_back(*itNextCustomer);
            push_heap(begin(priorityQueue), end(priorityQueue),
                [](const auto& lhs, const auto& rhs) { return lhs[1] > rhs[1]; });
            itNextCustomer = next(itNextCustomer);
        }

        averageSum += (currentTime - currentCustomer[0]) ;
    }

    return averageSum / customers.size();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> customers(n);
    for (int customers_row_itr = 0; customers_row_itr < n; customers_row_itr++) {
        customers[customers_row_itr].resize(2);

        for (int customers_column_itr = 0; customers_column_itr < 2; customers_column_itr++) {
            cin >> customers[customers_row_itr][customers_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long long result = minimumAverage(customers);

    fout << result << "\n";

    fout.close();

    return 0;
}
