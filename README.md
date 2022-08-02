# Soft323_MainAssignment

My Final Assignment for Programming For Entertainment Systems (Plymouth University 2006)

## Demo Instructions

Simple run the debug executable, on loading you will see a setup screen. Optimal settings are defaulted so you can just press OK. 

**Optimal settings are:**

1024/768 full screen, high detail meshes, music on.

A note on config settings, high resolutions work by cause problems with text alignment.
Once the game proper loads you will be presented with a briefing click LMB or return to continue to the game.
Once in the game use the control below to fly around, about 1 minute in the enemy ships will arrive.

### Demo Controls: 
**Yaw:**
MouseX or Keyboard Arrow Left/Arrow Right 

**Pitch:**
MouseY or Keyboard Arrow Up/ Arrow Down 

**Increase/Decrease Speed:**
Mouse Wheel or Keyboard PageUp/PageDown 

**Shoot:**
Left Mouse Button or Keyboard Return 

**Target Next Enemy:**
Keyboard 'E'

**Target Next Friendly:**
Keyboard 'T' 

**Target Nearest Enemy:**
Right Mouse Button or Keyboard 'N' 

**Exit Demo:**
Keyboard Esc

## Program Flow
1. Main.cpp sets up the configuration window which waits for the users selections
2. Once the various selections have been made, main.cpp creates window for the game and creates an instance of d3dApplication.cpp, this in the main demo code.
3. d3dApplication.cpp: 
  1. Configures the 3D hardware using an instance of capabilities.cpp
  2. Sets initial render states
  3. Loads and displays in game briefing and win and lose text screens
  4. Loads the sound and meshes for the players ship
  5. Sets up the games mission using missionSystem.cpp
  6. Load and draws the sky box (depending on max texture size)
  7. Starts the game proper using an instance of gameObjects.cpp
  8. Handles keyboards inputs
  9. Runs the game by updating playerShip, gameObjects and missionSystem
4. missionSystem.cpp controls game events, adding enemy and friendly ships according to a timer. missionSystem.cpp also handles mission objectives, mission critical ships and consequently the mission status (not started,won,lost). If the mission is in one of the previous states missionSystem.cpp alerts d3dApplication that in turn displays a briefing, won or lost screen. The text for those screens comes from missionSystem.cpp. 
5. gameObjects.cpp is perhaps the second most critical part of this application. 
  1. It updates AI ship movement
  2. Renders ALL in game objects
  3. Handles sound and graphics for explosions and warping
  4. Removes dead ships
  5. Checks for plasma hits on all in game objects
  6. Checks high level collisions on all in game objects
7. Checks for low level collisions on player ship.
6. objectTransform.cpp is the foundation of nearly all in game objects. If provides low and high level collision detection, chase cameras (and cull frustum), and movement. It also handles sound for each object and mesh data in the from of a list of ‘viewObjects.cpp’
7. Ship.cpp is relatively simple handling a ships movement capabilities, health, and gunfire.
  1. aiShip.cpp is a subclass of ship.cpp AI to move to, evade, and fire at other AI targets or nav points.
  2. playerShip is a subclass of ship.cpp. This provides required text and sound interfaces specific to the players ship.
  3. capitalShip.cpp ship is a subclass of ship.cpp and provides sporning capabilities for AI fighters
8. 3Dsound is a 3d sound class present in every objectTransform based object. It is largely Nigel’s code
9. imageSequence.cpp loads an flips through a sequences of images at a set speed. It is necessary for explosion and warp effects.
10. mp3Player.cpp plays mp3s using MCI, this is largely referenced code from a web article.
