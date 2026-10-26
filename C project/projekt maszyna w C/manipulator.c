#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "machine.h"
int move_pos = 0;
extern void (*struct_tabel[10])(Machine *);

void move_x(Machine *machine)
{
    printf("ile chcesz sie przesunac w osi x");
    scanf("%d", &move_pos);
    if(machine->manipulator.position_x + move_pos > MAX_POSITION)
    {
        move_pos = 0;
        error_number = 2;//cos ale jeszcze nie wiem ktory to numer bledu
        machine->menu = STATE_ERROR;
        struct_tabel[machine->menu](machine);
        
    }
    machine->manipulator.position_x += move_pos;
}
void move_y(Machine *machine)
{
    printf("ile chcesz sie przesunac w osi y");
    scanf("%d", &move_pos);
    if(machine->manipulator.position_y + move_pos > MAX_POSITION)
    {
        move_pos = 0;
        error_number = 2;
        machine->menu = STATE_ERROR;
        struct_tabel[machine->menu](machine);

    }
    machine->manipulator.position_y += move_pos;
}

