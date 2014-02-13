= FROG Project - Nicolas Cailloux & Julien Sagot =

For Really Outstanding Games

== Presentation ==

We wish to develop an engine for developing video games. The goal is to make 
the development of such programs faster and easier, by providing redundant 
components: we don't want to write again and again the same code. Thus, users 
can focus on more important tasks such as conception or writing application 
specific algorithms.

The FROG library will be based on [[https://github.com/LaurentGomila/SFML << 
SFML]], by Laurent Gomila. It will be coded in C++.

== Why? ==

There are many game engines available: why would we develop our own engine?

- Among current engines, a lot use 3D: in the context of 2D games, there are 
  more difficult to learn, for a dimension that you would not even use. 
- Among current engines, many are available only for Microsoft's Windows: as 
  SFML is portable, FROG will be portable. 
- Many //game making libraries// on drag & drop: we don't really like this 
  approch, because it can make you lose a lot of time, notably if not much 
  shortcuts are available. 
- Many are closed: one does not simply modify the code to add features. Our 
  project, once the university semester finished, will be free and open-source, 
  so that everybody could extend it.
- Some are not free of charges. 
- A lot are limited to one *genre*: fighting, plateform, RPG... We would like 
  to make something usable in the largest situations possible. 

== Details == 

Qualities wanted for the engine are: 

- Abstract: it should be generic enough to be used in as many programs as 
  possible.
- Simple: the goal is to speed up the development phase, by provinding 
  ready-to-use components with few configuration needed.
- Modular: we should be able to use a component regardless of other ones.  
- Extensible: it must be easy to add more components in the future.  

== Quality tests ==

In order to determine if the library is a success, we will implements 2 games 
of different kind sharing a lot of modules.

>>> I would like to reimplement [[https://github.com/Lasconik/LordzOfTheRing << 
    Lasconik's LOTR game]] to provide a comparison between a game using FROG 
    and the same game using it<<<

== Features ==

The components we thank about (by ourselves or after lectures) are described 
below. We sorted them by interest, because if we run out of time, it is easier 
to cut the non-vital features. List can seems long, but many features are 
simple and easy to implement, especially using SFML as base.

=== Bare minimum  ===

==== Game loop ====

A game takes place in a loop: read input, react to inputs, compute game logic, 
graphic rendering, and loop. We shall also handle time: according to the 
machine, the FPS (number of looping by second) can vary a lot, resulting on a 
different behaviour. The time has to be fixed, that's the idea of dealing with 
//delta time// (the time elapsed since the previous cycle). 

==== State Machine ====

What we are calling a state is a "phase" of the game: Main menu, Splash screen, 
a scene, the Options menu (...) are different state. By passing from one to 
another, we create implicit transitions: this creates an implicit automaton 
that can be handled in a generic way, so that the user will create his own 
states that will be handled by the engine. 

==== Files / Resources ====

Accessing a file is heavy: we want to limit these accesses as much as possible. 
For instance, if a file has been loaded in the memory, there is no need to 
reload it. We may also want to ensure a file has really been sucessfully loaded 
before accessing the resources it contains.  It is possible to make some kind 
of memoization on the files. >>>Need details about memoization<<<

==== Inputs ====

A game needs its player to interact with it. Inputs can be sent by the keyboard, 
the mouse, or the joystick. Each input can be associated to an action, but an 
action can be trigerred by several different inputs (for instance, one by the 
keyboard and one by the joystick). Theses associations have to be handled, while 
allowing an easy customisation.  
We think about a table **action <-> input(s)**.  

==== Rendering ====

SFML provides window displaying and textures drawing. We want to offer more, by 
proposing layers, views, but also a correct resolution handler (elements have to 
be positionned the same way, no matter the size of the window).  

=== Useful features === 

==== GUI toolkit ====

Based on container/component model, we should be able to easily produce:

- Windows
- Dialog window
- Panels
- Menus

- Buttons
- Text area
- Checkboxes
- Choices list
- Scroll bar

Frog will also provided few basics layout handlers:

- GridLayout: Same fixed size for each cell (responsive size)
- HResponsiveLayout: Fixed or relative height for each component
- VResponsiveLayout: Fixed or relative width for each component

==== Objects / Entities ====

Thanks to polymorphism, it is possible to group objects handled by the engine 
that appear within a scene. Those are treated the same way by the engine, without 
taking account of the differences.  

//For instance, a projectile and an enemy are two distinct entities: they don't 
behave the same way. But both are drawn, updated by the engine, depending on 
common attributs (position, rotation, scale, ...).//

//The best will occur if we can offer game objects a data-driven design: their 
attributes are loaded from a file, instead of being hard-coded. This reduces 
the compilation time, offers more flexibility, but may cause reliability 
problems: what if the file is missing? Should we use default values? Crash?//
>>> Even if it is not hard coded in source, it should be hardcoded in binaries. 
    Otherwise, I think we are runnning a major security issue -> players could 
    change any value for any field. It means no gain on compilation time. <<<

==== Animations ====

Animating a visual element is a commun feature. We think we will use "clip" 
animations, based on frames and spritesheets. However, the user should have 
the possibility to create his own animation system, so the engin should load 
the spritesheets (and convert them in animations) in an extensive way. 

==== Scene graphe ====

In order to class in a hierarchy the entities of a scene: if one moves a 
container, he expects the content to be moved with it; if the chief of a team 
moves, his fellows should follow him. It implies the implementation of a 
relative coordinate system (relative to a parent, for instance).  

=== Advanced features ===

==== Collision / Physics ====

Probably the longest task, this module mobilises algorithms for space sorting, 
collision testing, forces handling... These notions require mathematics, so as 
developers we want to avoid them: once written, we will not have to worry about 
maths. And so will the average user.  
>>> I think collision manager and physics manager are 2 different tasks, even if
    the second needs the first <<<

==== Views ====

Improve the cameras, allowing multiples view (such as map or spliscreen), or 
view of different shapes. We also think about culling (displaying only what 
can be viewed from a camera).

==== Tile maps ====

2D games' levels are often represented as a Tile map: a grid of values pointing 
to a tile, and this tile posseses the properties (such as the graphic, the 
collision, the destructability, ...). As this system is really spread among game 
developers, we should included tile mapped levels. It may imply the creation of 
a map editor, or a very high generic parser that allows customizint tiles' 
size, number of layers, tiles properties.

>>>Need more details<<<

==== Light / shadows ====

Managing lights and shadows will result in a fancier render.  
Many lights are frequently used: point light, directional light, ambient light... 
Shadows will be present where there is no light, but we have to think about 
some things: how will we handle multiple light sources? Can shadows be soft? Hard? 
Colorful?

>>>It could be realised as using an extra layer<<<

==== Network ====

Nowadays, online gaming is generalized. The time where players met around a 
video game console is over: today they play via the internet. Not doing a 
network module would really hinder the multiplayer potential of our library, 
and reduce its usefulness.  

>>>May not be available on v1.0 release, but certainly will be added asap<<<

==== AI ====

An Artificial Intelligence is obviously application-specific, but some 
low-levels components or templates are possible: blind search, heuristic 
search, minmax / alpha-beta, but also reactive agent machines, or bayesian 
networks... There is probably a way to propose some base skeleton on which the 
user could put some flesh.

>>>I do not believe in this feature. Examples may convince me.<<<
