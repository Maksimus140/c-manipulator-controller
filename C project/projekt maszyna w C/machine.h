#ifndef MACHINE_H
#define MACHINE_H

#include "conveyor.h"
#include "manipulator.h"

extern int error_number;


typedef enum
{
    STATE_MENU,
    STATE_PICK,
    STATE_DROP,
    STATE_SETTINGS,
    STATE_STATUS,
    STATE_MAGAZINE,
    STATE_MAP,
    STATE_MOVE,
    STATE_ERROR,
    STATE_COUNT,

}Menu;
typedef struct
{
    int id;
    int base_size;  
    int id_how_many;

}Magazine;
typedef struct
{
    int error_numbers;
    char *message;
}Error;
typedef struct
{
    bool target_on_position;
    bool target_gripped;
    bool in_magazine;
    bool target_on_map;

}Sensor;

typedef struct
{
    bool target_on_map;
    int position_x;
    int position_y;
    int size;

}Target;

struct Machine
{
    Target target;
    Sensor sensor;
    Error error;
    Magazine magazine;
    Menu menu;
    Motor motor;
    Conveyor conveyor;
    Manipulator manipulator;
    
};

void pick_target(Machine *machine);

void drop_target(Machine *machine);

void check_magazine(Machine *machine);

void map(Machine *machine);

void status(Machine *machine);

void settings(Machine *machine);

void working_machine(Machine *machine);

void move(Machine *machine);

bool position_check(int *position_a, int *position_b, int *position_c, int *position_d);

extern void (*struct_tabel[10])(Machine *);

#endif