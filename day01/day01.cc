#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int main()
{
  fstream input;
  input.open("input.txt");

  vector<int> weights;
  int current_weight = 0;

  string line;
  while (getline(input, line))
  {
    if (line.length() == 0)
    {
      weights.push_back(current_weight);
      current_weight = 0;
    }
    else
    {
      current_weight += stoi(line);
    }
  }
  input.close();

  sort(weights.begin(), weights.end(), greater<int>());

  cout << "Part 1: " << weights[0] << endl;
  cout << "Part 2: " << weights[0] + weights[1] + weights[2] << endl;
}
