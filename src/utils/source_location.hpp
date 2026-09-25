#pragma once

#include <string>

struct SourceLocation{
  int line,col;
  std::string filename;
  explicit SourceLocation(int line,int col):line(line),col(col){}
};
