# Snakes_and_Laders
Snakes and Ladders game for "Game of Blocks"

Let me start off by saying I made this in a day so it does not have the best features but it works!
I have made two classes board and game. I have inherited board into game and used its members in the game.

Under board you can make your personalized snakes and ladder board by adding/deleting snakes/ladders but if you just wish to play the game then there is a pre-set board available. I have stored snakes and ladders as pairs of numbers, and have also stored the size of the board. The first element of the pair is where a snake ends or where a ladder starts and the second element is where a snake starts or where a ladder ends.

The class game should technically have a 'has-a-relation' with board and that was my original plan but then for that i'll have to define accessory functions for board which I dint do while writing the code. Given more time I would have incorporated it that way, but for now consider this code where I have used 'is-a-relation'.
The class game is as you would expect the game itself, has functions for doing a round of the game and that is called from a function match.

I have also used constructors to do some of the pre-game setup work. I have used it for both classes.
All my member variables are either private or protected and only some member functions are public (as far as I remember, its 3 in the morning and im too tired to cross check)

I have also not formatted the output properly because it was mentioned that its not really necessary.

Hope you like my code :)



P.s. I know that my repo name has 'lader' in it instead of 'ladder' :')
