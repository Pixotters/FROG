#ifndef FROG_ANIMATOR_HPP
#define FROG_ANIMATOR_HPP

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Rendering/Animation.hpp"
#include "FROG/Rendering/Spritesheet.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

namespace frog{


  static Animation noAnim;

  /*!
   * Animator<ID> is the component handling Animation. The template indicates 
   * the type of identifiers of Animations. 
   * Basically, animators make the link between a Spritesheet and a texture. 
   * An animation played by default can be provided
   */
  template <typename ID>
  class Animator : virtual public RenderingComponent
  {

  public:
    typedef std::shared_ptr<Animator<ID>> PTR;
    sf::Time& deltaTime;

  protected:
    std::shared_ptr<sf::Sprite> m_sprite;
    Spritesheet<ID>& m_spritesheet;
    unsigned short m_frameKey;
    sf::Time m_timer;
    ID m_defaultAnimation;
    ID m_played;
    bool m_loop;

  public:

    Animator(sf::Time&, Spritesheet<ID>& , sf::Texture&);

    virtual ~Animator();

    virtual void update(const ComponentHolder& parent);

    /*!
     * @brief Plays the animation identified by the given id.
     * @details If loop is set to "true", animation will be played until 
     * an other call to this function with a different id. If it is not looped,
     * default animation will be played once it is finished. If no default 
     * was provided, the animation will stick. 
     * If given id doesn't match an animation, "NoSuchAnimation" exception will 
     * be thrown.
     * @param id ID associated with the animation
     * @param loop Tells if the animation should loop or not.
     */
    void playAnimation(ID id, bool loop = false);

    /*!
     * @brief Plays the given animation.
     * @details If loop is set to "true", animation will be played until 
     * an other call to this function with a different id. If it is not looped,
     * default animation will be played once it is finished. If no default 
     * was provided, the animation will stick. 
     * @param a Animation to play.
     * @param loop Tells if the animation should loop or not.
     */
    void playAnimation(const Animation& a, bool loop = false);
  
    /*!
     * @brief Defines a default animation
     * @details Default animation is played when "playAnimation" finished in
     * non-loop mode, and at the beginning (when "playAnimation" has not been 
     * called yet). 
     * If given id doesn't match an animation, "NoSuchAnimation" exception will 
     * be thrown.
     * @param id ID associated with the animation.
     * @return Previous default animation. 
     */
    void setDefaultAnimation(ID id);

    /*!
     * @brief Sets the texture associated to the spritesheet.
     * @param tex New sf::Texture to bind to the current spritesheet.
     */
    void changeTexture(sf::Texture& tex);

    /*!
     * @brief Sets the spritesheet associated to the texture.
     * @param tex New Spritesheet to bind to the current texture.
     */
    void changeSpritesheet(Spritesheet<ID>& sprt);

    static PTR create(sf::Time&, Spritesheet<ID>& , sf::Texture&);

  };

}

#include "FROG/Rendering/Animator.inl"

#endif
