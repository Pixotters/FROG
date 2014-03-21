
template <typename IN>
AbstractController<IN>::AbstractController(){ }

template <typename IN>
AbstractController<IN>::~AbstractController(){ }


template <typename IN>
std::list<IN *> AbstractController<IN>::handle(){
  update();
  cleanQueue();
  auto end = m_check.end();
  for(auto it = m_check.begin(); it != end; ++it)
    {
      if ( (*it)->check(this) )
        {
          add(*it );
        }
    }
  return getQueue();  
}

template <typename IN>
std::list<IN *> AbstractController<IN>::getQueue() const{
  return m_output;
}

template <typename IN>
void AbstractController<IN>::add(IN * i ){
  m_output.push_front(i);
}

template <typename IN>
void AbstractController<IN>::cleanQueue(){
  while(not m_output.empty() )
    {
      m_output.pop_front();
    }
}

template <typename IN>
void AbstractController<IN>::suscribe(IN * i){
  std::cout << "suscribing" <<std::endl;
  unsuscribe(i);
  std::cout << "pushing back" <<std::endl;

  m_check.push_back(i );
}

template <typename IN>
void AbstractController<IN>::unsuscribe(IN * i ){
  std::cout << "unsuscribing" <<std::endl;
  auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      std::cout << "loop" <<std::endl;
      if(*it == i){
        m_check.erase (it);
        break;
        std::cout << "found" <<std::endl;
      }
      it++;
    }
}
