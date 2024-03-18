#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h> // include the time header to get the current time

struct items
{
    char itm[30]; // names of items
    int quantity;
    float price;
};

struct ord
{
    char customer_names[50];
    char dates[50];
    int numitems;
    struct items item[30]; // items with properties from the 'items' structure
};

// Create function to generate bill header
void billHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t    ADV. Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}
void billbody(char item[30],int qty, float price){
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
}

void totalBill(float tot)
{
    printf("\n---------------------------------------------------\n");
    printf("Subtotal: %.2f\n", tot);
    printf("\n---------------------------------------------------\n");
}
int main()
{
    FILE *fp;
    char ans;
    struct ord order;
    int choice, n, total;
    // Interface with users
    printf("\t\t\t\t=====Welcome to MIXUE=====\n");
    printf("1. Generate Invoice.\n");
    printf("2. Show Invoice.\n");
    printf("3. Search Invoice.\n");
    printf("4. Exit.\n");
    printf("Please enter your choice: \n");
    scanf("%d", &choice);
    getchar(); // consume the newline character

    switch (choice)
    {
    case 1:
        printf("\nEnter Customer Name: ");
        fgets(order.customer_names, 50, stdin);
        order.customer_names[strcspn(order.customer_names, "\n")] = '\0';
        // Get the current time
        time_t current;
        time(&current);
        // Convert time to the format time string
        strcpy(order.dates, ctime(&current));
        order.dates[strcspn(order.dates, "\n")] = '\0';
        printf("\nPlease enter the number of items: ");
        scanf("%d",&n);
        order.numitems = n;

        for (size_t i = 0; i < n; i++)
        {
        getchar();
        printf("\n\nEnter item %d from Mixue: ",i+1);
        // Read item name
        fgets(order.item[i].itm, 30, stdin);
        order.item[i].itm[strcspn(order.item[i].itm, "\n")] = '\0';
        // Prompt user for quantity
        printf("\nQuantity: ");
        scanf("%d",&order.item[i].quantity);
        // Prompt user for price per unit
        printf("\nPrice per unit: ");
        scanf("%f",&order.item[i].price);
        total += order.item[i].price * order.item[i].quantity;
        }
        billHeader(order.customer_names, order.dates);
        for (size_t i = 0; i < order.numitems; i++)
        {
            billbody(order.item[i].itm, order.item[i].quantity, order.item[i].price);
        }
        totalBill(total);
        printf("Save the invoice[Y/N]??: ");
        scanf("%c" , &ans);
        if (ans == 'y' || ans == 'Y')
        {
            fp = fopen("Invoices.txt","a");
            if (fp != NULL) {
                fprintf(fp, "Customer Name: %s\n", order.customer_names);
                fprintf(fp, "Date: %s\n", order.dates);
                for (size_t i = 0; i < order.numitems; i++)
                {
                    fprintf(fp, "Item: %s, Quantity: %d, Price per unit: %.2f\n", order.item[i].itm, order.item[i].quantity, order.item[i].price);
                }
                fprintf(fp, "Total: %.2f\n", total);
                fclose(fp);
                printf("File is successfully written.\n");
            } else {
                printf("Error opening file.\n");

            }
        }
        break;
    
    default:
        break;
    }

    return 0;
}
