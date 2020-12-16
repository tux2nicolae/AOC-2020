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
  string name;

  int min = 0;
  int max = 0;

  int orMin = 0;
  int orMax = 0;
};

struct Ticket
{
  bool valid = true;
  vector<int> fields;
};

struct FieldCandidates
{
  int fieldId;
  vector<Rule> posibleRules;
};

int main()
{
  ifstream in("..\\..\\Day16\\src\\_Input.in");
  // ofstream out("..\\..\\Day16\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  int lineIndex = 0;

  // parse rules
  vector<Rule> rules;
  while (true)
  {
    auto& line = lines[lineIndex++];
    if (line.empty())
      break;

    auto rulesSplit = AOC::Explode(line, ':');
    assert(rulesSplit.size() == 2);

    auto rulesStr = AOC::Explode(rulesSplit[1], " or ");
    assert(rulesStr.size() == 2);

    auto minmax = AOC::Explode(rulesStr[0], '-');
    assert(minmax.size() == 2);

    auto orMinMax = AOC::Explode(rulesStr[1], '-');
    assert(orMinMax.size() == 2);

    Rule rule{ rulesSplit[0], atoi(minmax[0].c_str()), atoi(minmax[1].c_str()), atoi(orMinMax[0].c_str()), atoi(orMinMax[1].c_str()) };
    rules.push_back(rule);
  }

  assert(lines[lineIndex++] == "your ticket:");

  auto myTicketStrFields = AOC::Explode(lines[lineIndex++], ',');

  assert(lines[lineIndex++] == "");
  assert(lines[lineIndex++] == "nearby tickets:");

  // parse my ticket
  Ticket myTicket;

  transform(begin(myTicketStrFields), end(myTicketStrFields), back_inserter(myTicket.fields),
    [](const string& fieldStr) { return stoi(fieldStr.c_str()); });

  vector<Ticket> allTickets;
  allTickets.push_back(myTicket);

  // parse nearby tickets 
  for(; lineIndex < lines.size(); lineIndex++)
  {
    auto& line = lines[lineIndex];
    if (line.empty())
      continue;

    auto strFields = AOC::Explode(line, ',');

    Ticket ticket;

    transform(begin(strFields), end(strFields), back_inserter(ticket.fields),
      [](const string& fieldStr) { return stoi(fieldStr.c_str()); });

    allTickets.push_back(ticket);
  }

  // search invaid tickets
  int invalidNumbersSum = 0;
  for (auto & ticket : allTickets)
  {
    for(auto & ticketField : ticket.fields)
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
        ticket.valid = false;
      }
    }
  }

  // discard invalid tickets
  allTickets.erase(std::remove_if(allTickets.begin(), allTickets.end(),
    [](const Ticket & ticket)
    {
      return !ticket.valid;
    }), 
    allTickets.end());

  // gather all candidates
  vector<FieldCandidates> candidates;
  for (auto fieldId = 0; fieldId < myTicket.fields.size(); fieldId++)
  {
    FieldCandidates fieldCandidates;
    fieldCandidates.fieldId = fieldId;

    for (const auto & rule : rules)
    {
      int validTickets = 0;
      for (auto& ticket : allTickets)
      {
        // is valid
        if ((rule.min <= ticket.fields[fieldId] && ticket.fields[fieldId] <= rule.max) ||
          (rule.orMin <= ticket.fields[fieldId] && ticket.fields[fieldId] <= rule.orMax))
        {
          validTickets++;
        }
      }

      if(validTickets == allTickets.size())
        fieldCandidates.posibleRules.push_back(rule);
    }

    candidates.push_back(fieldCandidates);
  }

  // sort
  sort(begin(candidates), end(candidates),
    [](const FieldCandidates& first, const FieldCandidates& second)
    {
      return first.posibleRules.size() < second.posibleRules.size();
    });

  // process unique candidates
  for (auto [i, j] : AOC::GenerateIndexCombinations<2>(candidates.size()))
  {
    auto& currentCandidateRules = candidates[i].posibleRules;
    assert(currentCandidateRules.size() == 1);
  
    auto& nextCandidateRules = candidates[j].posibleRules;
    nextCandidateRules.erase(remove_if(begin(nextCandidateRules), end(nextCandidateRules), 
      [&](const Rule & rule) {
        return rule.name == currentCandidateRules[0].name;
      }), 
      nextCandidateRules.end());
  }

  // process departure products
  long long departureProduct = 1;
  for (auto [decodedFieldId, rules] : candidates)
  {
    assert(rules.size() == 1);
    auto& rule = rules[0];

    if (rule.name.find("departure") != string::npos)
    {
      departureProduct *= myTicket.fields[decodedFieldId];
    }
  }

  cout << invalidNumbersSum << endl;
  cout << departureProduct << endl;

  return 0;
}
