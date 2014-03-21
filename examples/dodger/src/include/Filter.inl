
template <typename IN>
Filter<IN>::Filter(){ }

template <typename IN>
Filter<IN>::Filter(std::list<IN *> l)
  : m_check(l)
{ 
}

template <typename IN>
Filter<IN>::~Filter(){ }


template <typename IN>
std::list<IN *> Filter<IN>::filter(std::list<T *> in){
  return postprocess(process(preprocess(in) ) );
  process();
  postprocess();
  return getQueue();   
}


std::list<T *> operator()(std::list<T *> in){
  return filter(in);
}

template <typename IN>
void Filter<IN>::suscribe(IN * i){
   auto it = m_check.begin();
  auto end = m_check.end();
  while( it != end )
    {
      if( *it == i){
        return;
      }
    }
  m_check.push_back(i );
}


template <typename IN>
void Filter<IN>::unsuscribe(IN * i ){
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


template <typename IN>
void Filter<IN>::clear(){
  m_check.clear();
}




template <typename IN>
std::list<T *> Filter<IN>::preprocess(std::list<T *> in){
  return in;
}


template <typename IN>
std::list<T *> Filter<IN>::process(std::list<T *> in){
  auto end = in.end();
  for(auto it = in.begin(); it != end; ++it)
    {
      if ( check(*it) )
        {
          filtered.push_back(*it );
        }
    }
}


template <typename IN>
std::list<T *> Filter<IN>::postprocess(std::list<T *> in){
  return in;
}


template <typename IN>
bool Filter<IN>::check(T * t){
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
