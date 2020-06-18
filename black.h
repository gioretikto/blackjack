#include <gtk/gtk.h>

#define CARDS 52

struct player_data {

	unsigned int card_value;  	
	unsigned int total;			/* total points */
	unsigned int hand;			/* card box index */
  	unsigned int aces; 			/* number of aces */

};

struct black {

	GtkWidget *hbox_dealer, *hbox_player, *hbox_buttons, *hbox_chips, *hbox_endGame, *label_msg,
			  *label_credit, *label_bet, *label_endGame, *button_start, *button_hit,
			  *button_stand, *button_playAgain;
	
	GtkWidget *cards_dealer[7];
	GtkWidget *cards_player[7];
	
	int credit;
	int bet;
	
	unsigned int cards_dealt;
	
	const char *covered_card;
	
	struct player_data dealer;
	struct player_data player;
	
	_Bool check_stand;

};

struct card {

   	const char *file;
   	unsigned int value;   	
   	
};

void create_window(void);
void destroy (GtkWidget *window G_GNUC_UNUSED, gpointer data G_GNUC_UNUSED);
void activate_about(void);
void buttonAdd (GObject *button, struct black *table);
void updatelabel_bet(struct black *table);
void updatelabel_credit(struct black *table);
void reset (GObject *button, struct black *table);
void init_game(GtkWidget *button G_GNUC_UNUSED, struct black *table);
void shuffle (struct card *xdeck);
void swap (struct card *a, struct card *b);
void assignPoints(struct player_data *player);
void button_hit_clicked(GtkWidget *widget G_GNUC_UNUSED, struct black *table);
void button_stand_clicked(GtkWidget *widget G_GNUC_UNUSED, struct black *table);
void findWinner (struct black *table);
void endHand(gchar *display, struct black *table);
void new_game (GtkWidget *window G_GNUC_UNUSED, struct black *table);
void updateLabelCredit(struct black *table);
gboolean dealer_reply (struct black *table);
