#include <gtk/gtk.h>

#define ACE 0
#define CARDS 13
#define SUITS 4
#define MAX_CARDS 10
#define SCREENLINECOUNT 17

struct table {

	int cards_dealer[MAX_CARDS];
	
	int cards_player[MAX_CARDS];
    
    int points[MAX_CARDS];  					/* Points for each hand */
   
    int total_player, total_dealer;				/* total points */
        
    int hand_player, hand_dealer;				/* number of cards dealt */
    
    int aces_player, aces_dealer;				/* N° of aces: These variable are used to attribute values 1/11 to Aces*/
    
    int credit;
    
    int bet;
    
    GtkWidget *vbox, *canvas;
    
};

struct {
  cairo_surface_t *image[MAX_CARDS];
  int x[MAX_CARDS];
} glob;

static void destroy (GtkWidget *window, gpointer data);
void button_clicked(GtkWidget *widget, struct table *game);
void init_game(struct table *game);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
static void do_drawing(cairo_t *cr);

int main (int argc, char *argv[])
{
        GtkWidget *window, *button_hit, *button_stand, *hbox;
        
		struct table game;
		
		int i;
		
		init_game(&game);
        
        gtk_init (&argc, &argv);        
        
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);				/* create window */
        gtk_window_set_title (GTK_WINDOW (window), "Show Images");
		gtk_window_maximize (GTK_WINDOW (window));
		
		GtkCssProvider *css_provider = gtk_css_provider_new();		/* Apply style */
  		gtk_css_provider_load_from_path (css_provider, "style.css", NULL);
  		
  		GdkScreen *myScreen= gdk_screen_get_default();
		gtk_style_context_add_provider_for_screen
                               (myScreen,
                                GTK_STYLE_PROVIDER (css_provider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
			
		game.vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
		gtk_container_add(GTK_CONTAINER (window), game.vbox);
			
 		game.canvas = gtk_drawing_area_new();  		
  		gtk_container_add (GTK_CONTAINER (game.vbox), game.canvas);
  		g_object_set (game.canvas, "expand", TRUE, NULL);			/* expand the canvas */
				    
	    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 30);		/* hbox for buttons */
		gtk_container_add (GTK_CONTAINER (game.vbox), hbox);
        button_hit = gtk_button_new_with_mnemonic ("Hit");
   		gtk_container_add (GTK_CONTAINER (hbox), button_hit);
   		
   		g_signal_connect(G_OBJECT(button_hit), "clicked", G_CALLBACK(button_clicked), &game);
   		g_signal_connect (G_OBJECT (window), "destroy",
			G_CALLBACK (destroy), NULL);
		g_signal_connect(G_OBJECT(game.canvas), "draw", 
      	G_CALLBACK(on_draw_event), NULL); 
			
   		button_stand = gtk_button_new_with_mnemonic ("Stand");
   		gtk_container_add (GTK_CONTAINER (hbox), button_stand);
   		
		gtk_widget_show_all (window);
   		               
   		gtk_main();
   		
   		for (i = 0; i < MAX_CARDS; i++)
			cairo_surface_destroy(glob.image[i]);
			
        return 0;
} 
 
void button_clicked(GtkWidget *widget, struct table *game)
{   		
	const gchar *cards_dealer[] = {"resized_cards/back.png" ,"resized_cards/010.png", "resized_cards/011.png", "resized_cards/312.png", "resized_cards/01.png"};
	/*const gchar *cards_player[] = {"resized_cards/00.png", "resized_cards/01.png", "resized_cards/03.png", "resized_cards/312.png"};*/

	int current_hand = game->hand_dealer;
	
    glob.image[current_hand] = cairo_image_surface_create_from_png(cards_dealer[current_hand]);

    game->hand_dealer++;

}

static void destroy (GtkWidget *window, gpointer data)
{
	gtk_main_quit ();
}

void init_game(struct table *game) {

	game->total_player = game->total_dealer = 0;

	game->aces_player = game->aces_dealer = 0;
	
	game->hand_dealer = game->hand_player = 0;
	
	/*draw_cards(player);*/
	
	/*assign_points(player); */
			
	/*assign_points(player); */
	
	game->credit = 50;
	
	int i;
	
	for (i = 0; i < MAX_CARDS; i++)
		glob.image[MAX_CARDS] = NULL;
	
	glob.x[0] = 10;
	
	for (i = 1; i < MAX_CARDS; i++)
		glob.x[i] += 220;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{   
 
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{  
  int i;
  
  for (i = 0; i < MAX_CARDS; i++) {
	  if (glob.image[i] != NULL) {
		  cairo_set_source_surface(cr, glob.image[i], glob.x[i], 10);
		  cairo_paint(cr);
	  }
  }
  
}
