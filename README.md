# TerraMU
TerraMU is a 2D game inspired by the [MMORPG server](https://www.terra.mu/) of the same name. One can explore the open world, attack monsters and obtain items. The game was implemented using the OpenGL library.

## Game world
The game world is a plane of tiles 255x255 in size. Most of these tiles can be stepped by a player, for example grass, sand and stone. The rest of the tiles contain static objects, like tree or fence, so a player cannot walk on them.

## Monsters
There are spots on the map near which monsters appear. Initially each monster is calm and just walks around. If player is close enough, it will start chasing and attacking him. The player, in turn, can attack back.

![Calm](https://media.giphy.com/media/yJMz20ivZmPQNnTSmK/giphy.gif)

![Angry](https://media.giphy.com/media/bCMyH9sEHFOHKRxdtS/giphy.gif)

![Angry2](https://media.giphy.com/media/4KJkaFUOzjR2U0CI5A/giphy.gif)

![Monsters](https://media.giphy.com/media/GJdPg5aByjcFTQlqaO/giphy.gif)

## Items
The item can either lie on the map or be in the player's inventory. Items can drop on map after a monster dies. After this, a player can pick up these items.

![Inventory](https://media.giphy.com/media/HGCswEMpAhkPwDTksf/giphy.gif)

# Used libraries
* GLFW, GLEW
* SOIL
* GLM

---
You can contact us if you want on mail:  
artem_chernikov00@list.ru  
or  
anton_chernikov1@list.ru
