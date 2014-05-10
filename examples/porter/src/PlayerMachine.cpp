#include "PlayerMachine.hpp"
#include "FROG/Component/AudioSource.hpp"

#include "FROG/Rendering/Animator.hpp"

#include <string>

PlayerMachine::PlayerMachine(Level * l)
  : frog::Component(), FSM<PlayerState>(), m_level(l)
{
}

PlayerMachine::~PlayerMachine()
{
}

void PlayerMachine::update(const frog::ComponentHolder& parent)
{
  static PlayerState::ID previous = PlayerState::COUNT;
  if (previous != m_stack.top()->getId() )
    {
      if ( m_stack.top()->getId() == PlayerState::STAND )
        {
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeTexture(m_level->defaultTextureManager.get("PORTER_SPRITESHEET") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeSpritesheet(m_level->defaultSpritesheetManager.get("Porter_anim") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->playAnimation("stand", true);
          previous = PlayerState::STAND;
        
        }
      if ( m_stack.top()->getId() == PlayerState::WAITING )
        {
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeTexture(m_level->defaultTextureManager.get("PORTER_SPRITESHEET") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeSpritesheet(m_level->defaultSpritesheetManager.get("Porter_anim") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->playAnimation("tap_foot", true);
          previous = PlayerState::WAITING;
        }
      if ( m_stack.top()->getId() == PlayerState::HANDING )
        {
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeTexture(m_level->defaultTextureManager.get("PORTER2_SPRITESHEET") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->changeSpritesheet(m_level->defaultSpritesheetManager.get("Porter_anim2") );
          parent.getComponent< frog::Animator<std::string> >("RENDERING")
            ->playAnimation("tap_foot", true);
          previous = PlayerState::HANDING;
        }

    }

}
    

