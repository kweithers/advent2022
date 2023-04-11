#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <memory>
#include <map>

using namespace std;

struct Node
{
  map<string, unique_ptr<Node>> children;
  int size;
  int weight;
  string name;
  Node *parent;

  Node(int file_size, string node_name, Node *node_parent)
  {
    size = file_size;
    name = node_name;
    parent = node_parent;
  };

  Node *find_child(string child_name)
  {
    auto iter = children.find(child_name);
    return iter->second.get();
  }
};

void bubble_up_weight(Node *node, int this_file_size)
{
  node->weight += this_file_size;
  if (node->parent != nullptr)
  {
    bubble_up_weight(node->parent, this_file_size);
  }
};

void traverse_tree(Node *node, int *sum1, int *sum2, int space_needed)
{
  // Part 1
  if (node->weight <= 100000)
  {
    *sum1 += node->weight;
  }

  // Part 2
  if (node->weight >= space_needed && node->weight <= *sum2)
  {
    *sum2 = node->weight;
  }

  for (auto &child : node->children)
  {
    if (child.second.get()->children.size() > 0) // If it's a dir
    {
      traverse_tree(child.second.get(), sum1, sum2, space_needed);
    }
  }
}

int main()
{
  fstream input;
  input.open("input.txt");

  unique_ptr<Node> root(new Node(0, "/", nullptr));

  Node *current = root.get();

  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(" "));

    if (v[0] == "$")
    {
      if (v[1] == "ls")
      { // The next lines will be either files or dirs.
        continue;
      }
      else if (v[1] == "cd")
      { // Update 'current' pointer.
        if (v[2] == "..")
        { // Update 'current' pointer to its parent.
          current = current->parent;
        }
        else
        { // Update 'current' pointer to the specified child.
          current = current->find_child(v[2]);
        }
      }
    }
    else if (v[0] == "dir")
    { // This will be a directory --> e.g. dir asjdfh
      current->children.emplace(std::make_pair(v[1], unique_ptr<Node>(new Node(0, v[1], current))));
    }
    else
    { // This will be a file size --> e.g. 244213 mvng
      current->children.emplace(std::make_pair(v[1], unique_ptr<Node>(new Node(stoi(v[0]), v[1], current))));
      bubble_up_weight(current, stoi(v[0]));
    }
  }

  int part1 = 0;
  int part2 = INT_MAX;

  int space_needed = 30000000 - (70000000 - root.get()->weight);

  traverse_tree(root.get(), &part1, &part2, space_needed);

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
}