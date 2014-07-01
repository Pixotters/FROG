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


template <typename IN, typename OUT>
Translator<IN, OUT>::Translator() 
{
}

template <typename IN, typename OUT>
Translator<IN, OUT>::~Translator() 
{
}


template <typename IN, typename OUT>
OUT Translator<IN, OUT>::get(IN i) const throw (NotFound){
  auto it = m_binding.find(i);
  if(it == m_binding.end() )
    {
      throw NotFound();
    }    
  return (it->second );
}


template <typename IN, typename OUT>
OUT Translator<IN, OUT>::suscribe(IN i, OUT o){
  auto it = m_binding.find(i);
  OUT old;
  if( it != m_binding.end() )
    {
      old = it->second;
      m_binding.erase (it);
    }
  set(i, o);
  return old;
}


template <typename IN, typename OUT>
void Translator<IN, OUT>::unsuscribe(IN i ){
  auto it = m_binding.find(i);
  if( it != m_binding.end() )
    {
      m_binding.erase (it);
    }
}


template <typename IN, typename OUT>
void Translator<IN, OUT>::clear(){
  m_binding.clear();
}


template <typename IN, typename OUT>
OUT Translator<IN, OUT>::set(IN i, OUT o){
  m_binding.insert(std::pair<IN , OUT >(i, o) );
}

template <typename IN, typename OUT>
typename Translator<IN,OUT>::iterator Translator<IN, OUT>::begin()
{
  return m_binding.begin();
}

template <typename IN, typename OUT>
typename Translator<IN, OUT>::iterator Translator<IN,OUT>::end()
{
  return m_binding.end();
}

template <typename IN, typename OUT>
typename Translator<IN, OUT>::const_iterator Translator<IN, OUT>::begin() const
{
  return m_binding.begin();
}

template <typename IN, typename OUT>
typename Translator<IN, OUT>::const_iterator Translator<IN, OUT>::end() const
{
  return m_binding.end();
}
