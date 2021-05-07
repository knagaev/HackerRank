#include <bits/stdc++.h>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

struct Gap
{
    Gap(int x, int y, int l, bool acr) : row(x), col(y), len(l), across(acr) {}

    int row;
    int col;
    int len;
    bool across;
};

bool operator==(const Gap& lhs, const Gap& rhs)
{
    return ((lhs.row == rhs.row) &&
        (lhs.col == rhs.col) &&
        (lhs.len == rhs.len) &&
        (lhs.across == rhs.across));
}

ostream& operator<<(ostream& os, const Gap& g)
{
    return os << "{" << g.row << ", " << g.col << ", " << g.len << ", " << g.across << "}";
}

pair<vector<string>, bool> solve(vector<string> M, vector<Gap> g, vector<string> w)
{
    if (w.empty())
        return make_pair(M, true);

    // Over all gaps
    for (int i = 0; i < g.size(); ++i)
    {
        // Try every remaining word
        for (int j = 0; j < w.size(); ++j)
        {
            Gap gg = g[i];
            if (gg.len != w[j].size())
                continue;

            // Make a copy of M
            vector<string> MM = M;

            // Every character of the gap
            if (gg.across)
            {
                bool success = true;
                for (int k = 0; k < gg.len; ++k)
                {
                    if (MM[gg.row][gg.col + k] == '-')
                        MM[gg.row][gg.col + k] = w[j][k];

                    else if (MM[gg.row][gg.col + k] != w[j][k])
                        success = false;
                }

                if (success)
                {
                    vector<Gap> gg = g;
                    gg.erase(gg.begin() + i);
                    vector<string> ww = w;
                    ww.erase(ww.begin() + j);
                    pair<vector<string>, bool> x = solve(MM, gg, ww);
                    if (x.second == true)
                        return x;
                }
            }
            else
            {
                bool success = true;
                for (int k = 0; k < gg.len; ++k)
                {
                    if (MM[gg.row + k][gg.col] == '-')
                        MM[gg.row + k][gg.col] = w[j][k];

                    else if (MM[gg.row + k][gg.col] != w[j][k])
                        success = false;
                }

                if (success)
                {
                    vector<Gap> gg = g;
                    gg.erase(gg.begin() + i);
                    vector<string> ww = w;
                    ww.erase(ww.begin() + j);
                    pair<vector<string>, bool> x = solve(MM, gg, ww);
                    if (x.second == true)
                        return x;
                }
            }

        }
    }

    return make_pair(M, false);
}

vector<Gap> find_gaps(const vector<string>& M)
{
    vector<Gap> gaps;

    // row wise iteration
    for (int row = 0; row < M.size(); ++row)
    {
        int start = -1;
        int stop = -1;
        if (M[row][0] == '-')
        {
            start = 0; stop = 0;
        }

        int col = 1;
        for (col = 1; col < M[row].size(); ++col)
        {
            if ((M[row][col] != M[row][col - 1]) && (start == -1))
            {
                start = col;
            }
            else if (M[row][col] != M[row][col - 1])
            {
                stop = col - 1;
                if (stop > start)
                {
                    gaps.push_back(Gap(row, start, stop - start + 1, true));
                }

                start = -1;
                stop = -1;
            }
        }

        stop = col - 1;
        if ((M[row][stop] == '-') && (stop > start))
        {
            gaps.push_back(Gap(row, start, stop - start + 1, true));
        }
    }

    // column wise iteration
    for (int col = 0; col < M[0].size(); ++col)
    {
        int start = -1;
        int stop = -1;
        if (M[0][col] == '-')
        {
            start = 0; stop = 0;
        }

        int row = 1;
        for (row = 1; row < M.size(); ++row)
        {
            if ((M[row][col] != M[row - 1][col]) && (start == -1))
            {
                start = row;
            }
            else if (M[row][col] != M[row - 1][col])
            {
                stop = row - 1;
                if (stop > start)
                {
                    gaps.push_back(Gap(start, col, stop - start + 1, false));
                }

                start = -1;
                stop = -1;
            }
        }

        stop = row - 1;
        if ((start > -1) && (M[stop][col] == '-') && (stop > start))
        {
            gaps.push_back(Gap(start, col, stop - start + 1, false));
        }

    }

    return gaps;
}

vector<string> vectorize(const string& words)
{
    int start = 0;
    int stop = 0;
    vector<string> out;

    for (int stop = 0; stop < words.size(); ++stop)
    {
        if (words[stop] == ';')
        {
            out.push_back(words.substr(start, stop - start));
            start = stop + 1;
            stop = stop + 2;
        }
    }

    // Push the last word
    out.push_back(words.substr(start, stop - start));

    return out;
}

vector<string> crosswordPuzzle(vector<string> crossword, string words)
{
    vector<Gap> gaps = find_gaps(crossword);
    vector<string> w = vectorize(words);

    pair<vector<string>, bool> x = solve(crossword, gaps, w);
    if (x.second == true)
    {
        return x.first;
    }
    else return vector<string>();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
