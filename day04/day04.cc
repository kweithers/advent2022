#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Range
{
  int lo;
  int hi;
};

struct RangePair
{
  Range first;
  Range second;

  bool xContainsY()
  {
    return second.lo <= first.lo && second.hi >= first.hi ||
           first.lo <= second.lo && first.hi >= second.hi;
  }

  bool anyOverlap()
  {
    return !(first.hi < second.lo || second.hi < first.lo);
  }
};

int main()
{
  fstream input;
  input.open("input.txt");

  int n = 0;
  int n2 = 0;

  string line;
  string range;
  string token;
  while (getline(input, line))
  {
    vector<int> v;

    stringstream ss;
    ss << line;
    while (getline(ss, range, ','))
    {
      stringstream s;
      s << range;
      while (getline(s, token, '-'))
      {
        v.push_back(stoi(token));
      }
    }

    RangePair rp;
    rp.first.lo = v[0];
    rp.first.hi = v[1];
    rp.second.lo = v[2];
    rp.second.hi = v[3];

    if (rp.xContainsY())
    {
      n++;
    }
    if (rp.anyOverlap())
    {
      n2++;
    }
  }

  input.close();
  cout << "Part 1: " << n << endl;
  cout << "Part 2: " << n2 << endl;
}