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
        unsigned id = sprite->UnsignedAttribute("id");
        int x = sprite->IntAttribute("x");
        int y = sprite->IntAttribute("y");
        unsigned width = sprite->UnsignedAttribute("width");
        unsigned height = sprite->UnsignedAttribute("height");
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
            const char* id = anim->Attribute("id");
            Animation a;
            tinyxml2::XMLElement * clips = anim->FirstChildElement("CLIPS");
            for(tinyxml2::XMLElement * clip = clips->FirstChildElement();
                clip != nullptr;
                clip = clip->NextSiblingElement() )
              {
                unsigned short id = clip->UnsignedAttribute("id");
                unsigned short duration = clip->UnsignedAttribute("duration");
                float move_x = clip->FloatAttribute("move_x");
                float move_y = clip->FloatAttribute("move_y");
                float rotation = clip->FloatAttribute("rotation");
                float scale_x = clip->FloatAttribute("scale_x");
                float scale_y = clip->FloatAttribute("scale_y");
                sf::Transform t = sf::Transform::Identity;
                t.translate( sf::Vector2f(move_x, move_y) );
                t.rotate( rotation );
                t.scale( sf::Vector2f(scale_x, scale_y) );                
                a.addClip( AnimationClip(id, duration, t ) );
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
