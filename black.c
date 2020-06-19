#include "black.h"

enum outcomes {NO_WINNER, PLY_WINS, BLACKJACK, CPU_WINS, TIE};

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
	
		if (table->player[CPU].total == table->player[PLY].total)			/* Tie */
			winner = TIE;
	
		else if (table->player[CPU].total <= 21) {
		
			if (table->player[PLY].total > table->player[CPU].total)  	/* Player wins */
				winner = PLY_WINS;
			else
				winner = CPU_WINS;
		}
			
		else   													/* Dealer wins  player->total > 21 */
			winner = CPU_WINS;
	}
	
	else {
	
		if ( (table->player[PLY].total == 21) && (table->player[CPU].total == 21) )		/* A tie */
			winner = TIE;
	
		else if (table->player[PLY].total > 21) 		/* If the player exceeds a sum of 21 "busts", loses, even if the dealer also exceeds 21 */
			winner = CPU_WINS;

		else if (table->player[PLY].total == 21)
				winner = PLY_WINS;
					
		else if (table->player[CPU].total == 21)		/* Dealer wins */
			winner = CPU_WINS;
			
		else if (table->player[CPU].total > 21)
				winner = PLY_WINS;
			
		else
			winner = NO_WINNER;					/* no winner found */
	}
	
	if (winner != NO_WINNER) {

		if (winner == BLACKJACK) {
			table->credit += (table->bet * 3)/2;
			endHand("Congratulation you win: ", table);			
		}
		
		else if (winner == PLY_WINS) {
			table->credit += table->bet;
			endHand("Congratulation you win: ", table);
		}
					
		else if (winner == CPU_WINS) {
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
