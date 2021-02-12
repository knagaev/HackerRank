#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops


struct Workshop
{
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops
{
    int n;
    Workshop* ws;
};

Available_Workshops* initialize(int* start_time, int* duration, int n)
{
    auto aw = new Available_Workshops;

    aw->n = n;
    auto ws = new Workshop[n];

    for (int i = 0; i < n; ++i)
    {
        ws[i].start_time = start_time[i];
        ws[i].duration = duration[i];
        ws[i].end_time = start_time[i] + duration[i] - 1;
    }
    aw->ws = ws;
    return aw;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    vector<Workshop> workshops(ptr->ws, ptr->ws + ptr->n);
    sort(begin(workshops), end(workshops), [](Workshop a, Workshop b)
        {
            return a.end_time < b.end_time;
        });

    vector<Workshop> bestAvailable(begin(workshops), next(begin(workshops)));
    int maxRight = (*begin(workshops)).end_time;

    for (auto it = next(begin(workshops)); it != end(workshops); ++it)
    {
        if ((*it).start_time > maxRight)
        {
            bestAvailable.push_back(*it);
            maxRight = max((*it).end_time, maxRight);
        }
    }
    return bestAvailable.size();
}


int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
