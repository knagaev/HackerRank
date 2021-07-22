#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


bool isIn(const set<int>& cities, int city)
{
    return cities.find(city) != end(cities);
}

int jeanisRoute(vector<int> k, vector<vector<int>> roads)
{
    map<int, map<int, int>> adjList;

    // convert to adjacency list
    for (const auto& r : roads)
    {
        adjList[r[0]].insert({ r[1], r[2] });
        adjList[r[1]].insert({ r[0], r[2] });
    }

    vector<int> lettersCities(adjList.size() + 1);
    for (const auto& letterCity : k)
        lettersCities[letterCity] = 1;

    vector<int> neighboursQuantity(adjList.size() + 1);
    for (const auto& al : adjList)
    {
        neighboursQuantity[al.first] = al.second.size();
    }

    vector<int> prunedCities(adjList.size() + 1);

    queue<int> q;

    // if city is leaf and not letter
    for (const auto& al : adjList)
    {
        if (neighboursQuantity[al.first] == 1 && lettersCities[al.first] == 0)
            q.push(al.first);
    }
    //set<int> prunedCities;
    while (!q.empty())
    {
        auto city = q.front();
        q.pop();
        prunedCities[city] = 1;
        
        for (const auto& nb : adjList[city])
        {
            --neighboursQuantity[nb.first];
            
            if (prunedCities[nb.first] == 1)
                continue;

            if (lettersCities[nb.first] == 1)
                break;
            else if (prunedCities[nb.first] == 0)
            {
                if (neighboursQuantity[nb.first] == 1)
                {
                    q.push(nb.first);
                    break;
                }
            }
        }
    }

    map<int, map<int, int>> prunedAdjList;
    for (const auto& r : roads)
    {
        if (prunedCities[r[0]] == 1 || prunedCities[r[1]] == 1)
            continue;
        prunedAdjList[r[0]].insert({ r[1], r[2] });
        prunedAdjList[r[1]].insert({ r[0], r[2] });
    }

    queue<pair<int, int>> bfsQueue;
    set<int> visitedCities;

    for (const auto& al : prunedAdjList)
    {
        if (prunedCities[al.first] == 0)
        {
            bfsQueue.push({ al.first, 0 });
            break;
        }
    }

    int totalDistance = 0;
    pair<int, int> farthestCityDist = bfsQueue.front();
    visitedCities.insert(bfsQueue.front().first);
    while (!bfsQueue.empty())
    {
        auto cityWithDist = bfsQueue.front();
        bfsQueue.pop();

        for (const auto& nb : prunedAdjList[cityWithDist.first])
        {
            if (isIn(visitedCities, nb.first))
                continue;

            auto nbWithDist = make_pair(nb.first, cityWithDist.second + nb.second);
            visitedCities.insert(nb.first);
            bfsQueue.push(nbWithDist);
            totalDistance += nb.second;
            if (farthestCityDist.second < nbWithDist.second)
                farthestCityDist = nbWithDist;
        }
    }

    bfsQueue.push({ farthestCityDist.first, 0 });
    pair<int, int> farthestFromFarthestCityDist = bfsQueue.front();
    visitedCities = set<int>({ bfsQueue.front().first });
    while (!bfsQueue.empty())
    {
        auto cityWithDist = bfsQueue.front();
        bfsQueue.pop();

        for (const auto& nb : prunedAdjList[cityWithDist.first])
        {
            if (isIn(visitedCities, nb.first))
                continue;

            auto nbWithDist = make_pair(nb.first, cityWithDist.second + nb.second);
            visitedCities.insert(nb.first);
            bfsQueue.push(nbWithDist);
            if (farthestFromFarthestCityDist.second < nbWithDist.second)
                farthestFromFarthestCityDist = nbWithDist;
        }
    }

    return 2 * totalDistance - farthestFromFarthestCityDist.second;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string city_temp_temp;
    getline(cin, city_temp_temp);

    vector<string> city_temp = split_string(city_temp_temp);

    vector<int> city(k);

    for (int city_itr = 0; city_itr < k; city_itr++) {
        int city_item = stoi(city_temp[city_itr]);

        city[city_itr] = city_item;
    }

    vector<vector<int>> roads(n-1);
    for (int roads_row_itr = 0; roads_row_itr < n-1; roads_row_itr++) {
        roads[roads_row_itr].resize(3);

        for (int roads_column_itr = 0; roads_column_itr < 3; roads_column_itr++) {
            cin >> roads[roads_row_itr][roads_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = jeanisRoute(city, roads);

    fout << result << "\n";

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
