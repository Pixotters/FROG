#include "FROG/XML/tinyxml2.hpp"

namespace frog{

  template <typename ID>
  Spritesheet<ID>::Spritesheet()
  {

  }

  template <typename ID>
  Spritesheet<ID>::Spritesheet(const Spritesheet& other)
  {
    auto sizeclip = other.m_clips.size();
    m_clips.resize(sizeclip);
    for(auto itclip = 0; itclip < sizeclip; itclip++)
      {
        m_clips.at(itclip) = Clip(other.m_clips.at(itclip) );
      }
    auto endanim = other.m_animations.end();
    for(auto itanim = other.m_animations.begin(); itanim != endanim; itanim++)
      {
        m_animations.insert( std::make_pair(itanim->first, Animation(itanim->second) )  );
      }
    
  }

  template <typename ID>
  Spritesheet<ID>::~Spritesheet()
  {
    deleteAnimations();
    deleteClips();
  }

  // TODO ensure that required fields are present (valid file)
  template <typename ID>
  bool Spritesheet<ID>::loadFromFile(const std::string& file)
  {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile( file.c_str() ) != tinyxml2::XML_NO_ERROR )
      {
        return false;
      }
    tinyxml2::XMLElement * sprt, * sprites, * animations;
    sprt = doc.RootElement();
    sprites = sprt->FirstChildElement("SPRITES");
    if( not sprites)
      {
        return false;
      }
    for(tinyxml2::XMLElement * sprite = sprites->FirstChildElement(); 
        sprite != nullptr; 
        sprite = sprite->NextSiblingElement() )
      {
        unsigned id = 0;
        if( sprite->QueryUnsignedAttribute("id", &id) != tinyxml2::XML_NO_ERROR )
          {
            std::cerr << "Could not create Clip without ID" << std::endl;
            continue;
          }
        int x = 0, y = 0;
        if( sprite->QueryIntAttribute("x", &x) != tinyxml2::XML_NO_ERROR )
          {
            std::cerr << "Could not create Clip "<< id \
                      << " because position (x) is missing" << std::endl;
            continue;
          }
        unsigned width = 1, height = 1;   
        if( sprite->QueryIntAttribute("y", &y) != tinyxml2::XML_NO_ERROR )
          {
            std::cerr << "Could not create Clip "<< id \
                      << " because position (y) is missing" << std::endl;
            continue;
          }
        if( sprite->QueryUnsignedAttribute("width", &width) != tinyxml2::XML_NO_ERROR )
          {
            std::cerr << "Could not create Clip "<< id \
                      << " because width is missing" << std::endl;
            continue;
          }
        if( sprite->QueryUnsignedAttribute("height", &height) != tinyxml2::XML_NO_ERROR )
          {
            std::cerr << "Could not create Clip "<< id \
                      << " because height is missing" << std::endl;
            continue;
          }
        int hot_x = sprite->IntAttribute("hot_x");
        int hot_y = sprite->IntAttribute("hot_y");
        addClip( Clip(x, y, width, height, hot_x, hot_y), id );
      }
    animations = sprt->FirstChildElement("ANIMATIONS");
    if ( animations )
      {
        for(tinyxml2::XMLElement * anim = animations->FirstChildElement();
            anim != nullptr;
            anim = anim->NextSiblingElement() )
          {
            const char* id;
            if ( (id = anim->Attribute("id") ) == NULL )
              {
                std::cerr << "Could not create animation without ID" << std::endl;
                continue;                                    
              }
            
            Animation a;
            tinyxml2::XMLElement * clips = anim->FirstChildElement("CLIPS");
            for(tinyxml2::XMLElement * clip = clips->FirstChildElement();
                clip != nullptr;
                clip = clip->NextSiblingElement() )
              {
                unsigned clipid; 
                if( clip->QueryUnsignedAttribute("id", &clipid) != tinyxml2::XML_NO_ERROR)
                  {
                    std::cerr << "Could not create animation clip without ID" << std::endl;
                    continue;                    
                  }
                unsigned duration = 1;
                clip->QueryUnsignedAttribute("duration", &duration);
                float move_x, move_y; 
                clip->QueryFloatAttribute("move_x", &move_x);
                clip->QueryFloatAttribute("move_y", &move_y);
                float rotation = clip->FloatAttribute("rotation");
                float scale_x = 1.0f, scale_y = 1.0f; 
                clip->QueryFloatAttribute("scale_x", &scale_x);
                clip->QueryFloatAttribute("scale_y", &scale_y);
                sf::Transform t = sf::Transform::Identity;
                t.translate( sf::Vector2f(move_x, move_y) );
                t.rotate( rotation );
                t.scale( sf::Vector2f(scale_x, scale_y) );                
                a.addClip( AnimationClip(clipid, duration, t ) );
              }
            addAnimation( a, id);
          }
      }
    return true;
  }

  template <typename ID>
  const Animation& Spritesheet<ID>::getAnimation(ID id) const
    throw(NoSuchAnimation)
  {
    try
      {
        return m_animations.at(id);
      }catch(std::out_of_range e)
      {
        std::cerr << "Animation "<< id \
                  <<" does not exist in Spritesheet "<< this << std::endl;
        throw NoSuchAnimation();
      }
  }

  template <typename ID>
  const Clip& Spritesheet<ID>::getClip(const unsigned short& id) const
    throw(NoSuchClip)
  {
    try
      {
        auto clip = m_clips.at(id);
        return clip;
      }catch(std::out_of_range e)
      {
        std::cerr << "Clip "<<id \
                  <<" does not exist in Spritesheet "<< this << std::endl;
        throw NoSuchClip();
      }
  }

  template <typename ID>
  void Spritesheet<ID>::addAnimation(const Animation& a, ID id)
  {
    m_animations.insert( std::make_pair(id, a) );
  }

  template <typename ID>
  void Spritesheet<ID>::addClip(const Clip& c, const unsigned short& id)
  {
    try{
      m_clips.at(id) = c;
    }catch(std::out_of_range e){
      m_clips.resize(id+1); // TODO : allocate good size at the beginning ?
      m_clips.at(id) = c;      
    }
  }

  template <typename ID>
  void Spritesheet<ID>::deleteAnimations()
  {
    // TODO ensure no leak
    m_animations.clear();
  }

  template <typename ID>
  void Spritesheet<ID>::deleteClips()
  {
    // TODO ensure no leak
    m_clips.clear();
  }

}
