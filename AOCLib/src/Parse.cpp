/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Parse.h"

std::vector<std::string> AOC::Explode(const std::string& str, char separator)
{
  std::vector<std::string> result;

  std::istringstream stream(str);
  for (std::string token; std::getline(stream, token, separator); )
  {
    result.push_back(std::move(token));
  }

  return result;
}

int AOC::RegexMatchInt(const string& str, const string& regexStr)
{
  smatch match;
  regex_match(str, match, regex(regexStr));
  assert(match.size() == 1);

  // 0
  return stoi(match[0]);
}
