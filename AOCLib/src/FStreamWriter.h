#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
class FStreamWriter
{
public:
  /**
   * Input stream
   */
  FStreamWriter(ofstream & aOut);

  void WriteVector(const vector<int> & aVector);
  void WriteMatrix(const vector<vector<int>> & aMatrix);
  void WriteMatrixAsGrid(const vector<vector<int>> & aMatrix);

private:
  ofstream & mFileStream;
};
