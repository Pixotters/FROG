
template <typename IN, typename OUT>
AbstractController<IN, OUT>::AbstractController(){ }

template <typename IN, typename OUT>
AbstractController<IN, OUT>::~AbstractController(){ }

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::handle(){
  cleanQueue();
  auto end = m_binding.end();
  for(auto it = m_binding.begin(); it != end; ++it)
    {
      if (it->first->handle(this) )
        {
          add(it->second );
        }
    }
  
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::cleanQueue(){
  while(not m_output.empty() )
    {
      m_output.pop();
    }
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::suscribe(IN * i, OUT * o){
  auto it = m_binding.find(i);
  if( it != m_binding.end() )
    {
      m_binding.erase (it);
    }
  m_binding.insert(std::pair<IN *, OUT *>(i, o) );
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::unsuscribe(IN * i ){
  auto it = m_binding.find(i);
  if( it != m_binding.end() )
    {
      m_binding.erase (it);
    }
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::clear(){
  m_binding.clear();
}

template <typename IN, typename OUT>
std::queue<OUT *> AbstractController<IN, OUT>::getQueue() const{
  return m_output;
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::add(OUT * o ){
  m_output.push(o);
}

template <typename IN, typename OUT>
bool AbstractController<IN, OUT>::handle(IN * i ){
     return false;
}
  
