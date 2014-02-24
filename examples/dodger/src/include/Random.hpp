#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random
{

private:
  static unsigned int sNumbers[100];

public:
  static void init();
  static int get(const unsigned int& min, const unsigned int& max);

};

#endif
