#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <numeric>
#include <functional>
#include <map>

using namespace std;

vector<string> split_string(string);

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) 
{
    // shift to 0 scale
    --r_q;
    --c_q;
    transform(begin(obstacles), end(obstacles),
        begin(obstacles), 
        [](const auto& o) -> vector<int> { return { o[0] - 1, o[1] - 1 }; }
        );

    // ends of row
    int ost[2] = { r_q, n };
    int west[2] = { r_q, -1 };
    // ends of col
    int nord[2] = { n, c_q };
    int sud[2] = { -1, c_q };

    // ends of left diagonal
    int nw[2] = { min(n, r_q + (c_q + 1)), max(-1, c_q - (n - r_q)) };
    int so[2] = { max(-1, r_q - (n - c_q)), min(n, c_q + (r_q + 1)) };
    // ends of right diagonal
    int no[2] = { min(n, r_q + (n - c_q)), min(n, c_q + (n - r_q)) };
    int sw[2] = { max(-1, r_q - (c_q + 1)), max(-1, c_q - (r_q + 1)) };

    for (const auto& o : obstacles)
    {
        int r_o = o[0];
        int c_o = o[1];

        // horizontal
        if (r_q == r_o)
        {
            if (c_o < c_q) 
                west[1] = max(west[1], c_o);
            else
                ost[1] = min(ost[1], c_o);
            continue;
        }

        // vertical
        if (c_q == c_o)
        {
            if (r_o < r_q)
                sud[0] = max(sud[0], r_o);
            else
                nord[0] = min(nord[0], r_o);
            continue;
        }

        // right diagonal
        if ((r_q - r_o) == (c_q - c_o))
        {
            if (c_o < c_q)
            {
                sw[0] = max(sw[0], r_o);
                sw[1] = max(sw[1], c_o);
            }
            else
            {
                no[0] = min(no[0], r_o);
                no[1] = min(no[1], c_o);
            }
            continue;
        }


        // left diagonal
        if ((r_q - r_o) == (c_o - c_q))
        {
            if (c_o < c_q)
            {
                nw[0] = min(nw[0], r_o);
                nw[1] = max(nw[1], c_o);
            }
            else
            {
                so[0] = max(so[0], r_o);
                so[1] = min(so[1], c_o);
            }
        }
    }

    int canAttack = (nord[0] - sud[0] - 2) + 
        (ost[1] - west[1] - 2) + 
        (nw[0] - so[0] - 2) + 
        (no[0] - sw[0] - 2);

    return canAttack;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    cout << result << "\n";

    //fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
