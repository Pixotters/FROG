namespace frog{

  template <typename ID>
  Spritesheet<ID>::Spritesheet()
  {

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
    tinyxml2::XMLElement * sprt, sprites, animations;
    sprt = doc.RootElement();
    sprites = sprt->FirstChildElement("SPRITES");
    if( not sprites)
      {
        return false;
      }
    for(tinyxml2::XMLElement * sprite = sprites->FirstChildElement(); 
        sprite != nullptr; 
        sprite = sprite->nextSiblingElement() )
      {
        unsigned id = sprite = sprite->UnsignedAttribute("id");
        int x = sprite = sprite->IntAttribute("x");
        int y = sprite = sprite->IntAttribute("y");
        unsigned width = sprite->UnsignedAttribute("width");
        unsigned height = sprite->UnsignedAttribute("height");
        int hot_x = sprite = sprite->IntAttribute("hot_x");
        int hot_y = sprite = sprite->IntAttribute("hot_y");
<<<<<<< HEAD
        addClip( new Clip(id, x, y, width, height, hot_x, hot_y) );
=======
        spritesheet.addClip( new Clip(id, x, y, width, height, hot_x, hot_y) );
>>>>>>> 3450c08994674b00ebfe84fbed45d3f668b5eb0b
      }
    animations = sprt->FirstChildElement("ANIMATIONS");
    if ( animations )
      {
        for(tinyxml2::XMLElement * anim = animations->FirstChildElement();
            anim != nullptr;
            anim = anim->NextSiblingElement() )
          {
            const char* id = anim->Attribute("id");
            Animation * a = new Animation();
            tinyxml2::XMLElement * clips = anim->FirstChildElement("CLIPS");
            for(tinyxml2::XMLElement * clip = clips->FirstChildElement();
                clip != nullptr;
                cli = clip->NextSiblingElement() )
              {
                unsigned id = clip->UnsignedAttribute("id");
                unsigned duration = clip->UnsignedAttribute("duration");
                float move_x = clip->FloatAttribute("move_x");
                float move_y = clip->FloatAttribute("move_y");
                float rotation = clip->FloatAttribute("rotation");
                float scale_x = clip->FloatAttribute("scale_x");
                float scale_y = clip->FloatAttribute("scale_y");
                a->addClip( new AnimationClip(id, duration, sf::Vector2f(move_x, move_y), ) );
              }
            addAnimation(a, id);
          }
      }
    return true;
  }

  template <typename ID>
  Animation * Spritesheet<ID>::getAnimation(ID id) const
  {
    return m_animations.at(id);
  }

  template <typename ID>
  void Spritesheet<ID>::addAnimation(Animation * a, ID id)
  {
    m_animations.insert( std::make_pair<Animation *, ID>(a, id) );
  }

  template <typename ID>
  void Spritesheet<ID>::addClip(Clip * c)
  {
    m_clips.push_back(c);
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
