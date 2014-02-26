#ifndef RANDOM_HPP
#define RANDOM_HPP


class Random{

private:
static unsigned int sNumbers[100];

public:
static void init();
static int get(const int& min, const int& max);

};

#endif
