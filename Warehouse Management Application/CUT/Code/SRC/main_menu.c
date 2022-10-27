/********************************************
 * *FILENAME	      : main_menu.c
 *
 * *DESCRIPTION        : This file defines the functions that consists of various subfunctions 
 * 			to perform certain operations. 
 *
 * Revision History   :	       
 *
 * 	Date			Name			Reason
 *
 *   26th Oct 2022		----			-----
 *
 *
********************** include Header ***********************/


#include<stdio.h>
#include"header.h"
#include<stdlib.h>
#include<string.h>


/********************************************************
 * *FUNCTION NAME : main 
 *
 * *DESCRIPTION   : This function calls the other functions to performs various 
 * 		    operations by taking choice option from the user. 
 * *RETURNS         : admin_file_maintenance
 *                  supplier_module.c
 *                  stockist_module.c
 *                  exit- exit the main function
 *
 *
 *
 **********************************************************/                  

int main()
{
	(void)file_to_list_supplier();
	(void)file_to_list_stockist();
	(void)file_to_list_product();
        (void)file_to_list_transaction();
	char pass[SIZE];
	int ch=0;
	while(ch!=4)
	{
		char f[SIZE1];
		printf("\n ----------WAREHOUSE SYSTEM APPLICATION----------\n");
		printf("\n1) Login(Existing user) \n2) Create Account(Supplier/stockist) \n3) Admin login\n4) Exit\n");              
		while(1)
		{
			printf("Enter your choice:-");
			(void)scanf("%s",f);
			if(valid_choice(f)==1)
				continue;
			break;
		}
		ch=atoi(f);
		switch(ch)
		{
			case 1:(void)login();
			       break;
			case 2:(void)create();
			       break;
			case 3:printf("Enter your password\n");
			       (void)scanf("%s",pass);
			       if(!strcmp(pass,"sss"))
			       {
				       (void)admin_module();
			       }
			       else 
			       {
				       printf("Incorrect password\n");
				       (void)system("read a");
			       }
			       break;
			case 4:break;
			default:printf("\n Invalid Choice \n");
		}
		(void)system("clear");
	}
	(void)list_to_file_supplier();
	(void)list_to_file_stockist();
       	(void)list_to_file_product();
        (void)list_to_file_transaction();
	return EXIT_SUCCESS;
}
/********************************************************
 * *FUNCTION NAME : supplier_module
 *
 * *DESCRIPTION   : This function display supplier menu. 
 *RETURNS         : add products - supplier adds the products
 *                  edit details - supplier edit personal details 
 *                  view selected products - views the product selected by supplier
 *                  ROL check - checks the Re-Order Level of each products
 *
 *
 *
 **********************************************************/                  


static int supplier_module(int id)
{
	(void)system("clear");
	int ch1=0;
	while(ch1!=5)
	{
	        char f[SIZE1];
		printf("\n--------------Welcome Supplier----------------\n");
		printf("\n1) Add products\n2) Edit details\n3) View selected products\n4) Check Status\n5) EXIT\n");
		while(1)
		{
			printf("Enter your choice:-");
			(void)scanf("%s",f);
			if(valid_choice(f)==1)
				continue;
			break;
		}
		ch1=atoi(f);
		switch(ch1)
		{
			case 1:(void)supplier_add_product(id);
			       return EXIT_SUCCESS;
			case 2:(void)supplier_edit_details(id);
                               (void)system("read a");
			       break;	
			case 3:(void)view_selected_products(id);
			       (void)system("read a");
			       break;
			case 4:(void)check_status(id);
		               (void)system("read a");
			       return EXIT_SUCCESS;
			case 5: break;
			default:printf("\nInvalid Choice\n");
		}
		(void)system("clear");
	}
	return EXIT_FAILURE;
}


/********************************************************
 * *FUNCTION NAME : stockist_module
 *
 * *DESCRIPTION   : This function display stockist menu.
 *RETURNS         : order items - shows the items for stockist to order
 *                  view stocks - shows the ordered items
 *                  request for items - requesting for the items to admin
 *                  edit stockist details - for editing stockist personal details
 *
 *
 *
 **********************************************************/                  



static int stockist_module(int n)
{
	(void)system("clear");
	int ch1=0;
	while(ch1!=5)
	{
		char f[SIZE1];
		printf("\n--------------Welcome Stockist----------------\n");
		printf("1) Order Items\n2) View Stock\n3) Request For Items\n4) Edit Stockist Details\n5) Exit\n");
		while(1)
		{
			printf("Enter your choice:-");
			(void)scanf("%s",f);
			if(valid_choice(f)==1)
				continue;
			break;
		}
		ch1=atoi(f);
		switch(ch1)
		{
			case 1:(void)order_items(n);
			       return EXIT_SUCCESS;
			case 2:(void)view_stock();
			       (void)system("read a");
			       break;
			case 3:(void)request_for_items();
			       break;
			case 4:(void)stockist_edit_details(n);
                               (void)system("read a");
			       break;
			case 5:break;
			default:printf("\nInvalid Choice\n");
		}
		(void)system("clear");
	}
	return EXIT_SUCCESS;
}

/********************************************************
 * *FUNCTION NAME : admin_module
 *
 * *DESCRIPTION   : This function display admin menu. 
 *
 *RETURNS         :file maintenance for suppliers
 *                 file maintence for stockist
 *                 file maintenance for products
 *
 *
 **********************************************************/                  


int admin_module()
{
	(void)system("clear");
	int choice=0;
	while(choice!=8)
	{
		char f[SIZE1];;
		printf("--------------Welcome Admin----------------\n");
		printf("1) File maintainance for suppliers\n2) File maintainance for stockist\n3) File maintainance for products\n4) Display transaction file\n5) Display report for stockist\n6) Display report for items\n7) Check ROL\n8) Go Back\n");
		(void)fflush(stdin);
		while(1)
		{
			printf("Enter your choice:-");
			(void)scanf("%s",f);
			if(valid_choice(f)==1)
				continue;
			break;
		}
		choice=atoi(f);
		switch(choice)
		{
			case 1:(void)menu(1);
			       break;
			case 2:(void)menu(2);
			       break;
			case 3:(void)menu(3);
			       break;
			case 4:(void)display_report();
			       (void)system("read a");
			       break;
			case 5:(void)display_report_stockist();
			       (void)system("read a");
			       break;
			case 6:(void)display_report_item();
			       (void)system("read a");
			       break;
			case 7:(void)rol_check();
			       (void)system("read a");
			       break;
			case 8:break;
			default:printf("\nInvalid Input\n");
		}
		(void)system("clear");
	}
	return EXIT_SUCCESS;
}

/********************************************************
 * *FUNCTION NAME : menu
 *
 * *DESCRIPTION   : This function is responsible for displaying 
 *                  sub menu.
 *RETURNS         : add - for adding supplier data
 *                  delete - for deleting supplier data
 *                  edit - for editing price and quantity
 *                  view - for viewing the details supplier entered
 *
 *
 **********************************************************/                  


int menu(int c)
{
	char f[SIZE1];
        (void)system("clear");
	int choice1=0;
	if(c==1)
	{
		while(choice1!=5)
		{
			printf("---------------Supplier File Maintenance-------------------\n");
			printf("1) Add\n2) Delete\n3) Edit\n4) View\n5) Go Back\n");
			while(1)
			{
				printf("Enter your choice:-");
				(void)scanf("%s",f);
				if(valid_choice(f)==1)
					continue;
				break;
			}
		        choice1=atoi(f);
			switch(choice1)
			{
				case 1:(void)add_supplier();
			               (void)system("read a");
				       break;
				case 2:(void)del_supplier();
				       (void)system("read a");
				       break;
				case 3:(void)edit_supplier();
			               (void)system("read a");
				       break;
				case 4:(void)view_supplier();
				       (void)system("read a");
				       break;
				case 5:break;
				default:printf("\nInvalid choice\n");
			}
			(void)system("clear");
		}
	}
	else if(c==2)
	{
		while(choice1!=5)
		{
			printf("---------------Stockist File Maintanence-------------------\n");
			printf("1) Add\n2) Delete\n3) Edit\n4) View\n5) Go Back\n");
			while(1)
			{
				printf("Enter your choice:-");
				(void)scanf("%s",f);
				if(valid_choice(f)==1)
					continue;
				break;
			}
		        choice1=atoi(f);
			switch(choice1)
			{
				case 1:(void)add_stockist();
			               (void)system("read a");
				       break;
				case 2:(void)del_stockist();
				       (void)system("read a");
				       break;
				case 3:(void)edit_stockist();
			               (void)system("read a");
				       break;
				case 4:(void)view_stockist();
				       (void)system("read a");
				       break;
		                case 5:break;
				default:printf("\nInvalid Choice\n");
			}
			(void)system("clear");
		}
	}
	else if(c==3)
	{
		while(choice1!=5)
		{
			printf("------------------Products File Maintanence----------------\n");
			printf("1) Add\n2) Delete\n3) Edit\n4) View\n5) Go Back\n");
			while(1)
			{
				printf("Enter your choice:-");
				(void)scanf("%s",f);
				if(valid_choice(f)==1)
					continue;
				break;
			}
		        choice1=atoi(f);
			switch(choice1)
			{
				case 1:(void)add_product();
				       break;
				case 2:(void)del_product();
				       (void)system("read a");
				       break;
				case 3:(void)edit_product();
			               (void)system("read a");
				       break;
				case 4:(void)view_product();
				       (void)system("read a");
				       break;
				case 5:break;
				default:printf("\nInvalid Choice\n");
			}
			(void)system("clear");
		}
	}
	else
	{
		printf("Invalid Range\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/********************************************************
 * *FUNCTION NAME : login
 *
 * *DESCRIPTION   : This function is used for login by 
 *                  warehouse admin, supplier and stockist.
 * 
 * *RETURNS       : for warehouse admin - for admin login
 *                  for suppliers - for supplier login
 *                  for stockist - for stockis login
 *
 *
********************************************************/


int login()
{
	char pass[SIZE];
	char f[SIZE];
	printf("\n-------------------Login for suppliers and stockists---------------------------\n");
	(void)system("clear");
	while(1)
	{
		printf("Enter your ID:-");
		(void)scanf("%s",f);
		if(valid_integer(f)==1)
		{
			continue;
		}
		printf("Enter your password:-");
		(void)scanf("%s",pass);
		int id=atoi(f);
		if(id>=200 && id<=299)
		{
			if(verify(1,id,pass))
			{
				(void)supplier_module(id);
			}
			break;
		}
		if(id>=100 && id<=199)
		{
			if(verify(2,id,pass))
			{
				(void)stockist_module(id);
			}
			break;
		}
		else
		{
			printf("Invalid range! ID should be between 100 to 299\n");
			(void)system("read a");
			(void)system("clear");
		}
	}
	return EXIT_SUCCESS;
}


int create()
{
	char f[SIZE];
	(void)system("clear");
	printf("\n-------------Create new account for suppliers and stockists-------------------\n");
	int c=0;
	while(1)
	{
		printf("Select 1 for STOCKIST \nSelect 2 for SUPPLIER\n");
		(void)scanf("%s",f);
		if(valid_integer(f)==1)
			continue;
		break;
	}
	c=atoi(f);
	if(c==1)
	{
		(void)add_stockist();
                (void)system("read a");
	}
	if(c==2)
	{
	        (void)add_supplier();
                (void)system("read a");
	}
	return EXIT_SUCCESS;
}


/***********  For login **********/
	
	
