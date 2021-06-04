#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TotalLocations (sizeof(locs) / sizeof(*locs)) // Variable 'locs' is statically allocated, meaning the calculation is done when compiled

char enter = 0;
char player[10];
char input[100] = "look around";
unsigned PlayerLocation = 0;

struct location // Define a struct to represent a certain location
{
    const char *info; // Description of locations
    const char *tag;  // How location will be recognized by parser
} locs[] =
    {{"an open field", "field"},
     {"a little cave", "cave"}};

struct person
{
    char *name[10];
    int *age;
    struct player
    {
        struct person *name;
        struct person *age;
    } pla;
} per;

void Look(const char *noun)
{
    if (noun != NULL && strcmp(noun, "around") == 0)
    {
        printf("I am in %s.\n", locs[PlayerLocation].info);
    }
    else
    {
        printf("I don't know/understand what you'd like me to see.\n");
    }
}

void Go(const char *noun)
{
    unsigned loc;
    for (loc = 0; loc < TotalLocations; loc++)
    {
        if (noun != NULL && strcmp(noun, locs[loc].tag) == 0)
        {
            if (loc == PlayerLocation)
            {
                printf("You can't get much closer than this.\n");
            }
            else
            {
                PlayerLocation = loc;
                Look("around");
            }
            return;
        }
    }
    printf("I don't know/understand where you want me to go.\n");
}

bool ParseAndExecute(char *input)
{
    // Create basic verb & noun parser
    char *verb = strtok(input, " \n"); // strtok breaks string into series of tokens using delimiter(s)
    char *noun = strtok(NULL, " \n");  // NULL is first parameter so strtok splits the string from next token's starting position
    if (verb != NULL)                  // If player enters nothing or just spaces, nothing is done
    {
        // strcmp to match user input with some known verbs; case-sensitive
        if (strcmp(verb, "quit") == 0)
        {
            return false; // Ends program
        }
        else if (strcmp(verb, "look") == 0 || strcmp(verb, "check") == 0 || strcmp(verb, "search") == 0)
        {
            Look(noun);
        }
        else if (strcmp(verb, "go") == 0 || strcmp(verb, "move") == 0 || strcmp(verb, "walk") == 0 || strcmp(verb, "run") == 0)
        {
            Go(noun);
        }
        else
        {
            printf("\nI don't know how to '%s'.\n", verb);
        }
    }
    return true;
}

bool GetInput(void)
{
    printf("\nWhat should I do? ");                    // Prompt
    return fgets(input, sizeof(input), stdin) != NULL; // Get keyboard inputs
}

int main()
{
    struct person per;
    char buff[255];
    char *WordofGod[5][100];
    int i = 0, a = 0;
    FILE *fp = fopen("WordofGod.txt", "r");

    while (!feof(fp)) // Check entire text file
    {
        for (int i = 0; i < 5; i++)
        {
            fgets(buff, sizeof(buff), fp);        // Read strings in file
            *WordofGod[i] = malloc(sizeof(buff)); // Dynamically allocate memory
            strcpy(*WordofGod[i], buff);          // Copy strings to array
        }
    };

    printf("\n\t\t\tWelcome to Isekai Adventure!\n\n"); // Introduction
    printf("Please enter your name: ");
    scanf("%s", per.pla.name);
    fflush(stdin);
    printf("\n%s%s %s%s\n", per.pla.name, *WordofGod[0], per.pla.name, *WordofGod[0]);
    getchar();
    printf("%s", *WordofGod[1]);
    getchar();
    printf("%s", *WordofGod[2]);
    getchar();
    printf("%s", *WordofGod[3]);
    getchar();
    printf("%s %s%s\n\n", *WordofGod[4], per.pla.name, *WordofGod[0]);
    getchar();
    printf("Ugh. What was that voice? Where am I...?\n\n");
    getchar();
    while (ParseAndExecute(input) && GetInput()) // Main loop, calls functions until one returns false
        ;

    return 0;
}