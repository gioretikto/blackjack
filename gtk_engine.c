#include "black.h"

#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_CARDS 10
#define ACE 0
#define CARDS 13
#define SUITS 4

void create_window() {

		int i;
		       	
       	struct black table;
        
   		table.dealer = malloc(sizeof(struct game));
        table.player = malloc(sizeof(struct game));        

		table.status = table.end = 0;
		
		table.credit = 50;
		
		table.image_back = cairo_image_surface_create_from_png("c/back.png");
		
		GtkWidget *window;
        GtkWidget *headbar;
        GtkWidget *vbox;
        GtkWidget *about_button;
        GtkWidget *button_hit;
        GtkWidget *button_stand;
       	GtkWidget *button_chip1, *button_chip5, *button_chip25, *button_chip100, *button_chip0;
       	GtkWidget *hbox_msg;
       	
		table.x[0] = 10;
	
		for (i = 1; i < MAX_CARDS; i++)
			table.x[i] = table.x[i-1] + 110;        
        
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);				/* create window */
        headbar = gtk_header_bar_new();
        about_button = gtk_button_new_with_mnemonic("_About");
        vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 30);
		table.hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 50);
		table.hbox_chips = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		hbox_msg = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		button_hit = gtk_button_new_with_mnemonic ("Hit");
		button_stand = gtk_button_new_with_mnemonic ("Stand");
		table.button_start = gtk_button_new_with_mnemonic ("Start");
		table.button_play_again = gtk_button_new_with_mnemonic ("Play Again");
		
		button_chip1 = gtk_button_new();
		button_chip5 = gtk_button_new();
		button_chip25 = gtk_button_new();
		button_chip100 = gtk_button_new();
		button_chip0 = gtk_button_new();
		
		g_object_set_data(G_OBJECT(button_chip1), "id", GINT_TO_POINTER(1));
		g_object_set_data(G_OBJECT(button_chip5), "id", GINT_TO_POINTER(5));
		g_object_set_data(G_OBJECT(button_chip25), "id", GINT_TO_POINTER(25));
		g_object_set_data(G_OBJECT(button_chip100), "id", GINT_TO_POINTER(100));
		g_object_set_data(G_OBJECT(button_chip0), "id", GINT_TO_POINTER(0));
		
		table.label_msg = gtk_label_new ("Please Bet  ");
		table.label_credit = gtk_label_new ("Credit");
		table.label_bet = gtk_label_new ("0");
       	table.canvas = gtk_drawing_area_new();
       	
       	/* Set Properties */
        
		gtk_header_bar_set_title (GTK_HEADER_BAR (headbar), "Ventuno");
		gtk_window_set_titlebar (GTK_WINDOW (window), headbar);
	    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (headbar), TRUE);
        gtk_window_set_title (GTK_WINDOW (window), "BlackJack");
		gtk_window_maximize (GTK_WINDOW (window));
		g_object_set (table.canvas, "expand", TRUE, NULL);			/* expand the canvas */
		GtkCssProvider *css_provider = gtk_css_provider_new();		/* Apply style */
  		gtk_css_provider_load_from_path (css_provider, "style.css", NULL);
  		
  		GdkScreen *myScreen = gdk_screen_get_default();
		gtk_style_context_add_provider_for_screen
                               (myScreen,
                                GTK_STYLE_PROVIDER (css_provider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
                                
        /* Fill the vertical box container */
        
		gtk_container_add(GTK_CONTAINER(headbar), about_button);
		gtk_container_add(GTK_CONTAINER (window), vbox);
		gtk_container_add (GTK_CONTAINER (vbox), table.canvas);
		gtk_container_add(GTK_CONTAINER (vbox), table.hbox);
		gtk_container_add(GTK_CONTAINER (vbox), hbox_msg);
   		gtk_container_add (GTK_CONTAINER (table.hbox), button_hit);
   		gtk_container_add (GTK_CONTAINER (table.hbox), button_stand);
		gtk_container_add(GTK_CONTAINER (hbox_msg), table.label_msg);
		gtk_container_add(GTK_CONTAINER (hbox_msg), table.label_bet);
		gtk_container_add(GTK_CONTAINER (hbox_msg), table.label_credit);
		gtk_container_add (GTK_CONTAINER (table.hbox_chips), table.button_start);
		gtk_container_add (GTK_CONTAINER (table.hbox), table.button_play_again);
		gtk_container_add(GTK_CONTAINER (vbox), table.hbox_chips);
		gtk_container_add (GTK_CONTAINER (table.hbox_chips), button_chip1);
		gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip5);
		gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip25);
		gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip100);
		gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip0);
		
		updatelabel_credit(&table);

		/* Update img to buttons */
		GtkWidget *image = gtk_image_new_from_file ("c/chip1.svg");
		gtk_button_set_image (GTK_BUTTON (button_chip1), image);

		image = gtk_image_new_from_file ("c/chip5.svg");
		gtk_button_set_image (GTK_BUTTON (button_chip5), image);

		image = gtk_image_new_from_file ("c/chip25.svg");
		gtk_button_set_image (GTK_BUTTON (button_chip25), image);

		image = gtk_image_new_from_file ("c/chip100.svg");
		gtk_button_set_image (GTK_BUTTON (button_chip100), image);
		
		image = gtk_image_new_from_file ("c/chip0.png");
		gtk_button_set_image (GTK_BUTTON (button_chip0), image);
		
		GtkStyleContext *context;
		context = gtk_widget_get_style_context(table.hbox_chips);		/* Apply style to hbox_chips */
		gtk_style_context_add_class(context,"my_hbox_chips");
								
		context = gtk_widget_get_style_context(table.hbox);				/* Apply style to hbox */
		gtk_style_context_add_class(context,"my_hbox");
		
		context = gtk_widget_get_style_context(hbox_msg);				/* Apply style to hbox */
		gtk_style_context_add_class(context,"my_hbox_msg");
		
   		g_signal_connect(G_OBJECT(button_hit), "clicked", G_CALLBACK(button_hit_clicked), &table);
   		g_signal_connect(G_OBJECT(button_stand), "clicked", G_CALLBACK(button_stand_clicked), &table);
		g_signal_connect (about_button, "clicked", G_CALLBACK (activate_about), NULL);
		g_signal_connect (G_OBJECT (window), "destroy",	G_CALLBACK (destroy), NULL);
		g_signal_connect(G_OBJECT(table.canvas), "draw", G_CALLBACK(on_draw_event), &table);
    	g_signal_connect(G_OBJECT(button_chip1), "clicked", G_CALLBACK(buttonAdd), &table);
		g_signal_connect(G_OBJECT(button_chip5), "clicked", G_CALLBACK(buttonAdd), &table);
		g_signal_connect(G_OBJECT(button_chip25), "clicked", G_CALLBACK(buttonAdd), &table);
		g_signal_connect(G_OBJECT(button_chip100), "clicked", G_CALLBACK(buttonAdd), &table);
		g_signal_connect(G_OBJECT(button_chip0), "clicked", G_CALLBACK(reset), &table);
 		g_signal_connect(G_OBJECT(table.button_start), "clicked", G_CALLBACK(init_game), &table);
 		g_signal_connect(G_OBJECT(table.button_play_again), "clicked", G_CALLBACK(new_game), &table);
 		
 		gtk_widget_show_all (window);
 		
 		gtk_widget_hide(table.hbox);
 		
  		gtk_main();
  		
  		for (i = 0; i < table.dealer->hand; i++)
			cairo_surface_destroy(table.dealer->card[i]);
			
		for (i = 0; i < table.player->hand; i++)
			cairo_surface_destroy(table.player->card[i]);
		
		cairo_surface_destroy(table.image_back);
		
		free(table.dealer);
		free(table.player);
}

void init_game(GtkWidget *widget, struct black *table) {

	int i;
	gtk_widget_hide(widget);
	gtk_widget_show(table->hbox);
	gtk_widget_hide(table->hbox_chips);
	gtk_widget_hide(table->button_play_again);
	gtk_label_set_text (GTK_LABEL(table->label_msg), "");
	table->status = 1;
	table->end = 0;
	
	table->dealer->total = table->dealer->aces = table->dealer->hand = table->check_stand = 0;
	table->player->total = table->player->aces = table->player->hand = 0;
 	memset(table->card_dealt, 0, sizeof(table->card_dealt));
	
	draw_cards(table->card_dealt, table->dealer);
	draw_cards(table->card_dealt, table->player);
	
	for (i = 0; i < MAX_CARDS; i++) {
		table->dealer->card[i] = NULL;
		table->player->card[i] = NULL;
	}
	
	for (i = 0; i < 2; i++) {		/* Initialize first hand */
		table->dealer->card[i] = cairo_image_surface_create_from_png(table->dealer->card_path[i]);
		table->player->card[i] = cairo_image_surface_create_from_png(table->player->card_path[i]);
		assign_points(table->dealer);
		assign_points(table->player);
		table->dealer->hand++;
		table->player->hand++;
	}
	
	table->dealer->hand = table->player->hand = 1;

	findWinner(table);
}
 
void button_hit_clicked(GtkWidget *widget, struct black *table)
{
	cairo_surface_t *img;
	table->player->hand++;
	assign_points(table->player);
	
	gtk_widget_queue_draw (table->canvas);
    
	if (table->dealer->total < 17) {
		table->dealer->hand++;
		assign_points(table->dealer);
		img = table->dealer->card[table->dealer->hand] = cairo_image_surface_create_from_png(table->dealer->card_path[table->dealer->hand]);
		
		if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS) {
    		fprintf(stderr, "Could not load imgage for dealer %s", table->dealer->card_path[table->dealer->hand]);
    	}
	}
	
    img = table->player->card[table->player->hand] = cairo_image_surface_create_from_png(table->player->card_path[table->player->hand]);
    
    if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS) {
    	fprintf(stderr, "Could not load imgage for player %s, status is: %d", table->player->card_path[table->player->hand],cairo_surface_status(img) );
    }
    
	findWinner(table);
}

void button_stand_clicked(GtkWidget *widget, struct black *table)
{
	cairo_surface_t *img;
	gtk_widget_queue_draw (table->canvas);
    
	if (table->dealer->total < 17) {
		table->dealer->hand++;
		assign_points(table->dealer);
		img = table->dealer->card[table->dealer->hand] = cairo_image_surface_create_from_png(table->dealer->card_path[table->dealer->hand]);
		
		if (cairo_surface_status(img) != CAIRO_STATUS_SUCCESS)
    		fprintf(stderr, "Could not load imgage for dealer %s", table->dealer->card_path[table->dealer->hand]);
	}
	
	else
		table->check_stand = 1;
	
	findWinner(table);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, struct black *table)
{
  if (table->status != 0 || table->end == 1)
  	do_drawing(cr, table);

  return FALSE;
}

void do_drawing(cairo_t *cr, struct black *table)
{
   int i;
  
	for (i = 0; i <= table->dealer->hand; i++) {
  
	  	if (i == 0 && table->end == 0)
		  	cairo_set_source_surface(cr, table->image_back, 10, 10);
		else
	    	cairo_set_source_surface(cr, table->dealer->card[i], table->x[i], 10);
		    
	    cairo_paint(cr);
	}
  
	for (i = 0; i <= table->player->hand; i++) {
		cairo_set_source_surface(cr, table->player->card[i], table->x[i], 320);
  		cairo_paint(cr);
	}
}

void activate_about() {

	const gchar *authors[] = {"Giovanni Resta", NULL};

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

void new_game (GtkWidget *window, struct black *table)
{
	gtk_label_set_text (GTK_LABEL(table->label_msg), "Please Bet ");
	gtk_label_set_text (GTK_LABEL(table->label_bet), "0");
	gtk_widget_hide(table->hbox);
	gtk_widget_show(table->hbox_chips);
}

void buttonAdd (GObject *button, struct black *table)
{
	gtk_widget_show(table->button_start);
	int data = GPOINTER_TO_INT(g_object_get_data (button,"id"));
	
	if (table->bet + data <= table->credit) {
	    table->bet += data;
    	updatelabel_bet(table);
    }
}

void updatelabel_bet(struct black *table)
{
	gchar *display;
    display = g_strdup_printf(" %d$ ", table->bet);					/* convert num to str */
    gtk_label_set_text (GTK_LABEL(table->label_bet), display);		/* set label to "display */
    g_free(display);                              					/* free display */
}

void updatelabel_credit(struct black *table)
{
	gchar *display;
    display = g_strdup_printf(" Credit %d$", table->credit);			/* convert num to str */
    gtk_label_set_text (GTK_LABEL(table->label_credit), display);		/* set label to "display */
    g_free(display);                              					/* free display */
}

void updatelabel_msg(gchar *display, struct black *table)
{
	gtk_label_set_text (GTK_LABEL(table->label_msg), display);
}

void reset (GObject *button, struct black *table)
{
    table->bet = GPOINTER_TO_INT(g_object_get_data (button,"id"));;
    updatelabel_bet(table);
    gtk_widget_hide(table->button_start);
}