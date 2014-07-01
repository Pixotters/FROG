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


template <typename T>
Filter<T>::Filter(){ }

template <typename T>
Filter<T>::Filter(std::list<T> check)
  : m_check(check)
{ 
}

template <typename T>
Filter<T>::~Filter(){ }


template <typename T>
std::list<T> Filter<T>::filter(std::list<T> in){
  return postprocess(process(preprocess(in) ) );
}

template <typename T>
std::list<T> Filter<T>::operator()(std::list<T> in){
  return filter(in);
}

template <typename T>
void Filter<T>::suscribe(T i){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if( *it == i){
        return;
      }
      it++;
    }
  m_check.push_back(i );
}


template <typename T>
void Filter<T>::unsuscribe(T i ){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if(*it == i){
        m_check.erase (it);
        break;
      }
      it++;
    }
}


template <typename T>
void Filter<T>::clear(){
  m_check.clear();
}




template <typename T>
std::list<T> Filter<T>::preprocess(std::list<T > in){
  return in;
}


template <typename T>
std::list<T> Filter<T>::process(std::list<T > in){
  auto end = in.end();
  std::list<T> filtered;
  for(auto it = in.begin(); it != end; ++it)
    {
      if ( check(*it) )
        {
          filtered.push_back(*it );
        }
    }
  return filtered;
}


template <typename T>
std::list<T> Filter<T>::postprocess(std::list<T > in){
  return in;
}


template <typename T>
bool Filter<T>::check(T t){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if( *it == t){
        return true;
      }
    }
  return false;
}
















//////////////////////



//////////////////////





template <typename T>
PFilter<T>::PFilter(){ }

template <typename T>
PFilter<T>::PFilter(std::list<T *> check)
  : m_check(check)
{ 
}

template <typename T>
PFilter<T>::~PFilter(){ }


template <typename T>
std::list<T *> PFilter<T>::filter(std::list<T *> in){
  return postprocess(process(preprocess(in) ) );
}

template <typename T>
std::list<T *> PFilter<T>::operator()(std::list<T *> in){
  return filter(in);
}

template <typename T>
void PFilter<T>::suscribe(T * i){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if( *it == i){
        return;
      }
      it++;
    }
  m_check.push_back(i );
}


template <typename T>
void PFilter<T>::unsuscribe(T * i ){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if(**it == *i){
        m_check.erase (it);
        break;
      }
      it++;
    }
}


template <typename T>
void PFilter<T>::clear(){
  m_check.clear();
}


template <typename T>
std::list<T *> PFilter<T>::preprocess(std::list<T * > in){
  return in;
}


template <typename T>
std::list<T *> PFilter<T>::process(std::list<T * > in){
  auto end = in.end();
  std::list<T *> filtered;
  for(auto it = in.begin(); it != end; ++it)
    {
      if ( check(*it) )
        {
          filtered.push_back(*it );
        }
    }
  return filtered;
}


template <typename T>
std::list<T *> PFilter<T>::postprocess(std::list<T * > in){
  return in;
}


template <typename T>
bool PFilter<T>::check(T * t){
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if( **it == *t){
        return true;
      }
    }
  return false;
}

