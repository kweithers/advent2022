#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <compare>
#include <boost/algorithm/string.hpp>
#include <cstdlib>

using namespace std;

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

int sign(int x)
{
  if (x > 0)
    return 1;
  if (x < 0)
    return -1;
  return 0;
}

struct Rope
{
  vector<Point> knots;
  set<Point> visited_points;

  Rope(int n)
  {
    for (auto i = 0; i < n; i++)
      knots.emplace_back(Point());
    visited_points.emplace(Point());
  }

  // Determines if two points are touching, diagonally counts!
  bool touching(int head, int tail)
  {
    int x_dist = abs(knots[head].x - knots[tail].x);
    int y_dist = abs(knots[head].y - knots[tail].y);
    return x_dist < 2 && y_dist < 2;
  }

  void move_head(char direction) // R, L, U, D
  {
    if (direction == 'R')
    {
      knots[0].x++;
    }
    else if (direction == 'L')
    {
      knots[0].x--;
    }
    else if (direction == 'U')
    {
      knots[0].y++;
    }
    else if (direction == 'D')
    {
      knots[0].y--;
    }
    else
    {
      printf("bad direction - exiting");
      exit(1);
    }
  }

  void move_tail(int head, int tail) // If necessary!
  {
    if (touching(head, tail))
      return;
    if (knots[head].x == knots[tail].x)
    {
      knots[tail].y += sign(knots[head].y - knots[tail].y);
    }
    else if (knots[head].y == knots[tail].y)
    {
      knots[tail].x += sign(knots[head].x - knots[tail].x);
    }
    else
    {
      knots[tail].y += sign(knots[head].y - knots[tail].y);
      knots[tail].x += sign(knots[head].x - knots[tail].x);
    }
  }

  void move(char direction)
  {
    move_head(direction);
    for (auto i = 1; i < knots.size(); i++)
    {
      move_tail(i - 1, i);
    }
    visited_points.insert(knots[knots.size() - 1]);
  }
};

int main()
{
  fstream input;
  input.open("input.txt");

  Rope rope1 = Rope(2);
  Rope rope2 = Rope(10);
  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(" "));

    for (int i = 0; i < stoi(v[1]); i++)
    {
      rope1.move(v[0].front());
      rope2.move(v[0].front());
    }
  }

  printf("Part 1: %lu\n", rope1.visited_points.size());
  printf("Part 2: %lu\n", rope2.visited_points.size());
}