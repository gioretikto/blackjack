#include "black.h"

int main (int argc, char *argv[])
{       	
       	gtk_init (&argc, &argv); 	
        
		srand((unsigned)time(NULL));
		
		create_window();
				
        return 0;
}