#include "Control/Controller.hpp"

namespace frog{

  namespace ctrl{

    Controller::Controller(ControlHandler * ch, 
                           InputMap * im)
      : m_handler(ch)
    {
      if(m_handler == nullptr)
        {
          m_handler = new ControlHandler();
        }

      if(im == nullptr)
        {
          m_mapping.push_back(new InputMap() );
        }else{
        m_mapping.push_back(im);
      }
    }

    Controller::~Controller()
    {

    }

    Command * Controller::bind(Input * i,
                               Command * c,
                               const unsigned short& n)
    {
      if(n >= m_mapping.size() or m_mapping.at(n) == nullptr){
        m_mapping.at(n) = new InputMap();
      }
      handle(i);
      return m_mapping.at(n)->suscribe(i, c);
    }

    void Controller::unbind(Input * i,
                            const unsigned short& n)
    {
      unsigned int size = m_mapping.size();
      if(n < size and m_mapping.at(n) != nullptr){
        m_mapping.at(n)->unsuscribe(i);        
      }
      // TODO check if the input is present in an other map before unhandling it
      Command * test;
      for(int it = 0; it < size; it++)
        {
          try{
            test = m_mapping.at(it)->get(i);
            if(test != nullptr)
              return;
          }catch(InputMap::NotFound ex){

          }
          
        }
      /* here, we have searched for the input without finding it : it is now 
         registered although no inputmap uses it : let's remove it.
       */
      unhandle(i);
    }

    void Controller::unbindAll(Input * i)
    {
      auto end = m_mapping.size();
      for(unsigned int it = 0; it < end; it++)
        {
          if(m_mapping.at(it) != nullptr){
            m_mapping.at(it)->unsuscribe(i);    
          }
        }
      unhandle(i);
    }

    unsigned short Controller::addInputMap(InputMap * im)
    {
      if(im == nullptr)
        {
          im = new InputMap();
        }
      unsigned int it;
      auto end = m_mapping.size();
      for(it = 0; it < end; it++)
        {
          if(m_mapping.at(it) == nullptr)
            {
              m_mapping.at(it) = im;
              return it;
            }
        }
      m_mapping.push_back(im);
      return it;
    }

    void Controller::removeInputMap(const unsigned short& i)
    {
      if(i < m_mapping.size() )
        {
          m_mapping.at(i) = nullptr;
        }
    }

    InputMap * Controller::changeInputMap(InputMap * im, 
                                          const unsigned short& i)
    {
      InputMap * res = im;
      if( i < m_mapping.size() )
        {
          res = m_mapping.at(i);
          m_mapping.at(i) = im;
        }
      return res;
    }



    void Controller::unhandle(InputMap * im)
    {
      auto end = m_mapping.size();
      auto endmap = im->end();
      Input * input;
      for(auto mapit = im->begin(); mapit != endmap; mapit++)
        {
          input = mapit->first;
          unsigned short it;
          for(it = 0; it < end; it++)
            {
              if(m_mapping.at(it) != im)
                {
                  if(m_mapping.at(it)->get(input) != nullptr){
                    break; // break should affect only the inner loop
                  }
                }
            }
          if(it >= end)
            {
              // here, we have seen all the others maps without finding the input
              unhandle(input);
            }
        }
    
    }


    void Controller::unhandle(Input * i)
    {
      m_handler->unsuscribe(i);
    }


    void Controller::handle(Input * i)
    {
      m_handler->suscribe(i);
    }

    std::list<Command *> Controller::update()
    {
      std::list<Command *> res;
      std::list<Input *> inputs = m_handler->update();
      if(m_mapping.empty() or inputs.empty() )
        {
          return res;
        }
      auto endmap = m_mapping.end();
      for(auto itmap = m_mapping.begin(); itmap != endmap; itmap++)
        {
          auto endinput = inputs.end();
          for(auto itinput = inputs.begin(); itinput != endinput; itinput++)
            {
              auto singleinput = ( (*itmap)->get(*itinput) );
              if(singleinput != nullptr)
                {
                  res.push_back(singleinput);
                }
            }
        }
      return res;
    }

  }

}
