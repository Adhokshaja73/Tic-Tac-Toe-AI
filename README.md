A simple tic-tac-toe AI that can play againsta a player. 


Computer is playing as X and player will be playing as O. 

To play, compile and run the C program.
Use numpad keys to make your move.
The board is a 3x3 grid that can be mapped to keys 1-9 in the NUMPAD.

When any number is pressed, O will be written in the position of the number in the board if it is free.



Working:
    First two plays by the computer are made random. When it's turn of the computer for the third time, 
It generates the State Space tree by only considering the future states where O (player) is not winning. 
And consider the next move only where O is not winning. 

Future Improvements:
   1) Currently it randomly choses the next move out of available options (where O is not winning). 
Sometimes due to randomness, the tree does not get generated if first random moves allow the player to win in all the possible future cases.
So the computer loses in some particular cases.
   2) The randomness in chosing the next move sometimes leads to the computer ignoring the best move possible and randomly chosing a move that leads to a tie. 
This can be fixed by implementing any of search algorithms like Alpha-Beta Pruning. 
