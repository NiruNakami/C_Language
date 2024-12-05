#include<stdio.h>
#include<string.h>
int main()
{
    float MoneyLimit = 500;
    float change = 0;
    float total = 0;
    float money = 0;
    scanf ("%2.f", total);


    do{
        
        printf("\n--- Summary of Your Purchases ---\n");
        printf("\nTotal in : %.2f \n" , total );
        printf("\nPlease money :");

        while (scanf("%.2f", & money) != 1 || money > MoneyLimit) {
            printf("Invalid input. Please enter a number or money is not enough to meet the limit %.2f: " , MoneyLimit);
            while (getchar() != '\n'); // Clear buffer
        }

        if (change > money)
        {
            change += total - money;
            printf("Change : %.2f \n", change);
        }
        
        
    } while (change < 0.00 || change < 0);
    printf("Thank use for shopping");
    printf("Change : %.2f \n", change);
    
    return 0;
}
