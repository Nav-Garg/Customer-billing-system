/* Customer Billing System.
*/


#include<stdio.h>
#include<stdlib.h>

void input();
void writefile();
void search();
void output();

struct date
{
	   int month;
	   int day;
	   int year;
};

struct account 
{
	int number;
	char name[100];
	int acct_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
}customer;
  
int tl,sl,ts;
void main()
{
	  int i,n;
	  char ch;

	  printf("\n\n            CUSTOMER BILLING SYSTEM:\n\n");
	  printf("==========================================================\n");
	  printf("\n       1:    To Add Account on list\n");
	  printf("       2:    To Search Customer Account\n");
	  printf("       3:    Exit\n");
	  printf("\n=========================================================\n");
	  
	  do{
	      // while(getchar() != '\n');
	       printf("\nSelect what do you want to do?\n ");
	       scanf("%c",&ch);
	       while(getchar() != '\n');
	  }while(ch<='0' || ch>'3');
	  
	  switch(ch)
	  {
		case '1':
			  printf("\nHow many customer accounts you have to add?\n");
			  scanf("%d",&n);
			  for(i=0;i<n;i++)
			  {
				input();
				if(customer.payment>0)
					customer.acct_type=(customer.payment<0.1*customer.oldbalance)? 'O': 'D';
				else
					customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
				customer.newbalance=customer.payment - customer.oldbalance;
				writefile();
			  }
			  main();
		 
		 case '2':
			   printf("Search by what?\n");
		           printf("\n1 --- Search by Customer_Number\n");
			   printf("2 --- Search by Customer_Name\n");
		           search();
			   scanf("%c",&ch);
			   main();
		
		case '3':
			  printf("\nA PROJECT BY NAVEEN GARG");
		          exit(1);
	  }
 }


   void input()
	{
	  FILE *fp=fopen("data","rb");
	  if(fp != NULL)
	  {
	   fseek (fp,0,SEEK_END);
	   tl=ftell(fp);
	   if(tl > 0)
	   { 
	  	sl=sizeof(customer);
	  	ts=tl/sl;
	  	fseek(fp,(ts-1)*sl,SEEK_SET);
	  	fread(&customer,sizeof(customer),1,fp);
	  	printf("\ncustomer no:%d\n",++customer.number);
	   }
	  }
	  else
	  {
	  	printf("\ncustomer no:%d\n", 1);
		customer.number = 1;
	  }	
	  fclose(fp);
	  printf("\n         Account number:");
	  scanf("%d",&customer.acct_no);
	  printf("\n         Name:");
	  scanf("%s",customer.name);
	  printf("\n         Mobile No.:");
	  scanf("%f",&customer.mobile_no);
	  printf("\n         Address:");
	  scanf("%s",customer.street);
	  printf("\n         City:");
	  scanf("%s",customer.city);
	  printf("\n         Previous balance:");
	  scanf("%f",&customer.oldbalance);
	  printf("         Current payment:");
	  scanf("%f",&customer.payment);
	  printf("\n         Payment Month(mm):");
	  scanf("%d",&customer.lastpayment.month);
	  printf("         Day:");
	  scanf("%d",&customer.lastpayment.day);
	  printf("         Year:");
	  scanf("%d",&customer.lastpayment.year);
	
	  while(getchar() != '\n');
	  return;
   }

   void writefile()
   {
	  FILE *fp;
	  fp=fopen("data","ab");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
   }

   void search()
   {
	 char ch,ch1;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("data","rb");
	 do{
		printf("\nEnter your choice:");
		scanf("%c",&ch);
	 }while(ch!='1' && ch!='2');
	 
	 switch(ch)
	 {
	      case '1':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    do{
			printf("\nEnter Customer_Number:");
			scanf("%d",&n);
			if(n<=0 || n>ts)
			printf("\nEntered Wrong Customer_Number\n");
			else{
			    fseek(fp,(n-1)*sl,SEEK_SET);
			    fread(&customer,sl,1,fp);
			    output();
			}
			while(getchar() != '\n');
			printf("\n\nAgain Search another account?(y/n):");
			scanf("%c",&ch);

		    }while(ch=='y');
		    fclose(fp);
		    break;

	      case '2':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&customer,sizeof(customer),1,fp);
		    n=customer.number;

		    do{
			printf("\nEnter the Name for Searching Account_Delail:");
			scanf("%s",nam);
			fseek(fp,0,SEEK_SET);
			for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,fp);
			     if(strcmp(customer.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			   printf("\n\nDoesn't exist\n");
		        while(getchar() != '\n');   
			printf("\nAgain Search for another_account?(y/n):");
			scanf("%c",&ch);
		    }while(ch =='y');
		    fclose(fp);
	      }
	      return;
	 }



   void output()
	 {
	   printf("\n\n    Customer no    :%d\n",customer.number);
	   printf("    Name 	   :%s\n",customer.name);
	   printf("    Mobile no      :%.f\n",customer.mobile_no);
	   printf("    Account number :%d\n",customer.acct_no);
	   printf("    Street         :%s\n",customer.street);
	   printf("    City           :%s\n",customer.city);
	   printf("    Old balance    :%.2f\n",customer.oldbalance);
	   printf("    Current payment:%.2f\n",customer.payment);
	   printf("    New balance    :%.2f\n",customer.newbalance);
	   printf("    Payment date   :%d/%d/%d\n\n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
	   printf("    Account status :");
	  
	   switch(customer.acct_type)
	      {
	      case 'C':
		 printf("CURRENT\n\n");
		 break;
	      case 'O':
		 printf("OVERDUE\n\n");
		 break;
	      case 'D':
		 printf("DELINQUENT\n\n");
		 break;
	      default:
		 printf("ERROR\\n\n");
	      }
	  
	      return;
	   }

