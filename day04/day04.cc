#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

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
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of("-,"));

    RangePair rp;
    rp.first.lo = stoi(v[0]);
    rp.first.hi = stoi(v[1]);
    rp.second.lo = stoi(v[2]);
    rp.second.hi = stoi(v[3]);

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