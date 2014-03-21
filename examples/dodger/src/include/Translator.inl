template <typename IN, typename OUT>
Translator<IN, OUT>::Translator() 
{
}

template <typename IN, typename OUT>
Translator<IN, OUT>::~Translator() 
{
}


template <typename IN, typename OUT>
OUT * Translator<IN, OUT>::get(IN * i) const{
  auto it = m_binding.find(i);
  if(it == m_binding.end() )
    {
    std::cout << "command not found" << std::endl;
      return nullptr;
    }    
    std::cout << "command ["<<this<<"] "<<i<<" -> "<<it->second << std::endl;
  return (it->second );
}


template <typename IN, typename OUT>
OUT * Translator<IN, OUT>::suscribe(IN * i, OUT * o){
  auto it = m_binding.find(i);
  OUT * old = o;
  if( it != m_binding.end() )
    {
    old = *it;
      m_binding.erase (it);
    }
    set(i, o);
  return old;
}


template <typename IN, typename OUT>
OUT * Translator<IN, OUT>::unsuscribe(IN * i ){
  auto it = m_binding.find(i);
  OUT * old = nullptr;
  if( it != m_binding.end() )
    {
        old = it->second;
      m_binding.erase (it);
    }
    return old;
}


template <typename IN, typename OUT>
void Translator<IN, OUT>::clear(){
  m_binding.clear();
}
       

template <typename IN, typename OUT>
OUT * Translator<IN, OUT>::set(IN * i, OUT * o){
  m_binding.insert(std::pair<IN *, OUT *>(i, o) );
}