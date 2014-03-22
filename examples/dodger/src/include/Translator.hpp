#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <map>

#include <iterator>

#include <iostream> //TODO remove

template <typename IN, typename OUT>
class Translator{

  //// attributes ////
protected:
  std::map< IN *, OUT * > m_binding;
  //  typedef typename std::pair<IN *, OUT *> * iterator;
  //  typedef typename const std::pair<IN *, OUT *> * const_iterator;

  //// operations ////
public:

  /*!
   * \brief Base constructor
   */
  Translator();

  virtual ~Translator();

  /*!
   * \brief Returns the <OUT> associated with the <IN *>
   * \details If no entry is associated with the argument, returns nullptr
   * \param i key to translate
   * \return the value associated to \a i, nullptr if there is none
   */
  virtual OUT * get(IN *) const;

  /*!
   * \brief Adds a new binding to the translator
   * \details If the key has already a value, it is overriden and returned
   * \param i key of the binding
   * \param o value of the binding
   * \return o if i doesn't already have a binding, the old binding if it has
   */
  OUT * suscribe(IN *, OUT *);

  /*!
   * \brief Removes a binding
   * \details If the given <IN> has no value associated, nothing is removed
   * \param i Key to remove
   */
  OUT * unsuscribe(IN *);

  /*!
   * \brief Removes all binding of the translator
   */
  void clear();
  

  /*!
   * \brief Iterator to the first entry
   * \return a std::pair * pointing to the first entry
   */
  //iterator begin();

  /*!
   * \brief Iterator to the last entry
   * \return a std::pair * pointing to the last entry
   */
  //iterator end();

  /*!
   * \brief Iterator to the first entry
   * \return a std::pair * pointing to the first entry
   */
  //const_iterator begin() const;

  /*!
   * \brief Iterator to the last entry
   * \return a std::pair * pointing to the last entry
   */
  //const_iterator end() const;

protected:
  /*!
   * \brief Adds a new binding to the translator
   * \details No checking is performed. This function should be use wisely 
   because it can insert doubles. If case of doubt, please use suscribe.
   * \param i key of the binding
   * \param o value of the binding
   * \return o if i doesn't already have a binding, the old binding if it has
   */
  OUT * set(IN * i , OUT * o);


};

#include "Translator.inl"

#endif
