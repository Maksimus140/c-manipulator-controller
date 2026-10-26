#ifndef MANIPULATOR_H
#define MANIPULATOR_H
#define MAX_POSITION 100

typedef struct Machine Machine;

typedef struct
{
    bool gripper;
    int position_x;
    int position_y;

}Manipulator;

void move_x(Machine *machine);

void move_y(Machine *machine);


#endif