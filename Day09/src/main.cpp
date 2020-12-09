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

int main()
{
  ifstream in("..\\..\\Day09\\src\\_Input.in");
  // ofstream out("..\\..\\Day09\\src\\_Output.out");

  FStreamReader reader(in);

  vector<long long> numbers = reader.ReadDataAs<long long>();

  //-----------------------------------

  long long part1Number = 0;
  for (int i = 25; i < numbers.size(); ++i)
  {
    bool found = false;

    for (int j = i - 25; j < i; j++)
    {
      for (int k = j + 1; k < i; k++)
      {
        if (numbers[i] == numbers[j] + numbers[k])
          found = true;
      }
    }

    if (!found)
    {
      part1Number = numbers[i];
    }
  }

  cout << part1Number << endl << endl;

  vector<long long> sums;
  sums.reserve(numbers.size());

  std::partial_sum(numbers.begin(), numbers.end(),
    back_inserter(sums));

  vector<long long> range;
  for (int i = 0; i < numbers.size(); ++i)
  {
    for (int j = i + 1; j < numbers.size(); ++j)
    {
      if (sums[j] - sums[i] == part1Number)
      {
        for(int k = i + 1; k<=j; k++)
          range.push_back(numbers[k]);

        i = numbers.size();
        j = numbers.size();
        break;
      }
    }
  }

  sort(begin(range), end(range));

  cout << range.front() + range.back();

  return 0;
}
