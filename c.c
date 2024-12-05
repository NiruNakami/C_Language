#include <stdio.h>
#include <string.h>

float totalLaos = 0, totalThai = 0, totalUSD = 0;

// Item structure
struct Item
{
    char name[20];
    int quantity;
    int price;
    int total;
    char currency[5];
};

// Array to store items
struct Item items[100];
int itemCount = 0;

// Example product definitions
// Product or DateItem  and keep Price KIp

struct Product{
    char name[20];
    int price; // Kip
}   
    Pepsi = {"Pepsi", 5000},
    EGG = {"Egg", 2000},
    Milk = {"Milk", 8000},
    Honey = {"Honey", 10000};

void TotalData(char name[20], char currency[5], float price, int exchangeRate) {
    int amount;
    printf("\n| Your selection is %s |\n", name);
    printf("\n---- %.2f %s ----\n", price / exchangeRate, currency);
    printf("\nEnter amount: ");
    scanf("%d", &amount);

    int itemTotal = price * amount;
    printf("--- You chose %s, amount: %d ---\n", name, amount);
    printf("--- %.2f %s ---\n", (float)itemTotal / exchangeRate, currency);

    // Update totals
    totalLaos += itemTotal;
    totalThai += (float)itemTotal / 600;
    totalUSD += (float)itemTotal / 21000;

    // Store item details
    items[itemCount++] = (struct Item){.name = "", .quantity = amount, .price = price, .total = itemTotal, .currency = ""};
    strcpy(items[itemCount - 1].name, name);
    strcpy(items[itemCount - 1].currency, currency);
}
// Shopping menu function
void ShoppingMenu(char currency[5], int exchangeRate) {
    char nextShop;
    int productChoice;

    do {
        printf("\n--- Welcome to shop---\n");
        printf("\n%s your Enter 1\n", Pepsi.name);
        printf("%s   your Enter 2\n", EGG.name);
        printf("%s  your Enter 3\n", Milk.name);
        printf("%s your Enter 4\n", Honey.name);
        printf("\nEnter your choice: ");
        while (scanf("%d", &productChoice) != 1 || productChoice < 1 || productChoice > 4) {
            printf("Invalid input. Please enter a number between 1 and 4: ");
            while (getchar() != '\n'); // Clear buffer
        }

        switch (productChoice) {
            case 1: TotalData(Pepsi.name, currency, Pepsi.price, exchangeRate); break;
            case 2: TotalData(EGG.name, currency, EGG.price, exchangeRate); break;
            case 3: TotalData(Milk.name, currency, Milk.price, exchangeRate); break;
            case 4: TotalData(Honey.name, currency, Honey.price, exchangeRate); break;
            default: printf("Invalid selection.\n"); break;
        }

        printf("\nDo you want to buy another item? (Y/N): ");
        while (getchar() != '\n'); // Clear buffer
        scanf("%c", &nextShop);
    } while (nextShop == 'Y' || nextShop == 'y');
}




struct CurrencyExchangeRate
{
    char Country[30];
    char NameCurrency[10];
    int Currency;
    float MoneyLimit;
}
    // CurrencyExchangeRate Global
    CurrencyLaos = {"Laos", "Kip", 1, 500},
    CurrencyThai = {"Thai", "Baht", 600, 1},
    CurrencyUSD = {"USD", "USD", 21000, 0.99};

void OrderItem(char Country[30], char NameCurrency[5], int CurrencyExchangeRate, float total, float MoneyLimit) {
    float totalS = total / CurrencyExchangeRate; // Total in selected currency
    float money = 0;
    float change = 0;

    printf("\n--- %s Currency (%s) ---\n", Country, NameCurrency);
    for (int i = 0; i < itemCount; i++) {
        printf("|%d| %s: %d units, Total: %.2f %s\n", i + 1, items[i].name, items[i].quantity, (float)items[i].total / CurrencyExchangeRate, NameCurrency);
    }

    do {
        printf("\n--- Summary of Your Purchases ---\n");
        printf("Total in %s: %.2f %s\n", Country, totalS, NameCurrency);
        printf("Please enter money: ");

        while (scanf("%f", &money) != 1  || money > MoneyLimit) {
            printf("Invalid input. Please enter a valid amount. (Limit: %.2f %s)\n", MoneyLimit, NameCurrency);
            while (getchar() != '\n'); // Clear buffer
        }

        change = money - totalS;

        if (change < 0) {
            printf("Insufficient money. Please add more.\n");
            totalS -= money; // Deduct the money paid so far from the total
        } else {
            printf("Thank you for shopping!\n");
            printf("Change: %.2f %s\n", change, NameCurrency);
        }
    } while (change < 0);

    printf("Transaction completed successfully.\n");
}


int main(){
    // Product or DateItem


    // Start shopping Welcome
    int List;
    char continueShopping;
    int Currency;
        printf("\n--- Please write the Currency you use ---\n");

        printf("\n--- Currency %s your Enter 1 ---\n", CurrencyLaos.NameCurrency);

        printf("\n--- Currency %s your Enter 2 ---\n", CurrencyThai.NameCurrency);

        printf("\n--- Currency %s your Enter 3 ---\n", CurrencyUSD.NameCurrency);

        printf("\n Enter Currency : ");

    while (scanf("%d", &Currency) != 1 || Currency < 1 || Currency > 3) {
        printf("Invalid input. Please enter a number between 1 and 3: ");
        while (getchar() != '\n'); // Clear buffer
    }
    switch (Currency) {
        case 1:
            ShoppingMenu(CurrencyLaos.NameCurrency, CurrencyLaos.Currency);
            OrderItem(CurrencyLaos.Country, CurrencyLaos.NameCurrency, CurrencyLaos.Currency, totalLaos  ,CurrencyLaos.MoneyLimit );
        break;
            case 2: ShoppingMenu(CurrencyThai.NameCurrency, CurrencyThai.Currency);
            OrderItem(CurrencyThai.Country, CurrencyThai.NameCurrency, CurrencyThai.Currency, totalThai ,CurrencyThai.MoneyLimit );
        break;
            case 3: ShoppingMenu(CurrencyUSD.NameCurrency, CurrencyUSD.Currency);
            OrderItem(CurrencyUSD.Country, CurrencyUSD.NameCurrency, CurrencyUSD.Currency, totalUSD ,CurrencyUSD.MoneyLimit );
        break;
        default: printf("Invalid selection.\n"); break;
    }
    

    return 0;
}