#ifndef FROG_ANIMATOR_HPP
#define FROG_ANIMATOR_HPP

#include "FROG/ComponentHolder.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Rendering/Animation.hpp"
#include "FROG/Rendering/Spritesheet.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <exception>
#include <map>
#include <string>

namespace frog{

  /*!
   * Animator<ID> is the component handling Animation. The template indicates 
   * the type of identifiers of Animations. 
   * Basically, animators make the link between a Spritesheet and a texture. 
   * An animation played by default can be provided
   */
  template <typename ID>
  class Animator : virtual public RenderingComponent{

  protected:
    sf::Sprite m_sprite;
    Spritesheet<ID>& m_spritesheet;
    unsigned short m_frameKey;
    unsigned short m_timer;
    const Animation * m_defaultAnimation;
    const Animation * m_played;
    bool m_loop;

  public:

    Animator(Spritesheet<ID>& , sf::Texture&);

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
    const Animation& setDefaultAnimation(ID id);

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

  };

}

#include "FROG/Rendering/Animator.inl"

#endif
