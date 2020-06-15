#include "black.h"
#include <stdlib.h>

enum outcomes {NO_WINNER, PLAYER_WINS, BLACKJACK, DEALER_WINS, TIE};

void draw_cards(int *card_dealt, struct game *player) {

    int card_pick, suit_pick;
    int i = 0;
      
    while (i < MAX_CARDS) { 					/* draw dealer's card_path */
    
    	suit_pick = rand() % SUITS;
    	card_pick = rand() % CARDS;
    	
    	if (card_dealt[suit_pick * CARDS + card_pick] == 0) {
    		
    		sprintf(player->card_path[i], "c/%d%d.png", suit_pick, card_pick);
    		
	    	card_dealt[suit_pick * CARDS + card_pick] = 1;
			
			if (card_pick == ACE)
				player->points[i] = 11;
			
			else if (card_pick >= 9)
				player->points[i] = 10;
					
			else
				 player->points[i] = card_pick + 1;
				 
			i++;
		}
	}
}

void assign_points(struct game *player) {

		if (player->points[player->hand] == 11)
			player->aces++;
			
		if ( (player->aces > 0) && ( (player->total + player->points[player->hand]) > 21) ) {
			player->total += player->points[player->hand];
			
			player->total = player->total - 10;
			player->aces--;
		}
		
		else
			player->total += player->points[player->hand];			
}

void findWinner (struct black *table) {

	int winner;

	if (table->check_stand == 1) {
	
		if (table->dealer->total == table->player->total)		/* Tie */
			winner = TIE;
	
		else if (table->dealer->total <= 21) {
		
			if (table->player->total > table->dealer->total)  	/* Player wins */
				winner = PLAYER_WINS;
			else
				winner = DEALER_WINS;
		}
			
		else   											/* Dealer wins  player->total > 21 */
			winner = DEALER_WINS;
	}
	
	else {
	
		if ( (table->player->total == 21) && (table->dealer->total == 21) )		/* A tie */
			winner = TIE;
	
		else if (table->player->total > 21) 		/* If the player exceeds a sum of 21 "busts", loses, even if the dealer also exceeds 21 */
			winner = DEALER_WINS;

		else if (table->player->total == 21)
				winner = PLAYER_WINS;
					
		else if (table->dealer->total == 21)			/* Dealer wins */
			winner = DEALER_WINS;
			
		else if (table->dealer->total > 21)
				winner = PLAYER_WINS;
			
		else
			winner = NO_WINNER;					/* no winner found */
	}
	
	if (winner != NO_WINNER) {
	
		table->status = 0;
		table->end = 1;
		gtk_widget_show (table->button_play_again);
		
		if (winner == BLACKJACK) {
			table->credit += (table->bet * 3)/2;
			endHand("Congratulation you win: ", table);
		}
		
		else if (winner == PLAYER_WINS) {
			endHand("Congratulation you win: ", table);
			table->credit += table->bet;
		}
					
		else if (winner == DEALER_WINS) {
			endHand("Dealer wins ", table);
			table->credit -= table->bet;
		}
					
		else
			endHand("No one wins", table);
		
		if (table->credit <= 0) {
			endHand("Dealer wins. Sorry you bankrupted", table);
			table->credit = 50;
		}
		
		table->bet = 0;
		updatelabel_credit(table);
	}
}
