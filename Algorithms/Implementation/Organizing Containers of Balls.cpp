#include <bits/stdc++.h>

using namespace std;

// Complete the organizingContainers function below.
string organizingContainers(vector<vector<int>> containers) 
{
    vector<int> sumContainers;
    transform(begin(containers), end(containers),
        back_inserter(sumContainers),
        [](const auto& container) -> int 
        {
            return accumulate(begin(container), end(container), 0);
        }
    );
    sort(begin(sumContainers), end(sumContainers));

    auto sumBalls = accumulate(begin(containers), end(containers),
        vector<int>(containers[0].size()),
        [](auto& acc, const auto& container)
        {
            transform(begin(acc), end(acc), begin(container),
                begin(acc),
                plus<int>()
            );
            return acc;
        }
    );
    sort(begin(sumBalls), end(sumBalls));

    if (equal(sumContainers.begin(), sumContainers.end(), sumBalls.begin()))
        return "Possible";
    else
        return "Impossible";

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> container(n);
        for (int i = 0; i < n; i++) {
            container[i].resize(n);

            for (int j = 0; j < n; j++) {
                cin >> container[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string result = organizingContainers(container);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
