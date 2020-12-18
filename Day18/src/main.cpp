/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <numeric>
#include <regex>

#include <assert.h>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

long long Evaluate(string& line, size_t & index, bool part1) 
{
  // parse current number
  auto getCurrentNumber = [&]() -> long long
  {
    int number = 0;

    while (line[index] >= '0' && line[index] <= '9') {
      number = number * 10 + line[index] - '0';
      index++;
    }

    assert(number != 0);
    return number;
  };

  // current number or evaluate paranthese
  auto getNextNumber = [&]() -> long long
  {
    if (line[index] == '(')
    {
      long long number = Evaluate(line, ++index, part1);

      assert(line[index++] == ')');
      return number;
    }

    return getCurrentNumber();
  };

  // iterate while * or +
  long long number = getNextNumber();
  while (index < line.size())
  {
    if (line[index] == ')')
      break;

    switch (line[index++])
    {
    case '+':
      number += getNextNumber();
      break;
    case '*':
      number *= part1 ? getNextNumber() : Evaluate(line, index, part1);
      break;
    default:
      assert(false);
      break;
    }
  }
  
  return number;
}

int main()
{
  ifstream in("..\\..\\Day18\\src\\_Input.in");
  // ofstream out("..\\..\\Day18\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  long long sum1 = 0;
  long long sum2 = 0;
  for (auto line : lines)
  {
    // remove all spaces
    line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x)
      {
        return std::isspace(x);
      }), line.end());

    size_t index1 = 0;
    sum1 += Evaluate(line, index1, true);

    size_t index2 = 0;
    sum2 += Evaluate(line, index2, false);
  }

  cout << sum1 << endl << sum2 << endl;

  return 0;
}
