#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <FROG/Core/ComponentHolder.hpp>
#include <FROG/Core/GameObject.hpp>
#include <FROG/Rendering/RenderingComponent.hpp>
#include <FROG/Rendering/TextSprite.hpp>
#include <FROG/Control/ControlComponent.hpp>
#include <FROG/Control/Command.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <string>
#include <vector>

class ButtonUI : virtual public frog::RenderingComponent
{

  friend class Button;
public:
  typedef std::shared_ptr<ButtonUI> PTR;

private:
  sf::RenderTexture canvas_texture;
  std::shared_ptr<sf::Sprite> canvas;
  std::shared_ptr<sf::RectangleShape> rectangle;
  std::shared_ptr<sf::Text> label;

public:
  ButtonUI(const std::string& text, 
           const sf::Font& font, 
           const sf::Vector2f& dimensions = sf::Vector2f(1,1) );
  virtual ~ButtonUI();
  virtual void update(const frog::ComponentHolder&);
  void setString(const std::string&);
  void setText(const sf::Text&);
  void setBackground(const sf::Color&);
  void setTexture(const sf::Texture *);
  sf::Vector2f getSize() const;
  

};

class Button : virtual public frog::GameObject
{

public:
  typedef std::shared_ptr<Button> PTR;

private:
  bool selected;

public:
  Button(std::vector<sf::Event>& e, 
         ButtonUI::PTR&, 
         const frog::Command::PTR& );
  virtual ~Button();
 
  void setAction(const frog::Command::PTR& fun);
  PTR create(std::vector<sf::Event>&, 
             ButtonUI::PTR&, 
             const frog::Command::PTR& );
};

#endif
