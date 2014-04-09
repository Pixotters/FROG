#ifndef FROG_CTRL_CONTROLLER_HPP
#define FROG_CTRL_CONTROLLER_HPP

#include "FROG/Control/ControlHandler.hpp"

#include "FROG/Control/InputMap.hpp"

namespace frog{

  namespace ctrl{

    /*!
     * Controller make the link between ControlHandler and InputMap. 
     */
    class Controller
    {
      //// attributes ////
    protected :

      ControlHandler * m_handler;

      std::vector<InputMap * > m_mapping;

      //// operations ////
    public:

      /*!
       * \brief Constructor
       * \details If given args are nullptr, real ones will be created
       * \param ch ControlHandler to use
       * \param im InputMap to place at the index 0
       */
      Controller(ControlHandler * ch = nullptr, 
                 InputMap * im = nullptr);

      /*!
       *
       */
      virtual ~Controller();

      /*!
       * \brief Binds an Input to a Command
       * \details An id can be specified, representing the index of the map. By 
       * default, it is the first. If the index matches a null or non existing 
       * map, a new one is created. 
       * \param i Input to bind
       * \param c Command to which bind the Input
       * \param n (optionnal) index of the InputMap to modify
       * \return the Command previously bound, c is there was none
       */
      Command * bind(Input * i, Command * c, const unsigned short& n = 0);

      /*!
       * \brief Removes a binding from a given InputMap's index.
       * \details if no index is given, the first InputMap is selected. If the 
       index matches a null or non-existing map, nothing will be done.
       * \param i Input to remove
       * \param n index of the InputMap in which the Input should be removed
       */
      void unbind(Input * i, const unsigned short& n = 0);

      /*!
       * \brief Removes a binding from all InputMaps
       * \param i Input to remove
       */
      void unbindAll(Input * i);
  
      /*!
       * \brief Adds an InputMap to the Controller
       * \details The InputMap tries to insert in the first available place (if 
       * an other InputMap is nullptr. If there is none, a new entry is created. 
       * If the passed map is nullptr, a new InputMap is created instead and added.
       * \param im InputMap to add. If nullptr, a new InputMap will be created.
       * \return the index in which the InputMap has been inserted.
       */
      unsigned short addInputMap(InputMap * im = nullptr);

      /*!
       * \brief Removes an InputMap from the Controller
       * \details The place will be replaced by nullptr. If the index is out of 
       * bounds of the maps, nothing appens. 
       * \param i Index of the InputMap to remove
       */
      void removeInputMap(const unsigned short& i);

      /*!
       * \brief Changes an InputMap
       * \details The old InputMap is returned. The new InputMap is placed at the 
       * same location. If the index doesn't refer to a valid map, a new entry is 
       * created. 
       * \param im new InputMap
       * \param i index of the InputMap to replace
       * \return old map if we replaced one, the current one if there was none.
       */
      InputMap * changeInputMap(InputMap * im, const unsigned short& i = 0);

      /*!
       * \brief Computes a list of command that should be executed
       * \details Monitors the inputs registered in the handler, and converts 
       * them in Commands with the InputMaps
       * \return A list of commands that should be executed in response to inputs
       */
      std::list<Command *> update();

    protected :

      /*!
       * \brief Removes from the handler all Inputs of the map
       * \details if an Input is present in another map, it won't be removed.
       * \param im InputMap of which Inputs have to be unhandled
       */
      void unhandle(InputMap * im);

      /*!
       * \brief Removes an Input from the handler
       * \details the Input is removed, even if an InputMap still needs it
       * \param i Input to remove from the handler
       */
      void unhandle(Input * i);

      /*!
       * \brief Adds an Input to the handler
       * \details If the Input is already there, it won't be added
       * \param i Input to add to the handle
       */
      void handle(Input * i);

    };

  }

}

#endif
