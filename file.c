#include <stdio.h>
#include "maze.h"
#include "file.h"

void read_file( char* filename ) {
   FILE* f;
   char scratchpad[1024];
   int i, j, z;
   f = fopen (filename, "r");
   if( f != NULL ) {
     for(i=0; i <10; i++) {
 	     for(j=0; j <10; j++) {
	        for(z=0; z <10; z++) {
		         set_room_wall(i,j,z,0);
	   	    }
       }
    }
    while( fgets( scratchpad, 1024, f) !=NULL ) {
      if( sscanf (scratchpad, "WALL %d %d %d", &i, &j, &z) ) {
        set_room_wall( i, j, z, 1 );
      }
      else if( sscanf (scratchpad, "X %d %d %d", &i, &j, &z)) {
        set_location_x_room (i);
        set_location_y_room(j);
        set_location_z_room(z);
      }
      else if( sscanf (scratchpad, "TREASURE %d %d %d",&i, &j, &z)) {
         summon_treasure(i, j, z);
      }
      else if( sscanf (scratchpad, "MONSTER %d %d %d",&i, &j, &z)) {
         summon_monster(i, j, z);
      }
      else if( sscanf (scratchpad, "SWORD %d %d %d",&i, &j, &z)) {
         summon_sword(i, j, z);
      }
	  else if( sscanf (scratchpad, "HAMMER %d %d %d",&i, &j, &z)) {
         summon_hammer(i, j, z);
      }
      else if( sscanf (scratchpad, "HOLE %d %d %d",&i, &j, &z)) {
        summon_hole(i, j, z);
      }
      else if( sscanf (scratchpad, "LADDER %d %d %d",&i, &j, &z)) {
         summon_ladder(i, j, z);
      }
      else if( sscanf (scratchpad, "INVENTORY %s", filename)) {
        if( filename[0] == 'S') {
	 	       set_sword(1);
		    }
		    else{
		       set_hammer(1);
		    }
      }
    }
    fclose (f);
  }
}

void save (char* filename) {
  FILE* f;
  char scratchpad[1024];
  int x, y, z;
  f = fopen (filename, "w");
  if( f != NULL ) {
    for (z=0; z<10; z++) {
      for (y=0; y<10; y++) {
        for( x=0; x<10; x++) {
          if( get_room_wall(x, y, z) == 1) {
            fprintf(f, "WALL %d %d %d\n", x, y, z);
          }
          else if( is_treasure(x,y,z) == 1) {
            fprintf(f, "TREASURE %d %d %d\n", x, y, z);
          }
          else if( is_monster(x,y,z) == 1) {
            fprintf(f, "MONSTER %d %d %d\n", x, y, z);
          }
          else if( is_sword(x,y,z) == 1) {
            fprintf(f, "SWORD %d %d %d\n", x, y, z);
          }
		      else if( is_hammer(x,y,z) == 1) {
            fprintf(f, "HAMMER %d %d %d\n", x, y, z);
          }
        }
      }
      if (have_sword()) {
        fprintf(f, "INVENTORY SWORD\n");
      }
      if (have_hammer) {
        fprintf(f, "INVENTORY HAMMER\n");
      }
      fprintf(f, "X %d %d %d\n", get_location_x_room(), get_location_y_room(), get_location_z_room());
      fclose (f);
    }
  }
}
