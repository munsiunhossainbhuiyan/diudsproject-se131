#include <stdio.h>
#include <string.h>

#define MAX_SEATS 50
#define MAX_NAME 50
#define TRAINS 2

// Train data
int train_nos[] = {12345, 12346};
char train_names[TRAINS][MAX_NAME] = {"Superfast Express", "Suborno Express"};
char train_from[TRAINS][MAX_NAME] = {"Dhaka", "Dhaka"};
char train_to[TRAINS][MAX_NAME] = {"Chittagong", "Chittagong"};

// Seat availability and passenger info
int sleeper[TRAINS][MAX_SEATS] = {{0}}, ac[TRAINS][MAX_SEATS] = {{0}};
char sName[TRAINS][MAX_SEATS][MAX_NAME], aName[TRAINS][MAX_SEATS][MAX_NAME];
char sPhone[TRAINS][MAX_SEATS][MAX_NAME], aPhone[TRAINS][MAX_SEATS][MAX_NAME];
int sBooked[TRAINS] = {0}, aBooked[TRAINS] = {0};

int priceS = 100, priceA = 250;

// Shows list of trains
void showTrains() {
    printf("\nAvailable Trains:\nNo\tName\t\t\tFrom\t\tTo\t\tSeats\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < TRAINS; i++)
        printf("%d\t%-20s%-15s%-15s%d\n", train_nos[i], train_names[i], train_from[i], train_to[i], MAX_SEATS * 2);
}

// Finds train index from number
int getIndex(int no) {
    for (int i = 0; i < TRAINS; i++)
        if (train_nos[i] == no) return i;
    return -1;
}

// Shows seat status for given train
void showSeats(int i) {
    printf("\nTrain: %s (%d)\nSleeper Available: %d\nAC Available: %d\n", train_names[i], train_nos[i], MAX_SEATS - sBooked[i], MAX_SEATS - aBooked[i]);

    // Sleeper seats display
    printf("\nS Class Seats (* = Booked):\n");
    for (int j = 0; j < MAX_SEATS; j++) {
        printf("%3d%s ", j + 1, sleeper[i][j] ? "*" : "");
        if ((j + 1) % 10 == 0) printf("\n");
    }

    // AC seats display
    printf("\n\nA Class Seats (* = Booked):\n");
    for (int j = 0; j < MAX_SEATS; j++) {
        printf("%3d%s ", j + 1, ac[i][j] ? "*" : "");
        if ((j + 1) % 10 == 0) printf("\n");
    }
}

// Takes user input for name and phone
void getInfo(char name[], char ph[]) {
    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    getchar();
    printf("Enter your contact number: ");
    scanf(" %[^\n]", ph);
    getchar();
}

// Books a ticket and displays confirmation
int book(int seats[], char names[][MAX_NAME], char phones[][MAX_NAME], int *count, int s, char name[], char ph[], int price) {
    if (s < 1 || s > MAX_SEATS || seats[s - 1]) return 0;
    seats[s - 1] = 1;
    strcpy(names[s - 1], name);
    strcpy(phones[s - 1], ph);
    (*count)++;
    printf("Your ticket is booked.\nBooked seat: %d\nName: %s\nContact: %s\nPrice: Tk.%d\n", s, name, ph, price);
    return 1;
}

// Cancels a booked ticket
int cancel(int seats[], char names[][MAX_NAME], char phones[][MAX_NAME], int *count, int s) {
    if (s < 1 || s > MAX_SEATS || !seats[s - 1]) return 0;
    seats[s - 1] = 0;
    names[s - 1][0] = phones[s - 1][0] = 0;
    (*count)--;
    return 1;
}

// Main menu and operations
int main() {
    int ch, tNo, idx, seat;
    char cls, name[MAX_NAME], ph[MAX_NAME];
    do {
        // Main menu
        printf("\n--- Train Ticket Reservation ---\n1. Show Trains\n2. Seat Status\n3. Book Ticket\n4. Cancel Ticket\n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                // Display train list
                showTrains();
                break;

            case 2:
                // Show seat status
                printf("Enter Train Number: "); scanf("%d", &tNo);
                if ((idx = getIndex(tNo)) != -1) {
                    printf("\nTrain No: %d\nTrain Name: %s\nFrom: %s\nTo: %s\nClasses: Sleeper, AC\n", train_nos[idx], train_names[idx], train_from[idx], train_to[idx]);
                    printf("Sleeper: %d seats, Tk.%d per seat\nAC: %d seats, Tk.%d per seat\n", MAX_SEATS, priceS, MAX_SEATS, priceA);
                    showSeats(idx);
                } else printf("Invalid train number.\n");
                break;

            case 3:
                // Book ticket
                printf("Enter Train Number: "); scanf("%d", &tNo);
                if ((idx = getIndex(tNo)) == -1) { printf("Train not found.\n"); break; }
                getInfo(name, ph);
                printf("Choose class (S/A): "); scanf(" %c", &cls);
                printf("Enter seat number (1-%d): ", MAX_SEATS); scanf("%d", &seat);
                if (cls == 'S' || cls == 's')
                    book(sleeper[idx], sName[idx], sPhone[idx], &sBooked[idx], seat, name, ph, priceS);
                else if (cls == 'A' || cls == 'a')
                    book(ac[idx], aName[idx], aPhone[idx], &aBooked[idx], seat, name, ph, priceA);
                else printf("Invalid class.\n");
                break;

            case 4:
                // Cancel ticket
                printf("Enter Train Number: "); scanf("%d", &tNo);
                if ((idx = getIndex(tNo)) == -1) { printf("Train not found.\n"); break; }
                printf("Enter class to cancel (S/A): "); scanf(" %c", &cls);
                printf("Enter seat number to cancel: "); scanf("%d", &seat);
                if ((cls == 'S' || cls == 's') && cancel(sleeper[idx], sName[idx], sPhone[idx], &sBooked[idx], seat))
                    printf("Seat %d cancelled.\n", seat);
                else if ((cls == 'A' || cls == 'a') && cancel(ac[idx], aName[idx], aPhone[idx], &aBooked[idx], seat))
                    printf("Seat %d cancelled.\n", seat);
                else printf("No booking found.\n");
                break;

            case 5:
                // Exit program
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 5);
    return 0;
}
