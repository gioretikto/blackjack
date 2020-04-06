#include <stdlib.h>
#include "black.h"

int main (int argc, char *argv[])
{
        GtkWidget *window;
        GtkWidget *headbar;
        GtkWidget *vbox;
        GtkWidget *about_button;
        GtkWidget *button_hit;
        GtkWidget *button_stand;
       	GtkWidget *button_chip1, *button_chip5, *button_chip25, *button_chip100, *button_chip0;
       	GtkWidget *hbox_msg; /* contains credit and bet label */
       	
       	gtk_init (&argc, &argv);
       	
        struct table dealer;
        
        int i;
		
		dealer.next = malloc(sizeof(struct table));
		
		dealer.next->next = NULL;		
		
		srand((unsigned)time(NULL));
		
		dealer.status = dealer.end = 0;
		glob.credit = 50;
		
		dealer.image_back = cairo_image_surface_create_from_png("c/back.png");
	
		dealer.x[0] = 10;
	
		for (i = 1; i < MAX_CARDS; i++)
			dealer.x[i] = dealer.x[i-1] + 110;        
        
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);				/* create window */
        headbar = gtk_header_bar_new();
        about_button = gtk_button_new_with_mnemonic("_About");
        vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 30);
		dealer.hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 50);
		dealer.hbox_chips = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		hbox_msg = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		button_hit = gtk_button_new_with_mnemonic ("Hit");
		button_stand = gtk_button_new_with_mnemonic ("Stand");
		glob.button_start = gtk_button_new_with_mnemonic ("Start");
		dealer.button_play_again = gtk_button_new_with_mnemonic ("Play Again");
		button_chip1 = gtk_button_new();
		button_chip5 = gtk_button_new();
		button_chip25 = gtk_button_new();
		button_chip100 = gtk_button_new();
		button_chip0 = gtk_button_new();
		dealer.label_msg = gtk_label_new ("Please Bet  ");
		glob.label_credit = gtk_label_new ("Credit");
		glob.label_bet = gtk_label_new ("0");
       	dealer.canvas = gtk_drawing_area_new();
       	
       	/* Set Properties */
        
		gtk_header_bar_set_title (GTK_HEADER_BAR (headbar), "Ventuno");
		gtk_window_set_titlebar (GTK_WINDOW (window), headbar);
	    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (headbar), TRUE);
        gtk_window_set_title (GTK_WINDOW (window), "BlackJack");
		gtk_window_maximize (GTK_WINDOW (window));
		g_object_set (dealer.canvas, "expand", TRUE, NULL);			/* expand the canvas */
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
		gtk_container_add (GTK_CONTAINER (vbox), dealer.canvas);
		gtk_container_add(GTK_CONTAINER (vbox), dealer.hbox);
		gtk_container_add(GTK_CONTAINER (vbox), hbox_msg);
   		gtk_container_add (GTK_CONTAINER (dealer.hbox), button_hit);
   		gtk_container_add (GTK_CONTAINER (dealer.hbox), button_stand);
		gtk_container_add(GTK_CONTAINER (hbox_msg), dealer.label_msg);
		gtk_container_add(GTK_CONTAINER (hbox_msg), glob.label_bet);
		gtk_container_add(GTK_CONTAINER (hbox_msg), glob.label_credit);
		gtk_container_add (GTK_CONTAINER (dealer.hbox_chips), glob.button_start);
		gtk_container_add (GTK_CONTAINER (dealer.hbox), dealer.button_play_again);
		gtk_container_add(GTK_CONTAINER (vbox), dealer.hbox_chips);
		gtk_container_add (GTK_CONTAINER (dealer.hbox_chips), button_chip1);
		gtk_container_add(GTK_CONTAINER (dealer.hbox_chips), button_chip5);
		gtk_container_add(GTK_CONTAINER (dealer.hbox_chips), button_chip25);
		gtk_container_add(GTK_CONTAINER (dealer.hbox_chips), button_chip100);
		gtk_container_add(GTK_CONTAINER (dealer.hbox_chips), button_chip0);
		
		updatelabel_credit();

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
		context = gtk_widget_get_style_context(dealer.hbox_chips);		/* Apply style to hbox_chips */
		gtk_style_context_add_class(context,"my_hbox_chips");
								
		context = gtk_widget_get_style_context(dealer.hbox);			/* Apply style to hbox */
		gtk_style_context_add_class(context,"my_hbox");
		
		context = gtk_widget_get_style_context(hbox_msg);			/* Apply style to hbox */
		gtk_style_context_add_class(context,"my_hbox_msg");
		
   		g_signal_connect(G_OBJECT(button_hit), "clicked", G_CALLBACK(button_hit_clicked), &dealer);
   		g_signal_connect(G_OBJECT(button_stand), "clicked", G_CALLBACK(button_stand_clicked), &dealer);
		g_signal_connect (about_button, "clicked", G_CALLBACK (activate_about), NULL);
		g_signal_connect (G_OBJECT (window), "destroy",	G_CALLBACK (destroy), NULL);
		g_signal_connect(G_OBJECT(dealer.canvas), "draw", G_CALLBACK(on_draw_event), &dealer);
	    g_signal_connect(G_OBJECT(button_chip1), "clicked", G_CALLBACK(buttonAdd), GINT_TO_POINTER(1));
		g_signal_connect(G_OBJECT(button_chip5), "clicked", G_CALLBACK(buttonAdd), GINT_TO_POINTER(5));
		g_signal_connect(G_OBJECT(button_chip25), "clicked", G_CALLBACK(buttonAdd), GINT_TO_POINTER(25));
		g_signal_connect(G_OBJECT(button_chip100), "clicked", G_CALLBACK(buttonAdd), GINT_TO_POINTER(100));
		g_signal_connect(G_OBJECT(button_chip0), "clicked", G_CALLBACK(reset), GINT_TO_POINTER(100));
 		g_signal_connect(G_OBJECT(glob.button_start), "clicked", G_CALLBACK(init_game), &dealer);
 		g_signal_connect(G_OBJECT(dealer.button_play_again), "clicked", G_CALLBACK(new_game), &dealer);
 		
		gtk_widget_show_all (window);
		
		gtk_widget_hide(dealer.hbox);
 
   		gtk_main();
   		
   		for (i = 0; i < dealer.hand; i++)
			cairo_surface_destroy(dealer.card[i]);
			
		for (i = 0; i < dealer.next->hand; i++)
			cairo_surface_destroy(dealer.next->card[i]);
		
		cairo_surface_destroy(dealer.image_back);
		
		free(dealer.next);
			
        return 0;
}