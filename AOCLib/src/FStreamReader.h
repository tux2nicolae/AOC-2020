#pragma once

/**
 * Advent of code 2019
 * @author : Nicolae Telechi
 */
class FStreamReader
{
public:
  /**
   * Input stream
   */
  FStreamReader(ifstream & aIn);

  template<typename T = int>
  vector<T> ReadVector()
  {
    vector<T> ret;

    T n = 0;
    while (mFileStream >> n)
      ret.push_back(n);

    return ret;
  }

  template<typename T = int>
  vector<T> ReadVectorSeparatedByChar()
  {
    vector<T> ret;
    while (mFileStream.good())
    {
      T x{};
      char _{};

      mFileStream >> x >> _;
      ret.push_back(x);
    }

    return ret;
  }

  vector<int> ReadLineAsVectorOfDigits();
  vector<string> ReadVectorOfWords();
  vector<string> ReadLineAsVectorOfWords();

  vector<vector<int>> ReadMatrix();
  vector<vector<int>> ReadMatrixOfDigits();
  vector<vector<string>> ReadMatrixOfWords();

private:
  ifstream & mFileStream;

};
