#include "TestFile.hpp"

#include <iostream>
#include <fstream>

TestFile::TestFile()
{
  data = new char[256];
  std::cout << "allocating a TestFile" << std::endl;
}

TestFile::~TestFile()
{
  delete[] data;
  std::cout << "deleting a TestFile" << std::endl;  
}

bool TestFile::loadFromFile(const std::string& path)
{
  std::ifstream ifs;
  ifs.open(path, std::ifstream::in);  
  if(ifs.good() ){
    ifs.getline(data, 256);
    return true;
  }else{
    return false;
  }
}
