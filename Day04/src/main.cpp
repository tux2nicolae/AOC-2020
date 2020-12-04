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

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Time.h"


int main()
{
  ifstream in("..\\..\\Day04\\src\\Day04.in");
  // ofstream out("..\\..\\Day04\\src\\Day04.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadVectorOfWords();

  int total = 0;

  unordered_map<string, string> passwordMap;
  for (const auto& line : v)
  {
    if (line.empty())
    {
      int s = 0;
      for (const string& test : { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" })
      {
        if (passwordMap.find(test) != passwordMap.end())
        {
          s++;
        }
      }

      if (s != 7)
      {
        passwordMap.clear();
        continue;
      }

      if (!(stoi(passwordMap["byr"]) >= 1920 && stoi(passwordMap["byr"]) <= 2002))
      {
        passwordMap.clear();
        continue;
      }

      if (!(stoi(passwordMap["iyr"]) >= 2010 && stoi(passwordMap["iyr"]) <= 2020))
      {
        passwordMap.clear();
        continue;
      }

      if (!(stoi(passwordMap["eyr"]) >= 2020 && stoi(passwordMap["eyr"]) <= 2030))
      {
        passwordMap.clear();
        continue;
      }

      string height = passwordMap["hgt"];
      if (height.find("cm") != string::npos)
      {
        height.pop_back();
        height.pop_back();

        int hgt = stoi(height);
        if (!(hgt >= 150 && hgt <= 193))
        {
          passwordMap.clear();
          continue;
        }
      }
      else
      {
        height.pop_back();
        height.pop_back();

        int hgt = stoi(height);
        if (!(hgt >= 59 && hgt <= 76))
        {
          passwordMap.clear();
          continue;
        }
      }

      smatch match;
      regex_match(passwordMap["hcl"], match, regex("#([a-f0-9]{6})$"));
      if (match.size() == 0)
      {
        passwordMap.clear();
        continue;
      }

      string ecl = passwordMap["ecl"];
      if (!(ecl == "amb"
        || ecl == "blu"
        || ecl == "brn"
        || ecl == "gry"
        || ecl == "grn"
        || ecl == "hzl"
        || ecl == "oth"))
      {
        passwordMap.clear();
        continue;
      }

      smatch match1;
      regex_match(passwordMap["pid"], match1, regex("([0-9]{9})$"));
      if (match1.size() == 0)
      {
        passwordMap.clear();
        continue;
      }
        
      total++;

      passwordMap.clear();
      continue;
    }



    auto tokens = AOC::Explode(line, ' ');

    for (const auto& token : tokens)
    {
      auto passwordPair = AOC::Explode(token, ':');
      passwordMap[passwordPair[0]] = passwordPair[1];
    }
  }

  // sort(begin(v), end(v));

  cout << total;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
