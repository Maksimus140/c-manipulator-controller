#ifndef MAIN_H
#define MAIN_H

#define MAX_DEFINE_X 100
#define MAX_DEFINE_Y 50

typedef enum
{
    STATE_MENU,
    STATE_MOVE,
    STATE_MAGAZINE,
    STATE_PICK,
    STATE_SETTINGS,
    STATE_DROP,
    STATE_STATUS,
    STATE_MAP,
    STATE_ERROR,
}Menu;

typedef struct
{
    int error_numbers;
    char const *message;
}Error_info; 

typedef struct //dodac tutaj tryb auto i manual jako druga wersja
{
    bool part_detected; 
    bool part_gripped;
    bool part_in_magazine;
} Sensors;

typedef struct
{
    bool gripper;
    int position_x;
    int position_y;

}Manipulator;

typedef struct
{
    int position_x;
    int position_y;
    bool target_on_map;
}Target;

typedef struct
{
    Manipulator manipulator;
    Menu menu;
    Target target;
    Sensors sensors;
    const Error_info *error_info;
    size_t error_count;

}Machine;

void map_print(Machine *machine);

void magazine(Machine *machine);

void move_y(Machine *machine);

void move_x(Machine *machine);

void move(Machine *machine);

void settings(Machine *machine);

void pick(Machine *machine);

void drop(Machine *machine);

void status(Machine *machine);

void menu(Machine *machine);

void error(Machine *machine);

void working_machine(Machine *machine);
#endif