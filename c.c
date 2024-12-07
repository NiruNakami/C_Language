#include <stdio.h>
#include <string.h>

/*
        ກູ່ມ 5
    ທ ນັດຕະພົງ
     
    ທ ສຸກສະຫວັນ
*/

// Global totals
float totalLaos = 0, totalThai = 0, totalUSD = 0;

struct Item {
    char name[20];
    int quantity;
    int price;
    int total;
    char currency[5];
};

struct Item items[100];
int itemCount = 0;

struct Product {
    char name[50];
    int price; // Kip
};

struct Product products[] = {
    {"Pepsi", 5000},
    {"Egg", 2000},
    {"Milk", 8000},
    {"Honey", 10000}
};



void Menu() {
    int totalProducts = sizeof(products) / sizeof(products[0]);
    for (int i = 0; i < totalProducts; i++) {
        printf("%-5s your Enter %d\n", products[i].name, i + 1);
    }
}

void TotalData(char name[20], char currency[5], int price, int exchangeRate) {
    int amount;
    printf("\n| Your selection is %s |\n", name);
    printf("\n---- %.2f %s ----\n", (float)price / exchangeRate, currency);
    printf("\nEnter amount: ");
    scanf("%d", &amount);

    int itemTotal = price * amount;
    printf("--- You chose %s, amount: %d ---\n", name, amount);
    printf("--- %.2f %s ---\n", (float)itemTotal / exchangeRate, currency);

    totalLaos += itemTotal;
    totalThai += (float)itemTotal / 600;
    totalUSD += (float)itemTotal / 21000;

    items[itemCount++] = (struct Item){.name = "", .quantity = amount, .price = price, .total = itemTotal, .currency = ""};
    strcpy(items[itemCount - 1].name, name);
    strcpy(items[itemCount - 1].currency, currency);
}

void ShoppingMenu(char currency[5], int exchangeRate) {
    char nextShop;
    int productChoice;
    int totalProducts = sizeof(products) / sizeof(products[0]);

    do {
        printf("\n--- Welcome to shop---\n");
        Menu();

        printf("\nEnter your choice: ");
        while (scanf("%d", &productChoice) != 1 || productChoice < 1 || productChoice > totalProducts) {
            printf("Invalid input. Please enter a number between 1 and %d: ", totalProducts);
            while (getchar() != '\n'); // Clear buffer
        }

        // Fetch product dynamically
        struct Product selectedProduct = products[productChoice - 1];
        TotalData(selectedProduct.name, currency, selectedProduct.price, exchangeRate);

        printf("\nDo you want to buy another item? (Y/N): ");
        while (getchar() != '\n'); // Clear buffer
        scanf("%c", &nextShop);
    } while (nextShop == 'Y' || nextShop == 'y');
}

struct CurrencyExchangeRate {
    char Country[30];
    char NameCurrency[10];
    int Currency;
    float MoneyLimit;
};

struct CurrencyExchangeRate CurrencyLaos = {"Laos", "Kip", 1, };
struct CurrencyExchangeRate CurrencyThai = {"Thai", "Baht", 600, };
struct CurrencyExchangeRate CurrencyUSD = {"USD", "USD", 21000, };

void OrderItem(char Country[30], char NameCurrency[5], int CurrencyExchangeRate, float total, float MoneyLimit) {
    float totalS = total / CurrencyExchangeRate;
    float money = 0;
    float change = 0;

    printf("\n--- %s Currency (%s) ---\n", Country, NameCurrency);
    for (int i = 0; i < itemCount; i++) {
        printf("|%d| %s: %d units, Total: %.2f %s\n", i + 1, items[i].name, items[i].quantity, (float)items[i].total / CurrencyExchangeRate, NameCurrency);
    }

    do {
        printf("\n--- Summary of Your Purchases ---\n");
        printf("\nTotal in %s: %.2f %s\n", Country, totalS, NameCurrency);
        printf("\nPlease enter money: ");

        while (scanf("%f", &money) != 1 || money < totalS) {
            printf("Invalid input. Please enter an amount greater than %.2f %s.\n", change, NameCurrency);
            while (getchar() != '\n'); // Clear buffer
        }

        change = money - totalS;

        if (change < 0) {
            printf("\nInsufficient money. Please add more.\n");
        } else {
            printf("\n---- Thank you for shopping! ----\n");
            printf("Change: %.2f %s\n", change, NameCurrency);
        }
    } while (change < 0);

    printf("Transaction completed successfully.\n");
}

int main() {
    int Currency;
    printf("\n--- Please write the Currency you use ---\n");
    printf("\n--- Currency %s your Enter 1 ---\n", CurrencyLaos.NameCurrency);
    printf("\n--- Currency %s your Enter 2 ---\n", CurrencyThai.NameCurrency);
    printf("\n--- Currency %s your Enter 3 ---\n", CurrencyUSD.NameCurrency);

    printf("\nEnter Currency: ");
    while (scanf("%d", &Currency) != 1 || Currency < 1 || Currency > 3) {
        printf("Invalid input. Please enter a number between 1 and 3: ");
        while (getchar() != '\n'); // Clear buffer
    }

    switch (Currency) {
        case 1:
            ShoppingMenu(CurrencyLaos.NameCurrency, CurrencyLaos.Currency);
            OrderItem(CurrencyLaos.Country, CurrencyLaos.NameCurrency, CurrencyLaos.Currency, totalLaos, CurrencyLaos.MoneyLimit);
            break;
        case 2:
            ShoppingMenu(CurrencyThai.NameCurrency, CurrencyThai.Currency);
            OrderItem(CurrencyThai.Country, CurrencyThai.NameCurrency, CurrencyThai.Currency, totalThai, CurrencyThai.MoneyLimit);
            break;
        case 3:
            ShoppingMenu(CurrencyUSD.NameCurrency, CurrencyUSD.Currency);
            OrderItem(CurrencyUSD.Country, CurrencyUSD.NameCurrency, CurrencyUSD.Currency, totalUSD, CurrencyUSD.MoneyLimit);
            break;
        default:
            printf("Invalid selection.\n");
            break;
    }

    return 0;
}
