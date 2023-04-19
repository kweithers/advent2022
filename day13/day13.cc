#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s)
{
  s = s.substr(1, s.size() - 2); // Remove leading and trailing [ ]
  vector<string> ans;
  int depth = 0;
  string tmp = "";

  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == '[')
      depth++;
    else if (s[i] == ']')
      depth--;
    else if (s[i] == ',' && depth == 0)
    {
      ans.push_back(tmp);
      tmp.clear();
    }

    if (s[i] != ',' || (s[i] == ',' && depth != 0))
      tmp.push_back(s[i]);
  }
  if (tmp.size() != 0)
    ans.push_back(tmp);

  return ans;
}

int compare(vector<string> packet1, vector<string> packet2)
{
  for (int i = 0; i < min(packet1.size(), packet2.size()); i++)
  {
    if (packet1[i][0] != '[' && packet2[i][0] != '[')
    {
      if (stoi(packet1[i]) - stoi(packet2[i]) != 0)
        return stoi(packet1[i]) - stoi(packet2[i]);
    }
    else if (packet1[i][0] == '[' && packet2[i][0] != '[')
    {
      int x = compare(split(packet1[i]), split("[" + packet2[i] + "]"));
      if (x != 0)
        return x;
    }
    else if (packet1[i][0] != '[' && packet2[i][0] == '[')
    {
      int x = compare(split("[" + packet1[i] + "]"), split(packet2[i]));
      if (x != 0)
        return x;
    }
    else
    {
      int x = compare(split(packet1[i]), split(packet2[i]));
      if (x != 0)
        return x;
    }
  }
  return packet1.size() - packet2.size();
}

int main()
{
  freopen("input.txt", "r", stdin);

  string packet1, packet2;
  int i = 1;
  int part1 = 0;

  vector<string> packets;
  while (cin >> packet1 >> packet2)
  {
    if (compare(split(packet1), split(packet2)) < 0)
    {
      part1 += i;
    }
    packets.push_back(packet1);
    packets.push_back(packet2);
    i++;
  }
  cout << "Part 1: " << part1 << endl;

  // Part 2
  packets.push_back("[[2]]");
  packets.push_back("[[6]]");

  sort(packets.begin(), packets.end(), [](string s1, string s2)
       { return compare(split(s1), split(s2)) < 0; });

  int two_index = find(packets.begin(), packets.end(), "[[2]]") - packets.begin() + 1;
  int six_index = find(packets.begin(), packets.end(), "[[6]]") - packets.begin() + 1;

  cout << "Part 2: " << two_index * six_index << endl;
}
