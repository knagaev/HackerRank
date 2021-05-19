#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene) 
{
    unordered_map<char, long> total;
    for (const auto ch : gene)
        ++total[ch];

    auto maxQty = gene.length() / 4;
    if (total['A'] == maxQty && total['C'] == maxQty && total['G'] == maxQty)
        return 0;

    unordered_map<char, long> running;
    long left = 0, right = 0;
    long minLength = numeric_limits<long>::max();
    size_t geneLength = gene.length();
    while (right < geneLength)
    {
        while (right < geneLength)
        {
            ++running[gene[right++]];

            bool isLower = true;
            for (const auto& ch : { 'A', 'C', 'G', 'T' })
            {
                if (total[ch] - running[ch] > maxQty)
                {
                    isLower = false;
                    break;
                }
            }

            if (isLower) break;
        }
        while (left < right)
        {
            --running[gene[left++]];
            bool isLower = true;
            for (const auto& ch : { 'A', 'C', 'G', 'T' })
            {
                if (total[ch] - running[ch] > maxQty)
                {
                    isLower = false;
                    break;
                }
            }

            if (!isLower) break;
        }
        minLength = min(minLength, right - left + 1);
    }

    return minLength;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
