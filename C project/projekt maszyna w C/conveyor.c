#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "machine.h"
int speed = 0;
extern void (*struct_tabel[10])(Machine *);
void motor_speed(Machine *machine)
{
    printf("podaj predkosc silnika");
    scanf("%", &speed);
    if(speed > MAX_SPEED)
    {
        speed = 0;
        error_number = 2;
        machine->menu = STATE_ERROR;
        struct_tabel[machine->menu](machine);
    }
    machine->motor.speed_motor = speed;
}
void math_conveyor_speed(Conveyor *conveyor)
{
    conveyor->speed = Distance/conveyor->motor.speed_motor;


}
void turn_on_motor(Conveyor *conveyor)
{
    conveyor->motor.turn_on = true;
    if(conveyor->motor.turn_on)
    {
        math_conveyor_speed(conveyor);

    }
}
