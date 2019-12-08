#include <stdio.h>
#include "maze.h"
static room_t maze[10][10][10];
static int location_x;
static int location_y;
static int location_z;
static int sword;
static int hammer;

int have_sword()
{
  if(sword == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
void set_sword(int x)
{
  sword = x;
}

int have_hammer()
{
  if(hammer == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
void set_hammer(int x)
{
  hammer = x;
}

void move_right()
{
  int move_to_x = get_location_x_room() + 1;
  if( move_to_x < 10 && ! is_wall(move_to_x, location_y, location_z) )
  {
    set_location_x_room( move_to_x);
  }
}
void move_left()
{
  int move_to_x = get_location_x_room() - 1;
  if( move_to_x >= 0 && ! is_wall(move_to_x, location_y, location_z) )
  {
    location_x=location_x-1;
  }
}
void move_up()
{
int move_to_y = get_location_y_room() - 1;
if( move_to_y >=0 && ! is_wall(location_x, move_to_y, location_z) )
  {
    location_y=location_y-1;
  }
}
void move_down()
{
  int move_to_y = get_location_y_room() + 1;
  if( move_to_y < 10 && ! is_wall(location_x, move_to_y, location_z) )
    {
       location_y=location_y+1;
    }
  }
void move_downstairs()
{
  int move_to_z = get_location_z_room() - 1;
  if( move_to_z < 10 && ! is_wall(location_x, location_y, move_to_z) )
    {
       location_z=location_z-1;
    }
  }
void move_upstairs()
{
int move_to_z = get_location_z_room() + 1;
if( move_to_z < 10 && ! is_wall(location_x, location_y, move_to_z) )
  {
    location_z=location_z+1;
  }
}



int get_location_x_room()
{
  return location_x;
}
void set_location_x_room(int x)
{
  location_x = x;
}
int get_location_y_room()
{
  return location_y;
}
void set_location_y_room(int y)
{
  location_y = y;
}
int get_location_z_room()
{
  return location_z;
}
void set_location_z_room(int z)
{
  location_z = z;
}


void print_maze()
{
  printf("\e[5A\e[G");
  int i, j, z;
  fprintf(stdout, "\x1b[7m\x1b[1m??????????\x1b[0m\n");
  for( z=0; z<10; z++ )
  {
    if( get_location_z_room()== z)
    {
    for( j=get_location_y_room() - 1; j<=get_location_y_room() +1; j++ )
    {
      fprintf(stdout, "\x1b[7m\x1b[1m??\x1b[0m");
      for( i=get_location_x_room() - 1; i<=get_location_x_room() +1; i++ )
      {
          if( i == location_x && j == location_y && z == location_z)
          {
            if( have_sword())
            {
              fprintf( stdout, "\x1b[34m\x1b[1mx\x1b[90m'\x1b[0m");
            }
            else if( have_hammer())
            {
              fprintf( stdout, "\x1b[34m\x1b[1mx\x1b[35mb\x1b[0m");
            }
            else
            {
              fprintf( stdout, "\x1b[34m\x1b[1mx\x1b[0m ");
            }
          }
          else if( !( i >= 0 && i <10 && j >= 0 && j <10 && z >= 0 && z <10 ))
          {
            fprintf(stdout, "  ");
          }
          else if( get_room_wall(i,j,z) == 1 )
          {
            fprintf( stdout, "##" );
          }
          else if( is_treasure(i,j,z) == 1)
          {
            fprintf(stdout, "\x1b[32m\x1b[1mT\x1b[0m " );
          }
          else if( is_monster(i,j,z) == 1)
          {
            fprintf(stdout, "\x1b[31m\x1b[1mM\x1b[0m " );
          }
          else if( is_sword(i,j,z) == 1)
          {
            fprintf(stdout, "\x1b[90m\x1b[1mS\x1b[0m " );
          }
          else if( is_hammer(i,j,z) == 1)
          {
            fprintf(stdout, "\x1b[35m\x1b[1mH\x1b[0m " );
          }
          else if( is_hole(i,j,z) == 1)
          {
            fprintf(stdout, "()" );
          }
          else if( is_ladder(i,j,z) == 1)
          {
            fprintf(stdout, "//" );
          }
          else
          {
            fprintf( stdout, ". ");
          }
        }
      fprintf(stdout, "\x1b[7m\x1b[1m??\x1b[0m\n");
    }
  }
}
fprintf(stdout, "\x1b[7m\x1b[1m??????????\x1b[0m");
//printf("\e[5A\e[G");
}


void clear_maze()
{
  set_location_x_room(0);
  set_location_y_room(0);
  set_location_z_room(0);
  int x=0;
  int y=0;
  int z=0;
  for( x=0; x<10; x++ )
  {
    for ( y=0; y<10; y++ )
    {
      for( z=0; z<10; z++ )
      {
        maze[x][y][z].wall=0;
      }
    }
  }
}

int  get_room_wall(int x, int y, int z)
{
  return maze[x][y][z].wall;
}

void set_room_wall(int x,int y, int z, int newwall)
{
  maze[x][y][z].wall = newwall;
}

void build_wall(int x, int y, int z)
{
  maze[x][y][z].wall = 1;
}

void break_wall(int x, int y, int z)
{
  if( maze[x][y][z].wall ==1 && have_hammer())
  {
    maze[x][y][z].wall = 0;
  }
}

int is_wall(int x, int y, int z)
{
  if( maze[x][y][z].wall == 1 )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int is_treasure(int x, int y, int z)
{
  if( maze[x][y][z].wall == 2)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void summon_treasure(int x, int y, int z)
{
  maze[x][y][z].wall = 2;
}

int is_monster(int x, int y, int z)
{
  if(maze[x][y][z].wall == 3)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void summon_monster(int x, int y, int z)
{
  maze[x][y][z].wall = 3;
}

int is_sword(int x, int y, int z)
{
  if(maze[x][y][z].wall == 4)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void summon_sword(int x, int y, int z)
{
  maze[x][y][z].wall = 4;
}

int is_hole(int x, int y, int z)
{
  if(maze[x][y][z].wall == 5)
  {
    return 1;
  } else {
    return 0;
  }
}

void summon_hole(int x, int y, int z)
{
  maze[x][y][z].wall = 5;
}

int is_ladder(int x, int y, int z)
{
  if(maze[x][y][z].wall == 6)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void summon_ladder(int x, int y, int z)
{
  maze[x][y][z].wall = 6;
}

int is_hammer(int x, int y, int z)
{
  if(maze[x][y][z].wall == 7)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void summon_hammer(int x, int y, int z)
{
  maze[x][y][z].wall = 7;
}
