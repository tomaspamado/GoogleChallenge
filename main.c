#include <stdio.h>
#include <stdlib.h>

// Actor Structure Definition
typedef struct actor {
    int first_side;
    int second_side;
} Actor;

// Title Function
void Title() {
    printf("Across the River\n\n");
    printf("This code will get a fox, a chicken, and a sack \nof corn across a river without any mishaps.\n");
}

// Initialization Function
void Initialization(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person) {
    Chicken->first_side = 1;
    Chicken->second_side = 0;

    Fox->first_side = 1;
    Fox->second_side = 0;

    Corn->first_side = 1;
    Corn->second_side = 0;

    Person->first_side = 1;
    Person->second_side = 0;
}

// Valid State Test Function
int Test(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person) {
    if ((Chicken->first_side == Fox->first_side && Chicken->first_side != Person->first_side) ||
        (Chicken->first_side == Corn->first_side && Chicken->first_side != Person->first_side)) {
        return 0;
    }
    return 1;
}

// End State Test Function
int Test_end(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person) {
    return (Chicken->second_side == 1 && Fox->second_side == 1 && Corn->second_side == 1 && Person->second_side == 1);
}

// Print State Function
void PrintState(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person, int step) {
    printf("\n        |---------|--------------|--------------|");
    printf("\n        |  ACTOR  |  FIRST SIDE  |  SECOND SIDE |");
    printf("\n        |---------|--------------|--------------|");
    printf("\n        | Chicken |       %d      |       %d      |", Chicken->first_side, Chicken->second_side);
    printf("\nSTEP %d  |   Fox   |       %d      |       %d      |", step, Fox->first_side, Fox->second_side);
    printf("\n        |   Corn  |       %d      |       %d      |", Corn->first_side, Corn->second_side);
    printf("\n        | Person  |       %d      |       %d      |", Person->first_side, Person->second_side);
    printf("\n        |---------|--------------|--------------|\n");
}

// Move Actor Function
void moveActor(Actor *Person, Actor *Chicken, Actor *Fox, Actor *Corn, int i) {
    int direction;

    if (Person->first_side == 1) {
        direction = 0;
    } else {
        direction = 1;
    }

    if (i == 0) {
        Person->first_side = direction;
        Person->second_side = 1 - direction;
    } else if (i == 1 && Chicken->first_side == Person->first_side) {
        Chicken->first_side = direction;
        Chicken->second_side = 1 - direction;
        Person->first_side = direction;
        Person->second_side = 1 - direction;
    } else if (i == 2 && Fox->first_side == Person->first_side) {
        Fox->first_side = direction;
        Fox->second_side = 1 - direction;
        Person->first_side = direction;
        Person->second_side = 1 - direction;
    } else if (i == 3 && Corn->first_side == Person->first_side) {
        Corn->first_side = direction;
        Corn->second_side = 1 - direction;
        Person->first_side = direction;
        Person->second_side = 1 - direction;
    }
}

// State Encoding Function
int encodeState(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person) {
    return (Chicken->first_side << 3) | (Fox->first_side << 2) | (Corn->first_side << 1) | (Person->first_side);
}

// Depth-First Search Solver Function
int solve(Actor *Chicken, Actor *Fox, Actor *Corn, Actor *Person, int step, int visited[]) {
    if (Test_end(Chicken, Fox, Corn, Person)) {
        PrintState(Chicken, Fox, Corn, Person, step + 1);
        printf("\nSolution found!\n");
        return 1;
    }

    int state = encodeState(Chicken, Fox, Corn, Person);

    if (visited[state]) {
        return 0;
    }

    visited[state] = 1;

    PrintState(Chicken, Fox, Corn, Person, step + 1);

    for (int i = 0; i < 4; i++) {
        Actor ChickenBackup = *Chicken;
        Actor FoxBackup = *Fox;
        Actor CornBackup = *Corn;
        Actor PersonBackup = *Person;

        moveActor(Person, Chicken, Fox, Corn, i);

        if (Test(Chicken, Fox, Corn, Person)) {
            if (solve(Chicken, Fox, Corn, Person, step + 1, visited)) {
                return 1;
            }
        }

        *Chicken = ChickenBackup;
        *Fox = FoxBackup;
        *Corn = CornBackup;
        *Person = PersonBackup;
    }

    return 0;
}

// Main Function
int main() {
    Actor Chicken, Fox, Corn, Person;
    Initialization(&Chicken, &Fox, &Corn, &Person);

    Title();

    int visited[16] = {0};

    if (!solve(&Chicken, &Fox, &Corn, &Person, 0, visited)) {
        printf("\nNo solution found.\n");
    }

    return 0;
}
