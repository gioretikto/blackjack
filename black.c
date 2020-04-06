#include "black.h"

#define ACE 0
#define CARDS 13
#define SUITS 4

enum outcomes {NO_WINNER, PLAYER_WINS, BLACKJACK, DEALER_WINS, TIE};

void draw_cards(struct table *player) {

    int card_pick, suit_pick;
    int i = 0;
      
    int drawn_card[SUITS][CARDS] = {0};
    
    while (i < MAX_CARDS) { 					/* draw dealer's card_path */
    
    	suit_pick = rand() % SUITS;
    	card_pick = rand() % CARDS;
    	
    	if (drawn_card[suit_pick][card_pick] == 0) {
    		
    		sprintf(player->card_path[i], "c/%d%d.png", suit_pick, card_pick);
    		
	    	drawn_card[suit_pick][card_pick] = 1;
			
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

void assign_points(struct table *player) {

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

void findWinner (struct table *player) {

	int winner;

	if (player->check_stand == 1) {
	
		if (player->total == player->next->total)		/* Tie */
			winner = TIE;
	
		else if (player->next->total <= 21) {
		
			if (player->next->total > player->total)  	/* Player wins */
				winner = PLAYER_WINS;
			else
				winner = DEALER_WINS;
		}
			
		else   											/* Dealer wins  player->total > 21 */
			winner = DEALER_WINS;
	}
	
	else {
	
		if ( (player->next->total == 21) && (player->total == 21) )		/* A tie */
			winner = TIE;
	
		else if (player->next->total > 21) 		/* If the player exceeds a sum of 21 "busts", loses, even if the dealer also exceeds 21 */
			winner = DEALER_WINS;

		else if (player->next->total == 21) {
			if (player->next->hand == 2)		/* Player wins with Blackjack */
				winner = BLACKJACK;
			else
				winner = PLAYER_WINS;
		}
					
		else if (player->total == 21)			/* Dealer wins */
			winner = DEALER_WINS;
			
		else if (player->total > 21)
				winner = PLAYER_WINS;
			
		else
			winner = NO_WINNER;					/* no winner found */
	}
	
	if (winner != NO_WINNER) {
	
		player->status = 0;
		player->end = 1;
		gtk_widget_show (player->button_play_again);
		
		if (winner == BLACKJACK) {
			glob.credit += (glob.bet * 3)/2;
			updatelabel_msg("Congratulation you win: ", player);
		}
		
		else if (winner == PLAYER_WINS) {
			updatelabel_msg("Congratulation you win: ", player);
			glob.credit += glob.bet;
		}
					
		else if (winner == DEALER_WINS) {
			updatelabel_msg("Dealer wins ", player);
			glob.credit -= glob.bet;
		}
					
		else
			updatelabel_msg("No one wins", player);
		
		if (glob.credit <= 0) {
			updatelabel_msg("Dealer wins. Sorry you bankrupted", player);			
			glob.credit = 50;
		}
		
		glob.bet = 0;
		updatelabel_credit();
	}
}