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
#include <queue>
#include <deque>

#include <assert.h>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"


pair<bool, deque<int>> NormalCombat(deque<int> player1, deque<int> player2)
{
  while (!player1.empty() && !player2.empty())
  {
    auto player1Top = player1.front();
    auto player2Top = player2.front();
  
    player1.pop_front();
    player2.pop_front();
  
    if (player1Top > player2Top)
    {
      player1.push_back(player1Top);
      player1.push_back(player2Top);
    }
    else
    {
      player2.push_back(player2Top);
      player2.push_back(player1Top);
    }
  }

  return { !player1.empty(), !player1.empty() ? player1 : player2 };
}

pair<bool, deque<int>> RecursiveCombat(deque<int> player1, deque<int> player2)
{
  unordered_map<string, bool> hystory;

  auto calculateHash = [](deque<int>& player1, deque<int>& player2)->string
  {
    string hash = accumulate(begin(player1), end(player1), string(), [](string acc, int card) { return acc + to_string(card) + ","; });
    hash += ":" + accumulate(begin(player2), end(player2), string(), [](string acc, int card) { return acc + to_string(card) + ","; });

    return hash;
  };

  auto addInHystory = [&](deque<int>& player1, deque<int>& player2)
  {
    hystory[calculateHash(player1, player2)] = true;
  };

  auto isInHystory = [&](deque<int>& player1, deque<int>& player2)
  {
    return hystory[calculateHash(player1, player2)];
  };

  while (!player1.empty() && !player2.empty())
  {
    // player 1 win cicle
    if (isInHystory(player1, player2))
      return { true, {} };

    // add in history
    addInHystory(player1, player2);

    auto player1Top = player1.front();
    auto player2Top = player2.front();

    player1.pop_front();
    player2.pop_front();

    bool winnerPlayer1 = false;
    if (player1Top <= player1.size() && player2Top <= player2.size())
    {
      deque<int> nextPlayer1Deck;
      copy(begin(player1), begin(player1) + player1Top, back_inserter(nextPlayer1Deck));

      deque<int> nextPlayer2Deck;
      copy(begin(player2), begin(player2) + player2Top, back_inserter(nextPlayer2Deck));

      auto [_winnerPlayer1, _] = RecursiveCombat(move(nextPlayer1Deck), move(nextPlayer2Deck));
      winnerPlayer1 = _winnerPlayer1;
    }
    else
    {
      winnerPlayer1 = (player1Top > player2Top);
    }

    // winner player 1
    if (winnerPlayer1)
    {
      player1.push_back(player1Top);
      player1.push_back(player2Top);
    }
    else
    {
      player2.push_back(player2Top);
      player2.push_back(player1Top);
    }
  }

  return { !player1.empty(), !player1.empty() ? player1 : player2 };
}

int main()
{
  ifstream in("..\\..\\Day22\\src\\_Input.in");
  ofstream out("..\\..\\Day22\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  deque<int> player1;
  deque<int> player2;

  bool parsingPlayer1 = true;
  for (auto& line : lines)
  {
    if (line == "Player 1:")
    {
      parsingPlayer1 = true;
      continue;
    }
    else if(line == "Player 2:")
    {
      parsingPlayer1 = false;
      continue;
    }

    if (line.empty())
      continue;
  
    if(parsingPlayer1)
      player1.push_back(stoi(line.c_str()));
    else
      player2.push_back(stoi(line.c_str()));
  }

  auto sumResult = [](const deque<int>& deck)
  {
    int cardId = 0;
    return accumulate(rbegin(deck), rend(deck), 1, [&](int acc, int card) {
      return acc + (++cardId) * card;
    });
  };

  auto [_, winningDeckPart1] = NormalCombat(player1, player2);
  auto [__, winningDeckPart2] = RecursiveCombat(player1, player2);

  cout << sumResult(winningDeckPart1) << endl;
  cout << sumResult(winningDeckPart2) << endl;

  return 0;
}
