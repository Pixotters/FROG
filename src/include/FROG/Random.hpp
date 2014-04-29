#ifndef FROG_RANDOM_HPP
#define FROG_RANDOM_HPP


namespace frog{

  class Random{

  private:
    static unsigned int sNumbers[100];

  public:

    /*!
     * @brief Initializes the seed
     */
    static void init();

    /*!
     * @brief Returns an integer in a given range. 
     * @param min Minimal value possibly returned. 
     * @param max Maximal value possibly returned. 
     */
    static int get(int min, int max);

  };

}

#endif
