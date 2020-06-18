#include "black.h"

enum outcomes {NO_WINNER, PLAYER_WINS, BLACKJACK, DEALER_WINS, TIE};

void assignPoints(struct player_data *player) {

		if (player->card_value == 11)
			player->aces++;
			
		if ( (player->aces > 0) && ( (player->total + player->card_value) > 21) ) {
		
			player->total += player->card_value;
			
			player->total = player->total - 10;		/* Ace now counts as 1 */
			
			player->aces--;
		}
		
		else
			player->total += player->card_value;		
}

void findWinner (struct black *table) {

	enum outcomes winner;

	if (table->check_stand == 1) {
	
		if (table->dealer.total == table->player.total)			/* Tie */
			winner = TIE;
	
		else if (table->dealer.total <= 21) {
		
			if (table->player.total > table->dealer.total)  	/* Player wins */
				winner = PLAYER_WINS;
			else
				winner = DEALER_WINS;
		}
			
		else   													/* Dealer wins  player->total > 21 */
			winner = DEALER_WINS;
	}
	
	else {
	
		if ( (table->player.total == 21) && (table->dealer.total == 21) )		/* A tie */
			winner = TIE;
	
		else if (table->player.total > 21) 		/* If the player exceeds a sum of 21 "busts", loses, even if the dealer also exceeds 21 */
			winner = DEALER_WINS;

		else if (table->player.total == 21)
				winner = PLAYER_WINS;
					
		else if (table->dealer.total == 21)		/* Dealer wins */
			winner = DEALER_WINS;
			
		else if (table->dealer.total > 21)
				winner = PLAYER_WINS;
			
		else
			winner = NO_WINNER;					/* no winner found */
	}
	
	if (winner != NO_WINNER) {

		if (winner == BLACKJACK) {
			table->credit += (table->bet * 3)/2;
			endHand("Congratulation you win: ", table);			
		}
		
		else if (winner == PLAYER_WINS) {
			table->credit += table->bet;
			endHand("Congratulation you win: ", table);
		}
					
		else if (winner == DEALER_WINS) {
			table->credit -= table->bet;
			endHand("Dealer wins ", table);
		}
					
		else
			endHand("No one wins", table);
		
		if (table->credit <= 0) {
			table->credit = 50;
			endHand("Dealer wins. Sorry you bankrupted", table);				
		}
	}
}
