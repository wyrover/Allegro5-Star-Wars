# Overview
This is an implementation of an incomplete 2D Star Wars game using the Allegro5 game programming library for C++. I worked on this project while taking <a href="https://www.youtube.com/playlist?list=PL6B459AAE1642C8B4">Allegro5 tutorials</a> online.

![alt tag](https://raw.githubusercontent.com/ckjoshi9/Allegro5-Star-Wars/master/screenshot.png)

The X-Wing fighter's position on the screen is controlled by the mouse pointer. If it crashes into the stationary asteroid, an explosion sprite is displayed and an irritating sound is played. The sound is also played when the X-Wing crashes against the edges of the screen. All this goes on with the Death Star in the background and the Star Wars title song playing on loop.

# To-do
1. Add comments to code.
2. Implement shooting animation for X-Wing (use `animation.png` as the sprite, switching between the panels). If asteroid is within fire range, it should be replaced by the explosion sprite.
3. Make asteroid move around the screen randomly.
