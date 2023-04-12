#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <compare>

using namespace std;

struct Forest
{
  vector<vector<char>> trees;
};

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

void walk_right_all_rows(Forest *grid, set<Point> *set)
{
  for (int j = 0; j < grid->trees.size(); j++)
  {
    char current_smallest = '0';
    for (int i = 0; i < grid->trees.size(); i++)
    {
      if (i == 0 || grid->trees[j][i] > current_smallest)
      {
        set->emplace(Point{j, i});
        current_smallest = grid->trees[j][i];
      }
    }
  }
}
void walk_left_all_rows(Forest *grid, set<Point> *set)
{
  for (int j = 0; j < grid->trees.size(); j++)
  {
    char current_smallest = '0';
    for (int i = grid->trees.size() - 1; i > -1; i--)
    {
      if (i == grid->trees.size() - 1 || grid->trees[j][i] > current_smallest)
      {
        set->emplace(Point{j, i});
        current_smallest = grid->trees[j][i];
      }
    }
  }
}
void walk_down_all_columns(Forest *grid, set<Point> *set)
{
  for (int i = 0; i < grid->trees.size(); i++)
  {
    char current_smallest = '0';
    for (int j = 0; j < grid->trees.size(); j++)
    {
      if (j == 0 || grid->trees[j][i] > current_smallest)
      {
        set->emplace(Point{j, i});
        current_smallest = grid->trees[j][i];
      }
    }
  }
}
void walk_up_all_columns(Forest *grid, set<Point> *set)
{
  for (int i = 0; i < grid->trees.size(); i++)
  {
    char current_smallest = '0';
    for (int j = grid->trees.size() - 1; j > -1; j--)
    {
      if (j == grid->trees.size() - 1 || grid->trees[j][i] > current_smallest)
      {
        set->emplace(Point{j, i});
        current_smallest = grid->trees[j][i];
      }
    }
  }
}

int look_right(Forest *grid, int y, int x)
{
  if (x == grid->trees.size() - 1)
  {
    return 0;
  }
  int i = 1;
  while (x + i < grid->trees.size() - 1)
  {
    if (grid->trees[y][x] <= grid->trees[y][x + i])
    {
      break;
    }
    else
    {
      i++;
    }
  }
  return i;
}
int look_left(Forest *grid, int y, int x)
{
  if (x == 0)
  {
    return 0;
  }
  int i = -1;
  while (x + i > 0)
  {
    if (grid->trees[y][x] <= grid->trees[y][x + i])
    {
      break;
    }
    else
    {
      i--;
    }
  }
  return -i;
}
int look_down(Forest *grid, int y, int x)
{
  if (y == grid->trees.size() - 1)
  {
    return 0;
  }
  int j = 1;
  while (y + j < grid->trees.size() - 1)
  {
    if (grid->trees[y][x] <= grid->trees[y + j][x])
    {
      break;
    }
    else
    {
      j++;
    }
  }
  return j;
}
int look_up(Forest *grid, int y, int x)
{
  if (y == 0)
  {
    return 0;
  }
  int j = -1;
  while (y + j > 0)
  {
    if (grid->trees[y][x] <= grid->trees[y + j][x])
    {
      break;
    }
    else
    {
      j--;
    }
  }
  return -j;
}

int calculate_score(Forest *grid, int y, int x)
{
  return look_right(grid, y, x) * look_left(grid, y, x) * look_up(grid, y, x) * look_down(grid, y, x);
}

int main()
{
  fstream input;
  input.open("input.txt");

  Forest grid;
  set<Point> visible_points;

  string line;
  while (getline(input, line))
  {
    vector<char> v(line.begin(), line.end());
    grid.trees.push_back(v);
  }

  walk_right_all_rows(&grid, &visible_points);
  walk_left_all_rows(&grid, &visible_points);
  walk_down_all_columns(&grid, &visible_points);
  walk_up_all_columns(&grid, &visible_points);

  int best_score = 0;
  for (int j = 0; j < grid.trees.size(); j++)
  {
    for (int i = 0; i < grid.trees.size(); i++)
    {
      best_score = max(best_score, calculate_score(&grid, j, i));
    }
  }
  
  cout << "Part 1: " << visible_points.size() << endl;
  cout << "Part 2: " << best_score << endl;
}