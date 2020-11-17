#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the acmTeam function below.
vector<int> acmTeam(vector<string> topic) 
{
    // transposed matrix: skills -> teams
    vector<vector<int>> skills(topic[0].size());

    for (const auto& t : topic)
    {
        for (size_t i = 0; i < t.length(); ++i)
        {
            skills[i].push_back(t[i] - '0');
        }
    }

    map<int, int> badSkills; // counter of bad skills (both zeroes) for team
    for (const auto& skill : skills)
    {
        for (size_t i = 0; i < skill.size() - 1; ++i)
        {
            if (skill[i] != 0) continue;
            for (size_t j = i + 1; j < skill.size(); ++j)
            {
                // hash value for pair of teams
                auto pairHash = i * topic.size() + j;
                
                if (badSkills.find(pairHash) == badSkills.end()) 
                    badSkills[pairHash] = 0;

                if (skill[j] != 0) continue;
                ++badSkills[pairHash];
            }
        }
    }

    auto minBadSkills = skills.size();
    int countTeams = 0;
    for (const auto& bs : badSkills)
    {
        if (bs.second == minBadSkills)
        {
            ++countTeams;
            continue;
        }
        if (bs.second < minBadSkills)
        {
            minBadSkills = bs.second;
            countTeams = 1;
        }
    }

    return { static_cast<int>(skills.size() - minBadSkills), countTeams};
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<string> topic(n);

    for (int i = 0; i < n; i++) {
        string topic_item;
        getline(cin, topic_item);

        topic[i] = topic_item;
    }

    vector<int> result = acmTeam(topic);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
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
