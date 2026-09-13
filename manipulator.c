#include  <stdio.h>
#include <stdbool.h>// jako werjsa 1.1 probowac pozbyc sie tylu ifow
typedef struct //dodac tutaj tryb auto i manual jako druga wersja
{
    bool part_detected; //dodac error jako struct i jako tabele zeby miec nazwe erroru i numer jego zeby wyszukiwac errory jako nastepny updejcik
    bool part_gripped;
    bool part_in_magazine;
    //bool manipulator_home;
} Sensors;
typedef enum
{
    STATE_MENU,
    STATE_MOVE_X,
    STATE_MAGAZINE,
    STATE_PICK,
    STATE_SETTINGS,
    STATE_ERROR,
    STATE_DROP,
    STATE_STATUS,
}Menu;
typedef struct
{
    bool gripper;
    int position_x;
    //bool on_off;

}Manipulator;
typedef struct
{
    int position_x;
    bool target_on_map;
}Target;
typedef struct
{
    Manipulator manipulator;
    Menu menu;
    Target target;
    Sensors sensors;

}Machine;

void working_machine(Machine *machine)
{
    int error_number = 0;
    int part_in_magazine = 0;
    int what_to_do_menu = 0;
    machine->menu = STATE_MENU;
    while (true)
    {
    if(machine->menu == STATE_MENU)
    {
        printf("co chcesz zrobic\r\n"
        "1.wejsc do ustawien\r\n"
        "2.podniesc figurke\r\n"
        "3.ruszyc sie w powierzchni x\r\n"
        "4.sprawdzic magazyn \r\n"
        "5.odlozyc figurke do magazynu\r\n"
        "6.sprawdzic status maszyny\r\n");
        scanf("%d", &what_to_do_menu);
        if(what_to_do_menu == 1)
        {
            machine->menu = STATE_SETTINGS;
        }
        else if(what_to_do_menu == 2)
        {
            machine->menu = STATE_PICK;
        }
        else if(what_to_do_menu == 3)
        {
            machine->menu = STATE_MOVE_X;
        }
        else if(what_to_do_menu == 4)
        {
            machine->menu = STATE_MAGAZINE;
        }
        else if(what_to_do_menu == 5)
        {
            machine->menu = STATE_DROP;
        }
        else if(what_to_do_menu == 6)
        {
            machine->menu = STATE_STATUS;
        }
        else
        {
            error_number = 1;
            machine->menu = STATE_ERROR;
        }
    }
    if(machine->menu == STATE_SETTINGS)
    {
        int what_to_do_settings = 0;
        printf("co chcesz zrobic\n"
        "1.ustawic pozycje x targetu\n");
        scanf("%d", &what_to_do_settings);
        if(what_to_do_settings == 1)
        {
            printf("podaj pozycje x");
                scanf("%d", &machine->target.position_x);
                machine->target.target_on_map = true;
                machine->menu = STATE_MENU;
        }
        else
        {
                error_number = 2;
                machine->menu = STATE_ERROR;
        }
    }
    if(machine->menu == STATE_MOVE_X)
    {
        int move_x = 0;
        printf("o ile chcesz sie ruszyc w pozycji x");
        scanf("%d", &move_x);
        machine->manipulator.position_x += move_x;
        machine->menu = STATE_MENU;
    }
    if(machine->menu == STATE_MAGAZINE)
    {
        printf("%d", part_in_magazine);
        machine->menu = STATE_MENU;
    }
    if(machine->menu == STATE_PICK)
    {
        if(machine->target.target_on_map)
        {
            machine->sensors.part_detected = true;
                    if(machine->target.position_x == machine->manipulator.position_x)
                    {
                        if(machine->sensors.part_detected)
                        {
                            printf("manipulator znajduje sie przy obiekcie");
                            machine->manipulator.gripper = true;
                            machine->sensors.part_gripped = true;
                            machine->target.position_x = 0;
                            machine->sensors.part_detected = false;
                            machine->target.target_on_map = false;
                            machine->menu = STATE_MENU;
                        }
                        else
                        {
                            error_number = 3;
                            machine->menu = STATE_ERROR;
                        }
                    }
                    else
                    {
                        error_number = 4;
                        machine->menu = STATE_ERROR;
                    }
        }
        else if(!machine->target.target_on_map)
        {
            error_number = 5;
            machine->menu = STATE_ERROR;
        }
    }
    if(machine->menu == STATE_DROP)
    {
        if(machine->manipulator.gripper && machine->sensors.part_gripped)
        {
            printf("wrzucasz figurke do magazynu");
            machine->manipulator.gripper = false;
            machine->sensors.part_gripped = false;
            machine->sensors.part_in_magazine = true;
            if(machine->sensors.part_in_magazine)
            {
                part_in_magazine += 1;
                machine->sensors.part_in_magazine = false;
                machine->menu = STATE_MENU;
            }
            else
            {
                error_number = 6;
                machine->menu = STATE_ERROR;
            }


        }
        else
        {
            error_number = 7;
            machine->menu = STATE_ERROR;
        }
    }
    if(machine->menu == STATE_STATUS)
    {
        printf("na jakim x znajduje sie manipulator - %d\r\n na jakim x znajduje sie target - %d\r\n", machine->manipulator.position_x, machine->target.position_x);
        machine->menu = STATE_MENU;
    }
    if(machine->menu == STATE_ERROR)
    {
        switch(error_number)
        {
            case 1:
                printf("nie ma takiego wyboru");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 2:
                printf("nie ma takiego wyboru");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 3:
                printf("sensor nie wykrywa partu");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 4:
                printf("manipulator nie znajduje sie przy targecie");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 5:
                printf("nie ma zadnego targetu na mapie");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 6:
                printf("figurka nie trafila do magazynu");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;
            case 7:
                printf("nie podniosles manipulatorem figurki");
                error_number = 0;
                machine->menu = STATE_MENU;
                break;

        }
    }
}
}
int main(void)
{
    Machine machine = {0};
    working_machine(&machine);
    return 0;
}