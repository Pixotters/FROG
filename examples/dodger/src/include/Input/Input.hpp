#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP

namespace Input{

  class Input
  {

    //// attributes ////
  protected:

    //// operations ////
  public:
    Input(){};
    virtual ~Input(){};
    virtual bool isContinuous() const = 0;
  };

}

#endif