# Server features

## Commands supported for AI(s)

- [X] `Forward` - Move the player forward
- [X] `Right` - Turn the player right
- [X] `Left` - Turn the player left
- [X] `Look` - Look around the player
- [X] `Inventory` - Get the player inventory
- [X] `Broadcast` - Send a message to all players
- [X] `Connect_nbr` - Connect to a team
- [X] `Fork` - Fork a new player
- [X] `Eject` - Eject a player from the tile
- [X] `Take [object]` - Take an object from the tile
- [X] `Set [object]` - Set an object on the tile
- [X] `Incantation` - Start an incantation

## Command supported for GUI

- [X] `msz` - Get the map size
- [X] `bct` - Get the content of a tile
- [X] `mct` - Get the content of all tiles
- [X] `tna` - Get the name of all teams
- [X] `pnw` - Get the new player
- [X] `ppo` - Get the player position
- [X] `plv` - Get the player level
- [X] `pin` - Get the player inventory
- [X] `pex` - Player expulsion
- [X] `pbc` - Player broadcast
- [X] `pic` - Start an incantation
- [X] `pie` - End an incantation
- [X] `pfk` - Start an egg laying
- [X] `pdr` - Drop an object
- [X] `pgt` - Take an object
- [X] `pdi` - Player death
- [X] `enw` - Egg laying
- [X] `eht` - Egg hatching
- [X] `ebo` - Egg broken
- [X] `edi` - End of the game
- [X] `sgt` - Get the time unit
- [X] `sst` - Set the time unit
- [X] `seg` - End of the game
- [X] `smg` - Send a message to all players
- [X] `suc` - Unknown command
- [X] `sbp` - Server bad parameter

## Bonus

 - Garbage collector - At the end of the program (Signals, or winning team), the server will free all the memory allocated.
 - Logs - The server will log all the actions done by the players.