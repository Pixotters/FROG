template <typename IN, typename OUT>
ControlManager<IN, OUT>::ControlManager() 
{
}

template <typename IN, typename OUT>
ControlManager<IN, OUT>::~ControlManager() 
{
}

template <typename IN, typename OUT>
std::map< IN *, OUT * > ControlManager<IN, OUT>::getBinding() const
{
        return m_binding;
}

template <typename IN, typename OUT>
OUT * ControlManager<IN, OUT>::get(IN * i) const{
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
void ControlManager<IN, OUT>::suscribe(IN * i, OUT * o){
  auto it = m_binding.find(i);
  if( it != m_binding.end() )
    {
      m_binding.erase (it);
    }
  m_binding.insert(std::pair<IN *, OUT *>(i, o) );
}

template <typename IN, typename OUT>
void ControlManager<IN, OUT>::unsuscribe(IN * i ){
  auto it = m_binding.find(i);
  if( it != m_binding.end() )
    {
      m_binding.erase (it);
    }
}

template <typename IN, typename OUT>
void ControlManager<IN, OUT>::clear(){
  m_binding.clear();
}
       
template <typename IN, typename OUT>
OUT * ControlManager<IN, OUT>::set(IN * i, OUT * o){
suscribe(i, o);
            return get(i);
}