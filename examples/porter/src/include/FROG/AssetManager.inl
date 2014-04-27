#include <cassert>

template <typename ID, typename R>
AssetManager<ID,R>::AssetManager()
{

}

template <typename ID, typename R>
AssetManager<ID,R>::~AssetManager()
{
  m_files.clear();
}


template <typename ID, typename R>
R& AssetManager<ID,R>::get(const ID& id)
{
  auto itr = m_files.find(id);
  assert(itr != m_files.end() );
  return *itr->second;
}


template <typename ID, typename R>
const R& AssetManager<ID,R>::get(const ID& id) const
{
  auto itr = m_files.find(id);
  assert(itr != m_files.end() );
  return *itr->second;
}


template <typename ID, typename R>
void AssetManager<ID,R>::loadFromFile(const std::string& path, const ID& id) 
  throw (std::runtime_error)
{
  if( m_files.find(id) == m_files.end() )
    {
      std::unique_ptr<R> pr(new R() );  
      if( not pr->loadFromFile(path) )
        {
          std::string err = "Impossible to create asset because a problem"; 
          err += " occured while loading " + path;
          throw std::runtime_error(err);
        }
      auto check = m_files.insert(  std::make_pair( id, std::move(pr) )  );
      assert( check.second );

    }

}

