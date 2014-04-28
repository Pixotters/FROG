#include "PlayerMachine.hpp"

#include "FROG/Rendering/Animator.hpp"

#include <string>
#include <iostream> //TODO remove

PlayerMachine::PlayerMachine(Level * l)
  : frog::Component(), FSM<PlayerState>(), m_level(l)
{
}

PlayerMachine::~PlayerMachine()
{
}

void PlayerMachine::update(const frog::ComponentHolder& parent)
{
  static std::string previous = "";
  if ( m_stack.top()->getId().compare("stand") == 0 
       && previous.compare("stand") != 0 )
    {
      std::cerr << "Changing state" << std::endl;
      parent.getComponent< frog::Animator<std::string> >()->changeTexture(m_level->m_textureManager.get("PORTER_SPRITESHEET") );
      parent.getComponent< frog::Animator<std::string> >()->changeSpritesheet(m_level->m_spritesheetManager.get("Porter_anim") );
      parent.getComponent< frog::Animator<std::string> >()->playAnimation("stand", true);
      previous = "stand";

    }
  if ( m_stack.top()->getId().compare("wait") == 0 
       && previous.compare("wait") != 0 )
    {
      std::cerr << "Changing state" << std::endl;
      parent.getComponent< frog::Animator<std::string> >()->changeTexture(m_level->m_textureManager.get("PORTER_SPRITESHEET") );
      parent.getComponent< frog::Animator<std::string> >()->changeSpritesheet(m_level->m_spritesheetManager.get("Porter_anim") );
      parent.getComponent< frog::Animator<std::string> >()->playAnimation("tap_foot", true);
      previous = "wait";
    }
  if ( m_stack.top()->getId().compare("rapping") == 0 
       && previous.compare("rapping") != 0 )
    {
      std::cerr << "Changing state" << std::endl;
      parent.getComponent< frog::Animator<std::string> >()->changeTexture(m_level->m_textureManager.get("PORTER2_SPRITESHEET") );
      parent.getComponent< frog::Animator<std::string> >()->changeSpritesheet(m_level->m_spritesheetManager.get("Porter_anim2") );
      parent.getComponent< frog::Animator<std::string> >()->playAnimation("tap_foot", true);
      previous = "rapping";
    }
  

}
