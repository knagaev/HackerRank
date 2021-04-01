#include <bits/stdc++.h>

using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) 
{
  
  reverse(s.begin(), s.end());
  
  size_t char_counter[26] = {0};
  vector<size_t> positions[26];  // array of vectors with char positions

  for (size_t i = 0; i < s.size(); ++i)
  {
    auto code = s[i] - 'a';
    char_counter[code]++;
    positions[code].push_back(i);
  }

  for (auto& f : char_counter) f /= 2;

  vector<size_t> must_be_placed(s.size());  // must be placed by this position
  size_t discovered[26] = {0};  // discovered by this position

  for (size_t i = s.size(); i > 0 ; --i)
  {
    auto code = s[i - 1] - 'a';
    must_be_placed[i - 1] = char_counter[code] - discovered[code];
    discovered[code] = min(discovered[code] + 1, char_counter[code]);
  }

  string smallestString;
  size_t sync_position = 0;
  size_t next_to_place[26] = {0};
  size_t last_pos = 0;
  size_t written[26] = {0};

  auto halfSize = s.size() / 2;
  while (smallestString.size() < halfSize)
  {
    while (!(written[s[sync_position] - 'a'] < must_be_placed[sync_position]))
      sync_position++;

    size_t next_char = 0;
    while (written[next_char] == char_counter[next_char] || positions[next_char][next_to_place[next_char]] > sync_position)
      next_char++;

    size_t str_pos = positions[next_char][next_to_place[next_char]];
    while (last_pos != str_pos)
    {
      next_to_place[s[last_pos] - 'a']++;
      last_pos++;
    }

    do {
      smallestString.push_back(next_char + 'a');
      written[next_char]++;
      next_to_place[next_char]++;
    } while (written[next_char] < must_be_placed[str_pos]);

    last_pos = str_pos + 1;
  }

  return smallestString;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
