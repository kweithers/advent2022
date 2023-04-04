#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <map>

using namespace std;

struct Rucksack
{
  string first;
  string second;
};

struct GroupOf3
{
  std::map<char, int> map1;
  std::map<char, int> map2;
  std::map<char, int> map3;
};

int main()
{
  fstream input;
  input.open("input.txt");

  int sum = 0;
  int sum2 = 0;

  string line;
  int i = 0;
  GroupOf3 group;
  std::map<char, int> char_map;
  while (getline(input, line))
  {
    int n = line.length();
    Rucksack r;
    r.first = line.substr(0, n / 2);
    r.second = line.substr(n / 2, n / 2);

    std::set<char> char_set;
    for (int i = 0; i < n / 2; i++)
    {
      char_set.insert(r.first[i]);
    }

    for (int i = 0; i < n / 2; i++)
    {
      if (char_set.count(r.second[i]))
      {
        if (isupper(r.second[i]))
        {
          sum += ((int)r.second[i]) - 38;
        }
        else
        {
          sum += ((int)r.second[i]) - 96;
        }
        break;
      }
    }

    switch (i % 3)
    {
    case 0:
      for (int i = 0; i < line.length(); i++)
      {
        group.map1[line[i]]++;
      }
      break;
    case 1:
      for (int i = 0; i < line.length(); i++)
      {
        group.map2[line[i]]++;
      }
      break;
    case 2:
      for (int i = 0; i < line.length(); i++)
      {
        group.map3[line[i]]++;
      }

      // Find the char that is in all three sets
      for (auto i : group.map1)
      {
        if (group.map2.count(i.first) && group.map3.count(i.first))
        {
          if (isupper(i.first))
          {
            sum2 += ((int)i.first) - 38;
          }
          else
          {
            sum2 += ((int)i.first) - 96;
          }
          break;
        }
      }

      // Reset the struct
      group = GroupOf3();
    }
    i++;
  }

  cout << "Part 1: " << sum << endl;
  cout << "Part 2: " << sum2 << endl;
}