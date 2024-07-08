# Server documentation

## Networking

- The server is a TCP server.

- The server is listening on a port defined in the command line arguments.

- The select function is used to handle multiple clients, and its unlocking when something has to happens at a given time, or when there is activity on a socket.

## Game mechanics

## Map and Tiles

- Map is generated randomly by the server.
- The map is a 2D array of tiles. Stored in a linked list.
- Each tile has a position, and a list of objects. (players not included)

## Players

Players have a team_name, position, direction, level, inventory, ID (fd), is_alive, timer_action and death and is_frozen.

- The team_name is defined in the command line arguments. (when launching the AI)

- The position is assigned by the server and is randomly selected. (the first player of the team will be placed on the spawnpoint, then the next players will be placed on the same tile as the first player)

- The direction is given by the IA by using the `Right` and `Left` commands.

- The level is increased by the server when the player has incanted.

- The inventory is a list of 7 integers representing the number of objects the player has. Food is needed to survive, the other objects are needed to incant.

- The ID is assigned by the server.

- The is_alive is set to false when the player dies.

- The timer_action is set to 0 when the player can do an action.

- The death is set to the current time when the player dies.

- The is_frozen is set to true when the player is frozen (while incanting).

## Teams

Teams have a name, slots (Max, Available), ID, spawnpoint and eggs.

- Their name is defined in the command line arguments.

- The slots are defined in the command line arguments.

- The ID is assigned by the server.

- The spawnpoint is assigned by the server and is randomly selected. the first player of the team will be placed on the spawnpoint, then the next players will be placed on the same tile as the first player.

- The eggs are layed by players and can be hatched to create new players. (at the position of the Egg)

## Eggs

Eggs have a position, and ID.

- In order to to lay an egg, a player must use the `Fork` command.

- Once an egg is layed, the team that is the owner of the egg will have a new player when the egg hatches. (slotMax is incremented so an AI can connect). The connection of the new AI is done manually.

- If a player calls `Eject` on a tile with an egg, the Egg will be destroyed.

## Incantation

The incantation is a ritual that players must do in order to level up. The incantation is done by calling the `Incantation` command.

- The incantation requires a certain number of players on the same tile. All players need to be the same level.

- The incantation requires a certain number of objects on the same tile.

- The incantation requires a certain level of the players. Players can be in different teams.

- The max level is 8.

## Time unit

- The time unit is the time it takes for a player to do an action. The time unit is set by the server.

## Look around (vision)

- The look around is done by calling the `Look` command.

- The player can only see so far. It depends on his level.

- With each elevation, the vision increases by one unit in front, and one on each side of the new
line.

The formatting looks like : 
```
look
[player, object-on-tile1, ..., object-on-tileP,...]
```

## Broadcast (sound)

- Sound is a wave that spreads out linearly (at least on Trantor) by broadcasting.

- All the players can hear the broadcasts without knowing who is playing them.

- They can only perceive the direction the sound is coming from and its subsequent message.

- The direction is relative to the direction the player is facing.

## Winning conditions

- The game ends when a team has 6 players at level 8.