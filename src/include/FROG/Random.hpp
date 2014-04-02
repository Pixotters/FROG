#ifndef FROG_RANDOM_HPP
#define FROG_RANDOM_HPP


namespace frog{

  class Random{

  private:
    static unsigned int sNumbers[100];

  public:
    static void init();
    static int get(const int& min, const int& max);

  };

}

#endif
