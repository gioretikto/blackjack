#include <gtk/gtk.h>
#include <stdio.h>

#define ACE 0
#define CARDS 13
#define SUITS 4
#define MAX_CARDS 10

struct table {

	char card_path[MAX_CARDS][10];	
	
    int points[MAX_CARDS];  		/* Points for each hand */
    
    int total;						/* total points */
        
    int hand;						/* number of card_path dealt */
    
    int aces;						/* N° of aces: These variable are used to attribute values 1/11 to Aces*/
    
    _Bool check_stand;
    
    GtkWidget *canvas, *hbox_chips;
    
    struct table *next;
    
    cairo_surface_t *card[MAX_CARDS];
};

struct {
  cairo_surface_t *image_back;
  _Bool status, end;
  int x[MAX_CARDS];
  int credit;
  int bet;
} glob;

GtkWidget *label_msg;
GtkWidget *label_credit;
GtkWidget *label_bet;
GtkWidget *button_start;
GtkWidget *button_play_again;

void button_hit_clicked(GtkWidget *widget, struct table *game);
void button_stand_clicked(GtkWidget *widget, struct table *game);
void init_game(GtkWidget *widget, struct table *player);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, struct table *player);
static void do_drawing(cairo_t *cr, struct table *player);
void draw_cards(struct table *game);
void assign_points(struct table *player);
static void activate_about();
static void destroy (GtkWidget *window, gpointer data);
void buttonAdd (GtkButton *button, gpointer data);
void updateLabel(GtkWidget *label_credit, int *num);
void updatelabel_msg(gchar *display);
void reset (GtkButton *button, gpointer data);
void findWinner (struct table *player);
static void new_game (GtkWidget *window, struct table *player);