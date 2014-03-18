#include "Random.hpp"

#include <cstdlib>
#include <cstdlib>
#include <ctime>


unsigned int Random::sNumbers[100];

void Random::init(){
  std::srand ( std::time(NULL) );
  for (unsigned char c =0; c < 100; c++)
    sNumbers[c] = rand();
}

 int Random::get(const int& min, const int& max){
  unsigned int index = (unsigned int)(rand()%100);
  int res = sNumbers[index];
  sNumbers[index] = rand();
  return (res%(max-min+1) )+min;

}
