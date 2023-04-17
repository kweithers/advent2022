#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

enum Op
{
  add,
  multiply
};

struct Operation
{
  Op operation;
  bool old;
  int value;
};

struct Monkey
{
  deque<int> items;
  Operation operation;
  int modulus;
  int if_true_throw_to;
  int if_false_throw_to;
  int inspection_count;
};

struct ManyMonkeys
{
  vector<Monkey> monkeys;

  ManyMonkeys(string s) // Test example
  {
    deque<int> q0;
    deque<int> q1;
    deque<int> q2;
    deque<int> q3;

    q0.push_back(79);
    q0.push_back(98);

    q1.push_back(54);
    q1.push_back(65);
    q1.push_back(75);
    q1.push_back(74);

    q2.push_back(79);
    q2.push_back(60);
    q2.push_back(97);

    q3.push_back(74);

    Operation op0;
    Operation op1;
    Operation op2;
    Operation op3;

    op0.operation = multiply;
    op0.old = false;
    op0.value = 19;

    op1.operation = add;
    op1.old = false;
    op1.value = 6;

    op2.operation = multiply;
    op2.old = true;

    op3.operation = add;
    op3.old = false;
    op3.value = 3;

    Monkey m0;
    Monkey m1;
    Monkey m2;
    Monkey m3;

    m0.items = q0;
    m0.operation = op0;
    m0.modulus = 23;
    m0.if_true_throw_to = 2;
    m0.if_false_throw_to = 3;
    m0.inspection_count = 0;

    m1.items = q1;
    m1.operation = op1;
    m1.modulus = 19;
    m1.if_true_throw_to = 2;
    m1.if_false_throw_to = 0;
    m1.inspection_count = 0;

    m2.items = q2;
    m2.operation = op2;
    m2.modulus = 13;
    m2.if_true_throw_to = 1;
    m2.if_false_throw_to = 3;
    m2.inspection_count = 0;

    m3.items = q3;
    m3.operation = op3;
    m3.modulus = 17;
    m3.if_true_throw_to = 0;
    m3.if_false_throw_to = 1;
    m3.inspection_count = 0;

    monkeys.push_back(m0);
    monkeys.push_back(m1);
    monkeys.push_back(m2);
    monkeys.push_back(m3);
  }

  ManyMonkeys() // Real input
  {
    deque<int> q0 = {93, 54, 69, 66, 71};
    deque<int> q1 = {89, 51, 80, 66};
    deque<int> q2 = {90, 92, 63, 91, 96, 63, 64};
    deque<int> q3 = {65, 77};
    deque<int> q4 = {76, 68, 94};
    deque<int> q5 = {86, 65, 66, 97, 73, 83};
    deque<int> q6 = {78};
    deque<int> q7 = {89, 57, 59, 61, 87, 55, 55, 88};

    Operation op0;
    Operation op1;
    Operation op2;
    Operation op3;
    Operation op4;
    Operation op5;
    Operation op6;
    Operation op7;

    op0.operation = multiply;
    op0.old = false;
    op0.value = 3;

    op1.operation = multiply;
    op1.old = false;
    op1.value = 17;

    op2.operation = add;
    op2.old = false;
    op2.value = 1;

    op3.operation = add;
    op3.old = false;
    op3.value = 2;

    op4.operation = multiply;
    op4.old = true;
    
    op5.operation = add;
    op5.old = false;
    op5.value = 8;

    op6.operation = add;
    op6.old = false;
    op6.value = 6;

    op7.operation = add;
    op7.old = false;
    op7.value = 7;

    Monkey m0;
    Monkey m1;
    Monkey m2;
    Monkey m3;
    Monkey m4;
    Monkey m5;
    Monkey m6;
    Monkey m7;

    m0.items = q0;
    m0.operation = op0;
    m0.modulus = 7;
    m0.if_true_throw_to = 7;
    m0.if_false_throw_to = 1;
    m0.inspection_count = 0;

    m1.items = q1;
    m1.operation = op1;
    m1.modulus = 19;
    m1.if_true_throw_to = 5;
    m1.if_false_throw_to = 7;
    m1.inspection_count = 0;

    m2.items = q2;
    m2.operation = op2;
    m2.modulus = 13;
    m2.if_true_throw_to = 4;
    m2.if_false_throw_to = 3;
    m2.inspection_count = 0;

    m3.items = q3;
    m3.operation = op3;
    m3.modulus = 3;
    m3.if_true_throw_to = 4;
    m3.if_false_throw_to = 6;
    m3.inspection_count = 0;

    m4.items = q4;
    m4.operation = op4;
    m4.modulus = 2;
    m4.if_true_throw_to = 0;
    m4.if_false_throw_to = 6;
    m4.inspection_count = 0;

    m5.items = q5;
    m5.operation = op5;
    m5.modulus = 11;
    m5.if_true_throw_to = 2;
    m5.if_false_throw_to = 3;
    m5.inspection_count = 0;

    m6.items = q6;
    m6.operation = op6;
    m6.modulus = 17;
    m6.if_true_throw_to = 0;
    m6.if_false_throw_to = 1;
    m6.inspection_count = 0;

    m7.items = q7;
    m7.operation = op7;
    m7.modulus = 5;
    m7.if_true_throw_to = 2;
    m7.if_false_throw_to = 5;
    m7.inspection_count = 0;

    monkeys.push_back(m0);
    monkeys.push_back(m1);
    monkeys.push_back(m2);
    monkeys.push_back(m3);
    monkeys.push_back(m4);
    monkeys.push_back(m5);
    monkeys.push_back(m6);
    monkeys.push_back(m7);
  }

  void RunRound()
  {
    for (int i = 0; i < monkeys.size(); i++)
    {
      int j_size = monkeys[i].items.size();
      for (int j = 0; j < j_size; j++)
      {
        int value = monkeys[i].items.front();
        monkeys[i].items.pop_front();
        // cout << value;

        monkeys[i].inspection_count++;

        // Apply operation
        if (monkeys[i].operation.operation == add)
        {
          if (monkeys[i].operation.old)
          {
            value += value;
          }
          else
          {
            value += monkeys[i].operation.value;
          }
        }
        else
        {
          if (monkeys[i].operation.old)
          {
            value *= value;
          }
          else
          {
            value *= monkeys[i].operation.value;
          }
        }
        // cout << " " << value;
        // Divide it by three
        value /= 3;
        // cout << " " << value << endl;;

        // Test and Throw it to next monkey
        if (value % monkeys[i].modulus == 0)
        {
          monkeys[monkeys[i].if_true_throw_to].items.push_back(value);
          // cout << "Throwing " << value << "to " << monkeys[i].if_true_throw_to << endl;
        }
        else
        {
          monkeys[monkeys[i].if_false_throw_to].items.push_back(value);
          // cout << "Throwing " << value << "to " << monkeys[i].if_false_throw_to << endl;
        }
      }
    }
  };
};

int main()
{
  ManyMonkeys part1 = ManyMonkeys();

  for (auto i = 0; i < 20; i++)
    part1.RunRound();

  for (int i = 0; i < part1.monkeys.size(); i++)
  {
    cout << "Monkey " << i << " has inspected " << part1.monkeys[i].inspection_count << " items" << endl;
    // for (int j = 0; j < part1.monkeys[i].items.size(); j++)
    // {
    //   cout << part1.monkeys[i].items[j] << " ";
    // }
    // cout << endl;
  }
}
