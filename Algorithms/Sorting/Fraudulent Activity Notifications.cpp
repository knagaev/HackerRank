#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void printSets(const auto& lessThan, const auto& biggerThan, char c)
{
    cout << c << " ";
    for(const auto& l : lessThan)
      cout << l << " ";
    cout << "|";
    for(const auto& b : biggerThan)
      cout << b << " ";
    cout << endl;
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditures, int d) 
{
  int notifications = 0;
  multiset<int> lessThan;
  multiset<int> biggerThan;

  vector<int> firstD(d);
  for(int i = 0; i < d; ++i)
  {
    firstD[i] = expenditures[i];
  }
  sort(firstD.begin(), firstD.end());
 
  for(int i = 0; i < (d + 1) / 2; ++i)
    lessThan.insert(firstD[i]);
 
  for(int i = (d + 1) / 2; i < d; ++i)
    biggerThan.insert(firstD[i]);
  
  for(vector<int>::size_type i = d, j = 0; i < expenditures.size(); ++i, ++j)
  {
    //printSets(lessThan, biggerThan, 'a');

    double doubleMedian = (d % 2 == 0) ?
      (*prev(lessThan.cend()) + *biggerThan.cbegin()) :
      *prev(lessThan.cend()) * 2;

    if(expenditures[i] >= doubleMedian) ++notifications;

    if (expenditures[j] < *biggerThan.cbegin())
      lessThan.erase(lessThan.find(expenditures[j]));
    else
      biggerThan.erase(biggerThan.find(expenditures[j]));

    if (expenditures[i] < *biggerThan.cbegin())
      lessThan.insert(expenditures[i]);
    else
      biggerThan.insert(expenditures[i]);

    auto lessThanSize = lessThan.size();
    auto biggerThanSize = biggerThan.size();

    if( (d % 2 == 0 && biggerThanSize != lessThanSize)
     || (d % 2 == 1 && biggerThanSize + 1 != lessThanSize))
    {
      if(biggerThanSize > lessThanSize)
      {
        //cout << "biggerThanSize > lessThanSize" << endl;
        //printSets(lessThan, biggerThan, 'b');
        lessThan.insert(*biggerThan.cbegin());
        biggerThan.erase(biggerThan.cbegin());
        //printSets(lessThan, biggerThan, 'c');
      }
      else
      {
        //cout << "biggerThanSize < lessThanSize" << endl;
        //printSets(lessThan, biggerThan, 'd');
        biggerThan.insert(*prev(lessThan.cend()));
        lessThan.erase(prev(lessThan.cend()));
        //printSets(lessThan, biggerThan, 'e');
      }
    }
  }

  return notifications;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
