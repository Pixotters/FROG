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


/*
  template <typename IN, typename OUT>
  Translator<IN, OUT>::iterator Translator<IN, OUT>::begin()
  {
  return m_binding.begin();
  }

  iterator Translator::end()
  {
  return m_binding.end();
  }

  const_iterator Translator::begin() const
  {
  return m_binding.begin();
  }

  const_iterator Translator::end() const
  {
  return m_binding.end();
  }
*/


