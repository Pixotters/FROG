#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <map>

#include <iostream> //TODO remove

template <typename IN, typename OUT>
class Translator{

  //// attributes ////
protected:
  std::map< IN *, OUT * > m_binding;

  //// operations ////
public:
  Translator();
  virtual ~Translator();
  std::map< IN *, OUT * > getBinding() const;
  virtual OUT * get(IN *) const;
  OUT * suscribe(IN *, OUT *);
  OUT * set(IN *, OUT *);
  void unsuscribe(IN *);
  void clear();

};

#include "Translator.inl"

#endif
