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

long long EvaluatePart1(string& line, size_t & index) 
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
    return line[index] == '(' ? EvaluatePart1(line, ++index)
      : getCurrentNumber();
  };

  // iterate while * or +
  long long number = getNextNumber();
  while (index < line.size())
  {

    switch (line[index++])
    {
    case '+':
      number += getNextNumber();
      break;
    case '*':
      number *= getNextNumber();
      break;
    case ')':
      return number;
      break;
    default:
      assert(false);
      break;
    }
  }
  
  return number;
}

long long EvaluatePart2(string& line, size_t& index)
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
      long long number = EvaluatePart2(line, ++index);

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
      number *= EvaluatePart2(line, index);
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
    sum1 += EvaluatePart1(line, index1);

    size_t index2 = 0;
    sum2 += EvaluatePart2(line, index2);
  }

  cout << sum1 << endl << sum2 << endl;

  return 0;
}
