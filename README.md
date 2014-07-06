# FROG

For Really Outstanding Games, a C++ framework for game development.  
FROG is **free**, open-source, and **easy to use**. 

## Overview

- Abstract and modular: FROG is generic enough to be used in as many games 
genre as possible. It is provided in separated modules, users can choose 
features they need. 
- Game loop (scenario): handling the general process of computing and 
rendering among different scenes, considering the frame lag.
- Resources: smart assets managment, avoiding to load the same file twice. 
- Easy inputs: FROG supports keyboard, mouse and up to 8 joysticks. You can 
define buttons and actions very easily. 
- Rendering: sprites, text, animations, are simple to define.
- Physics: a simple physic engine is provided, allowing to apply forces. In 
case you don't need powerful physics. 
- Collision: famous algorithm *Sweep And Prune* is provided as collision 
detection handler. 

## Coming soon 

- Tile maps (format **Tiled**)
- Network facilities and lag compensation
- Light / Shadows (*not sure*)
- Basic AI (*not sure*)

## Installation 

### Linux 

Make sure SFML 2 (at least) is installed. Then you can build the library and 
copy it in your path : 

```
$ cd src
$ make
$ make install
```

## Manual

FROG is based on Scenes. A Scene is composed by GameObjects that can be 
customised by adding Component. Several components are already provided, 
such as graphics, physics... 
You can learn more thanks to the [tutorials](http://www.pixotters.org/frog/) 
and the [online API](http://pixotters.org/frog/api/html/).

## MIT License 

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
