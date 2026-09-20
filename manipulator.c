#include  <stdio.h>// zrobic to ze pozycja targetu gdy jest podniesiony rowna sie pozycji manipulatora
#include <stdbool.h>
#define MAX_DEFINE_X 100 // nauczyc sie size_off
#define MAX_DEFINE_Y 50
int error_number = 0;// zaczac bawic sie plikiem main.h
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
int map[MAX_DEFINE_Y][MAX_DEFINE_X] = {0};
const Error_info error_infoo  [] =
{
    {1, "nie ma takiego wyboru\r\n"},
    {2, "nie ma takiego wyboru\r\n"},
    {3, "sensor nie wykrywa partu\r\n"},
    {4, "manipulator nie znajduje sie przy targecie\r\n"},
    {5, "nie ma zadnego targetu na mapie\r\n"},
    {6, "figurka nie trafila do magazynu\r\n"},
    {7, "nie podniosles manipulatorem figurki\r\n"},
    {8, "maksymalny x osiagniety nie mozna isc powyzej 100 \r\n"},
};

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
void (*struct_tabel[9])(Machine *);

void map_print(Machine *machine)
{
    for(int y = 0; y < MAX_DEFINE_Y; y++)
    {
        for(int x = 0; x < MAX_DEFINE_X; x++)
        {
            printf("[%d]", map[y][x]);
        }
        printf("\n");
    }
    machine->menu = STATE_MENU;
}
void move_y(Machine *machine)
{
    int move_y = 0;
    printf("o ile chcesz sie ruszyc w osi y");
    scanf("%d", &move_y);
    if(move_y > MAX_DEFINE_Y)
    {
        move_y = 0;
        error_number = 0;
        machine->menu = STATE_ERROR;
        struct_tabel[STATE_ERROR](machine);
    }
    machine->manipulator.position_y += move_y;
    machine->menu = STATE_MOVE;
    struct_tabel[machine->menu](machine);


}
void move_x(Machine *machine)
{
        int move_x = 0;
        printf("o ile chcesz sie ruszyc w pozycji x\r\n");
        scanf("%d", &move_x);
        if(move_x > MAX_DEFINE_X)
        {
            move_x = 0;
            error_number = 8;
            machine->menu = STATE_ERROR;
            struct_tabel[machine->menu](machine);

        }
        machine->manipulator.position_x += move_x;
        machine->menu = STATE_MOVE;
        struct_tabel[machine->menu](machine);
}
void move(Machine *machine)
{
    int what_to_do_move = 0;
    printf("w ktorej osi chcesz sie poruszyc 1.x 2.y 3.zakonczyc akcje");
    scanf("%d", &what_to_do_move);
    if(what_to_do_move == 1)
    {
        move_x(machine);
    }
    if(what_to_do_move == 2)
    {
        move_y(machine);
    }
    if(what_to_do_move == 3)
    {
        map[machine->manipulator.position_y][machine->manipulator.position_x] = 2;
        machine->menu = STATE_MENU;
        struct_tabel[machine->menu](machine);

    }

}
void settings(Machine *machine)
{
        int target_move_x = 0; 
        int target_move_y = 0;
        int what_to_do_settings = 0;
        printf("co chcesz zrobic\r\n"
        "1.ustawic pozycje targetu\r\n");
        scanf("%d", &what_to_do_settings);
        if(what_to_do_settings == 1)
        {
            printf("podaj pozycje x i y\r\n");
                scanf("%d", &target_move_x);
                scanf("%d", &target_move_y);
                if(target_move_x > MAX_DEFINE_X)
                {
                    target_move_x = 0;
                    error_number = 8;
                    machine->menu = STATE_ERROR;
                    struct_tabel[machine->menu](machine);
                }
                if(target_move_y > MAX_DEFINE_Y)
                {
                    target_move_y = 0;
                    error_number = 8;
                    machine->menu = STATE_ERROR;
                    struct_tabel[machine->menu](machine);
                }
                machine->target.position_y = target_move_y;
                machine->target.position_x = target_move_x;
                map[machine->target.position_y][machine->target.position_x] = 1;
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
        for(int i = 0; i < machine->error_count; i++)
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


void menu(Machine *machine)
{
        printf("co chcesz zrobic\r\n"
        "1.rusz manipulator\r\n"
        "2.sprawdz magazyn\r\n"
        "3.podniesc przedmiot\r\n"
        "4.przejdz do ustawien\r\n"
        "5.odloz figurke do magazynu\r\n"
        "6.sprawdzic status maszyny\r\n"
        "7.pokaz mape\n\r");
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
    struct_tabel[0] = menu;
    struct_tabel[1] = move;
    struct_tabel[2] = magazine;
    struct_tabel[3] = pick;
    struct_tabel[4] = settings;
    struct_tabel[5] = drop;
    struct_tabel[6] = status;
    struct_tabel[7] = map_print;
    struct_tabel[8] = error;
    Machine machine = {0};
    machine.error_count = sizeof(error_infoo) / sizeof(error_infoo[0]);
    machine.error_info = error_infoo;
    working_machine(&machine);
    return 0;
}