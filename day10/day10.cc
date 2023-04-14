#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{
  fstream input;
  input.open("input.txt");

  int x = 1; // The sole register
  int cycle = 1;
  int sum_signal_strength = 0;

  // Part 2
  char pixels[240];
  std::fill_n(pixels, 240, '.');

  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(" "));

    if (v[0] == "noop") // Takes 1 cycle to complete
    {
      if (cycle % 40 == 20)
      {
        sum_signal_strength += (cycle * x);
      }
      // Draw pixel cycle-1
      if (x >= (cycle % 40) - 2 && x <= (cycle % 40))
      {
        pixels[cycle - 1] = '#';
      }
      cycle++;
    }
    else if (v[0] == "addx") // Takes 2 cycles to complete!!
    {
      for (int i = 1; i <= 2; i++)
      {
        if (cycle % 40 == 20)
        {
          sum_signal_strength += (cycle * x);
        }
        // Draw pixel cycle-1
        if (x >= (cycle % 40) - 2 && x <= (cycle % 40))
        {
          pixels[cycle - 1] = '#';
        }
        cycle++;
      }
      x += stoi(v[1]);
    }
  }

  cout << "Part 1: " << sum_signal_strength << endl;
  cout << "Part 2: " << endl;

  for (int j = 0; j < 6; j++)
  {
    for (int i = 0; i < 40; i++)
    {
      cout << pixels[40 * j + i];
    }
    cout << endl;
  }
}