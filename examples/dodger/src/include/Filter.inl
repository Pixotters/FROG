
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
