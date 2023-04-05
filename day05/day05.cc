#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <stack>
#include <deque>

using namespace std;

/* Starting positions
                [B]     [L]     [S]
        [Q] [J] [C]     [W]     [F]
    [F] [T] [B] [D]     [P]     [P]
    [S] [J] [Z] [T]     [B] [C] [H]
    [L] [H] [H] [Z] [G] [Z] [G] [R]
[R] [H] [D] [R] [F] [C] [V] [Q] [T]
[C] [J] [M] [G] [P] [H] [N] [J] [D]
[H] [B] [R] [S] [R] [T] [S] [R] [L]
 1   2   3   4   5   6   7   8   9
 */

struct CargoShip
{
  vector<stack<string>> stacks;

  CargoShip()
  {
    vector<vector<string>> crates = {
        {"H", "C", "R"},
        {"B", "J", "H", "L", "S", "F"},
        {"R", "M", "D", "H", "J", "T", "Q"},
        {"S", "G", "R", "H", "Z", "B", "J"},
        {"R", "P", "F", "Z", "T", "D", "C", "B"},
        {"T", "H", "C", "G"},
        {"S", "N", "V", "Z", "B", "P", "W", "L"},
        {"R", "J", "Q", "G", "C"},
        {"L", "D", "T", "R", "H", "P", "F", "S"}};

    for (int i = 0; i < crates.size(); i++)
    {
      stack<string> stack;
      for (int j = 0; j < crates[i].size(); j++)
      {
        stack.push(crates[i][j]);
      }
      stacks.push_back(stack);
    }
  }
};

int main()
{
  fstream input;
  input.open("input.txt");

  CargoShip ship1;
  CargoShip ship2;

  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(","));

    int n = stoi(v[0]);
    int from = stoi(v[1]) - 1; // -1 for zero indexing
    int to = stoi(v[2]) - 1;

    // Part 1
    for (int i = 0; i < n; i++)
    {
      string s = ship1.stacks[from].top();
      ship1.stacks[from].pop();
      ship1.stacks[to].push(s);
    }

    // Part 2
    deque<string> d;
    for (int i = 0; i < n; i++)
    {
      string s = ship2.stacks[from].top();
      ship2.stacks[from].pop();
      d.push_back(s);
    }
    int size = d.size();
    for (int j = 0; j < size; j++)
    {
      string ss = d.back();
      d.pop_back();
      ship2.stacks[to].push(ss);
    }
  }

  string result1;
  string result2;
  for (int i = 0; i < 9; i++)
  {
    result1.push_back(ship1.stacks[i].top().front());
    result2.push_back(ship2.stacks[i].top().front());
  }
  cout << "Part 1: " << result1 << endl;
  cout << "Part 2: " << result2 << endl;
}