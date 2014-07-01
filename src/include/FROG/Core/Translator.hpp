/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_TRANSLATOR_HPP
#define FROG_TRANSLATOR_HPP

#include <exception>
#include <iterator>
#include <map>


namespace frog{

  /*!
   * Translator<IN, OUT> acts like a map of < IN -> OUT >
   */
  template <typename IN, typename OUT>
  class Translator{

  public:
    class NotFound: public std::exception{};

    //// attributes ////
  protected:
    std::map< IN, OUT > m_binding;

  public:
    typedef typename std::map<IN,OUT>::iterator iterator;
    typedef typename std::map<IN, OUT>::const_iterator const_iterator;

    //// operations ////
  public:

    /*!
     * \brief Base constructor
     */
    Translator();

    virtual ~Translator();

    /*!
     * \brief Returns the <OUT> associated with the <IN>
     * \details If no entry is associated with the argument, returns nullptr
     * \param i key to translate
     * \return the value associated to \a i, throws NotFound if there is none
     */
    virtual OUT get(IN i) const throw (NotFound);

    /*!
     * \brief Adds a new binding to the translator
     * \details If the key has already a value, it is overriden and returned
     * \param i key of the binding
     * \param o value of the binding
     * \return o if i doesn't already have a binding, the old binding if it has
     */
    OUT suscribe(IN i, OUT o);

    /*!
     * \brief Removes a binding
     * \details If the given <IN> has no value associated, nothing is removed
     * \param i Key to remove
     */
    void unsuscribe(IN i);

    /*!
     * \brief Removes all binding of the translator
     */
    void clear();
  

    /*!
     * \brief Iterator to the first entry
     * \return a std::pair * pointing to the first entry
     */
    iterator begin();

    /*!
     * \brief Iterator to the last entry
     * \return a std::pair * pointing to the last entry
     */
    iterator end();

    /*!
     * \brief Iterator to the first entry
     * \return a std::pair * pointing to the first entry
     */
    const_iterator begin() const;

    /*!
     * \brief Iterator to the last entry
     * \return a std::pair * pointing to the last entry
     */
    const_iterator end() const;

  protected:
    /*!
     * \brief Adds a new binding to the translator
     * \details No checking is performed. This function should be use wisely 
     because it can insert doubles. If case of doubt, please use suscribe.
     * \param i key of the binding
     * \param o value of the binding
     * \return o if i doesn't already have a binding, the old binding if it has
     */
    OUT set(IN i , OUT o);


  };

#include "FROG/Core/Translator.inl"

}

#endif
