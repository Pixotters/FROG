#ifndef TESTFILE_HPP
#define TESTFILE_HPP

#include <string>

class TestFile{

protected:
  char * data;

public:
  TestFile();
  virtual ~TestFile();
  bool loadFromFile(const std::string& path);

};

#endif
