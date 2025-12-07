#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 50

struct Node {
    char name[NAME];
    int quantity;
    float price;
    struct Node *next;
};

struct Node* addItem(struct Node *head, char itemName[], int qty, float price);
void displayMenu(struct Node *head);
void orderItem(struct Node *head, char itemName[], int orderQty);
void updateQuantity(struct Node *head, char itemName[], int newQty);
struct Node* deleteItem(struct Node *head, char itemName[]);
void freeList(struct Node *head);

int main() {
    struct Node *head = NULL;
    int choice;
    char name[NAME];
    int qty;
    float price;
    head = addItem(head, "Tiramisu", 20, 250.0);
    head = addItem(head, "Cheesecake", 25, 230.0);
    head = addItem(head, "Croissant", 15, 240.0);
    head = addItem(head, "Capaccino", 10, 220.0);

    while(1) {
        printf("\n============* welcome to TARA CAFE' *============\n");
        printf("\n============ ORDERING SYSTEM DISPLAY============\n");
        printf("1. Display Available Menu\n");
        printf("2. Order an Item\n");
        printf("3. Add New Item to Menu\n");
        printf("4. Update Item Quantity\n");
        printf("5. Remove Item from Menu\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(head);
                break;

            case 2:
                printf("Enter item name to order (single word): ");
                scanf("%s", name);
                printf("Enter quantity to order: ");
                scanf("%d", &qty);
                orderItem(head, name, qty);
                break;

            case 3:
                printf("Enter new item name (single word): ");
                scanf("%s", name);
                printf("Enter starting quantity: ");
                scanf("%d", &qty);
                printf("Enter price per unit: ");
                scanf("%f", &price);
                head = addItem(head, name, qty, price);
                break;

            case 4:
                printf("Enter item name to update quantity: ");
                scanf("%s", name);
                printf("Enter new quantity: ");
                scanf("%d", &qty);
                updateQuantity(head, name, qty);
                break;

            case 5:
                printf("Enter item name to remove: ");
                scanf("%s", name);
                head = deleteItem(head, name);
                break;

            case 6:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } 

  
    return 0;
}

struct Node* addItem(struct Node *head, char itemName[], int qty, float price) {
    struct Node *newNode, *temp;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot add item.\n");
        return head;
    }

    strcpy(newNode->name, itemName);
    newNode->quantity = qty;
    newNode->price = price;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Item '%s' added with quantity %d and price %.2f\n", itemName, qty, price);
    return head;
}

void displayMenu(struct Node *head) {
    struct Node *temp = head;
    int index = 1;

    if (head == NULL) {
        printf("Menu is empty! No items available.\n");
        return;
    }

    printf("\n----------------- CAFE MENU -----------------\n");
    printf("No.  Item         Price    Available Qty\n");
    printf("--------------------------------------------\n");
    while (temp != NULL) {
        printf("%-4d %-12s %-8.2f %d\n", index, temp->name, temp->price, temp->quantity);
        temp = temp->next;
        index++;
    }
    printf("--------------------------------------------\n");
}

void orderItem(struct Node *head, char itemName[], int orderQty) {
    struct Node *temp = head;
    float total;

    if (head == NULL) {
        printf("Menu is empty! Cannot place order.\n");
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->name, itemName) == 0) {
            if (orderQty <= 0) {
                printf("Invalid order quantity.\n");
                return;
            }
            if (temp->quantity == 0) {
                printf("Item '%s' is out of stock.\n", temp->name);
                return;
            }
            if (orderQty > temp->quantity) {
                printf("Only %d '%s' available. Cannot order %d.\n",
                       temp->quantity, temp->name, orderQty);
                return;
            }

            // Enough quantity, process order
            temp->quantity -= orderQty;
            total = temp->price * orderQty;
            printf("Order placed: %d x %s\n", orderQty, temp->name);
            printf("Total amount: Rs. %.2f\n", total);
            printf("Remaining '%s' in stock: %d\n", temp->name, temp->quantity);
            return;
        }
        temp = temp->next;
    }

    printf("Item '%s' not found in menu.\n", itemName);
}

void updateQuantity(struct Node *head, char itemName[], int newQty) {
    struct Node *temp = head;

    if (head == NULL) {
        printf("Menu is empty! Nothing to update.\n");
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->name, itemName) == 0) {
            temp->quantity = newQty;
            printf("Quantity of '%s' updated to %d.\n", itemName, newQty);
            return;
        }
        temp = temp->next;
    }

    printf("Item '%s' not found. Cannot update.\n", itemName);
}

struct Node* deleteItem(struct Node *head, char itemName[]) {
    struct Node *temp = head;
    struct Node *prev = NULL;

    if (head == NULL) {
        printf("Menu is empty! Nothing to remove.\n");
        return head;
    }

    if (strcmp(temp->name, itemName) == 0) {
        head = temp->next;
        printf("Item '%s' removed from menu.\n", temp->name);
        free(temp);
        return head;
    }

    while (temp != NULL && strcmp(temp->name, itemName) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Item '%s' not found in menu.\n", itemName);
        return head;
    }

    prev->next = temp->next;
    printf("Item '%s' removed from menu.\n", temp->name);
    free(temp);

    return head;
}