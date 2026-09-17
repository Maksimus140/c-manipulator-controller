#include  <stdio.h>// zrobic to ze pozycja targetu gdy jest podniesiony rowna sie pozycji manipulatora
#include <stdbool.h>// jako werjsa 1.1 probowac pozbyc sie tylu ifow
int error_number = 0;
int part_in_magazine = 0;
int what_to_do_menu = 0;
typedef struct //dodac tutaj tryb auto i manual jako druga wersja
{
    bool part_detected; 
    bool part_gripped;
    bool part_in_magazine;
} Sensors;
typedef struct
{
    int error_numbers;
    char const *message;
}Error_info; 

const Error_info error_infoo  [] =
{
    {1, "nie ma takiego wyboru\r\n"},
    {2, "nie ma takiego wyboru\r\n"},
    {3, "sensor nie wykrywa partu\r\n"},
    {4, "manipulator nie znajduje sie przy targecie\r\n"},
    {5, "nie ma zadnego targetu na mapie\r\n"},
    {6, "figurka nie trafila do magazynu\r\n"},
    {7, "nie podniosles manipulatorem figurki\r\n"},
};

typedef enum
{
    STATE_MENU,
    STATE_MOVE_X,
    STATE_MAGAZINE,
    STATE_PICK,
    STATE_SETTINGS,
    STATE_DROP,
    STATE_STATUS,
    STATE_ERROR,
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
    const Error_info *error_info;

}Machine;
void (*struct_tabel[8])[Machine *]
{

};


void move_x(Machine *machine)
{
        int move_x = 0;
        printf("o ile chcesz sie ruszyc w pozycji x\r\n");
        scanf("%d", &move_x);
        machine->manipulator.position_x += move_x;
        machine->menu = STATE_MENU;
        struct_tabel[machine->menu](machine);
}
void settings(Machine *machine)
{
        int what_to_do_settings = 0;
        printf("co chcesz zrobic\r\n"
        "1.ustawic pozycje x targetu\r\n");
        scanf("%d", &what_to_do_settings);
        if(what_to_do_settings == 1)
        {
            printf("podaj pozycje x\r\n");
                scanf("%d", &machine->target.position_x);
                machine->target.target_on_map = true;
                machine->menu = STATE_MENU;
                struct_tabel[machine->menu](machine);
        }
        else
        {
                error_number = 2;
                machine->menu = STATE_ERROR;
                struct_tabel[machine->menu](machine);
        }
}
void pick(Machine *machine)
{
        if(machine->target.target_on_map)
        {
            machine->sensors.part_detected = true;
                    if(machine->target.position_x == machine->manipulator.position_x)
                    {
                        if(machine->sensors.part_detected)
                        {
                            printf("manipulator znajduje sie przy obiekcie\r\n");
                            machine->manipulator.gripper = true;
                            machine->sensors.part_gripped = true;
                            machine->target.position_x = 0;
                            machine->sensors.part_detected = false;
                            machine->target.target_on_map = false;
                            machine->menu = STATE_MENU;
                            struct_tabel[machine->menu](machine);
                        }
                        else
                        {
                            error_number = 3;
                            machine->menu = STATE_ERROR;
                            struct_tabel[machine->menu](machine);
                        }
                    }
                    else
                    {
                        error_number = 4;
                        machine->menu = STATE_ERROR;
                        struct_tabel[machine->menu](machine);
                    }
        }
        else if(!machine->target.target_on_map)
        {
            error_number = 5;
            machine->menu = STATE_ERROR;
            struct_tabel[machine->menu](machine);
        }
}
void magazine(Machine *machine)
{
        printf("%d", part_in_magazine);
        machine->menu = STATE_MENU;
        struct_tabel[machine->menu](machine);
}
void drop(Machine *machine)
{
        if(machine->manipulator.gripper && machine->sensors.part_gripped)
        {
            printf("wrzucasz figurke do magazynu\r\n");
            machine->manipulator.gripper = false;
            machine->sensors.part_gripped = false;
            machine->sensors.part_in_magazine = true;
            if(machine->sensors.part_in_magazine)
            {
                part_in_magazine += 1;
                machine->sensors.part_in_magazine = false;
                machine->menu = STATE_MENU;
                struct_tabel[machine->menu](machine);
            }
            else
            {
                error_number = 6;
                machine->menu = STATE_ERROR;
                struct_tabel[machine->menu](machine);
            }


        }
        else
        {
            error_number = 7;
            machine->menu = STATE_ERROR;
            struct_tabel[machine->menu](machine);
        }
}
void status(Machine *machine)
{
        printf("na jakim x znajduje sie manipulator - %d\r\n na jakim x znajduje sie target - %d\r\n", machine->manipulator.position_x, machine->target.position_x);
        machine->menu = STATE_MENU;
        struct_tabel[machine->menu](machine);
}
void menu(Machine *machine);

void error(Machine *machine)
{
        for(int i = 0; i < 7; i++)
        {
            if(machine->error_info[i].error_numbers == error_number)
            {
                printf("%s", machine->error_info[i].message);
                error_number = 0;
                machine->menu = STATE_MENU;     
                struct_tabel[machine->menu](machine);     
            }
        }
}
struct_tabel[0] = menu;
struct_tabel[1] = move_x;
struct_tabel[2] = magazine;
struct_tabel[3] = pick;
struct_tabel[4] = settings;
struct_tabel[5] = drop;
struct_tabel[6] = status;
struct_tabel[7] = error;
void (*struct_tabel[])(Machine *) =
{
    menu,
    move_x,
    magazine,
    pick,
    settings,
    drop,
    status,
    error
};
void menu(Machine *machine)
{
        printf("co chcesz zrobic\r\n"
        "1.rusz manipulator\r\n"
        "3.sprawdz magazyn\r\n"
        "3.podniesc przedmiot\r\n"
        "4.przejdz do ustawien\r\n"
        "5.odloz figurke do magazynu\r\n"
        "6.sprawdzic status maszyny\r\n");
        scanf("%d", &what_to_do_menu);
        struct_tabel[what_to_do_menu](machine);
}

void working_machine(Machine *machine)
{
    while (true)
    {
        struct_tabel[0](machine);


    }
}
int main(void)
{
    Machine machine = {0};
    machine.error_info = error_infoo;
    working_machine(&machine);
    return 0;
}