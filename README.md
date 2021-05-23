# Number-Hunt

1. Goal: 
    The goal of the project is to develop a game where the first player thinks of a
    secret number in range and also the second player thinks of a secret number in
    range .Both the players attempts to hunt the number of the other player. After each
    guess, the message is displayed on the terminal of both the players either “Higher”,
    “Lower” or “Correct!” depending on whether the secret number is higher, lower or
    equal to the guessed number . Fixed number of trials will be given to each player and
    after the completion of trials “you lost” message will be displayed.
    If one of the players wins then automatically the other player’s terminal will show the
    message “you lost” and will exit the game. Also, if one player leaves the game then
    the other player’s terminal will show the message “other player left you won” and will
    exit the game.

2. Requirements:
  a. Both the players are on the same network.
  b. Both the players share the folder where all files are present.
  c. The files should have read and write access.
  
3. Assumptions:
  a. The number to be hunted is always greater than 0.
  b. There is a static number of trials, randomly 10 is chosen to be that
  static number.
  c. Game will always be initiated by player1.
  d. Game will not be started until both the players have entered their
  number to hunt.
  e. Only integers are entered by the players.
