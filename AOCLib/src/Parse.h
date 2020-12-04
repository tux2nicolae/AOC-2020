#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  vector<string> Explode(const string& str, char separator);

  int ExtractInt(const string& str, const string& regexStr = "(.*)");
  vector<string> ExtractMatches(const string& str, const string& regexStr = "(.*)");

  // previous rexec expresions
  //
  // [a-f0-9]{5}
  // amb|blu|brn|gry|grn|hzl|oth
  // [0-9]{9}
  // (.*) units each with (.*) hit points (.*)with an attack that does (.*) (.*) damage at initiative (.*)
}
