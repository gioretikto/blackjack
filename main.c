#include <stdlib.h>
#include <time.h>
#include "black.h"

int main (int argc, char *argv[])
{       	
	srand ((unsigned) time(NULL));
		
   	gtk_init (&argc, &argv);
       	
	create_window();
						
    return 0;
}
