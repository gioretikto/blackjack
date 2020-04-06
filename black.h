#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_CARDS 10

struct table {

	char card_path[MAX_CARDS][10];	
	
    int points[MAX_CARDS];  		/* Points for each hand */
    
    int total;						/* total points */
        
    int hand;						/* number of card_path dealt */
    
    int aces;						/* N° of aces: These variable are used to attribute values 1/11 to Aces*/
    
    _Bool check_stand, status, end;    
    
    GtkWidget *canvas, *hbox_chips, *hbox, *label_msg,  *button_play_again;
    
    cairo_surface_t *card[MAX_CARDS];
    
  	cairo_surface_t *image_back;
  	
	int x[MAX_CARDS];
	
    struct table *next;
};

struct {
	int bet;
	int credit;
	GtkWidget *label_credit;
	GtkWidget *label_bet;
	GtkWidget *button_start;
} glob;

void button_hit_clicked(GtkWidget *widget, struct table *game);
void button_stand_clicked(GtkWidget *widget, struct table *game);
void init_game(GtkWidget *widget, struct table *player);
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, struct table *player);
void do_drawing(cairo_t *cr, struct table *player);
void draw_cards(struct table *game);
void assign_points(struct table *player);
void activate_about();
void destroy (GtkWidget *window, gpointer data);
void buttonAdd (GtkButton *button, gpointer data);
void updatelabel_bet();
void updatelabel_credit();
void updatelabel_msg(gchar *display, struct table *player);
void reset (GtkButton *button, gpointer data);
void findWinner (struct table *player);
void new_game (GtkWidget *window, struct table *player);