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

struct Rule
{
  char c{ 0 };
  vector<vector<size_t>> subRules;
};

vector<size_t> MatchRule(const unordered_map<size_t, Rule>& rules, size_t ruleId, const string& line, size_t offset)
{
  if (offset > line.size())
    return {};

  const Rule& rule = rules.at(ruleId);
  size_t maxOffset = offset;

  if (rule.c)
  {
    if (rule.c == line[offset])
      return { 1 };
    else
      return {};
  }

  vector<size_t> matchingRules;

  bool machAny = false;
  for (auto& subRule : rule.subRules)
  {
    bool machAll = true;
    vector<size_t> previousMachingSubRules{ 0 };

    for (auto subRuleId : subRule)
    {
      vector<size_t> nextMachingSubRules;
      for (auto& prevLenght : previousMachingSubRules)
      {
        auto temp = MatchRule(rules, subRuleId, line, offset + prevLenght);
        transform(begin(temp), end(temp), back_inserter(nextMachingSubRules),
          [&](const size_t length) { return prevLenght + length; });
      }

      machAll &= !nextMachingSubRules.empty();
      previousMachingSubRules = nextMachingSubRules;
    }

    if (machAll)
    {
      copy(begin(previousMachingSubRules), end(previousMachingSubRules), back_inserter(matchingRules));
    }

    machAny |= machAll;
  }

  return matchingRules;
}

int main()
{
  ifstream in("..\\..\\Day19\\src\\_Input.in");
  // ofstream out("..\\..\\Day19\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  size_t lineIndex = 0;

  // parse rules
  unordered_map<size_t, Rule> rules;
  while (true)
  {
    auto& line = lines[lineIndex++];
    if (line.empty())
      break;

    auto rulesSplit = AOC::Explode(line, ':');
    assert(rulesSplit.size() == 2);

    Rule rule;

    if (rulesSplit[1].find('"') != string::npos)
    {
      // [space]"a"
      rule.c = rulesSplit[1][2];
    }
    else
    {
      // add subrules
      for (auto& subRule : AOC::Explode(rulesSplit[1], " \\| "))
      {
        vector<size_t> nextSubRules;

        for (auto nextRule : AOC::Explode(subRule, ' '))
        {
          if (!nextRule.empty())
            nextSubRules.push_back(stoll(nextRule));
        }

        rule.subRules.push_back(nextSubRules);
      }
    }

    rules[stoll(rulesSplit[0])] = rule;
  }

  const size_t startMessagesIndex = lineIndex;

  auto getNumberOfMaches = [&]()
  {
    int numberOfMaches = 0;

    for (size_t i = startMessagesIndex; i < lines.size(); i++)
    {
      auto& line = lines[i];
      if (line.empty())
        continue;

      auto matchLengths = MatchRule(rules, 0, line, 0);

      bool found = false;
      for (auto matchLendth : matchLengths)
      {
        if (matchLendth == line.size())
          found = true;
      }

      numberOfMaches += found;
    }

    return numberOfMaches;
  };

  // part 1
  cout << getNumberOfMaches() << endl;

  // part 2
  rules[8] = Rule{ 0, { {42}, {42, 8} } };
  rules[11] = Rule{ 0, { {42, 31}, {42, 11, 31} } };

  cout << getNumberOfMaches() << endl;

  return 0;
}
