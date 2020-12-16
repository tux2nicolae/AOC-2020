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

int main()
{
  ifstream in("..\\..\\Day15\\src\\_Input.in");
  // ofstream out("..\\..\\Day15\\src\\_Output.out");

  FStreamReader reader(in);
  auto numbers = reader.ReadDataSeparatedByCharAs<long long>();

  unordered_map<int, int> memory;

  int step = 1;
  int lastSpoken = 0;
  int lastSpokenAge = 0;

  for (auto& number : numbers)
  {
    lastSpoken = number;
    lastSpokenAge = step;

    memory[number] = step;

    step++;
  }

  // part 1
  // just change 30000000 with 2020

  while (step <= 30000000)
  {
    if (lastSpokenAge + 1 == step)
    {
      lastSpoken = 0;
      lastSpokenAge = step - memory[0];

      memory[0] = step;
    }
    else
    {
      lastSpoken = lastSpokenAge;
      lastSpokenAge = step - memory[lastSpokenAge];

      memory[lastSpoken] = step;
    }

    step++;
  }
  
  cout << lastSpoken;

  return 0;
}
