#ifndef FROG_INPUTCOMPONENT_HPP
#define FROG_INPUTCOMPONENT_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
#include <vector>
#include <map>

namespace frog{

  template <typename IN, typename CMD>
  class InputComponent : virtual public Component
  {

  protected:
    std::vector< std::map<IN*, CMD* > > m_maps;

  public:

    InputComponent();

    virtual void preupdate(const ComponentHolder& parent);

    virtual void update(const ComponentHolder& parent);

    virtual void postupdate(const ComponentHolder& parent);

    /*!
     * \brief Binds an IN to a CMD
     * \details An id can be specified, representing the index of the map. By 
     * default, it is the first. If the index matches a null or non existing 
     * map, a new one is created. 
     * \param i IN to bind
     * \param c CMD to which bind the IN
     * \param n (optionnal) index of the map to modify
     * \return the CMD previously bound, c is there was none
     */
    CMD * bind(IN * i, CMD * o, unsigned short n = 0);

    /*!
     * \brief Removes a binding from a given map's index.
     * \details if no index is given, the first map is selected. If the 
     * index matches a null or non-existing map, nothing will be done.
     * \param i IN to remove
     * \param n index of the IN in which the IN should be removed
     */
    void unbind(IN * i, unsigned short n = 0);

    /*!
     * \brief Removes a binding from all maps
     * \param i Input to remove
     */
    void unbindAll(IN * i);

    /*!
     * \brief Adds an map to the Controller
     * \details The map tries to insert in the first available place (if 
     * an other map is nullptr. If there is none, a new entry is created. 
     * If the passed map is nullptr, a new map is created instead and 
     * added.
     * \param im map to add. If nullptr, a new map will be created.
     * \return the index in which the map has been inserted.
     */
    unsigned short addMap(std::map<IN *, CMD *> * map = nullptr);

    /*!
     * \brief Removes an map from the InputComponent
     * \details The place will be replaced by nullptr. If the index is out of 
     * bounds of the maps, nothing happens. 
     * \param i Index of the map to remove
     */
    void removeMap(unsigned short i);
    
    /*!
     * \brief Changes an map
     * \details The old map is returned. The new map is placed at 
     * the  same location. If the index doesn't refer to a valid map, a new 
     * entry is created. 
     * \param im new map
     * \param i index of the map to replace
     * \return old map if we replaced one, the current one if there was none.
     */
    std::map<IN *, CMD *> changeMap(std::map<IN *, CMD *> map, 
                                    unsigned short i = 0);


  protected:
    virtual bool check(IN *, const ComponentHolder&) const = 0;

    /*!
     * \brief Removes from the handler all IN of the map
     * \details if an IN is present in another map, it won't be removed.
     * \param im map of which IN have to be unhandled
     */
    void unhandle(std::map<IN *, CMD *> im);

    /*!
     * \brief Removes from the handler all IN of the vector
     * \details if an IN is present in another map, it won't be removed.
     * \param im vector of which IN have to be unhandled
     */
    void unhandle(std::vector<IN> im);

    /*!
     * \brief Removes an IN from the handler
     * \details the IN is removed, even if an map still needs it
     * \param i IN to remove from the handler
     */
    void unhandle(IN * i);

  };

}

#include "FROG/Control/InputComponent.inl"

#endif
