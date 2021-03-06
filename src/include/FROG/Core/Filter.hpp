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

#ifndef FROG_FILTER_HPP
#define FROG_FILTER_HPP

#include <list>


namespace frog{

  /*! \class Filter
   * \brief Filters according to a list of <T>, with "check(T)" methods.
   * \details Filter<T *>, will not follow pointers
   */
  template <typename T>
  class Filter
  {
    //// attributes ////
  protected:
    std::list<T> m_check;
    std::list<T> m_output;

    //// operations ////
  public:
    Filter();

    /*!
     * \brief Constructor with filter list
     * \param check : list of <T> to suscribe at the beginning.
     */
    Filter(std::list<T> check);

    virtual ~Filter(); 

    /*!
     * \brief Performs the filtering on the given input
     * \param in : list of <T> to filter
     * \return filtered list
     */
    std::list<T> filter(std::list<T> in);

    /*!
     * \brief Performs the filtering on the given input
     * \param in : list of <T *> to filter
     * \return filtered list
     */
    std::list<T> operator()(std::list<T> in);

    /*!
     * \brief Adds a <T> to the filter list
     * \details Prevents for doubles by checking if the <T> is already there. 
     * \param t <T> to add to the filter list
     * \
     */
    void suscribe(T t);

    /*!
     * \brief Removes all occurences of a <T> from the list
     * \details If it is not present, nothing is done
     * \param t <T> to remove from the filter list
     */
    void unsuscribe(T t);

    /*!
     * \brief Removes all elements of the filter list
     */
    void clear();    

  protected:


    /*!
     * \brief Actions to perform before filtering
     * \details By default, nothing is performed
     * \param in list of <T> to filter
     * \return the preprocessed list
     */
    virtual std::list<T> preprocess(std::list<T> in);    


    /*!
     * \brief Actual filtering
     * \details Checks for all <T> in the input list if it is present in the 
     * filter list
     * \param in list of <T> to filter
     * \return the filtered list
     */
    std::list<T> process(std::list<T> in);

    /*!
     * \brief Actions to perform after filtering
     * \details By default, nothing is performed
     * \param in list of <T *> to filter
     * \return the postprocessed list
     */    
    virtual std::list<T> postprocess(std::list<T> in);

    /*!
     * \brief Verifies if a <T> has to be kept or not
     * \details By default, uses "==" comparisons
     * \param t <T> to filter
     * \return true if \a t must be kept, false otherwise
     */    
    virtual bool check(T t);
  
  };






  /*! \class PFilter
   * \brief Filters according to a list of <T *>, with "check(T *)" methods.
   * \details Unlink Filter<T>, PFilter<T *> will follow the pointers.
   */
  template <typename T>
  class PFilter
  {
    //// attributes ////
  protected:
    std::list<T *> m_check;
    std::list<T *> m_output;

    //// operations ////
  public:
    PFilter(); 
 
    PFilter(std::list<T *> check);

    virtual ~PFilter();    
 
    std::list<T *> filter(std::list<T *> in);  
  
    std::list<T *> operator()(std::list<T *> in);

    void suscribe(T * t);
 
    void unsuscribe(T * t);
 
    void clear();    

  protected:
 
    virtual std::list<T *> preprocess(std::list<T *> in);    
  
    std::list<T *> process(std::list<T *> in);

    virtual std::list<T *> postprocess(std::list<T *> in);

    virtual bool check(T * t);
  
  };


#include "FROG/Core/Filter.inl"


}

#endif
