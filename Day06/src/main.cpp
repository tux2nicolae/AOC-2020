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
  ifstream in("..\\..\\Day06\\src\\Day06.in");
  // ofstream out("..\\..\\Day06\\src\\Day06.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadLines();


  unordered_map<char, int> answers;

  int s = 0;
  int nr = 0;
  for (const auto& line : v)
  {
    if(line.empty())
    {

      for (auto [answer, count] : answers)
      {
        if (nr == count)
          s++;
      };


      nr = 0;
      answers.clear();
      continue;
    }

    nr++;
    for (const auto& c : line)
    {
      answers[c]++;
    }
  }

  cout << s;

  // for (const auto& seat : seats)
  // {
  //   cout << seat.first << " " << seat.second << endl;
  // }


  return 0;
}
