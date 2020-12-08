/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <optional>
#include <numeric>
#include <regex>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

struct Instruction
{
  string op;
  int value;
};

Instruction swapInstruction(Instruction aInstruction)
{
  if (aInstruction.op == "jmp")
    aInstruction.op = "nop";
  else
    aInstruction.op = "jmp";

  return aInstruction;
}

int main()
{
  ifstream in("..\\..\\Day08\\src\\_Input.in");
  // ofstream out("..\\..\\Day08\\src\\_Output.out");

  vector<Instruction> readProgram;
  vector<int> jumpOrNop;

  string op;
  int value;

  int i = 0;
  while (in >> op >> value)
  {
    readProgram.push_back(Instruction{op, value});

    if (op == "jmp" || op == "nop")
    {
      jumpOrNop.push_back(i);
    }

    i++;
  }

  for(auto & changeInstruction : jumpOrNop)
  {
    bool stopped = false;

    int acc = 0;
    unordered_map<int, bool> visited;

    vector<Instruction> program = readProgram;
    program[changeInstruction] = swapInstruction(program[changeInstruction]);

    int pointer = 0;
    while (pointer < program.size())
    {
      if (visited[pointer])
      {
        stopped = true;
        break;
      }

      visited[pointer] = true;

      const Instruction& currentInstruction = program[pointer];

      if (currentInstruction.op == "jmp")
      {
        pointer += currentInstruction.value;
        continue;
      }

      if (currentInstruction.op == "acc")
      {
        acc += currentInstruction.value;
      }

      // go next
      pointer++;
    }

    if (!stopped)
      cout << acc;
  }

  return 0;
}
