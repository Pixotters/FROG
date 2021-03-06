#include "GUI_Button.hpp"

#include <FROG/Collision/BoxCollider.hpp>
#include <FROG/Collision/Collision.hpp>
#include <FROG/Control/Function.hpp>
#include <FROG/Control/MouseButton.hpp>

#include <iostream> // TODO remove

using namespace frog;

ButtonUI::ButtonUI(const std::string& text, 
                   const sf::Font& font, 
                   const sf::Vector2f& dimensions)
  : RenderingComponent(new sf::Sprite),
    rectangle(new sf::RectangleShape),
    label(new sf::Text(text, font) )
{
  canvas = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
  canvas_texture.create(dimensions.x, dimensions.y);
  canvas->setTexture(canvas_texture.getTexture() );
  rectangle->setOutlineThickness(2);
  rectangle->setFillColor(sf::Color(0,0,0,0) );
  rectangle->setSize( dimensions );
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::update(const ComponentHolder& parent)
{
  auto t = parent.getComponent<Transform>("TRANSFORM");
  canvas->setPosition( t->getPosition() );
  canvas->setRotation( t->getRotation() );
  canvas->setScale( t->getScale().x, -t->getScale().y );
  canvas_texture.draw(*rectangle, sf::RenderStates::Default );
  canvas_texture.draw(*label, sf::RenderStates::Default );
  // TODO check if this is necessary
  canvas->setTexture(canvas_texture.getTexture() );
  /*  std::cerr << "canvas : "<< canvas->getPosition().x        \
      << ',' << canvas->getPosition().y << std::endl;
      std::cerr << "canvas_tex : "<< canvas_texture.getSize().x \
      << ',' << canvas_texture.getSize().y << std::endl; */
}

void ButtonUI::setString(const std::string& s)
{
  label->setString(s);
}

void ButtonUI::setText(const sf::Text& t)
{
  label.reset(new sf::Text(t) );
}


void ButtonUI::setBackground(const sf::Color& col)
{
  rectangle->setFillColor(col);
}

void ButtonUI::setTexture(const sf::Texture * tex)
{
  rectangle->setTexture(tex);
}


sf::Vector2f ButtonUI::getSize() const
{
  return rectangle->getSize();
}

////////////////////
////////////////////


Button::Button(std::vector<sf::Event>& e, 
               ButtonUI::PTR& bu,
               const Command::PTR& act)
  : GameObject(),
    selected(false)
{
  addComponent(bu, "RENDERING");
  auto fun = [this](Collision c)
    {
      try{
        if (c.second->getProperty<std::string>("type").compare("cursor") == 0 )
          {
            if (c.trigger == Collision::COLLISION)
              {
                selected = true;
              }else if (c.trigger == Collision::SEPARATION)
              {
                selected = false;
              }
          }
      }catch(std::logic_error e)
        {

        }
    };
  addComponent(BoxCollider::create(bu->getSize(), 
                                   sf::Vector2f(0,0), fun ), 
               "COLLIDER");
  addComponent(ControlComponent::create(e), "CONTROL");
  setAction(act);
}

Button::~Button()
{
}


void Button::setAction(const Command::PTR& fun)
{
  auto ctrl = getComponent<ControlComponent>("CONTROL");
  ctrl->removeMap(0); 
  ctrl->bind(MouseButton::create(sf::Mouse::Left, Trigger::PRESSED), 
             Function::create(
                              [this, fun](){ 
                                if (selected){
                                  fun->execute();
                                }
                              })
             );
}

Button::PTR Button::create(std::vector<sf::Event>& e, 
                           ButtonUI::PTR& u, 
                           const frog::Command::PTR& a)
{
  return PTR(new Button(e, u, a) );
}

