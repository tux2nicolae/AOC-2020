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

// part 1
long long WriteInValue(const string& mask, long long currentValue)
{
  // apply mask
  for (long long i = 0; i < 36; i++)
  {
    const auto maskElement = mask[35 - i];
    if (maskElement == 'X')
      continue;

    if (maskElement == '1')
      currentValue |= (1LL << i);
    else
      currentValue &= ~(1LL << i);
  }

  return currentValue;
};

// part 2
string MergeAddressIntoMask(string mask, long long address)
{
  // the address has 1
  for (long long i = 0; i < 36; i++)
  {
    const auto posInMask = 35 - i;
    const auto maskElement = mask[posInMask];

    if (maskElement == '0' && (address & (1LL << i)))
      mask[posInMask] = '1';
  }

  return mask;
}

void WriteInMemory(unordered_map<long long, long long> & memory, const string & mask, long long value)
{
  // apply mask
  for (long long i = 0; i < 36; i++)
  {
    const auto posInMask = 35 - i;
    const auto maskElement = mask[posInMask];

    if (maskElement == 'X')
    {
      auto newMask = mask;

      newMask[posInMask] = '0';
      WriteInMemory(memory, newMask, value);

      newMask[posInMask] = '1';
      WriteInMemory(memory, newMask, value);

      return;
    }
  }

  // transform final mask to address
  long long maskAddress = 0;
  for (long long i = 0; i < 36; i++)
  {
    const auto posInMask = 35 - i;
    const auto maskElement = mask[posInMask];

    if (maskElement == '1')
      maskAddress |= (1LL << i);
  }

  memory[maskAddress] = value;
};

int main()
{
  ifstream in("..\\..\\Day14\\src\\_Input.in");
  // ofstream out("..\\..\\Day14\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  unordered_map<long long, long long> memory1;
  unordered_map<long long, long long> memory2;

  string mask;
  for (auto & line : lines)
  {
    auto maskMaches = AOC::ExtractMatches(line, "mask = ([X-X0-1]{36})");
    if (maskMaches.size() == 2)
    {
      mask = maskMaches[1];
      continue;
    }

    auto memoryAccessMatches = AOC::ExtractMatches(line, "mem\\[([0-9]*)\\] = ([0-9]*)");
    assert(memoryAccessMatches.size() == 3);

    const long long address = stoi(memoryAccessMatches[1].c_str());
    long long value = stoi(memoryAccessMatches[2].c_str());

    // part 1
    memory1[address] = WriteInValue(mask, value);

    // part 2
    auto mergedMask = MergeAddressIntoMask(mask, address);
    WriteInMemory(memory2, mergedMask, value);
  }

  // acumulate
  auto part1 = std::accumulate(begin(memory1), end(memory1), 0LL,
    [](long long acc, const pair<long long, long long>& value)
    {
      return acc + value.second;
    }
  );

  auto part2 = std::accumulate(begin(memory2), end(memory2), 0LL, 
    [](long long acc, const pair<long long, long long>& value)
      {
        return acc + value.second;
      }
  );

  cout << part1 << endl;
  cout << part2 << endl;

  return 0;
}
