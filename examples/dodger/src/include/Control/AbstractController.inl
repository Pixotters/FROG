
template <typename IN, typename OUT>
AbstractController<IN, OUT>::AbstractController(){ }

template <typename IN, typename OUT>
AbstractController<IN, OUT>::~AbstractController(){ }


template <typename IN, typename OUT>
std::queue<OUT *> AbstractController<IN, OUT>::handle(){
  std::cout << "handling" << std::endl;
  update();
  cleanQueue();
  std::map< IN *, OUT * > binding = m_controlManager->getBinding();
  auto end = binding.end();
  for(auto it = binding.begin(); it != end; ++it)
    {
      if (it->first->occurred(this) )
        {
          add(it->second );
        }
    }
    return getQueue();  
}

template <typename IN, typename OUT>
std::queue<OUT *> AbstractController<IN, OUT>::getQueue() const{
  return m_output;
}

template <typename IN, typename OUT>
ControlManager<IN, OUT> * AbstractController<IN, OUT>::setManager(ControlManager<IN, OUT> * cm ){
     auto old = m_controlManager;
  m_controlManager = cm;
return old;
}

template <typename IN, typename OUT>
ControlManager<IN, OUT> * AbstractController<IN, OUT>::getManager( ) const{
  return m_controlManager;
}

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::add(OUT * o ){
  m_output.push(o);
}

/*
template <typename IN, typename OUT>
bool AbstractController<IN, OUT>::occurred(IN * i ){
     return false;
}
*/

template <typename IN, typename OUT>
void AbstractController<IN, OUT>::cleanQueue(){
  while(not m_output.empty() )
    {
      m_output.pop();
    }
}
