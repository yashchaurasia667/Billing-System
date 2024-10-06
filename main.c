#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items
{
  char item[20];
  float price;
  int qty;
};
typedef struct items Items;

struct orders
{
  char customer[50];
  char date[50];
  int numOfItems;
  Items itm[50];
};
typedef struct orders Orders;

// functions to generate bills
void generateBillHeader(char name[50], char date[30])
{
  printf("\n\n");
  printf("\n ADV. Restraunt");
  printf("\n\t ------------------");
  printf("\nDate: %s", date);
  printf("\nInvoice To: %s", name);
  printf("\n");
  printf("----------------------------------\n");
  printf("Items\t\t");
  printf("Qty\t\t");
  printf("Total\t\t");
  printf("\n---------------------------------");
  printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price)
{
  printf("%s\t\t", item);
  printf("%d\t\t", qty);
  printf("%.2f\t\t", qty * price);
  printf("\n");
}

void generateBillFooter(float total)
{
  printf("\n");
  float dis = 0.1 * total;
  float netTotal = total - dis;
  float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;

  printf("-------------------------------------\n");
  printf("Sub Total\t\t\t %.2f", total);
  printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
  printf("\n\t\t\t\t------------");
  printf("\nNet Total\t\t\t%.2f", netTotal);
  printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
  printf("\n-------------------------------------\n");
  printf("Grand Total\t\t\t%.2f", grandTotal);
  printf("\n-------------------------------------\n");
}

int main()
{
  float total;
  int opt, n, invoiceFound = 0;

  char name[50];

  Orders ord;
  Orders order;

  char saveBill = 'y';
  FILE *fp;

  printf("\t==================GUGU RESTRAUNT==================");
  printf("\n\nPlease select your prefered operation:\n");
  printf("\n1.Generate Invoice");
  printf("\n2.Show All Invoices");
  printf("\n3.Search Invoice");
  printf("\n4.Exit");

  printf("\n\nYour Choice:\t");
  scanf("%d", &opt);
  fgetc(stdin);

  switch (opt)
  {
  case 1:
    system("clear");
    printf("\nPlease enter the name of the customer:\t");
    fgets(ord.customer, 50, stdin);
    ord.customer[strlen(ord.customer) - 1] = 0;
    strcpy(ord.date, __DATE__);

    printf("\nPlease enter the number of items:\t");
    scanf("%d", &n);
    ord.numOfItems = n;

    for (int i = 0; i < n; i++)
    {
      fgetc(stdin);
      printf("\n\n");
      printf("Enter the item %d:\t", i + 1);
      fgets(ord.itm[i].item, 20, stdin);
      ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
      printf("\nEnter the quantity:\t");
      scanf("%d", &ord.itm[i].qty);
      printf("\nEnter the unit price:\t");
      scanf("%f", &ord.itm[i].price);
      total += ord.itm[i].qty * ord.itm[i].price;
    }
    generateBillHeader(ord.customer, ord.date);
    for (int i = 0; i < ord.numOfItems; i++)
      generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
    generateBillFooter(total);

    printf("Do you want to save the invoice? (Y/n)");
    scanf("%c", &saveBill);

    if (saveBill == 'y')
    {
      fp = fopen("RestrauntBill.dat", "a+");
      int write = fwrite(&ord, sizeof(Orders), 1, fp);
      if (write)
        printf("Saved successfully");
      else
        printf("Error saving file");
      fclose(fp);
    }
    break;

  case 2:
    system("clear");
    fp = fopen("RestrauntBill.dat", "r");
    printf("\n  ******* Your Previous Invoices *******\n");
    while(fread(&order, sizeof(Orders), 1, fp)) {
      float tot=0;
      generateBillHeader(order.customer, order.date);
      for(int i=0; i<order.numOfItems; i++) {
        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
        tot += order.itm[i].qty * order.itm[i].price;
      }
      generateBillFooter(tot);
      fclose(fp);
    }
    break;

  case 3:
    printf("\nEnter Name of the customer:\t");
    fgets(name, 50, stdin);
    name[strlen(name)-1] = 0;
    system("clear");
    fp = fopen("RestrauntBill.dat", "r");
    printf("\n  ******* Invoice of %s *******\n", name);
    while(fread(&order, sizeof(Orders), 1, fp)) {
      float tot=0;
      if(!strcmp(order.customer, name)) {
        generateBillHeader(order.customer, order.date);
        for(int i=0; i<order.numOfItems; i++) {
          generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
          tot += order.itm[i].qty * order.itm[i].price;
        }
        generateBillFooter(tot);
        invoiceFound = 1;
      }
    }
    if(!invoiceFound)
      printf("Sorry the invoice for %s does not exist...", name);
   
    fclose(fp);
    break;
  
  case 4:
    printf("\n\t\t Bye Bye :)");
    exit(0);
    break;

  default:
    printf("Please choose an option from 1 to 4");
    break;
  }

  printf("\n\n");

  return 0;
}