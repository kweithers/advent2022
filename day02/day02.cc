#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Round
{
  string opponent_move;
  string my_move;

  int round_score()
  {
    if (my_move == "X")
    { // Rock
      if (opponent_move == "A")
      { // Rock
        return 3;
      }
      else if (opponent_move == "B")
      { // Paper
        return 0;
      }
      else if (opponent_move == "C")
      { // Scissors
        return 6;
      }
    }
    else if (my_move == "Y")
    { // Paper
      if (opponent_move == "A")
      { // Rock
        return 6;
      }
      else if (opponent_move == "B")
      { // Paper
        return 3;
      }
      else if (opponent_move == "C")
      { // Scissors
        return 0;
      }
    }
    // Scissors
    if (opponent_move == "A")
    { // Rock
      return 0;
    }
    else if (opponent_move == "B")
    { // Paper
      return 6;
    }
    // Scissors
    return 3;
  };

  int move_score()
  {
    if (my_move == "X")
    {
      return 1;
    }
    else if (my_move == "Y")
    {
      return 2;
    }
    return 3;
  }

  int round_score2()
  {
    if (my_move == "X")
    { // Must Lose
      if (opponent_move == "A")
      { // Rock --> Play Scissors
        return 0 + 3;
      }
      else if (opponent_move == "B")
      { // Paper --> Play Rock
        return 0 + 1;
      }
      else if (opponent_move == "C")
      { // Scissors --> Play Paper
        return 0 + 2;
      }
    }
    else if (my_move == "Y")
    { // Must Draw
      if (opponent_move == "A")
      { // Rock --> Play Rock
        return 3 + 1;
      }
      else if (opponent_move == "B")
      { // Paper --> Play Paper
        return 3 + 2;
      }
      else if (opponent_move == "C")
      { // Scissors --> Play Scissors
        return 3 + 3;
      }
    }
    // Must Win
    if (opponent_move == "A")
    { // Rock --> Play Paper
      return 6 + 2;
    }
    else if (opponent_move == "B")
    { // Paper --> Play Scissors
      return 6 + 3;
    }
    // Scissors --> Play Rock
    return 6 + 1;
  };
};

int main()
{
  fstream input;
  input.open("input.txt");

  int current_score = 0;
  int part2_score = 0;

  string line;
  while (getline(input, line))
  {
    stringstream ss;
    ss << line;
    Round r;
    ss >> r.opponent_move;
    ss >> r.my_move;
    current_score += r.move_score();
    current_score += r.round_score();
    part2_score += r.round_score2();
  }
  input.close();
  cout << "Part 1: " << current_score << endl;
  cout << "Part 2: " << part2_score << endl;
}
