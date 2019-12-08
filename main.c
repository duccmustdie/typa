#include <stdio.h>
#include <termios.h>
#include "maze.h"

static struct termios old_settings;
static struct termios new_settings;

int main( int argc, char** argv ) {
  tcgetattr(0, &old_settings);
  tcgetattr(0, &new_settings);
  new_settings.c_lflag &= ~(ICANON|ECHO);
  new_settings.c_cc[VMIN] = 1;
  new_settings.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new_settings);
  char c;
  char userinput[1024];
  clear_maze();
  if (argc >1) {
    read_file(argv[1]);
  }


  fprintf(stdout,"\nWELCOME MORTAL. \nI SEE YOU ARE SEARCHING FOR A TRESURE, IT IS HIDDEN IN THIS MAZE.\nGOOD LUCK FINDING IT...\n");
  fprintf(stdout,"USE THE ARROW KEYS TO MOVE AROUND THE MAZE\n");
  fprintf(stdout,"HIT q TO EXIT THE GAME\nPRESS : TO ACESS COMMAND MODE\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"\n\n\n\n\n");
  print_maze();
  fprintf(stdout,"\n");

  while ((c = getchar()) != 'q') {
    if (c == 'c') {
      move_upstairs();
    }	else if (c == 27 && (c = getchar()) == 91) { /* hey, look, arrow key */
      int i = get_location_x_room();
      int j = get_location_y_room();
      int z = get_location_z_room();
			if ((c = getchar()) == 65) {
        if (have_hammer() && is_wall(i, j-1, z)) {
          break_wall(i, j-1, z, 0);
        } else {
          move_up();
        }
      } else if (c == 66) {
        if (have_hammer() && is_wall(i, j+1, z)) {
          break_wall(i, j+1, z, 0);
        } else {
          move_down();
        }
      } else if (c == 67) {
        if (have_hammer() && is_wall(i+1, j, z)) {
          break_wall(i+1, j, z, 0);
        } else {
          move_right();
        }
      } else if (c == 68) {
        if (have_hammer() && is_wall(i-1, j, z)) {
          break_wall(i-1, j, z, 0);
        } else {
          move_left();
        }
      }
		} else if (c == ':') {
      tcsetattr(0, TCSANOW, &old_settings);

      if( fgets( userinput, 1024, stdin) !=NULL  ) {
        int z;
        int i;
        int j;
        char file[1024];
        if (sscanf (userinput, "save %s", file) != 0) {
          save (file);
        } else if (sscanf (userinput, "load %s", file) != 0) {
        fprintf(stdout, "test\n");
        read_file (file);
        } else if (sscanf (userinput, "empty %d %d %d", &i, &j, &z ) != 0) {
          set_room_wall(i, j, z, 0);
        } else if (sscanf (userinput, "wall %d %d %d", &i, &j, &z) != 0) {
          set_room_wall(i, j, z, 1);
        } else if (sscanf (userinput, "x %d %d %d", &i, &j, &z) != 0) {
          set_location_x_room (i);
          set_location_y_room (j);
          set_location_z_room (z);
        }
      }
      fprintf(stdout, "\e[1A\e[G");
      tcsetattr(0, TCSANOW, &new_settings);
    }

    if( is_treasure(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      fprintf(stdout, "\e[5A\e[G");
      fprintf(stdout, "YOU WIN!\n");
      fprintf(stdout,"\n\n\n\n\n");
      tcsetattr(0, TCSANOW, &old_settings);
      return 0;
    }
check_hole:
    if( is_hole(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      move_downstairs();
      fprintf(stdout, "\e[5A\e[G");
      fprintf(stdout, "OH, NO! YOU FELL DOWN, FIND A LADDER TO GET BACK UPSTAIRS.\n");
      fprintf(stdout,"\n\n\n\n\n");
      goto check_hole;
    } else if( is_sword(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      set_sword(1);
      fprintf(stdout, "\e[5A\e[G");
      fprintf(stdout, "THOU HATH FOUND THE SWORD!\n");
      fprintf(stdout,"\n\n\n\n\n");
      set_room_wall(get_location_x_room(), get_location_y_room(), get_location_z_room(), 0);
      if(have_hammer()) {
        set_hammer(0);
        summon_hammer(get_location_x_room(), get_location_y_room(), get_location_z_room());
      }
    } else if( is_hammer(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      set_hammer(1);
      fprintf(stdout, "\e[5A\e[G");
      fprintf(stdout, "THOU HATH FOUND THE HAMMER!\n NOW YOU CAN TEAR DOWN WALLS\nI TRUST YOU CAN FIGURE OUT THE COMMANDS BY YOURSELF\n");
      fprintf(stdout,"\n\n\n\n\n");
      set_room_wall(get_location_x_room(), get_location_y_room(), get_location_z_room(), 0);
      if(have_sword()) {
        set_sword(0);
        summon_sword(get_location_x_room(), get_location_y_room(), get_location_z_room());
      }
    } else if( is_monster(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      if( have_sword()) {
        fprintf(stdout, "\e[5A\e[G");
        fprintf( stdout, "THOU HATH SLAIN THE MONSTER\n");
        fprintf(stdout,"\n\n\n\n\n");
      } else {
        fprintf(stdout, "\e[5A\e[G");
        fprintf(stdout, "THOU ART DEAD\nYOU NEED SOMETHING SHARPER TO DEFEAT THE MONSTER\n");
        fprintf(stdout,"\n\n\n\n\n");
        print_maze();
        fprintf(stdout,"\n");
        tcsetattr(0, TCSANOW, &old_settings);
        return 0;
      }
      set_room_wall(get_location_x_room(), get_location_y_room(), get_location_z_room(), 0);
    } else if( is_ladder(get_location_x_room(), get_location_y_room(), get_location_z_room())) {
      move_upstairs();
      fprintf(stdout, "\e[5A\e[G");
      fprintf(stdout, "YOU WENT UP\n" );
      fprintf(stdout,"\n\n\n\n\n");
    }
    print_maze();
    fprintf(stdout, "\n");
	}
  tcsetattr(0, TCSANOW, &old_settings);
  return 0;
}
