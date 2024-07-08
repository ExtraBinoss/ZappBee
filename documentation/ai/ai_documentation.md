# AI Documentation

## Networking

The AI connect to the server with socket. We have a connection class that allow us to:
- Connect to the server.
- Disconnect from the server.
- Send data to the server.
- Use select to know if there's something to read from the server.
- Wait for a response after a command has been sent, filtering messages and handling death.

## AI Commands

Our AI have all the asked commands implemented in an Action class:
- `Left` - Turn the player left
- `Right` - Turn the player right
- `Forward` - Move the player forward
- `Take [object]` - Take an object from the tile
- `Set [object]` - Set an object on the tile
- `Inventory` - Get the player inventory
- `Look` - Look around the player
- `Connect_nbr` - Connect to a team
- `Incantation` - Start an incantation
- `Broadcast` - Send a message to all players
- `Fork` - Fork a new player
- `Eject` - Eject a player from the tile
Each of these commands send their name to the server, use the connection class to wait for a response and catch messages,
then process, if needed, the data, and return it along with messages.
Logs are writen in the process to keep track of what's happening.

## AI Logic

Our AI is actually divided in two kind of AI, a Queen one, and a Subject one.
The Queen is the IA that we first connect, then we have nothing to do, cause the Queen is gonna connect, herself, the Subjects.
At first, all AI have the same comportment, finding food and ressources to elevate to level 2,
once level 2, the Subjects only look for more food, while the Queen look for all the ressources needed to go from level 2, all the way to level 8.
When the Queen meet her food and ressource requirements, she broadcast the team name until 6 players are on her tile, which should be her and her Subjects.
When the Subjects catch the Queen messages, if they meet the food and level requirements, they go in the direction of the Queen.
When everyone's reunited, she start incantations to go straight to level 8 and win.
