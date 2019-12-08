typedef struct { int wall; } room_t;
void clear_maze();
int  get_room_wall(int x, int y, int z);
void set_room_wall(int x, int y, int z, int newwall);
int have_sword();
void set_sword(int x);
int have_hammer();
void set_hammer(int x);

void move_right();
void move_left();
void move_up();
void move_down();
void move_downstairs();
void move_upstairs();

int get_location_x_room();
void set_location_x_room(int x);
int get_location_y_room();
void set_location_y_room(int y);
int get_location_z_room();
void set_location_z_room(int z);
void print_maze();

void summon_treasure(int x, int y, int z);
int is_treasure(int x, int y, int z);

int is_monster(int x, int y, int z);
void summon_monster(int x, int y, int z);

int is_sword(int x, int y, int z);
void summon_sword(int x, int y, int z);

int have_sword();
void set_sword(int x);

int is_hole(int x, int y, int z);
void summon_hole(int x, int y, int z);

int is_ladder(int x, int y, int z);
void summon_ladder(int x, int y, int z);

int is_hammer(int x, int y, int z);
void summon_hammer(int x, int y, int z);
