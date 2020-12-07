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

struct Node {
  string name;
  int count;
};

unordered_map<string, bool> visited;

int CountBags(const unordered_map<string, vector<Node>> & tree, const string & node)
{
  if (tree.count(node) == 0)
    return 1;

  int s = 1;
  for (const auto& child : tree.at(node))
  {
    if(!visited[child.name])
    { 
      visited[child.name] = true;
      s += CountBags(tree, child.name);
    }
  }

  return s;
}


int CountBagsPart2(const unordered_map<string, vector<Node>>& tree, const string& node)
{
  if (tree.count(node) == 0)
    return 1;

  int s = 1;
  for (const auto& child : tree.at(node))
  {
    s += child.count * CountBagsPart2(tree, child.name);
  }

  return s;
}

int main()
{
  ifstream in("..\\..\\Day07\\src\\_Input.in");
  // ofstream out("..\\..\\Day07\\src\\_Output.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadLines();


  unordered_map<string, vector<Node>> tree;
  unordered_map<string, vector<Node>> tree2;

  for (const auto& line : v)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) bags contain (.*).");
    auto contains = AOC::Explode(matches[2], ',');

    const auto fromType = matches[1];
    for (auto contain : contains)
    {
      // remove first space
      if (contain.front() == ' ')
        contain = contain.substr(1);

      // add . at the end for all strings
      if (contain.back() != '.')
        contain.push_back('.');

      auto toMatches = AOC::ExtractMatches(contain, "([1-9]+) (.*) bag(.*).");
      if (toMatches.empty())
        continue;

      const auto toCount = stoi(toMatches[1]);
      const auto toType = toMatches[2];

      ////////////
      tree[toType].push_back( Node{fromType, toCount} );
      tree2[fromType].push_back(Node{ toType , toCount });
    }
  }

  visited["shiny gold"] = true;
  cout << CountBags(tree, "shiny gold") - 1 << endl;
  cout << CountBagsPart2(tree2, "shiny gold") - 1 << endl;

  return 0;
}
