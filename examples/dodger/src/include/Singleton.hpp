#ifndef SINGLETON_HPP
#define SINGLETON_HPP


namespace frog{

  template <class T>
  class Singleton{

  private:
    T& operator=(const T&){};

  public:
    static T * instance(){
      if( s_instance == nullptr ){
        s_instance = new T();
      }
      return s_instance;
    }

    static void destroy(){
      delete s_instance;
      s_instance = nullptr;
    }
  
  protected:
    static T * s_instance;

  };


  /////////////////////////////////////////////
  /////////////////////////////////////////////

  template <class T> 
  T * Singleton<T>::s_instance= nullptr;

}

#endif
