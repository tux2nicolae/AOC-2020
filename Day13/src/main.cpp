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

struct Bus
{
  long long bussId{};
  long long departDiff{};
};

long long Run(Bus bus, long long timestamp, long long step)
{
  for (; (timestamp + bus.departDiff) % bus.bussId != 0; timestamp += step);
  return timestamp;
}

int main()
{
  ifstream in("..\\..\\Day13\\src\\_Input.in");
  // ofstream out("..\\..\\Day13\\src\\_Output.out");

  int earliest{}; 
  string strData;

  in >> earliest >> strData;
  auto data = AOC::Explode(strData, ',');

  long long minBusId = 0;
  long long minBusStop = numeric_limits<long long>::max();

  // part 1
  for (auto& bus : data)
  {
    if (bus == "x")
      continue;

    long long busId = stoi(bus.c_str());

    long long busStop = 1;
    for (long long i = 0; busStop < earliest; ++i)
      busStop = i * busId;

    if (minBusStop > busStop)
    {
      minBusId = busId;
      minBusStop = busStop;
    }
  };

  std::cout << (minBusStop - earliest) * minBusId << endl;

  // part 2
  assert(data.size() && data[0] != "x");
  long long firstBusId = stoi(data[0].c_str());

  long long timestamp = firstBusId;
  long long step = firstBusId;

  for (int diff = 1, i = 1; i < data.size(); ++i, ++diff)
  {
    auto& busStr = data[i];
    if (busStr == "x")
      continue;
  
    Bus bus;
    bus.bussId = stoi(busStr.c_str());
    bus.departDiff = diff;

    // next timestamp
    timestamp = Run(bus, timestamp, step);

    // next step
    step = step * bus.bussId;
  }
  
  cout << timestamp << endl;
  return 0;
}
