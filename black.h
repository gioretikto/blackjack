#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_CARDS 10
#define ACE 0
#define CARDS 13
#define SUITS 4

struct game {

	char card_path[MAX_CARDS][10];
	
	int points[MAX_CARDS];  		/* Points for each hand */
    
    int total;						/* total points */
        
    int hand;						/* number of card_path dealt */
    
    int aces;
    
    cairo_surface_t *card[MAX_CARDS];
    
};

struct black {

	int card_dealt[CARDS*SUITS];
    
    _Bool check_stand, status, end;    
    
    GtkWidget *canvas, *hbox_chips, *hbox, *label_msg,  *button_play_again;
    
  	cairo_surface_t *image_back;
  	
	int x[MAX_CARDS];
	
	struct game *dealer;
	
	struct game *player;
	
};

struct {
	int bet;
	int credit;
	GtkWidget *label_credit;
	GtkWidget *label_bet;
	GtkWidget *button_start;
} glob;

void create_window();
void button_hit_clicked(GtkWidget *widget, struct black *table);
void button_stand_clicked(GtkWidget *widget, struct black *table);
void init_game(GtkWidget *widget, struct black *table);
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, struct black *table);
void do_drawing(cairo_t *cr, struct black *table);
void draw_cards(int *card_dealt, struct game *player);
void assign_points(struct game *player);
void activate_about();
void destroy (GtkWidget *window, gpointer data);
void buttonAdd (GtkButton *button, gpointer data);
void updatelabel_bet();
void updatelabel_credit();
void updatelabel_msg(gchar *display, struct black *table);
void reset (GtkButton *button, gpointer data);
void findWinner (struct black *table);
void new_game (GtkWidget *window, struct black *table);