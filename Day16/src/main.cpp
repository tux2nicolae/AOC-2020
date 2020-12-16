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
  ifstream in("..\\..\\Day16\\src\\_Input.in");
  // ofstream out("..\\..\\Day16\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  struct Rule
  {
    string name;

    int min = 0;
    int max = 0;

    int orMin = 0;
    int orMax = 0;
  };

  vector<Rule> rules;

  // parse rules
  for (int i = 0; i < 20; ++i)
  {
    auto& line = lines[i];
    auto rulesSplit = AOC::Explode(line, ':');
    assert(rulesSplit.size() == 2);

    auto rulesStr = AOC::Explode(rulesSplit[1], ',');
    assert(rulesStr.size() == 2);

    auto minmax = AOC::Explode(rulesStr[0], '-');
    assert(minmax.size() == 2);

    auto orMinMax = AOC::Explode(rulesStr[1], '-');
    assert(orMinMax.size() == 2);

    Rule rule{ rulesSplit[0], atoi(minmax[0].c_str()), atoi(minmax[1].c_str()), atoi(orMinMax[0].c_str()), atoi(orMinMax[1].c_str()) };
    rules.push_back(rule);
  }

  // parse nearby tickets 
  struct Ticket
  {
    bool valid = true;
    vector<int> fields;
  };

  vector<Ticket> nearbyTickets;
  for (int i = 25; i < lines.size(); ++i)
  {
    auto& line = lines[i];
    if (line.empty())
      continue;

    auto numbers = AOC::Explode(line, ',');

    Ticket ticket;
    for (auto numberStr : numbers)
      ticket.fields.push_back(atoi(numberStr.c_str()));

    nearbyTickets.push_back(ticket);
  }

  int invalidNumbersSum = 0;
  for (auto & nearbyTicket : nearbyTickets)
  {
    for(auto & ticketField : nearbyTicket.fields)
    {
      int validRules = 0;

      for (auto rule : rules)
      {
        // is valid
        if ((rule.min <= ticketField && ticketField <= rule.max) ||
          (rule.orMin <= ticketField && ticketField <= rule.orMax))
        {
          validRules++;
        }
      }

      if (validRules == 0)
      {
        invalidNumbersSum += ticketField;
        nearbyTicket.valid = false;
      }
    }
  }

  // discard invalid tickets
  nearbyTickets.erase(std::remove_if(nearbyTickets.begin(), nearbyTickets.end(), 
    [](const Ticket & ticket)
    {
      return !ticket.valid;
    }), nearbyTickets.end());

  // add my ticket
  Ticket myTicket;
  myTicket.valid = true;
  myTicket.fields = { 157,73,79,191,113,59,109,61,103,101,67,193,97,179,107,89,53,71,181,83 };

  nearbyTickets.push_back(myTicket);

  // fieldId, rules
  struct FieldCandidates
  {
    int fieldId;
    vector<Rule> posibleRules;
  };

  vector<FieldCandidates> candidates;

  // part 2
  for (auto fieldId = 0; fieldId < myTicket.fields.size(); fieldId++)
  {
    FieldCandidates fieldCandidates;
    fieldCandidates.fieldId = fieldId;

    for (const auto & rule : rules)
    {
      int validTickets = 0;
      for (auto& ticket : nearbyTickets)
      {
        // is valid
        if ((rule.min <= ticket.fields[fieldId] && ticket.fields[fieldId] <= rule.max) ||
          (rule.orMin <= ticket.fields[fieldId] && ticket.fields[fieldId] <= rule.orMax))
        {
          validTickets++;
        }
      }

      if(validTickets == nearbyTickets.size())
        fieldCandidates.posibleRules.push_back(rule);
    }

    candidates.push_back(fieldCandidates);
  }

  sort(begin(candidates), end(candidates),
    [](const FieldCandidates& first, const FieldCandidates& second)
    {
      return first.posibleRules.size() < second.posibleRules.size();
    });

  for (auto [i, j] : AOC::GenerateIndexCombinations<2>(candidates.size()))
  {
    auto& currentCandidateRules = candidates[i].posibleRules;
    assert(currentCandidateRules.size() == 1);
  
    // remove rules from second
    auto& nextCandidateRules = candidates[j].posibleRules;
    nextCandidateRules.erase(remove_if(begin(nextCandidateRules), end(nextCandidateRules), 
      [&](const Rule & rule) {
        return rule.name == currentCandidateRules[0].name;
      }), 
      nextCandidateRules.end());
  }

  long long departureProduct = 1;
  for (auto [decodedFieldId, rules] : candidates)
  {
    assert(rules.size() == 1);
    auto& rule = rules[0];

    if (rule.name.find("departure") != string::npos)
    {
      cout << rule.name << ":" << myTicket.fields[decodedFieldId] << endl;
      departureProduct *= myTicket.fields[decodedFieldId];
    }
  }

  cout << endl;

  cout << invalidNumbersSum << endl;
  cout << departureProduct << endl;

  return 0;
}
