#ifndef CONVEYOR_H
#define CONVEYOR_H

typedef struct Machine Machine;

#define MAX_SPEED 100
#define Distance 500
typedef struct
{
    bool turn_on;
    int speed_motor;

}Motor;
typedef struct
{
    int speed;
    Motor motor;

}Conveyor;

void motor_speed(Machine *machine);

void turn_on_motor(Conveyor *conveyor);

void math_conveyor_speed(Conveyor *conveyor);

#endif