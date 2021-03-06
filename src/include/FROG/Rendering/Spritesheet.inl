/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#include "FROG/XML.hpp"
#include "FROG/Core/Debug.hpp"

#include <sstream>

namespace frog{

  template <typename ID>
  Spritesheet<ID>::Spritesheet()
  {

  }

  template <typename ID>
  Spritesheet<ID>::Spritesheet(const Spritesheet& other)
  {
    for(auto itclip : other.m_clips)
      {
        m_clips.push_back( itclip );
      }    
    for(auto itanim : other.m_animations)
      {
        m_animations.emplace( itanim.first, itanim.second );
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
    unsigned max_id=0;
    if (sprites->QueryUnsignedAttribute("max_id", &max_id) 
        != tinyxml2::XML_NO_ERROR)
      {
        print_debug("Need to know the max id of clips");
        return false;
      }
    m_clips.resize(max_id+1);
    for(tinyxml2::XMLElement * sprite = sprites->FirstChildElement(); 
        sprite != nullptr; 
        sprite = sprite->NextSiblingElement() )
      {
        unsigned id = 0;
        if( sprite->QueryUnsignedAttribute("id", &id) != tinyxml2::XML_NO_ERROR )
          {
            print_debug("Could not create Clip without ID");
            continue;
          }
        int x = 0, y = 0;
        if( sprite->QueryIntAttribute("x", &x) != tinyxml2::XML_NO_ERROR )
          {           
            continue;
          }
        unsigned width = 1, height = 1;   
        if( sprite->QueryIntAttribute("y", &y) != tinyxml2::XML_NO_ERROR )
          {
            print_debug("Could not create Clip because position(y) is missing");
            continue;
          }
        if( sprite->QueryUnsignedAttribute("width", &width) != tinyxml2::XML_NO_ERROR )
          {
            print_debug("Could not create Clip because width is missing");
            continue;
          }
        if( sprite->QueryUnsignedAttribute("height", &height) != tinyxml2::XML_NO_ERROR )
          {
            print_debug("Could not create Clip because height is missing");
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
                print_debug("Could not create Animation without ID");
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
                    print_debug("Could not create Animation Clip without ID");
                    continue;                    
                  }
                float float_dur = 1.0f/60.0f;
                clip->QueryFloatAttribute("duration", &float_dur);
                sf::Time duration = sf::seconds(float_dur);
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
    throw(std::logic_error)
  {
    try
      {
        return m_animations.at(id);
      }catch(std::out_of_range e)
      {
        std::ostringstream oss;
        oss << "Animation "<< id \
            <<" does not exist in Spritesheet "<< this;
        throw std::logic_error( oss.str().c_str() );
        oss.flush();
      }
  }

  template <typename ID>
  const Clip& Spritesheet<ID>::getClip(unsigned short id) const
    throw(std::logic_error)  
  {
    try
      {
        const Clip& clip = m_clips.at(id);
        return clip;
      }catch(std::out_of_range e)
      {
        std::ostringstream oss;
        oss << "Clip "<< id \
            <<" does not exist in Spritesheet "<< this;
        throw std::logic_error( oss.str().c_str() );
        oss.flush();
      }
  }

  template <typename ID>
  void Spritesheet<ID>::addAnimation(const Animation& a, ID id)
  {
    m_animations.emplace( id, Animation(a) );
  }

  template <typename ID>
  void Spritesheet<ID>::addClip(const Clip& c, unsigned short id)
  {
    m_clips.at(id) = Clip(c);
  }


  template <typename ID>
  void Spritesheet<ID>::deleteAnimations()
  {
    m_animations.clear();
  }

  template <typename ID>
  void Spritesheet<ID>::deleteClips()
  {
    m_clips.clear();
  }

}
