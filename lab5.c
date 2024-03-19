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
void billHeader(char name[50], char date[30]) {
    printf("\n\n");
    printf("\t\t    MIXUE");
    printf("\n\t   -----------------");
    
    //extract day, month, and year from the date string
    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    printf("\nDate: %02d/%02d/%d", day, month, year);

    //get the current time
    time_t current;
    time(&current);
    struct tm *timeinfo = localtime(&current);

    //print current time with hours and minutes
    printf("\t\tPrint at: %02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);

    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("------------------------------------------------------\n");
    printf("| %-30s | %-7s | %-6s |\n", "Items", "Qty", "Total");
    printf("------------------------------------------------------\n");
}

void billbody(char item[30], int qty, float price) {
    printf("| %-30s | %-7d | $%-6.2f |\n", item, qty, qty * price);
}

void totalBill(float tot) {
    printf("------------------------------------------------------\n");
    printf("| %-40s | $%-6.2f |\n", "Sub Total", tot);
    printf("------------------------------------------------------\n");
}

//function to generate Invoice
void generateInvoice()
{
    FILE* fp;
    char ans;
    struct ord order;
    int n, total = 0;
    printf("\nEnter Customer Name: ");
        fgets(order.customer_names, 50, stdin);

        order.customer_names[strcspn(order.customer_names, "\n")] = '\0';
        // Get the current time
        //hold information about calendar time
        struct tm *clock; 
        //declare variable
        time_t current; 
        char timeString[80]; // store the formatted time string
        time(&current); 
        clock = localtime(&current); //localtime function to adjust timezone
        //strftime() forrmats a timestamp string according to locale settings
        strftime(timeString, sizeof(timeString), "%d/%m/%Y", clock);
        strcpy(order.dates, timeString);
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
        //call to create a header with invoice details
        billHeader(order.customer_names, order.dates);
        for (size_t i = 0; i < order.numitems; i++)
        {
            //call to creae the body of the invoice which contains each individual item
            billbody(order.item[i].itm, order.item[i].quantity, order.item[i].price);
        }
        totalBill(total);
        printf("Save the invoice [Y/N]?: ");
        getchar();
        scanf("%c", &ans); 
        if (ans == 'y' || ans == 'Y')
        {
            //open file to write on filetr
            fp = fopen("Invoices.txt","a");
            if (fp != NULL) {\
                //wrtie the data in struct to file
                fwrite(&order, sizeof(struct ord), 1, fp);
                fclose(fp);
                printf("File is successfully written.\n");
            } else {
                printf("Error opening file.\n");
                fclose(fp);
            }
        }
}

//function to search invoice
void showInvoice()
{
    int tot = 0;
    struct ord order;
    FILE* fp = fopen("Invoices.txt", "r");
    printf("\n\t-------Invoices History-------\n");
    //read the data from file and print it on screen
    while (fread(&order,sizeof(struct ord), 1 ,fp))
    {
       tot = 0; //set the total amount to zero before adding new items
       billHeader(order.customer_names, order.dates);
       for (size_t i = 0; i < order.numitems; i++)
       {
           billbody(order.item[i].itm, order.item[i].quantity, order.item[i].price);
           tot +=  order.item[i].price * order.item[i].quantity ;
       }
       totalBill(tot);
    }
    fclose(fp);
}

void searchInvoice()
{
    int total = 0, found = 0; // declare found to ensure it it found or not
    struct ord order;
    char names[50];
    printf("\nEnter customer name : ");
    fgets(names,sizeof(names),stdin);
    //remove newline
    names[strcspn(names,"\n")]='\0';
    FILE* fp = fopen("Invoices.txt", "r");
    printf("\n\t-------%s Invoices-------\n", names);
    //read the data from file and print it on screen
    while(fread(&order, sizeof(struct ord),1 ,fp))
    {
       if(strcmp(names, order.customer_names) == 0)
       {
       billHeader(order.customer_names, order.dates);
       for (size_t i = 0; i < order.numitems; i++)
       {
           billbody(order.item[i].itm, order.item[i].quantity, order.item[i].price);
           total +=  order.item[i].price * order.item[i].quantity ;
       }
       totalBill(total);
       found = 1; //set found = 1 if it is found
       }
    }
    fclose(fp);
    if (!found){
        printf("\nCustomer with this name does not exist.\n");
    }
}
int main()
{
    int choice;
    do
    {
        // Interface with users
        printf("\t\t\t=====Welcome to MIXUE=====\n\n");
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
                generateInvoice(); //call the generate invoice
                break;
            case 2:
                showInvoice(); //call to show invoice
                break;
            case 3:
                searchInvoice(); // call to search
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);
}
