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


class Passport
{
public:
  void AddField(const string& name, const string& value)
  {
    fields[name] = value;
  }

  bool IsValid()
  {
    int fieldsNumber = 0;
    for (const string& fieldName : { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" })
    {
      if (fields.find(fieldName) != fields.end())
      {
        fieldsNumber++;
      }
    }

    if (fieldsNumber != 7)
      return false;

    if (!(stoi(fields["byr"]) >= 1920 && stoi(fields["byr"]) <= 2002))
      return false;

    if (!(stoi(fields["iyr"]) >= 2010 && stoi(fields["iyr"]) <= 2020))
      return false;

    if (!(stoi(fields["eyr"]) >= 2020 && stoi(fields["eyr"]) <= 2030))
      return false;

    string height = fields["hgt"];
    if (height.find("cm") != string::npos)
    {
      height.pop_back();
      height.pop_back();

      int hgt = stoi(height);
      if (!(hgt >= 150 && hgt <= 193))
        return false;
    }
    else
    {
      height.pop_back();
      height.pop_back();

      int hgt = stoi(height);
      if (!(hgt >= 59 && hgt <= 76))
        return false;
    }

    smatch matchHcl;
    regex_match(fields["hcl"], matchHcl, regex("#([a-f0-9]{6})$"));
    if (matchHcl.size() == 0)
      return false;


    smatch matchEcl;
    regex_match(fields["ecl"], matchEcl, regex("amb|blu|brn|gry|grn|hzl|oth"));
    if (matchEcl.size() == 0)
      return false;

    smatch matchPid;
    regex_match(fields["pid"], matchPid, regex("([0-9]{9})$"));
    if (matchPid.size() == 0)
      return false;

    return true;
  };

private:
  unordered_map<string, string> fields;
};


int main()
{
  ifstream in("..\\..\\Day04\\src\\Day04.in");
  // ofstream out("..\\..\\Day04\\src\\Day04.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadLines();

  int validPassports = 0;

  Passport passport;
  for (const auto& line : v)
  {
    if (line.empty())
    {
      if(passport.IsValid())
        validPassports++;

      passport = Passport();
      continue;
    }

    auto tokens = AOC::Explode(line, ' ');
    for (const auto& token : tokens)
    {
      auto passwordPair = AOC::Explode(token, ':');
      passport.AddField(passwordPair[0], passwordPair[1]);
    }
  }

  cout << validPassports;
  return 0;
}
