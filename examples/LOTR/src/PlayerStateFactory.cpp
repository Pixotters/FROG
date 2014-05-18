#include "PlayerStateFactory.hpp"

#include <FROG/Rendering/Animator.hpp>

using namespace frog;



PlayerStateFactory::PlayerStateFactory(const frog::GameObject::PTR& o1,
                                       const frog::GameObject::PTR& o2,
                                       const PlayerMachine::PTR& m)
  : object1(o1), object2(o2), machine(m)
{
  createStates();
}

PlayerStateFactory::~PlayerStateFactory()
{
}

PlayerState PlayerStateFactory::get(const std::string& id) const
{
  return map.at(id);
}

void PlayerStateFactory::createStates()
{
  auto anim1 = object1->getComponent<Animator<std::string>>("RENDERING");
  auto anim2 = object2->getComponent<Animator<std::string>>("RENDERING");
  // stand state
  auto stand_enter = [anim1, anim2]()
    {
      anim1->playAnimation("stand", true);
      anim2->playAnimation("stand", true);
    };
  map.emplace("stand", PlayerState(stand_enter) );
  // punchL
  auto punchL_enter = [anim1, anim2]()
    {
      anim1->playAnimation("punchL");
      anim2->playAnimation("punchL");
    };
  map.emplace("punchL", PlayerState(punchL_enter) );
  // punchM
  auto punchM_enter = [anim1, anim2]()
    {
      anim1->playAnimation("punchM");
      anim2->playAnimation("punchM");
    };
  map.emplace("punchM", PlayerState(punchM_enter) );
  // punchR
  auto punchR_enter = [anim1, anim2]()
    {
      anim1->playAnimation("punchR");
      anim2->playAnimation("punchR");
    };
  map.emplace("punchR", PlayerState(punchR_enter) );
  // dodgeL
  auto dodgeL_enter = [anim1, anim2]()
    {
      anim1->playAnimation("dodgeL");
      anim2->playAnimation("dodgeL");
    };
  map.emplace("dodgeL", PlayerState(punchR_enter) );
  // dodgeM
  auto dodgeM_enter = [anim1, anim2]()
    {
      anim1->playAnimation("dodgeM");
      anim2->playAnimation("dodgeM");
    };
  map.emplace("dodgeM", PlayerState(punchR_enter) );
  // dodgeR
  auto dodgeR_enter = [anim1, anim2]()
    {
      anim1->playAnimation("dodgeR");
      anim2->playAnimation("dodgeR");
    };
  map.emplace("dodgeR", PlayerState(punchR_enter) );
}
