#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
void loadsave();
void save();
void command_interpreter();
void startmenu();
void menu();
void leveler();
void skilltree();
void transform();
void workoutplanner();
int levelerhandler();
void detransform(int a);
// Global Variables
//--Stats
int intelligence;
int transform_intelligence;
int wisdom;
int transform_wisdom;
int strength;
int transform_strength;
int endurance;
int transform_endurance;
int agility;
int transform_agility;
int level;
int skillpoints;
//--Counters
int workout_counter;
int consistency_counter;
int projects_finished;
int tl = 0;
//--profile
char name[10];
char sex[10];
char race[20];
char class[30];
char skills[26];
char transformation[20];

int main()
{
    startmenu();
}

// utility Functions
void loadsave() // loads character
{
    // open the file as read and put it in a string
    FILE *pF = fopen("save.txt", "rgt");
    if (pF == NULL)
    {
        printf("Make a character first\n");
        startmenu();
    }
    else
    {
        char buffer[255];
        fread(buffer, 1, 255, pF);
        // Extract the first token
        char *token = strtok(buffer, ",");
        // loop through the string to extract all other tokens and assign them to their proper stats
        for (int i = 0; i <= 17; i += 1)
        {
            if (token != NULL)
            {
                switch (i)
                {
                case 0:
                    intelligence = atoi(token); // atoi casts the values stored in char form to integers
                    transform_intelligence = atoi(token);
                    break;
                case 1:
                    wisdom = atoi(token);
                    transform_wisdom = atoi(token);
                    break;
                case 2:
                    strength = atoi(token);
                    transform_strength = atoi(token);
                    break;
                case 3:
                    endurance = atoi(token);
                    transform_endurance = atoi(token);
                    break;
                case 4:
                    agility = atoi(token);
                    transform_agility = atoi(token);
                    break;
                case 5:
                    level = atoi(token);
                    break;
                case 6:
                    skillpoints = atoi(token);
                    break;
                case 7:
                    workout_counter = atoi(token);
                    break;
                case 8:
                    consistency_counter = atoi(token);
                    break;
                case 9:
                    projects_finished = atoi(token);
                    break;
                case 10:
                    strcpy(name, token); // use this to assign the token to the array of characters
                    break;
                case 11:
                    strcpy(sex, token);
                    break;
                case 12:
                    strcpy(race, token);
                    break;
                case 13:
                    strcpy(class, token);
                    break;
                case 14:
                    strcpy(skills, token);
                    break;
                }
                token = strtok(NULL, ",");
            }
        }
        strcpy(transformation, "None    ");
        fclose(pF);
    }
}
void save() // saves character
{
    FILE *pF = fopen("save.txt", "w");
    if (pF == NULL)
    {
        printf("No save found!\n");
    }
    else
    {
        fprintf(pF, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s", intelligence, wisdom, strength, endurance, agility, level, skillpoints, workout_counter, consistency_counter, projects_finished, name, sex, race, class, skills);
        fclose(pF);
    }
}

// cli functions
void startmenu()
{
    while (1)
    {
        // First few variables
        char choice[5];
        // Print menu
        printf("Welcome to LIFE RPG");
        printf("\n-Play");
        printf("\n-New");
        printf("\n-Exit\n");
        scanf("%s", &choice);
        // Take in users choice and compare
        if (strcmp(choice, "play") == 0 || strcmp(choice, "p") == 0)
        {
            // Load save, Start RPG
            loadsave();
            command_interpreter();
        }
        else if (strcmp(choice, "exit") == 0 || strcmp(choice, "e") == 0)
        {
            break;
        }
        else if (strcmp(choice, "new") == 0 || strcmp(choice, "n"))
        {

            printf("!!!!!!!!!Are you sure!!!!!!!!!");
            scanf("%s", &choice);
            if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 0)
            {
                // open a file and initialize values
                FILE *pF = fopen("save.txt", "w");
                intelligence = 5;
                transform_intelligence = 5;
                wisdom = 5;
                transform_wisdom = 5;
                strength = 5;
                transform_strength = 5;
                endurance = 5;
                transform_endurance = 5;
                agility = 5;
                transform_agility = 5;
                level = 1;
                skillpoints = 0;
                workout_counter = 0;
                consistency_counter = 0;
                projects_finished = 0;
                printf("What is your name?: ");
                scanf("%s", &name);
                printf("What is your sex?: ");
                scanf("%s", &sex);
                printf("What is your class?: ");
                printf("\n1. Mage \n");
                scanf("%s", &class);
                strcpy(race, "Human             ");
                strcpy(transformation, "None    ");
                strcpy(skills, "100000");
                // save initial values to file
                fprintf(pF, "5,5,5,5,5,0,0,0,0,0,%s,%s,Human             ,%s             ,100000", name, sex, class);
                fclose(pF);
                // Start RPG
                command_interpreter();
            }
        }
    }
}
void menu()
{
    printf("\n---------------------MENU---------------------");
    printf("\nInformation");
    printf("\nName: %s             | Intelligence: %d", name, transform_intelligence);
    printf("\nSex: %s               | Wisdom: %d", sex, transform_wisdom);
    printf("\nRace: %s| Strength: %d", race, transform_strength);
    printf("\nClass: %s| Agility: %d", class, transform_agility);
    printf("\nTransformation: %s| Endurance: %d", transformation, transform_endurance);
    printf("\n----------------------------------------------");
    printf("\nProjects finished: %d Workouts Completed: %d", projects_finished, workout_counter);
    printf("\nConsistency Counter: %d Skillpoints: %d", consistency_counter, skillpoints);
    printf("\n----------------------------------------------");
}
void command_interpreter() // Takes in commands for gameplay
{
    while (1)
    {

        char command[30];
        printf("\nEnter a command: ");
        scanf("%s", &command);
        if (strcmp(command, "help") == 0 || strcmp(command, "h") == 0)
        {
            printf("ACTIONS:");
            printf("\nhelp or h");
            printf("\nexit or e");
            printf("\nsave or s");
            printf("\nmenu or m");
            printf("\nstart menu or sm");
            printf("\nskill tree or st");
            printf("\nworkout plan or wp");
            printf("\nproject complete or pc");
            printf("\nworkout complete or wc");
            printf("\nconsistency or cc");
            if (level >= 3)
            {
                printf("\ntransform or tf");
                printf("\ndetransform or dtf");
            }
        }
        else if (strcmp(command, "save") == 0 || strcmp(command, "s") == 0)
        {
            save();
        }
        else if (strcmp(command, "exit") == 0 || strcmp(command, "e") == 0)
        {
            char answer[10];
            printf("Would you like to save first?: ");
            scanf("%s", &answer);
            if (strcmp(answer, "yes") == 0 | strcmp(answer, "y") == 0)
            {
                save();
                break;
            }
            else
            {
                break;
            }
        }
        else if (strcmp(command, "project complete") == 0 || strcmp(command, "pc") == 0)
        {
            while (1)
            {
                char attrib[12];
                int points_to_add;
                printf("Focus which Stats?\n1.Intelligence\n1.Wisdom\n1.Agility\n1.Endurance\n1.Strength\n");
                scanf("%s", &attrib);
                // use traits here
                if (skills[1] == '1')
                {
                    points_to_add = 5;
                }
                else if (skills[1] == '2')
                {
                    points_to_add = 10;
                }
                else if (skills[1] == '3')
                {
                    points_to_add = 20;
                }
                else if (skills[1] == '4')
                {
                    points_to_add = 40;
                }
                else if (skills[1] == '5')
                {
                    points_to_add = 60;
                }
                else if (skills[1] == '6')
                {
                    points_to_add = 80;
                }
                else
                {
                    points_to_add += 5;
                }

                // Stat Choosing
                if (strcmp(attrib, "intelligence") == 0 || strcmp(command, "i") == 0)
                {
                    intelligence += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "wisdom") == 0 || strcmp(attrib, "w") == 0)
                {
                    wisdom += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "agility") == 0 || strcmp(attrib, "a") == 0)
                {
                    agility += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "endurance") == 0 || strcmp(attrib, "e") == 0)
                {
                    endurance += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "strength") == 0 || strcmp(attrib, "s") == 0)
                {
                    strength += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
            }
            projects_finished += 1;
            leveler();
        }
        else if (strcmp(command, "workout complete") == 0 || strcmp(command, "wc") == 0)
        {
            while (1)
            {
                char attrib[12];
                int points_to_add;
                printf("Focus which Stats?\n1.Intelligence\n1.Wisdom\n1.Agility\n1.Endurance\n1.Strength\n");
                scanf("%s", &attrib);
                // use traits here
                if (skills[3] == '1')
                {
                    points_to_add = 5;
                }
                else if (skills[3] == '2')
                {
                    points_to_add = 10;
                }
                else if (skills[3] == '3')
                {
                    points_to_add = 20;
                }
                else if (skills[3] == '4')
                {
                    points_to_add = 40;
                }
                else if (skills[3] == '5')
                {
                    points_to_add = 60;
                }
                else if (skills[3] == '6')
                {
                    points_to_add = 80;
                }
                else
                {
                    points_to_add += 5;
                }

                // Stat Choosing
                if (strcmp(attrib, "intelligence") == 0 || strcmp(attrib, "i") == 0)
                {
                    intelligence += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "wisdom") == 0 || strcmp(attrib, "w") == 0)
                {
                    wisdom += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "agility") == 0 || strcmp(attrib, "a") == 0)
                {
                    agility += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "endurance") == 0 || strcmp(attrib, "e") == 0)
                {
                    endurance += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "strength") == 0 || strcmp(attrib, "s") == 0)
                {
                    strength += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
            }
            workout_counter += 1;
            leveler();
        }
        else if (strcmp(command, "consistency") == 0 || strcmp(command, "cc") == 0)
        {
            while (1)
            {
                char attrib[12]; // consistency_counter += 1;
                int points_to_add;

                printf("Focus which Stats?\n1.Intelligence\n1.Wisdom\n1.Agility\n1.Endurance\n1.Strength\n");
                scanf("%s", &attrib);
                // use traits here
                if (skills[2] == '1')
                {
                    points_to_add = 5;
                }
                else if (skills[2] == '2')
                {
                    points_to_add = 10;
                }
                else if (skills[2] == '3')
                {
                    points_to_add = 20;
                }
                else if (skills[2] == '4')
                {
                    points_to_add = 40;
                }
                else if (skills[2] == '5')
                {
                    points_to_add = 60;
                }
                else if (skills[2] == '6')
                {
                    points_to_add = 80;
                }
                else
                {
                    points_to_add += 5;
                }

                // Stat Choosing
                if (strcmp(attrib, "intelligence") == 0 || strcmp(attrib, "i") == 0)
                {
                    intelligence += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "wisdom") == 0 || strcmp(attrib, "w") == 0)
                {
                    wisdom += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "agility") == 0 || strcmp(attrib, "a") == 0)
                {
                    agility += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "endurance") == 0 || strcmp(attrib, "e") == 0)
                {
                    endurance += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
                else if (strcmp(attrib, "strength") == 0 || strcmp(attrib, "s") == 0)
                {
                    strength += points_to_add;
                    // the way to handle adding attributes while transformed
                    detransform(0);
                    break;
                }
            }
            consistency_counter += 1;
            leveler();
        }
        else if (strcmp(command, "transform") == 0 || strcmp(command, "tf") == 0)
        {
            transform();
        }
        else if (strcmp(command, "detransform") == 0 || strcmp(command, "dtf") == 0)
        {
            detransform(0);
        }
        else if (strcmp(command, "workout plan") == 0 || strcmp(command, "wp") == 0)
        {
            workoutplanner();
        }
        else if (strcmp(command, "skill tree") == 0 || strcmp(command, "st") == 0)
        {
            skilltree();
        }
        else if (strcmp(command, "menu") == 0 || strcmp(command, "m") == 0)
        {
            menu();
        }
        else if (strcmp(command, "start menu") == 0 || strcmp(command, "sm") == 0)
        {
            startmenu();
        }
    }
}

// RpgFunctions
void workoutplanner()
{ // used for workout managment
    while (1)
    {
        char command[15];
        printf("\nEnter a Command for workout planner: ");
        scanf("%s", &command);
        if (strcmp(command, "help") == 0 || strcmp(command, "h") == 0)
        {
            printf("ACTIONS:");
            printf("\nhelp or h");
            printf("\ncreate new or cn");
            printf("\nprint workout or pw");
            printf("\ncreate routine or cr");
            printf("\ncreate header or ch");
            printf("\nexit or e");
        }
        else if (strcmp(command, "create routine") == 0 || strcmp(command, "cr") == 0)
        {
            FILE *pF = fopen("workout.txt", "a");
            if (pF == NULL)
            {
                printf("Make a workout first");
            }
            else
            {
                fclose(pF);
                while (1)
                {
                    char command[50];
                    printf("Add Exercise(yes or no):");
                    scanf("%s", &command);
                    if (strcmp(command, "yes") == 0 || strcmp(command, "y") == 0)
                    {
                        FILE *pF = fopen("workout.txt", "a");
                        printf("Format, Exercise|sets|reps):");
                        scanf("%s", &command);
                        fprintf(pF, "    %s\n", command);
                        fclose(pF);
                    }
                    else if (strcmp(command, "no") == 0 || strcmp(command, "n") == 0)
                    {
                        printf("Done!\n");
                        break;
                    }
                }
            }
        }
        else if (strcmp(command, "exit") == 0 || strcmp(command, "e") == 0)
        {
            break;
            command_interpreter();
        }
        else if (strcmp(command, "create header") == 0 || strcmp(command, "ch") == 0)
        {

            FILE *pF = fopen("workout.txt", "a");
            if (pF == NULL)
            {
                printf("Make a workout first");
            }
            else
            {
                char plan_header[50];
                printf("Workout Header(---- for subheader, --for sub title): ");
                scanf("%s", &plan_header);
                fprintf(pF, "%s\n", plan_header);
                fclose(pF);
            }
        }
        else if (strcmp(command, "create new") == 0 || strcmp(command, "cn") == 0)
        {

            if (remove("workout.txt") == 0)
            {
                char plan_header[50];
                FILE *pF = fopen("workout.txt", "w");
                printf("Workout Header: ");
                scanf("%s", &plan_header);
                fprintf(pF, "%s\n", plan_header);
                fclose(pF);
            }
            else
            {
                printf("\nno new file created");
            }
        }
        else if (strcmp(command, "print workout") == 0 || strcmp(command, "pw") == 0)
        {
            FILE *pF = fopen("workout.txt", "r");
            char buffer[255];
            if (pF == NULL)
            {
                printf("Unable to open file!\n");
            }
            else
            {
                printf("Workout plan: Sets, Reps\n");
                while (fgets(buffer, 255, pF) != NULL)
                {
                    printf("%s", buffer);
                }
                fclose(pF);
            }
        }
    }
    command_interpreter();
}
void skilltree()
{
    printf("            |-----------Training Adept(0)-------------|");
    printf("            |                  |                      |");
    printf("      Consistency(4)  Working Out adept(1)  Project Management(7)");
    printf("            |                  |                      |  ");
    printf("      Consistency(5)  Working Out adept(2)  Project Management(8)");
    printf("            |                  |                      |");
    printf("      Consistency(6)  Working Out adept(3)  Project Management(9)");
    if (level > 10)
    {
        printf("            |                  |                      |       ");
        printf("      Consistency(10) Working Out adept(11) Project Management(12)");
        printf("            |                  |                      |       ");
        printf("      Consistency(13) Working Out adept(14) Project Management(15)");
        if (level > 15)
        {
            printf("            |                  |                      |       ");
            printf("      Consistency(16) Working Out adept(17) Project Management(18)");
        }
    }
    char choice[3];
    int point_spend;
    printf("Would you like to spend a point: ");
    scanf("%s", &choice);
    if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 0)
    {
        printf("What would you like to spend the point on?: ");
        scanf("%d", &point_spend);
        if (skillpoints == 0)
        {
            printf("No points to spend");
        }
        else if (point_spend > 9 && level <= 10)
        {
            printf("This does not Exist");
        }
        else if (point_spend > 15 && level <= 15)
        {
            printf("This does not Exist");
        }
        else if (point_spend > 20 && level <= 20)
        {
            printf("This does not Exist");
        }
        else
        {
            // handle projects skill spending
            if (point_spend == 7 && skills[1] == '0')
            {
                skillpoints -= 1;
                skills[1] = '1';
            }
            else if (point_spend == 8 && skills[1] == '1')
            {
                skillpoints -= 1;
                skills[1] = '2';
            }
            else if (point_spend == 9 && skills[1] == '2')
            {
                skillpoints -= 1;
                skills[1] = '3';
            }
            else if (point_spend == 12 && skills[1] == '3')
            {
                skillpoints -= 1;
                skills[1] = '4';
            }
            else if (point_spend == 15 && skills[1] == '4')
            {
                skillpoints -= 1;
                skills[1] = '5';
            }
            else if (point_spend == 18 && skills[1] == '5')
            {
                skillpoints -= 1;
                skills[1] = '6';
            }
            // handle consistency skill spending
            if (point_spend == 4 && skills[2] == '0')
            {
                skillpoints -= 1;
                skills[2] = '1';
            }
            else if (point_spend == 5 && skills[2] == '1')
            {
                skillpoints -= 1;
                skills[2] = '2';
            }
            else if (point_spend == 6 && skills[2] == '2')
            {
                skillpoints -= 1;
                skills[2] = '3';
            }
            else if (point_spend == 10 && skills[2] == '3')
            {
                skillpoints -= 1;
                skills[2] = '4';
            }
            else if (point_spend == 13 && skills[2] == '4')
            {
                skillpoints -= 1;
                skills[2] = '5';
            }
            else if (point_spend == 16 && skills[2] == '5')
            {
                skillpoints -= 1;
                skills[2] = '6';
            }
            // handle workout skill spending
            if (point_spend == 1 && skills[3] == '0')
            {
                skillpoints -= 1;
                skills[3] = '1';
            }
            else if (point_spend == 2 && skills[3] == '1')
            {
                skillpoints -= 1;
                skills[3] = '2';
            }
            else if (point_spend == 3 && skills[3] == '2')
            {
                skillpoints -= 1;
                skills[3] = '3';
            }
            else if (point_spend == 11 && skills[3] == '3')
            {
                skillpoints -= 1;
                skills[3] = '4';
            }
            else if (point_spend == 14 && skills[3] == '4')
            {
                skillpoints -= 1;
                skills[3] = '5';
            }
            else if (point_spend == 17 && skills[3] == '5')
            {
                skillpoints -= 1;
                skills[3] = '6';
            }
        }
    }
    command_interpreter();
}
void detransform(int a)
{
    if (a == 1)
    {
        transform_agility = agility;
        transform_intelligence = intelligence;
        transform_wisdom = wisdom;
        transform_endurance = endurance;
        transform_strength = strength;
    }
    else
    {
        transform_agility = agility;
        transform_intelligence = intelligence;
        transform_wisdom = wisdom;
        transform_endurance = endurance;
        transform_strength = strength;
        tl = 0;
        strcpy(transformation, "None    ");
    }
}
void transform()
{ // Handles transformations
    // mage transformations
    if (level >= 3 && tl == 0)
    {
        transform_agility *= 2.5;
        transform_intelligence *= 2.5;
        transform_wisdom *= 2.5;
        transform_endurance *= 2.5;
        transform_strength *= 2.5;
        tl += 1;
        strcpy(transformation, "Ascended");
    }
    else if (level >= 6 && tl == 1)
    {
        // detransform first
        detransform(1);

        transform_agility *= 5;
        transform_intelligence *= 5;
        transform_wisdom *= 5;
        transform_endurance *= 5;
        transform_strength *= 5;
        tl += 1;
        strcpy(transformation, "Ascend 1");
    }
    else if (level >= 10 && tl == 2)
    {
        // detransform first
        detransform(1);

        transform_agility *= 10;
        transform_intelligence *= 10;
        transform_wisdom *= 10;
        transform_endurance *= 10;
        transform_strength *= 10;
        tl += 1;
        strcpy(transformation, "Ascend 2");
    }
    else if (level >= 11 && tl == 3)
    {
        // detransform first
        detransform(1);

        transform_agility *= 25;
        transform_intelligence *= 25;
        transform_wisdom *= 25;
        transform_endurance *= 25;
        transform_strength *= 25;
        tl += 1;
        strcpy(transformation, "Ascend 3");
    }
    else if (level >= 15 && tl == 4)
    {
        // detransform first
        detransform(1);

        transform_agility *= 50;
        transform_intelligence *= 50;
        transform_wisdom *= 50;
        transform_endurance *= 50;
        transform_strength *= 50;
        tl += 1;
        strcpy(transformation, "Ascend 4");
    }
    else if (level >= 16 && tl == 5)
    {
        // detransform first
        detransform(1);

        transform_agility *= 100;
        transform_intelligence *= 100;
        transform_wisdom *= 100;
        transform_endurance *= 100;
        transform_strength *= 100;
        tl += 1;
        strcpy(transformation, "Ascend 5");
    }
    else if (level >= 19 && tl == 6)
    {
        // detransform first
        detransform(1);

        transform_agility *= 500;
        transform_intelligence *= 500;
        transform_wisdom *= 500;
        transform_endurance *= 500;
        transform_strength *= 500;
        tl += 1;
        strcpy(transformation, "Ascend 6");
    }
    else if (level >= 20 && tl == 7)
    {
        // detransform first
        detransform(1);

        transform_agility *= 1000;
        transform_intelligence *= 1000;
        transform_wisdom *= 1000;
        transform_endurance *= 1000;
        transform_strength *= 1000;
        tl += 1;
        strcpy(transformation, "Ascend ?");
    }
    command_interpreter();
}
int levelerhandler()
{
    char choice[10];
    printf("Would you like to level up?: ");
    scanf("%s", &choice);
    if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 1)
    {
        return 1;
    }
}
void leveler()
{
    // will handle skills points and threshhold changes in leveler
    if (level == 0 && agility >= 15 && intelligence >= 25 && wisdom >= 25 && strength >= 15 && endurance >= 15)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 25 && intelligence >= 40 && wisdom >= 40 && strength >= 25 && endurance >= 25)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 1)     ");
            }
            else if (agility >= 15 && intelligence >= 25 && wisdom >= 25 && strength >= 15 && endurance >= 15)
            {
                skillpoints += 1;
                level += 1;
            }
        }
    }

    else if (level == 1 && agility >= 25 && intelligence >= 50 && wisdom >= 50 && strength >= 25 && endurance >= 25)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 35 && intelligence >= 75 && wisdom >= 75 && strength >= 35 && endurance >= 35 && strcmp(class, "Mage(Rank 1)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 2)     ");
            }
            else if (agility >= 25 && intelligence >= 50 && wisdom >= 50 && strength >= 25 && endurance >= 25)
            {
                strcpy(class, "Mage(Rank 1)     ");
                skillpoints += 1;
                level += 1;
            }
        }
    }
    else if (level == 2 && agility >= 35 && intelligence >= 75 && wisdom >= 75 && strength >= 35 && endurance >= 35)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 45 && intelligence >= 100 && wisdom >= 100 && strength >= 45 && endurance >= 45 && strcmp(class, "Mage(Rank 2)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 3)     ");
                strcpy(race, "Human(Evolved)    ");
            }
            else if (agility >= 35 && intelligence >= 75 && wisdom >= 75 && strength >= 35 && endurance >= 35)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 2)     ");
                strcpy(race, "Human(Evolved)    ");
            }
        }
    }
    else if (level == 3 && agility >= 80 && intelligence >= 200 && wisdom >= 200 && strength >= 80 && endurance >= 80)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 90 && intelligence >= 300 && wisdom >= 300 && strength >= 90 && endurance >= 90 && strcmp(class, "Mage(Rank 3)  ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 4)     ");
            }
            else if (agility >= 80 && intelligence >= 200 && wisdom >= 200 && strength >= 80 && endurance >= 80)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 3)     ");
            }
        }
    }
    else if (level == 4 && agility >= 90 && intelligence >= 300 && wisdom >= 300 && strength >= 90 && endurance >= 90)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 100 && intelligence >= 400 && wisdom >= 400 && strength >= 100 && endurance >= 100 && strcmp(class, "Mage(Rank 4)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 5)     ");
            }
            else if (agility >= 90 && intelligence >= 300 && wisdom >= 300 && strength >= 90 && endurance >= 90)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 4)     ");
            }
        }
    }
    else if (level == 5 && agility >= 100 && intelligence >= 400 && wisdom >= 400 && strength >= 100 && endurance >= 100)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 110 && intelligence >= 500 && wisdom >= 500 && strength >= 110 && endurance >= 110 && strcmp(class, "Mage(Rank 5)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 6)     ");
                strcpy(race, "Human(Ascended)   ");
            }
            else if (agility >= 100 && intelligence >= 400 && wisdom >= 400 && strength >= 100 && endurance >= 100)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 5)     ");
                strcpy(race, "Human(Ascended)   ");
            }
        }
    }

    else if (level == 6 && agility >= 200 && intelligence >= 1000 && wisdom >= 1000 && strength >= 200 && endurance >= 200)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 220 && intelligence >= 1200 && wisdom >= 1200 && strength >= 220 && endurance >= 220 && strcmp(class, "Mage(Rank 6)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 7)     ");
            }
            else if (agility >= 200 && intelligence >= 1000 && wisdom >= 1000 && strength >= 200 && endurance >= 200)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 6)     ");
            }
        }
    }
    else if (level == 7 && agility >= 220 && intelligence >= 1200 && wisdom >= 1200 && strength >= 220 && endurance >= 220)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 240 && intelligence >= 1400 && wisdom >= 1400 && strength >= 240 && endurance >= 240 && strcmp(class, "Mage(Rank 7)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 8)     ");
            }
            else if (agility >= 220 && intelligence >= 1200 && wisdom >= 1200 && strength >= 220 && endurance >= 220)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 7)     ");
            }
        }
    }
    else if (level == 8 && agility >= 240 && intelligence >= 1400 && wisdom >= 1400 && strength >= 240 && endurance >= 240)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 260 && intelligence >= 1600 && wisdom >= 1600 && strength >= 260 && endurance >= 260 && strcmp(class, "Mage(Rank 8)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 9)     ");
            }
            else if (agility >= 240 && intelligence >= 1400 && wisdom >= 1400 && strength >= 240 && endurance >= 240)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Peak)     ");
            }
        }
    }
    else if (level == 9 && agility >= 260 && intelligence >= 1600 && wisdom >= 1600 && strength >= 260 && endurance >= 260)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 280 && intelligence >= 1800 && wisdom >= 1800 && strength >= 280 && endurance >= 280 && strcmp(class, "Mage(Rank 9)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Mage(Rank 10)     ");
                strcpy(race, "Human(^^^^)       ");
                printf("You have reached the ^^^^ of the Human Race");
            }
            else if (agility >= 260 && intelligence >= 1600 && wisdom >= 1600 && strength >= 260 && endurance >= 260)
            {
                skillpoints += 1;
                level += 1;
                strcpy(race, "Human(Peak)       ");
                printf("You have reached the Peak of the Human Race");
            }
        }
    }
    else if (level == 10 && agility >= 400 && intelligence >= 3000 && wisdom >= 3000 && strength >= 400 && endurance >= 400 && strcmp(class, "Mage(Rank 10)     ") == 0 && strcmp(race, "Human(^^^^)       ") == 0)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 450 && intelligence >= 3500 && wisdom >= 3500 && strength >= 450 && endurance >= 450)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage     ");
                strcpy(race, "Demi God          ");
            }
            else if (agility >= 400 && intelligence >= 3000 && wisdom >= 3000 && strength >= 400 && endurance >= 400)
            {
                skillpoints += 1;
                level += 1;
                strcpy(race, "Demi God          ");
            }
        }
    }
    else if (level == 11 && agility >= 450 && intelligence >= 3500 && wisdom >= 3500 && strength >= 450 && endurance >= 450)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 500 && intelligence >= 4000 && wisdom >= 4000 && strength >= 500 && endurance >= 500 && strcmp(class, "Ascetic Mage(R1) ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R2) ");
            }
            else if (agility >= 430 && intelligence >= 3500 && wisdom >= 3500 && strength >= 430 && endurance >= 430)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage     ");
            }
        }
    }
    else if (level == 12 && agility >= 500 && intelligence >= 4000 && wisdom >= 4000 && strength >= 500 && endurance >= 500)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 550 && intelligence >= 4500 && wisdom >= 4500 && strength >= 550 && endurance >= 550 && strcmp(class, "Ascetic Mage(R2) ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R3) ");
            }
            else if (agility >= 460 && intelligence >= 4000 && wisdom >= 4000 && strength >= 460 && endurance >= 460)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R1) ");
            }
        }
    }
    else if (level == 13 && agility >= 500 && intelligence >= 4500 && wisdom >= 4500 && strength >= 500 && endurance >= 500)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 600 && intelligence >= 5000 && wisdom >= 5000 && strength >= 600 && endurance >= 600 && strcmp(class, "Ascetic Mage(R3) ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R4) ");
            }
            else if (agility >= 500 && intelligence >= 4500 && wisdom >= 4500 && strength >= 500 && endurance >= 500)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R2) ");
            }
        }
    }
    else if (level == 14 && agility >= 550 && intelligence >= 5000 && wisdom >= 5000 && strength >= 550 && endurance >= 550)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 650 && intelligence >= 5500 && wisdom >= 5500 && strength >= 650 && endurance >= 650 && strcmp(class, "Ascetic Mage(R4) ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage(R5) ");
            }
            else if (agility >= 550 && intelligence >= 5000 && wisdom >= 5000 && strength >= 550 && endurance >= 550)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Ascetic Mage Peak");
                printf("You have reached the Peak of the world");
            }
        }
    }
    else if (level == 15 && agility >= 750 && intelligence >= 7500 && wisdom >= 7500 && strength >= 750 && endurance >= 750 && strcmp(class, "Ascetic Mage(R5) ") == 0)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 850 && intelligence >= 8500 && wisdom >= 8500 && strength >= 850 && endurance >= 850)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "God Mage         ");
                strcpy(race, "God               ");
            }
            else if (agility >= 750 && intelligence >= 7500 && wisdom >= 7500 && strength >= 750 && endurance >= 750)
            {
                skillpoints += 1;
                level += 1;
                strcpy(race, "God               ");
            }
        }
    }
    else if (level == 16 && agility >= 850 && intelligence >= 8500 && wisdom >= 8500 && strength >= 850 && endurance >= 850)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 950 && intelligence >= 10000 && wisdom >= 10000 && strength >= 950 && endurance >= 950 && strcmp(class, "God Mage         ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "God Mage(R1)     ");
            }
            else if (agility >= 850 && intelligence >= 8500 && wisdom >= 8500 && strength >= 850 && endurance >= 850)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "God Mage         ");
            }
        }
    }
    else if (level == 17 && agility >= 950 && intelligence >= 10000 && wisdom >= 10000 && strength >= 950 && endurance >= 950)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 1000 && intelligence >= 11000 && wisdom >= 11000 && strength >= 1000 && endurance >= 1000 && strcmp(class, "God Mage(R1)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "God Mage(R2)     ");
            }
            else if (agility >= 950 && intelligence >= 10000 && wisdom >= 10000 && strength >= 950 && endurance >= 950)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "God Mage(R1)     ");
            }
        }
    }
    else if (level == 18 && agility >= 1500 && intelligence >= 17700 && wisdom >= 17500 && strength >= 1500 && endurance >= 1500)
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 25 && intelligence >= 40 && wisdom >= 40 && strength >= 25 && endurance >= 25 && strcmp(class, "God Mage(R2)     ") == 0)
            {
                skillpoints += 1;
                level += 1;
                printf("There is nothing higher");
                strcpy(class, "God Mage(R3)     ");
                strcpy(race, "Lord of Gods      ");
            }
            else if (agility >= 15 && intelligence >= 25 && wisdom >= 25 && strength >= 15 && endurance >= 15)
            {
                skillpoints += 1;
                level += 1;
                strcpy(class, "Eternal Mage     ");
                strcpy(race, "Lord of Gods      ");
            }
        }
    }
    else if (level == 19 && agility >= 15 && intelligence >= 25 && wisdom >= 25 && strength >= 15 && endurance >= 15 && strcmp(class, "God Mage(R3)     ") == 0) // Special requirements for this one
    {
        if (levelerhandler() == 1)
        {
            if (agility >= 25 && intelligence >= 40 && wisdom >= 40 && strength >= 25 && endurance >= 25)
            {
                skillpoints += 3;
                level += 1;
                strcpy(class, "Nothing Higher   ");
                strcpy(race, "You don't exist  ");
                printf("The only thing that truly matters is what you make matter");
                // maybey add starfield type system
            }
        }

        command_interpreter();
    }
}