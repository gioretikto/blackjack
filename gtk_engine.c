#include "black.h"

void init_game(GtkWidget *widget, struct table *player) {

	int i;
	gtk_widget_hide(widget);
	gtk_widget_show(player->hbox);
	gtk_widget_hide(player->hbox_chips);
	gtk_widget_hide(player->button_play_again);
	gtk_label_set_text (GTK_LABEL(player->label_msg), "");
	player->status = 1;
	player->end = 0;
	
	player->total =	player->aces = player->hand = player->check_stand = 0;
	player->next->total = player->next->aces = player->next->hand = 0;
	
	draw_cards(player);
	draw_cards(player->next);
	
	for (i = 0; i < MAX_CARDS; i++) {
		player->card[i] = NULL;
		player->next->card[i] = NULL;
	}
	
	for (i = 0; i < 2; i++) {		/* Initialize first hand */
		player->card[i] = cairo_image_surface_create_from_png(player->card_path[i]);
		player->next->card[i] = cairo_image_surface_create_from_png(player->next->card_path[i]);
		assign_points(player);
		assign_points(player->next);
		player->hand++;
		player->next->hand++;
	}
	
	player->hand = player->next->hand = 1;

	findWinner(player);
}
 
void button_hit_clicked(GtkWidget *widget, struct table *player)
{
	cairo_surface_t *img;
	player->next->hand++;
	assign_points(player->next);
	
	gtk_widget_queue_draw (player->canvas);
    
	if (player->total < 17) {
		player->hand++;
		assign_points(player);
		img = player->card[player->hand] = cairo_image_surface_create_from_png(player->card_path[player->hand]);
		
		if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS) {
    		fprintf(stderr, "Could not load imgage for dealer %s", player->card_path[player->hand]);
    	}
	}
	
    img = player->next->card[player->next->hand] = cairo_image_surface_create_from_png(player->next->card_path[player->next->hand]);
    
    if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS) {
    	fprintf(stderr, "Could not load imgage for player %s, status is: %d", player->next->card_path[player->next->hand],cairo_surface_status(img) );
    }
    
	findWinner(player);
}

void button_stand_clicked(GtkWidget *widget, struct table *player)
{
	cairo_surface_t *img;
	gtk_widget_queue_draw (player->canvas);
    
	if (player->total < 17) {
		player->hand++;
		assign_points(player);
		img = player->card[player->hand] = cairo_image_surface_create_from_png(player->card_path[player->hand]);
		
		if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS)
    		fprintf(stderr, "Could not load imgage for dealer %s", player->next->card_path[player->hand]);
	}
	
	else
		player->check_stand = 1;
	
	findWinner(player);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, struct table *player)
{
  if (player->status != 0 || player->end == 1)
  	do_drawing(cr, player);

  return FALSE;
}

void do_drawing(cairo_t *cr, struct table *player)
{
   int i;
  
	for (i = 0; i <= player->hand; i++) {
  
	  	if (i == 0 && player->end == 0)
		  	cairo_set_source_surface(cr, player->image_back, 10, 10);
		else
	    	cairo_set_source_surface(cr, player->card[i], player->x[i], 10);
		    
	    cairo_paint(cr);
	}
  
	for (i = 0; i <= player->next->hand; i++) {
		cairo_set_source_surface(cr, player->next->card[i], player->x[i], 320);
  		cairo_paint(cr);
	}
}

void activate_about() {

	const gchar *authors[] = {"simplicius", NULL};

	gtk_show_about_dialog (NULL,
                       "program-name", "BlackJack",
                       "version", "0.0.1",
    				   "license-type", GTK_LICENSE_GPL_3_0,
    				   "website", "https://github.com/gioretikto/blackjack",
					   "authors", authors,
    				   "logo-icon-name", "start-here",
    				   "comments", "reach me on #cansi Freenode IRC",
                       "title", ("BlackJack"),
                       NULL);
}

/* Stop the GTK+ main loop function when the window is destroyed. */
void destroy (GtkWidget *window, gpointer data)
{
	gtk_main_quit ();
}

void new_game (GtkWidget *window, struct table *player)
{
	gtk_label_set_text (GTK_LABEL(player->label_msg), "Please Bet ");
	gtk_label_set_text (GTK_LABEL(glob.label_bet), "0");
	gtk_widget_hide(player->hbox);
	gtk_widget_show(player->hbox_chips);
}

void buttonAdd (GtkButton *button, gpointer data)
{
	gtk_widget_show(glob.button_start);
	if (glob.bet + GPOINTER_TO_INT(data) <= glob.credit) {
	    glob.bet += GPOINTER_TO_INT(data);
    	updatelabel_bet();
    }
}

void updatelabel_bet()
{
	gchar *display;
    display = g_strdup_printf(" %d$ ", glob.bet);			/* convert num to str */
    gtk_label_set_text (GTK_LABEL(glob.label_bet), display);		/* set label to "display */
    g_free(display);                              			/* free display */    
}

void updatelabel_credit()
{
	gchar *display;
    display = g_strdup_printf(" Credit %d$",  glob.credit);		/* convert num to str */
    gtk_label_set_text (GTK_LABEL(glob.label_credit), display);		/* set label to "display */
    g_free(display);                              				/* free display */    
}

void updatelabel_msg(gchar *display, struct table *player)
{
	gtk_label_set_text (GTK_LABEL(player->label_msg), display);
}

void reset (GtkButton *button, gpointer data)
{
    glob.bet = 0;
    updatelabel_bet();
    gtk_widget_hide(glob.button_start);
}