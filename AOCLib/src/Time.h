#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  time_t GetTime();
  time_t GetTime(int year, int month, int day, int hour, int min, int sec);

  string PrintTime(time_t aTime);
}
