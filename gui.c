#include "black.h"

extern struct card deck[CARDS];

void create_window(void)
{
  	struct black table;
  	
	table.credit = 50;
	table.bet = 0;
	
	table.cards_dealt = 0;
  	
	GtkWidget *window;
	GtkWidget *headbar;
	GtkWidget *vbox;

   	GtkWidget *button_chip1, *button_chip5, *button_chip25, *button_chip100, *button_chip0;
   	
   	GtkWidget *chips_img0 = gtk_image_new();
   	GtkWidget *chips_img1 = gtk_image_new();
   	GtkWidget *chips_img5 = gtk_image_new();
   	GtkWidget *chips_img25 = gtk_image_new();
   	GtkWidget *chips_img100 = gtk_image_new();   	
     	
	GtkWidget *hbox_creditBet;
	GtkWidget *about_button;
        
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	headbar = gtk_header_bar_new();
	about_button = gtk_button_new_with_label("About");
	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 35);
	hbox_creditBet = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 35);
	table.hbox_dealer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 35);
	table.hbox_player = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 35);
	table.hbox_chips = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	table.hbox_buttons = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	table.hbox_endGame = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);        
    
	gtk_header_bar_set_title (GTK_HEADER_BAR (headbar), "Blackjack");
	gtk_window_set_title (GTK_WINDOW (window), "Blackjack");    
	gtk_window_set_titlebar (GTK_WINDOW (window), headbar);
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (headbar), TRUE);
	gtk_window_maximize (GTK_WINDOW (window));
    
	table.button_hit = gtk_button_new_with_mnemonic ("Hit");
	table.button_stand = gtk_button_new_with_mnemonic ("Stand");
	table.button_start = gtk_button_new_with_mnemonic ("Start");
	table.button_playAgain = gtk_button_new_with_mnemonic ("Play Again");
	
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
	
	table.label_credit = gtk_label_new ("Credit 50$");
	table.label_bet = gtk_label_new ("Please Bet");
	table.label_endGame = gtk_label_new ("");	
	
	gtk_container_add(GTK_CONTAINER (headbar), about_button);
	gtk_container_add(GTK_CONTAINER (window), vbox);
	
	gtk_container_add(GTK_CONTAINER (vbox), table.hbox_chips);
	gtk_container_add(GTK_CONTAINER (vbox), hbox_creditBet);	
	gtk_container_add(GTK_CONTAINER (vbox), table.hbox_dealer);	
	gtk_container_add(GTK_CONTAINER (vbox), table.hbox_player);	
	gtk_container_add(GTK_CONTAINER (vbox), table.hbox_buttons);	
	gtk_container_add(GTK_CONTAINER (vbox), table.hbox_endGame);
	
	gtk_container_add (GTK_CONTAINER (table.hbox_chips), button_chip1);
	gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip5);
	gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip25);
	gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip100);
	gtk_container_add(GTK_CONTAINER (table.hbox_chips), button_chip0);
	gtk_container_add (GTK_CONTAINER (table.hbox_chips), table.button_start);
	
	int i;	
	
	for (i = 0; i < MAX_CARDS_HAND; i++)
	{
		table.player[0].cards[i] = gtk_image_new();
		table.player[1].cards[i] = gtk_image_new();
		gtk_container_add (GTK_CONTAINER (table.hbox_dealer), table.player[0].cards[i]);
		gtk_widget_hide(table.player[0].cards[i]);
		gtk_container_add (GTK_CONTAINER (table.hbox_player), table.player[1].cards[i]);
		gtk_widget_hide(table.player[1].cards[i]);
	}
	
	gtk_container_add (GTK_CONTAINER (table.hbox_buttons), table.button_hit);
	gtk_container_add (GTK_CONTAINER (table.hbox_buttons), table.button_stand);
	
	gtk_container_add (GTK_CONTAINER (table.hbox_endGame), table.label_endGame);
	gtk_container_add (GTK_CONTAINER (table.hbox_endGame), table.button_playAgain);
	
	gtk_container_add(GTK_CONTAINER (hbox_creditBet), table.label_credit);
	gtk_container_add(GTK_CONTAINER (hbox_creditBet), table.label_bet);
	
	/* Apply style */
	
	GtkCssProvider *css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_resource(css_provider, "/media/style.css");
  		
	GdkScreen *myScreen = gdk_screen_get_default();
	gtk_style_context_add_provider_for_screen (myScreen, GTK_STYLE_PROVIDER (css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
                               
    GtkStyleContext *context;
	context = gtk_widget_get_style_context(table.hbox_buttons);		/* Apply style to hbox_buttons */
	gtk_style_context_add_class(context,"my_hbox_buttons");
	
	context = gtk_widget_get_style_context(table.hbox_chips);		/* Apply style to hbox */
	gtk_style_context_add_class(context,"my_hbox_chips");
	
	context = gtk_widget_get_style_context(hbox_creditBet);			/* Apply style to hbox */
	gtk_style_context_add_class(context,"my_hbox_creditBet");
	
	context = gtk_widget_get_style_context(table.hbox_dealer);		/* Apply style to hbox */
	gtk_style_context_add_class(context,"my_hbox_dealer");
	
	context = gtk_widget_get_style_context(table.hbox_player);		/* Apply style to hbox */
	gtk_style_context_add_class(context,"my_hbox_player");
	
	context = gtk_widget_get_style_context(table.hbox_endGame);		/* Apply style to hbox */
	gtk_style_context_add_class(context,"my_hbox_endGame");
	
	/* Style buttons as images */
	
	gtk_image_set_from_resource (GTK_IMAGE(chips_img1), "/media/chip1.svg");
	gtk_button_set_image (GTK_BUTTON (button_chip1), chips_img1);
	
	gtk_image_set_from_resource (GTK_IMAGE(chips_img5), "/media/chip5.svg");
	gtk_button_set_image (GTK_BUTTON (button_chip5), chips_img5);
	
	gtk_image_set_from_resource (GTK_IMAGE(chips_img25), "/media/chip25.svg");
	gtk_button_set_image (GTK_BUTTON (button_chip25), chips_img25);

	gtk_image_set_from_resource (GTK_IMAGE(chips_img100), "/media/chip100.svg");
	gtk_button_set_image (GTK_BUTTON (button_chip100), chips_img100);
		
	gtk_image_set_from_resource (GTK_IMAGE(chips_img0), "/media/chip0.png");
	gtk_button_set_image (GTK_BUTTON (button_chip0), chips_img0);
	
	/* Handlers */
	
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);
	g_signal_connect (about_button, "clicked", G_CALLBACK (activate_about), NULL);
   	g_signal_connect(G_OBJECT(button_chip1), "clicked", G_CALLBACK(buttonAdd), &table);
	g_signal_connect(G_OBJECT(button_chip5), "clicked", G_CALLBACK(buttonAdd), &table);
	g_signal_connect(G_OBJECT(button_chip25), "clicked", G_CALLBACK(buttonAdd), &table);
	g_signal_connect(G_OBJECT(button_chip100), "clicked", G_CALLBACK(buttonAdd), &table);
	g_signal_connect(G_OBJECT(button_chip0), "clicked", G_CALLBACK(reset), &table);
	g_signal_connect(G_OBJECT(table.button_start), "clicked", G_CALLBACK(init_game), &table);
	g_signal_connect(G_OBJECT(table.button_hit), "clicked", G_CALLBACK(button_hit_clicked), &table);
	g_signal_connect(G_OBJECT(table.button_stand), "clicked", G_CALLBACK(button_stand_clicked), &table);
	g_signal_connect(G_OBJECT(table.button_playAgain), "clicked", G_CALLBACK(new_game), &table);
	
	gtk_widget_show_all (window);
	gtk_widget_hide(table.hbox_buttons);
	gtk_widget_hide(table.button_start);
	gtk_widget_hide(table.hbox_endGame);
	
	shuffle(deck);

	gtk_main();
}

void init_game(GtkWidget *button G_GNUC_UNUSED, struct black *table)
{
	gtk_widget_hide(table->hbox_chips);
	gtk_widget_show(table->hbox_buttons);
	
	table->player[PLY].total = table->player[CPU].total = 0;
	table->player[PLY].hand = table->player[CPU].hand = 0;
	table->player[PLY].aces = table->player[CPU].aces = 0;
	table->check_stand = 0;
	
	gtk_image_set_from_resource (GTK_IMAGE(table->player[CPU].cards[table->player[CPU].hand]), "/media/back.png");
	
	/* Deal 1st hand: first two cards */
	
	int i;
	
	for (i = 0; i < 2; i++)
	{
		getCard(table, CPU);
		getCard(table, PLY);
	}
	
	findWinner(table);
}

void button_hit_clicked(GtkWidget *widget G_GNUC_UNUSED, struct black *table)
{
	getCard(table, PLY);
	gtk_widget_hide(table->hbox_buttons);
	g_timeout_add(1000, (GSourceFunc)dealer_reply, table);
}

void getCard(struct black *table, enum players id)
{
	if (table->cards_dealt == CARDS)
	{
		shuffle(deck);
		table->cards_dealt = 0;
	}
	
	if (table->player[CPU].hand == 0 && id == CPU)
	{
		table->covered_card = deck[table->cards_dealt].file;	
	}
	
	else
		gtk_image_set_from_resource (GTK_IMAGE(table->player[id].cards[table->player[id].hand]), deck[table->cards_dealt].file);
		
	table->player[id].card_value = deck[table->cards_dealt].value;
	gtk_widget_show(table->player[id].cards[table->player[id].hand]);
	assignPoints(&table->player[id]);
	table->player[id].hand++;
	table->cards_dealt++;
}

void button_stand_clicked(GtkWidget *widget G_GNUC_UNUSED, struct black *table)
{
	if (table->player[CPU].total < 17)
	{
		gtk_widget_hide(table->hbox_buttons);
		g_timeout_add(1000, (GSourceFunc)dealer_reply, table);
	}
	
	else
	{
		table->check_stand = 1;
		findWinner(table);
	}
}

gboolean dealer_reply (struct black *table)
{
	if (table->player[CPU].total < 17)
	{
		getCard(table, CPU);
	}
	
	gtk_widget_show(table->hbox_buttons);
	findWinner(table);
	
	return FALSE;
}

void destroy (GtkWidget *window G_GNUC_UNUSED, gpointer data G_GNUC_UNUSED)
{
	gtk_main_quit ();
}

void buttonAdd (GObject *button, struct black *table)
{
	gtk_widget_show(table->button_start);
	
	int tmp_bet = GPOINTER_TO_INT(g_object_get_data (button,"id"));
		
	if (table->bet + tmp_bet <= table->credit)
	{
	    table->bet += tmp_bet;
    	updatelabel_bet(table);
    }
}

void updatelabel_bet(struct black *table)
{
	gchar *display;
	display = g_strdup_printf("Bet %d$ ", table->bet);				/* convert num to str */
	gtk_label_set_text (GTK_LABEL(table->label_bet), display);		/* set label to "display */
	g_free(display);                              					/* free display */
}

void updateLabelCredit(struct black *table)
{
	gchar *display;
	display = g_strdup_printf("Credit %d$", table->credit);			/* convert num to str */
	gtk_label_set_text (GTK_LABEL(table->label_credit), display);	/* set label to "display */
	g_free(display);                              					/* free display */
}

void reset (GObject *button, struct black *table)
{
	table->bet = GPOINTER_TO_INT(g_object_get_data (button,"id"));
	updatelabel_bet(table);
	gtk_widget_hide(table->button_start);
}

void endHand(gchar *display, struct black *table)
{
	gtk_label_set_text (GTK_LABEL(table->label_endGame), display);
	gtk_widget_show (table->hbox_endGame);
	gtk_widget_hide(table->hbox_buttons);
	updateLabelCredit(table);
	gtk_image_set_from_resource (GTK_IMAGE(table->player[CPU].cards[0]), table->covered_card);
	table->bet = 0;
}

void new_game (GtkWidget *window G_GNUC_UNUSED, struct black *table)
{
	gtk_label_set_text (GTK_LABEL(table->label_bet), "Please Bet");
	gtk_widget_show(table->hbox_chips);
	gtk_widget_hide(table->hbox_endGame);
	
	int i;
	
	for (i = 0; i < MAX_CARDS_HAND; i++) {
		gtk_widget_hide(table->player[CPU].cards[i]);
		gtk_widget_hide(table->player[PLY].cards[i]);
	}
}

void activate_about(void)
{
	const gchar *authors[] = {"Giovanni Resta", "giovannirestadev@gmail.com", NULL};

	gtk_show_about_dialog (NULL,
                       "program-name", "BlackJack",
                       "version", "1.3",
    				   "license-type", GTK_LICENSE_GPL_3_0,
    				   "website", "https://github.com/gioretikto/blackjack",
					   "authors", authors,
    				   "logo-icon-name", "start-here",
    				   "comments", "reach me on #cansi Freenode IRC",
                       "title", ("BlackJack"),
                       NULL);
}
