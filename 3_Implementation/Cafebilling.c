
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct items
{
    char item[30];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50]; 
};
//functions to genrating bills
void generateBillHeader(char name[50],char date[30])
{
    printf("\n\n");
        printf("\t     ===**=== Prathm Cafeeeeeee ===**===");
        printf("\n\t  --------------------");
        printf("\nDate:%s",date);
        printf("\nBill To: %s",name);
        printf("\n");
        printf("----------------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n-----------------------------------------------");
        printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.3f\t\t",qty * price);
    printf("\n");
}
void generateBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst; //netTotal + cgst *sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n----------------------------------------\n");
}
int main()
{
      
      int choice,n;
      struct orders ord;
      struct orders order;
      char saveBill = 'y',contFlag ='y';
      char name[50];
      FILE *fp;
      //dashboard
      while(contFlag == 'y'){
          float total = 0;
          int BillFound = 0;
      printf("\n\t\t==============**********==========   Prathm.Cafeeeeeee   ======**********================");
      printf("\n\nPlease enter your choice");
      printf("\n\n1.Generate Bill");
      printf("\n2.Show all Bills");
      printf("\n3.Search Bill");
      printf("\n4.Exit");

      printf("\n\nYour choice:\t");
      scanf("%d",&choice);
      fgetc(stdin);

      switch (choice){
          case 1:
          printf("\nPlease enter the name of the customer : ");
          fgets(ord.customer,50,stdin);
          ord.customer[strlen(ord.customer)-1]=0;
          strcpy(ord.date,__DATE__);
          printf("Please enter the number of items : \t");
          scanf("%d",&n);
          ord.numOfItems= n;
          for(int i=0;i<n;i++)
          {
              fgetc(stdin);
              printf("\n");
              printf("Please enter the item %d : ",i+1);
              fgets(ord.itm[i].item,30,stdin);
              ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
              printf("Please enter the quantity : ");
              scanf("%d",&ord.itm[i].qty);
              printf("Please enter the price : ");
              scanf("%f",&ord.itm[i].price);    
              total += ord.itm[i].qty * ord.itm[i].price;   
            }
            generateBillHeader(ord.customer,ord.date);
            for(int i=0;i<ord.numOfItems;i++){
                   generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateBillFooter(total);
            printf("\nDo you want to save the Bills[y/n] : ");
            scanf("%s",&saveBill);
            if(saveBill == 'y')
            {
                fp = fopen("Bill.exe","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if (fwrite != 0)
                printf("\nSuccesfully saved");
                else
                printf("\nError saving");
                fclose(fp);      
            }
            break;

            case 2:
            fp = fopen("Bill.exe","r");
            printf("\n *****Your Previous Bills*****\n");
            while (fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot +=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;
             
             case 3:
             printf("\nEnter the name of the customer:\t");
             //fgetc(stdin);
             fgets(name,50,stdin);
             name[strlen(name)-1]=0;
            
            fp = fopen("Bill.exe","r");
            printf("\t*****Bills of %s*****",name);
            while (fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                if(!strcmp(order.customer,name)){
                   generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot +=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot); 
                BillFound = 1;
                }
            
            }
            if(!BillFound){
                printf("Sorry the bill for %s doesn't exits",name);
            }
            fclose(fp);
            break;
         case 4:
         exit(0);
         break;
         default:
         printf("Sorry invalid option");
         break;
      }
      printf("\nDo you want to perform another opration?[y/n] :\t");
      scanf("%s",&contFlag);
      }
      printf("\n\n");
return 0;
}

