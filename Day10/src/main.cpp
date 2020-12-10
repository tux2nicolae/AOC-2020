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

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

int main()
{
  ifstream in("..\\..\\Day10\\src\\_Input.in");
  // ofstream out("..\\..\\Day10\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadDataAs<int>();

  std::sort(begin(lines), end(lines));

  unordered_map<int, bool> exists;
  exists[0] = true;

  //-----------------------------------

  int oneDifference = 0;
  int threeDiference = 1;

  int previous = 0;
  for(auto adapter : lines)
  {
    exists[adapter] = true;

    if (adapter - previous == 1)
      oneDifference++;

    if (adapter - previous == 3)
      threeDiference++;

    previous = adapter;
  }

  cout << oneDifference * threeDiference << endl;

  //-----------------------------------

  unordered_map<int, long long> arrangments;

  arrangments[0] = arrangments[-1] = arrangments[-2] = 1;
  for (auto adapter : lines)
  {
    long long sum = 0;
    if (exists[adapter - 1])
      sum += arrangments[adapter - 1];

    if (exists[adapter - 2])
      sum += arrangments[adapter - 2];

    if (exists[adapter - 3])
      sum += arrangments[adapter - 3];

    arrangments[adapter] = sum;
  }

  cout << arrangments[lines.back()];

  return 0;
}
