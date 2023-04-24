#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <compare>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

enum Material
{
  rock,
  sand
};

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

bool drop_sand(map<Point, Material> *grid, int y_max, bool part2)
{
  Point sand = Point{0, 500};

  while (true)
  {
    if (part2 && (sand.y == y_max + 1)) // We have hit the floor, this grain of sand is done moving.
    {
      (*grid).emplace(sand, Material::sand);
      return true;
    }
    // Try down
    if ((*grid).find(Point{sand.y + 1, sand.x}) == (*grid).end())
    {
      sand.y++;
      if (!part2 && sand.y > y_max)
      {
        return false; // We are dropping infinitely!
      }
    }
    // Try down + left
    else if ((*grid).find(Point{sand.y + 1, sand.x - 1}) == (*grid).end())
    {
      sand.y++;
      sand.x--;
    }
    // Try down + right
    else if ((*grid).find(Point{sand.y + 1, sand.x + 1}) == (*grid).end())
    {
      sand.y++;
      sand.x++;
    }
    // Can't move! This grain of sand is done.
    else
    {
      // If we don't add a new item, we are done dropping sand!
      return (*grid).emplace(sand, Material::sand).second;
    }
  }
}

int main()
{
  fstream input;
  input.open("input.txt");

  map<Point, Material> grid;

  string line;
  Point p1, p2;
  int y_max = 0;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(">,"));
    int line_index = 3;
    int hi, lo;

    // Define rock structure
    while (line_index <= v.size() - 1)
    {
      p1.x = stoi(v[line_index - 3]);
      p1.y = stoi(v[line_index - 2]);
      p2.x = stoi(v[line_index - 1]);
      p2.y = stoi(v[line_index]);

      if (p1.x == p2.x)
      {
        lo = min(p1.y, p2.y);
        hi = max(p1.y, p2.y);
        y_max = max(y_max, hi);
        for (int y = lo; y <= hi; y++)
        {
          grid[Point{y, p1.x}] = rock;
        }
      }
      else
      {
        lo = min(p1.x, p2.x);
        hi = max(p1.x, p2.x);
        for (int x = lo; x <= hi; x++)
        {
          grid[Point{p1.y, x}] = rock;
        }
      }
      line_index += 2;
    }
  }

  // Copy the original grid for part2.
  auto grid2 = grid;

  // Drop Sand from (500,0) until sand drops infinitely
  int n_sand = 0;
  while (drop_sand(&grid, y_max, false))
  {
    n_sand++;
  }
  cout << "Part 1: " << n_sand << endl;

  // Part 2: Now there is an infinite horizontal floor at y_max+2
  int n_sand2 = 0;
  while (drop_sand(&grid2, y_max, true))
  {
    n_sand2++;
  }
  cout << "Part 2: " << n_sand2 << endl;
}
