#include  <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "machine.h"
//dodac log
//dodanie tego ze figurki sa wyjmowalne
//wersja v1.0 bez conveyora
//wersja v2.0 z conveyorem
//dodac admin panel i normalny panel 
//tryb auto i manual
//dodanie sortowania magazynu po id rozmiaru podkladki
//zeby ten admin panel mial moze jakies dodanie bledow czy usuwanie rzeczy z magazynu cos takiego 
bool end = 0;
int error_number = 0;
int n = 0;
int id_giver = 0;
int id_giver_how_many = 0;
Magazine *magazine = NULL;
int mape[MAX_POSITION][MAX_POSITION] = {0};
void (*struct_tabel[10])(Machine *);
bool position_check(int *position_a, int *position_b, int *position_c, int *position_d)
{
    return *position_a == *position_b && *position_c == *position_d;
}

const Error error_info [] =
{
    {1, "nie znaleziono opcji"},
    {2, "za duza wartosc"},
    {3, "magazyn wywalil bład"},
    {4, "nie znaleziono błedu"},
    {5, "target juz jest na mapie"},
    {6, "nie jestes w dobrej pozycji"},
    {7, "nie chwyciles figurki"},
    {8, "targetu nie ma na mapie"},
    {9, "magazyn jest pusty"},
    {10, "nie znaleziono opcji (menu)"}

};
//tu chodzi o to ze wybieram na start element i go sortuje uzywac porownania element
void sort_magazine(Machine *machine)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            if(magazine[i].id > magazine[j].id)
            {
                Magazine tmp = magazine[j];
                magazine[j] = magazine[i];
                magazine[i] = tmp;
            }
        }
    }
}

void check_magazine(Machine *machine)
{
    if(magazine == NULL)
    {
        error_number = 9;
        machine->menu = STATE_ERROR;
        return;
    }
    for(int i = 0; i < n; i++)
    {
        sort_magazine(machine);
        printf("%d %d %d", magazine[i].id, magazine[i].base_size, magazine[i].id_how_many);
    }
}

void move(Machine *machine)
{
    int what_to_do_move = 0;
    printf("co chcesz zrobic  1.zmienic pozycje x 2. zmienic pozycje y 3.wyjsc z menu ruchu");
    scanf("%d", &what_to_do_move);
    if(what_to_do_move == 1)
    {
        move_x(machine);
    }
    else if(what_to_do_move == 2)
    {
        move_y(machine);
    }
    else if(what_to_do_move == 3)
    {
        machine->menu = STATE_MENU;
    }
    else
    {
        error_number = 1;
        machine->menu = STATE_ERROR;
    }
    mape[machine->manipulator.position_y][machine->manipulator.position_x] = 2;


}

void error(Machine *machine)
{
    int error_found = 0;
    for(int i = 0; i < sizeof(error_info)/sizeof(error_info[0]); i++)
    {
        if(error_info[i].error_numbers == error_number)
        {
            printf(error_info[i].message);
            error_found = 1;
            machine->menu = STATE_MENU;
        }
    }
    if(!error_found)
        {
            error_number = 4;
            machine->menu = STATE_MENU;
        }
}

void settings(Machine *machine)
{
    int what_to_do_settings = 0;
    printf("co chcesz zrobic\n"
          "1.ustawic predkosc silnika\n"
          "2.wlaczyc silnik\n"
          "3.dac target\n"
          "4.wyjsc");
    scanf("%d", &what_to_do_settings);
    if(what_to_do_settings == 1)
    {
        motor_speed(machine);
    }
    else if(what_to_do_settings == 2)
    {
        turn_on_motor(&machine->conveyor);
    }
    else if(what_to_do_settings == 3)
    {   
        if(!machine->target.target_on_map)//dac tu blokade ze jesli target jest na mapie nie mozna dodac drugiego targetu i jesli jest nadal zlapany target to tez nie mozna
        {
        int position_x = 0;
        int position_y = 0;
        int what_to_do_move = 0;
        int if_ended = 0;
        bool ended = 0;
        while (!ended)
        {
            printf("co chcesz zrobic ustawic pozycje 1.x 2.y 3.zakonczyc");
            scanf("%d", &what_to_do_move);
            if(what_to_do_move == 1)
            {
                printf("wprowadz pozycje x");
                scanf("%d", &position_x);
                if(position_x > MAX_POSITION)
                {
                    position_x = 0;
                    error_number = 2;
                    machine->menu = STATE_ERROR;
                }
                machine->target.position_x = position_x;
            }
            else if(what_to_do_move == 2)
            {
                printf("wprowadz pozycje y");
                scanf("%d", &position_y);
                if(position_y > MAX_POSITION)
                {
                    position_y = 0;
                    error_number = 2;
                    machine->menu = STATE_ERROR;
                }
                machine->target.position_y = position_y;
            }
            else if(what_to_do_move == 3)
            {
            printf("czy chcesz zakonczyc ustawianie pozycji");
            scanf("%d", &if_ended);
            ended = (if_ended != 0);
            }
            else
            {
              error_number = 1;
              machine->menu = STATE_ERROR;
              return;
            }
        }
        if(ended)
        {
            mape[machine->target.position_y][machine->target.position_x] = 1;
            machine->target.target_on_map = true;
            printf("podaj rozmiar podkladki na figurke");
            scanf("%d", &machine->target.size);
            ended = 0;
            machine->menu = STATE_MENU;
        }
      }
      else
      {
        error_number = 5;
        machine->menu = STATE_ERROR;
      }
    }
    else
    {
        error_number = 1;
        machine->menu = STATE_ERROR;
    }
}

void status(Machine *machine)
{
    printf("pozycja x manipulatora - %d,pozycja y manipulatora - %d"
    "pozycja x targetu - %d, pozycja y targetu - %d", 
    machine->manipulator.position_x, machine->manipulator.position_y,
     machine->target.position_x, machine->target.position_y );
     machine->menu = STATE_MENU;
}

void map(Machine *machine)
{
    for(int y = 0; y < MAX_POSITION; y++)
    {
        printf("\n");
        for(int x = 0; x < MAX_POSITION; x++)
        {
            printf("[%d]", mape[y][x]);
        }
    }
    machine->menu = STATE_MENU;

}

void pick_target(Machine *machine)
{
    if(position_check(&machine->manipulator.position_x, &machine->target.position_x, &machine->manipulator.position_y, &machine->target.position_y))
    {
        printf("%s\n", machine->target.target_on_map ? "true" : "false");
        machine->sensor.target_on_position = true;
        if(machine->sensor.target_on_position && machine->target.target_on_map)
        {
            machine->target.position_x = 0;
            machine->target.position_y = 0;
            machine->target.target_on_map = false;
            machine->sensor.target_gripped = true;
            machine->manipulator.gripper = true;
        }
        else
        {
            error_number = 8;
            machine->menu = STATE_ERROR;
            return;
        }
        machine->menu = STATE_MENU;
    }
    else
    {
        error_number = 6;
        machine->menu = STATE_ERROR;
        return;
    }
}

void drop_target(Machine *machine)
{
    bool found = 0;
    if(machine->sensor.target_gripped)
    {
        n += 1;
        Magazine *tmp = realloc(magazine, n * sizeof *magazine);
        if(tmp != NULL)
        {
            magazine = tmp;
            id_giver_how_many += 1;
        } 
        else
        {
            n -= 1;
            error_number = 3;
            machine->menu = STATE_ERROR;
            return;
            
        }
        magazine[n-1].id = 0;
        magazine[n-1].base_size = 0;
        printf("%d %d",magazine[n-1].id, magazine[n-1].base_size);
        machine->sensor.target_gripped = false;
        machine->sensor.in_magazine = true;
        machine->manipulator.gripper = false;
        for(int i = 0; i < n; i++)
        {
            if(magazine[i].base_size == machine->target.size)
            {
                found = 1;
                id_giver = magazine[i].id;
                for(int y = 0; y < n; y++)
                {
                    if(magazine[y].id == 0)
                    {
                        magazine[y].id_how_many = id_giver_how_many;
                        magazine[y].id = id_giver;
                        magazine[y].base_size = machine->target.size;
                        machine->menu = STATE_MENU;
                        break;
                    }
                } 
            }
        }
        if(!found)
            {
                id_giver += 1;
                for(int y = 0; y < n; y ++)
                {
                    if(magazine[y].id == 0)
                    {
                        magazine[y].id_how_many = id_giver_how_many;
                        magazine[y].id = id_giver;
                        magazine[y].base_size = machine->target.size;
                        machine->menu = STATE_MENU;
                        break;
                    }
                }
            }
    }
    else
    {
        error_number = 7;
        machine->menu = STATE_ERROR;
    }
return;
}

void menu(Machine *machine)
{
    while (!end)
    {
    if(machine->menu == STATE_ERROR)
    {
        struct_tabel[machine->menu](machine);
    }
    else
    {
    int menu_what_to_do = 0;
    printf("\n0. menu\n"
        "1.pick target\n"
        "2.drop target\n"
        "3.settings\n"
        "4.status\n"
        "5.check magazine\n"
        "6.map\n"
        "7.move\n"
        "9.zakoncz\n"
    );
    scanf("%d", &menu_what_to_do);
    if(menu_what_to_do > STATE_COUNT )
    {
        menu_what_to_do = 0;
        error_number = 10;
        machine->menu = STATE_ERROR;
    }
    else
    {
    machine->menu = menu_what_to_do;
    struct_tabel[machine->menu](machine);
    }
    }
    }
}

void end_function(Machine *machine)
{
    end = true;
    machine->menu = STATE_MENU;
    return;
}

int main(void)
{
    //magazine = malloc(n * sizeof *magazine);
    Machine Machine = {0};
    Machine.target.position_y = 0;
    Machine.menu = 0;
    struct_tabel[0] = menu;
    struct_tabel[1] = pick_target;
    struct_tabel[2] = drop_target;
    struct_tabel[3] = settings;
    struct_tabel[4] = status;
    struct_tabel[5] = check_magazine;
    struct_tabel[6] = map;
    struct_tabel[7] = move;
    struct_tabel[8] = error;
    struct_tabel[9] = end_function;
    menu(&Machine);
    free(magazine);
    return 0;
}