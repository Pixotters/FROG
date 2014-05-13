#include "FROG/Core/Random.hpp"

#include <cstdlib>
#include <ctime>

namespace frog{

  unsigned int Random::sNumbers[100];

  void Random::init(){
    std::srand ( std::time(NULL) );
    for (unsigned char c =0; c < 100; c++)
      sNumbers[c] = rand();
  }

  int Random::get(int min, int max){
    unsigned int index = (unsigned int)(rand()%100);
    int res = sNumbers[index];
    sNumbers[index] = rand();
    return (res%(max-min+1) )+min;

  }

}