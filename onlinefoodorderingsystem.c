#include <stdio.h>
#include <stdlib.h>

struct Food {
    int id;
    char name[50];
    float price;
};

struct Cart {
    char name[50];
    int qty;
    float price;
    float total;
};

void clearInput() {
    while(getchar() != '\n');
}

void saveBillToFile(float bill) {

    FILE *fp;

    fp = fopen("bill.txt", "a");

    if(fp == NULL) {
        printf("File could not be opened\n");
        return;
    }

    fprintf(fp, "Total Bill = %.2f\n", bill);

    fclose(fp);

    printf("Bill saved to file successfully\n");
}

void showMenu(struct Food f[], int n) {

    printf("\n------ MENU ------\n");

    for(int i = 0; i < n; i++) {
        printf("%d. %s - %.2f\n", f[i].id, f[i].name, f[i].price);
    }
}

float calculateCost(float price, int qty) {
    return price * qty;
}

float orderFood(struct Food f[], int n) {

    int choice, qty;
    float totalBill = 0;

    struct Cart cart[100];
    int cartCount = 0;

    while(1) {

        printf("\nEnter Food ID (0 to stop): ");

        if(scanf("%d", &choice) != 1) {
            printf("Invalid Input\n");
            clearInput();
            continue;
        }

        if(choice == 0)
            break;

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(f[i].id == choice) {

                found = 1;

                printf("Enter Quantity: ");

                if(scanf("%d", &qty) != 1) {
                    printf("Invalid Quantity\n");
                    clearInput();
                    break;
                }

                if(qty <= 0) {
                    printf("Quantity must be greater than 0\n");
                    break;
                }

                float itemTotal = calculateCost(f[i].price, qty);

                totalBill += itemTotal;

                cart[cartCount].qty = qty;
                cart[cartCount].price = f[i].price;
                cart[cartCount].total = itemTotal;

                sprintf(cart[cartCount].name, "%s", f[i].name);

                cartCount++;

                printf("%s added to cart\n", f[i].name);

                break;
            }
        }

        if(found == 0) {
            printf("Invalid Food ID\n");
        }
    }

    printf("\n------ CART ------\n");

    for(int i = 0; i < cartCount; i++) {

        printf("%s | Qty: %d | Price: %.2f | Total: %.2f\n",
               cart[i].name,
               cart[i].qty,
               cart[i].price,
               cart[i].total);
    }

    return totalBill;
}

void displayBill(float bill) {

    printf("\nTotal Bill = %.2f\n", bill);

    saveBillToFile(bill);
}

void viewSavedBills() {

    FILE *fp;

    char ch;

    fp = fopen("bill.txt", "r");

    if(fp == NULL) {
        printf("No bill records found\n");
        return;
    }

    printf("\n------ SAVED BILLS ------\n");

    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }

    fclose(fp);
}

void startSystem(struct Food menu[], int n) {

    int choice;
    float bill;

    while(1) {

        printf("\n1. Show Menu");
        printf("\n2. Order Food");
        printf("\n3. View Saved Bills");
        printf("\n4. Exit");
        printf("\nEnter Choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("Invalid Input\n");
            clearInput();
            continue;
        }

        switch(choice) {

            case 1:
                showMenu(menu, n);
                break;

            case 2:
                bill = orderFood(menu, n);
                displayBill(bill);
                break;

            case 3:
                viewSavedBills();
                break;

            case 4:
                printf("Exiting Program...\n");
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }
}

int main() {

    struct Food menu[] = {
        {1, "Burger", 80},
        {2, "Pizza", 250},
        {3, "Pasta", 150},
        {4, "Sandwich", 120}
    };

    int n = 4;

    startSystem(menu, n);

    return 0;
}