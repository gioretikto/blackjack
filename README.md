# Blackjack v.1.1

A Blackjack written in C and Gtk+3. This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

The game is played with one deck of 52 cards. The rules are simple: The goal of the game is to beat the Dealer's hand. The better hand is the hand where the sum of the card values is closer to 21 without exceeding 21. The detailed outcome of the hand follows:  

    - If the dealer exceeds 21 ("busts") and the player does not; the player wins.
    
    - If the player attains a final sum higher than the dealer and does not bust; the player wins.
    
    - If both dealer and player receive a blackjack or any other hands with the same sum, called a "push", no one wins.
    
    - If the player exceeds a sum of 21 "busts": the player loses, even if the dealer also exceeds 21.
    
    - If the player is dealt an Ace and a ten-value card, called a "blackjack" or "natural", and the dealer does not, the player wins and usually receives a bonus: 2/3 of the bet equal to 150%.
    
![Screenshot](https://github.com/gioretikto/blackjack/blob/master/blackjack.png)

# Required packages

	- Gtk+ 3: sudo apt-get install libgtk-3-dev
	- gcc
	- make

# Installation

	- make blackjack
	- sudo make install

# How to report bugs?

This game was brought to you by Giovanni Resta giovannirestadev@gmail.com
You can reach me also in Freenode IRC channel #cansi
