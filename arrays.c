#include <stdio.h>
#include <string.h>

struct CustomerDetails {
    char username[50];
    char lastName[50];
    char email[100];
    char address[100];
    char phoneNumber[15];
};

struct Room {
    int roomNumber;
    int status; 
    int roomType;
    struct CustomerDetails customer;
    char checkInDate[15];
    char checkOutDate[15];
};

void bookRoom(struct Room *rooms, int roomType);
void viewCustomerDetails(struct Room *rooms, int roomNumber);
void editCustomerDetails(struct Room *rooms, int roomNumber);
void checkOut(struct Room *rooms, int roomNumber);
void viewReport(struct Room *rooms);

int findRoomIndex(struct Room *rooms, int roomNumber) {
    for (int i = 0; i < 20; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            return i;
        }
    }
    return -1; 
}

void bookRoom(struct Room *rooms, int roomType) {
    int roomNumber;
    printf("Normal Rooms: 1-10\nDeluxe Rooms: 11-20\n");
    printf("Enter the room number to book: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > 20) {
        printf("Invalid room number. Please enter a number between 1 and 20.\n");
        return;
    }

    int index = findRoomIndex(rooms, roomNumber);
    if (index != -1 && rooms[index].status == 0 && rooms[index].roomType == roomType) {

        rooms[index].status = 1; 
        rooms[index].roomType = roomType;

        // Input customer details
        printf("Enter customer details:\n");
        printf("Username: ");
        scanf("%s", rooms[index].customer.username);
        printf("Last Name: ");
        scanf("%s", rooms[index].customer.lastName);
        printf("Email Address: ");
        scanf("%s", rooms[index].customer.email);
        printf("Address: ");
        scanf("%s", rooms[index].customer.address);
        printf("Phone Number: ");
        scanf("%s", rooms[index].customer.phoneNumber);
        printf("Check-in Date (xx/xx/xx format): ");
        scanf("%s", rooms[index].checkInDate);
        printf("Check-out Date (xx/xx/xx format): ");
        scanf("%s", rooms[index].checkOutDate);

        printf("Room booked successfully.\n");
    } else {
        printf("Room already booked or not of the requested type.\n");
    }
}

void viewCustomerDetails(struct Room *rooms, int roomNumber) {
    if (roomNumber < 1 || roomNumber > 20) {
        printf("Invalid room number. Please enter a number between 1 and 20.\n");
        return;
    }

    int index = findRoomIndex(rooms, roomNumber);
    if (index != -1) {
        printf("Room Details for Room %d:\n", roomNumber);
        printf("Status: %s\n", (rooms[index].status == 1) ? "Booked" : "Vacant");

        if (rooms[index].status == 1) {
            printf("Customer Details:\n");
            printf("Username: %s\n", rooms[index].customer.username);
            printf("Last Name: %s\n", rooms[index].customer.lastName);
            printf("Email Address: %s\n", rooms[index].customer.email);
            printf("Address: %s\n", rooms[index].customer.address);
            printf("Phone Number: %s\n", rooms[index].customer.phoneNumber);
            printf("Check-in Date (xx/xx/xx format): %s\n", rooms[index].checkInDate);
            printf("Check-out Date (xx/xx/xx format): %s\n", rooms[index].checkOutDate);
        }
    } else {
        printf("Invalid room number.\n");
    }
}


void editCustomerDetails(struct Room *rooms, int roomNumber) {
    int index = findRoomIndex(rooms, roomNumber);
    if (index != -1) {
        if (rooms[index].status == 1) {
            printf("Editing customer details for Room %d:\n", roomNumber);
            printf("New Username: ");
            scanf("%s", rooms[index].customer.username);
            printf("New Last Name: ");
            scanf("%s", rooms[index].customer.lastName);
            printf("New Email Address: ");
            scanf("%s", rooms[index].customer.email);
            printf("New Address: ");
            scanf("%s", rooms[index].customer.address);
            printf("New Phone Number: ");
            scanf("%s", rooms[index].customer.phoneNumber);

            printf("Customer details updated successfully.\n");
        } else {
            printf("Room %d is vacant.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void checkOut(struct Room *rooms, int roomNumber) {
    int index = findRoomIndex(rooms, roomNumber);
    if (index != -1) {
        if (rooms[index].status == 1) {
            int roomType = rooms[index].roomType;
            int dayRate = (roomType == 0) ? 50 : 80;
            printf("Checking out Room %d...\n", roomNumber);
            printf("Customer Details:\n");
            printf("Username: %s\n", rooms[index].customer.username);
            printf("Last Name: %s\n", rooms[index].customer.lastName);
            printf("Email Address: %s\n", rooms[index].customer.email);
            printf("Address: %s\n", rooms[index].customer.address);
            printf("Phone Number: %s\n", rooms[index].customer.phoneNumber);
            printf("Check-in Date: %s\n", rooms[index].checkInDate);
            printf("Check-out Date: %s\n", rooms[index].checkOutDate);


            int daysStayed = 0;
            int checkInMonth, checkInDay, checkInYear;
            int checkOutMonth, checkOutDay, checkOutYear;
            sscanf(rooms[index].checkInDate, "%d/%d/%d", &checkInMonth, &checkInDay, &checkInYear);
            sscanf(rooms[index].checkOutDate, "%d/%d/%d", &checkOutMonth, &checkOutDay, &checkOutYear);

            daysStayed = (checkOutYear - checkInYear) * 365 +
                         (checkOutMonth - checkInMonth) * 30 +
                         (checkOutDay - checkInDay);

            int totalBill = daysStayed * dayRate;
            printf("Total Bill: $%d\n", totalBill);
            strcpy(rooms[index].customer.username, "N/A"); 
            strcpy(rooms[index].customer.lastName, "N/A");
            rooms[index].status = 0;
        } else {
            printf("Room %d is vacant.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void viewReport(struct Room *rooms) {
    printf("Room Report:\n");
    printf("%-10s%-10s%-12s%-15s%-15s\n", "Room No", "Status", "Room Type", "First Name", "Last Name");
    for (int i = 0; i < 20; i++) {
        printf("%-10d%-10s%-12s%-15s%-15s\n", rooms[i].roomNumber,
               (rooms[i].status == 1) ? "Reserved" : "Vacant",
               (rooms[i].roomType == 0) ? "Normal" : "Deluxe",
               rooms[i].customer.username, rooms[i].customer.lastName);
    }
}

int main() {
    struct Room rooms[20];
    for (int i = 0; i < 20; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].status = 0; 
        rooms[i].roomType = (i < 10) ? 0 : 1;
        strcpy(rooms[i].customer.username, "N/A"); 
        strcpy(rooms[i].customer.lastName, "N/A"); 
    }

    char choice;
    int numroom;  

    do {

        printf("\nHotel Management System Menu:\n");
        printf("Book a Room (B/b)\n");
        printf("View Customer Details (V/v)\n");
        printf("Edit Customer Details (E/e)\n");
        printf("Check-out and Print Bill (C/c)\n");
        printf("View Room Report (A/a)\n");
        printf("Exit Program (X/x)\n");
        printf("Enter your choice (B/V/E/C/A/X): ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'B':
            case 'b':
                bookRoom(rooms, 0);
                break;
            case 'V':
            case 'v':
                printf("Enter Room Number: ");
                scanf("%d", &numroom);
                viewCustomerDetails(rooms, numroom);
                break;
            case 'E':
            case 'e':
                printf("Enter Room Number: ");
                scanf("%d", &numroom);
                editCustomerDetails(rooms, numroom);
                break;
            case 'C':
            case 'c':
                printf("Enter Room Number: ");
                scanf("%d", &numroom);
                checkOut(rooms, numroom);
                break;
            case 'A':
            case 'a':
                viewReport(rooms);
                break;
            case 'X':
            case 'x':
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                fflush(stdin);
        }
    } while (choice != 'X' && choice != 'x');

    return 0;
}
