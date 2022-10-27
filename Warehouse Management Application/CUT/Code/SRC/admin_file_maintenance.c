/********************************************
 * *FILENAME	      : admin_file_maintenance
 *
 * *DESCRITION        : This file defines the functions that uses the functions
 *                      to perform various operations of the admin database.
 *
 *
 * Revision History   :	       
 *
 * 	Date			Name			Reason
 *
 * 25th Oct 2022		----			-----
 *
 *
*********************************************/

#include<stdio.h>
#include<string.h>
#include"header.h"
#include<stdlib.h>


/********************************   FOR SUPPLIER   *****************************/

// ADD NEW SUPPLIER


/********************************************
 * *FUNCTION NAME : add_supplier 
 *
 * DESCRIPTION   : This function add the supplier  information by taking data as  *                 input from the  user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/

sud *start,*new,*ptr,*prev,*last;     //Strucutre pointers declared for supplier module related link list functions
std *start1,*new1,*ptr1,*prev1,*last1; //Strucutre pointers declared for stockist module related link list functions
prd *start2,*new2,*ptr2,*prev2,*last2;  //Structure pointers declared for products link list related operations
tra *start3,*new3,*ptr3,*prev3,*last3;  //Structures pointers declared for transactions link list related operations

int supplier_add_product(int mid)
{                                                   //add function starts here--

	if(!start2)
	{
		printf("There are no available products in the warehouse\n");
		return EXIT_FAILURE;
	}
	printf("\nThe available products are -\n");
	view_product();
	int n=0,a;
	char s[SIZE];
	char x[SIZE];
	while(n!=3)              //Loop will run 3 times max to accpet product IDs
	{
		printf("Enter product ID to add products \nPress 2 to exit \n");
		scanf("%s",s);
		if(valid_integer(s))
		{
			continue;
		}
		a=atoi(s);
		if(a==2)          
		{
			break;
		}
		for(ptr2=start2;(ptr2) && ptr2->id!=a;ptr2=ptr2->next);
		if(!ptr2)
		{
			printf("\nProduct ID not found\n");
			continue;
		}
		for(ptr=start;(ptr) && ptr->id!=mid;ptr=ptr->next);
		if(!ptr)
		{
			printf("\nSupplier ID %d not found\n",mid);
			return EXIT_FAILURE;
		}
		ptr->items_supplied[n]=a;
		while(1)
		{
			printf("\nEnter product quantity -\n");
			scanf("%s",x);
			if(valid_integer(x))
			{
				continue;
			}
			break;
		}
		ptr2->quantity=atoi(x)+ptr2->quantity;
		if(ptr2->quantity > ptr2->rol)
		{
			ptr2->status_indicator='N';
		}
		printf("\nEnter product unit price -\n");
		scanf("%lf",&ptr2->unit_price);
		n++;
	}
}                                               //The add function ends here.


/********************************************

* *FUNCTION NAME : supplier_edit_details
*
* DESCRIPTION   : This function edit the supplier personal information by taking *                 data as input from the supplier with respective validations.
*
* *RETURNS       : No Returns
*
*
*
*
*********************************************/

int supplier_edit_details(int mid)
{                                                //edit function starts here--
	if(!start)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	for(ptr=start;(ptr) && ptr->id!=mid;ptr=ptr->next);
	printf("\nOld name is - %s\nOld contact no. is - %lld\n",ptr->name,ptr->contact_no);
	char name[SIZE];
	char contact_no[SIZE];
	char ch[SIZE];
	char pass[SIZE];
	int f;
	while(1)
	{
		printf("Press 1 to change name\nPress 2 to change contact no\nPress 3 to change password\nPress 4 to exit\n");
		scanf("%s",ch);
		if(valid_choice(ch))
		{
			continue;
		}
		f=atoi(ch);
		if(f==1)
		{
			while(1)
			{
				printf("\nEnter new name-\n");
				scanf("%s",name);
				if(valid_name(name))
					continue;
				break;
			}
			strcpy(ptr->name,name);
		}
		else if(f==2)
		{
			while(1)
			{
				printf("\nEnter new contact no.-\n");
				scanf("%s",contact_no);
				if(valid_contact_num(contact_no))
					continue;
				break;
			}
			ptr->contact_no=atol(contact_no);
		}
		else if(f==3)
		{
			while(1)
			{
				printf("\nEnter new password(It should atleast have 4 characters, have an uppercase letter and a number and shouldn't contain /)-\n");
				scanf("%s",pass);
				if(valid_password(pass))
				{
					printf("Incorrect format\n");
					continue;
				}
				break;
			}
			strcpy(ptr->password,pass);
		}
		else if(f==4)
		{
			break;
		}
		else
		{
			printf("Invalid choice! Range must be between 1-3\n");
			continue;
		}
	}
	printf("Deatails edited successfully\n");
	return EXIT_SUCCESS;
}                                               //The edit function ends here.


/********************************************

* *FUNCTION NAME : view_selected_products
*
* DESCRIPTION   : This function view the selected product information by taking  *                 data as input from the supplier with respective validations.
*
* *RETURNS       : No Returns
*
*
*
*
*********************************************/

int view_selected_products(int mid)
{                                                  //view function starts here--
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	for(ptr=start;(ptr) && ptr->id!=mid;ptr=ptr->next);
	if(!ptr)
	{
		printf("\nSupplier ID %d not found for viewing products\n",mid);
		return EXIT_FAILURE;
	}
	printf("\nPRODUCT ID   PRODUCT NAME    QUANTITY    UNIT PRICE\n");
	int f=0;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		for(int i=0;i<3;i++)
		{
			if(ptr2->id==ptr->items_supplied[i])
			{
				printf("\n%3d-------%10s---------%3d---------%5.2lf\n",ptr2->id,ptr2->name,ptr2->quantity,ptr2->unit_price);
				f=1;
			}
		}
	}
	if(f==0)
	{
		printf("\nYou have not supplied any products\n");
	}
	printf("\n");
	return EXIT_SUCCESS;
}                                               //The view function ends here.



/********************************************

* *FUNCTION NAME : rol_check
*
* *DESCRIPTION   : This function check the product ROL(Re-Order-Level) by taking *                  data as input from the supplier with respective validations.
*
* *RETURNS       : No Returns
*
*
*
*
*********************************************/

int rol_check()
{                                             //rol_check function starts here--
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nPRODUCT ID   PRODUCT NAME    QUANTITY   ROL    UNIT PRICE\n");
	int f=0;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		if(ptr2->quantity <= ptr2->rol)
		{
                        printf("\n%d       %10s        %3d        %d        %5.2lf\n",ptr2->id,ptr2->name,ptr2->quantity,ptr2->rol,ptr2->unit_price);
			f=1;
		}
	}
	if(f==0)
	{
		printf("\nNo product is below the re order level\n");
	}
	printf("\n");
	return EXIT_SUCCESS;
}                                            //The rol_check function ends here.

int order_items(int mid)
{                                          //order function starts from here--
	if(!start2)
	{
		printf("\nThere are no available products\n");
		system("read a");
		return EXIT_FAILURE;
	}
	printf("\n------------List of products available in Warehouse------------\n");
	printf("\nSerial NO    Product ID     Product NAME    Product QUANTITY \n");
	int count=1;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		printf("\n%3d",count);
		printf(" %15d  %10s  %20d\n ",ptr2->id,ptr2->name,ptr2->quantity);
		count++;
	}
	int n=0,a;
	char s[SIZE];
	char x[SIZE];
	while(n!=3)
	{
		printf("\nEnter product ID to add products or press 2 to exit -\n");
		scanf("%s",s);
		if(valid_integer(s))
		{
			continue;
		}
		a=atoi(s);
		if(a==2)
		{
			break;
		}
		for(ptr2=start2;(ptr2) && ptr2->id!=a;ptr2=ptr2->next);
		if(!ptr2)
		{
			printf("\nProduct ID not found\n");
			continue;
		}
		for(ptr1=start1;(ptr1) && ptr1->id!=mid;ptr1=ptr1->next);
		ptr1->items_ordered[n]=a;
		while(1)
		{
			printf("\nEnter product quantity -\n");
			scanf("%s",x);
			if(valid_integer(x))
			{
				continue;
			}
			break;
		}
		int temp=ptr2->quantity-atoi(x);
		if(temp<0)
		{
			printf("Cannot order due to less quantity\n");
			continue;
		}
		ptr2->quantity=temp;
		if((new3=(tra*)calloc(1,sizeof(tra)))==NULL)
		{
			printf("\nMemory Allocation Failed\n");
			return EXIT_FAILURE;
		}
		new3->stockist_id=mid;
		new3->product_id=a;
		new3->product_quantity=atoi(x);
	        strcpy(new3->product_name,ptr2->name);	
	        strcpy(new3->stockist_name,ptr1->name);	
		if(!start3)
		{
			start3=new3;
			start3->next=NULL;
		}
		else
		{
			for(ptr3=start3;(ptr3);prev3=ptr3,ptr3=ptr3->next);
			prev3->next=new3;
			new3->next=ptr3;
		}
		n++;
	}
		return EXIT_SUCCESS;
}


	///    FOR DELETING THE SUPPLIER DETAILS


/********************************************
 * *FUNCTION NAME : del__supplier 
 *
 * *DESCRIPTION   : This function delete the supplier  information by taking data *                  as input from the user with respective validations.
}                                                     //order function ends here
*/

/********************************************
 * *FUNCTION NAME : view_stock 
 *
 * *DESCRIPTION   : This function views the stock information by taking data as
 *                  input from the stockist with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int view_stock()
{                                              //The view function starts here--
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nS.no    Product ID      NAME      ROL     Quantity\n");
	int count2=1;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		printf("\n%3d",count2);
		printf("\n%15d  %10s %15d  %20d\n",ptr2->id,ptr2->name,ptr2->rol,ptr2->quantity);
		count2++;
	}
	printf("\n");

}                                                //The view function ends here


/********************************************
 * *FUNCTION NAME : request_for_items
 *
 * *DESCRIPTION   : This function requests for items by taking data as an 
 * 		    input from the stockist with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/
int request_for_items(int id)
{
	char pid[SIZE];
	view_stock();
	if(!start2)
	{
		printf("There are no available products\n");
		system("read a");
		return EXIT_FAILURE;
	}
	while(1)
	{
		printf("Enter product ID for which to place request\n");
		scanf("%s",pid);
		if(valid_integer(pid))
			continue;
		break;
	}
	for(ptr2=start2;(ptr2) && ptr2->id!=atoi(pid);ptr2=ptr2->next);
	if(!ptr2)
	{
		printf("Product ID not found\n");
		return EXIT_FAILURE;
	}
	ptr2->status_indicator='Y';
	printf("Request placed\n");
	return EXIT_SUCCESS;
}
/*
                                              //The request function ends here.

*/
/********************************************
 * *FUNCTION NAME : stockist_edit_details 
 *
 * *DESCRIPTION   : This function edit the stockist personal details  by taking
 *                  data as an input from the stockist with respective 
 *                  validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int stockist_edit_details(int st_id)
{                                              // The edit function starts here--
	if(!start1)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
        for(ptr1=start1;(ptr1)&&ptr1->id!=st_id;ptr1=ptr1->next);
	printf("Old name is %s\nOld contact No %lld\n",ptr1->name,ptr1->contact_no);
	char name[SIZE];
	char contact_no[SIZE];
	char ch[SIZE];
	char pass[SIZE];
	int f;
	while(1)
	{
		printf("Press 1 to change name\nPress 2 to change contact no\nPress 3 to change password\nPress 4 to exit\n");
		scanf("%s",ch);
		if(valid_choice(ch))
		{
			continue;
		}
		f=atoi(ch);
		if(f==1)
		{
			while(1)
			{
				printf("\nEnter new name-\n");
				scanf("%s",name);
				if(valid_name(name))
					continue;
				break;
			}
			strcpy(ptr1->name,name);
		}
		else if(f==2)
		{
			while(1)
			{
				printf("\nEnter new contact no.-\n");
				scanf("%s",contact_no);
				if(valid_contact_num(contact_no))
					continue;
				break;
			}
			ptr1->contact_no=atoll(contact_no);
		}
		else if(f==3)
		{
			while(1)
			{
				printf("\nEnter new password(It should atleast have 4 characters, have an uppercase letter and a number and shouldn't contain /)-\n");
				scanf("%s",pass);
				if(valid_password(pass))
				{
					printf("Incorrect format\n");
					continue;
				}
				break;
			}
			strcpy(ptr->password,pass);
		}
		else if(f==4)
		{
			break;
		}
		else 
		{
			printf("Invalid choice! Enter a number in range 1-4\n");
		}
	}
	printf("Deatails edited successfully\n");
	return EXIT_SUCCESS;
}                                                 //The edit function ends here.
	
int add_supplier()
{
	if((new=(sud*)calloc(1,sizeof(sud)))==NULL)
	{
		printf("\nMemory Allocation Failed\n");
		return EXIT_FAILURE;
	}
	char name[SIZE];
	char pass[SIZE];
	while(1)
	{
		printf("Enter Supplier Name -");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(new->name,name);
	while(1)
	{
		printf("\nEnter new password(It should atleast have 4 characters, have an uppercase letter and a number and shouldn't contain /)-\n");
		scanf("%s",pass);
		if(valid_password(pass))
		{
			printf("Incorrect format\n");
			continue;
		}
		break;
	}
	strcpy(new->password,pass);
	char contact_no[SIZE];
	while(1)
	{
		printf("Enter Supplier Contact No -");
		scanf("%s",contact_no);
		if(valid_contact_num(contact_no))
			continue;
		break;
	}
	new->contact_no=atoll(contact_no);
	new->items_supplied[0]=0;
	new->items_supplied[1]=0;
	new->items_supplied[2]=0;
	if(!start)
	{
		start=new;
		new->id=200;
		new->next=NULL;
	}
	else
	{
		for(ptr=start;(ptr);prev=ptr,ptr=ptr->next);
		new->id=prev->id+1;
		prev->next=new;
		new->next=ptr;
	}
	printf("Supplier ID is - %d\n",new->id);
	return EXIT_SUCCESS;
}


///    FOR DELETING THE SUPPLIER DETAILS


/********************************************
 * *FUNCTION NAME : del__supplier 
 *
 * *DESCRIPTION   : This function delete the supplier  information by taking data *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int del_supplier()
{
	if(!start)
	{
		printf("\n Empty List\n");
		return EXIT_FAILURE;
	}
	char x[SIZE];
	while(1)
	{
		printf("\n Enter Supplier ID to delete -");
		scanf("%s",x);
		if(valid_integer(x))
		{
			continue;
		}
		break;
	}
	int f=atoi(x);
	if(f==start->id)
	{
		ptr=start;
		start=start->next;
		free(ptr);
	}
	else
	{
		for(ptr=start;(ptr)&& ptr->id!=f;prev=ptr,ptr=ptr->next);
		if(!ptr)
		{
			printf("\nSupplier id %d not found for deletion\n",atoi(x));
			return EXIT_FAILURE;
		}
		prev->next=ptr->next;
		free(ptr);
	}
	printf("Supplier ID %d deleted successfully\n",f);
	return EXIT_SUCCESS;
}


// FOR EDITING SUPPLIER


/********************************************
 * *FUNCTION NAME : edit_supplier 
 *
 * *DESCRIPTION   : This function edit the supplier  information by taking data
 *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
 *********************************************/


int edit_supplier()
{
	if(!start)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	char x[SIZE];
	while(1)
	{
		printf("\nEnter the Supplier ID for editing -\n");
		scanf("%s",x);
		if(valid_integer(x))
		{
			continue;
		}
		break;
	}
	int f=atoi(x);
	for(ptr=start;(ptr)&& ptr->id!=f;prev=ptr,ptr=ptr->next);
	if(!ptr)
	{
		printf("\nSupplier id %d not found for editing\n",f);
		return EXIT_FAILURE;
	}
	printf("\nOld name is - %s\nOld contact no is - %lld\n",ptr->name,ptr->contact_no,ptr->items_supplied[0],ptr->items_supplied[1],ptr->items_supplied[2]);
	char name[SIZE];
	char contact_no[SIZE];
	while(1)
	{
		printf("\nEnter new name-\n");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(ptr->name,name);
	while(1)
	{
		printf("\nEnter new contact no.-\n");
		scanf("%s",contact_no);
		if(valid_contact_num(contact_no))
			continue;
		break;
	}
	ptr->contact_no=atoll(contact_no);
	printf("\nSupplier ID %d is edited successfully\n",f);
	return EXIT_SUCCESS;
}

// FOR VIEWING FUNCTION


/********************************************
 * *FUNCTION NAME : view_supplier 
 *
 * *DESCRIPTION   : This function views the supplier information by taking data
 *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int view_supplier()
{
	if(!start)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\n Supplier ID       Supplier NAME    Supplier CONTACT    Product ID's\n");
	for(ptr=start;(ptr);ptr=ptr->next)
	{
		printf("\n%d--%s --%s---%lld--%d, %d, %d\n ",ptr->id,ptr->name,ptr->password,ptr->contact_no,ptr->items_supplied[0],ptr->items_supplied[1],ptr->items_supplied[2]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}


/******************END OF SUPPLIER FUNCTION *************/



/****************  FOR STOCKIST ***********/



/********************************************
 * *FUNCTION NAME : add_stockist 
 *
 * *DESCRIPTION   : This function add the stockist  information by taking data as *                  input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/



int add_stockist()
{
	if((new1=(std*)calloc(1,sizeof(std)))==NULL)
	{
		printf("\nMemory Allocation Failed\n");
		return EXIT_FAILURE;
	}
	char name[SIZE];
	char pass[SIZE];
	char contact_no[SIZE];
	while(1)
	{
		printf("\nEnter stockist name-\n");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(new1->name,name);
	while(1)
	{
		printf("\nEnter new password(It should atleast have 4 characters, have an uppercase letter and a number and shouldn't contain /)-\n");
		scanf("%s",pass);
		if(valid_password(pass))
		{
			printf("Incorrect format\n");
			continue;
		}
		break;
	}
	strcpy(new1->password,pass);
	while(1)
	{
		printf("\nEnter stockist contact no.-\n");
		scanf("%s",contact_no);
		if(valid_contact_num(contact_no))
			continue;
		break;
	}
	new1->contact_no=atoll(contact_no);
	new1->items_ordered[0]=0;
	new1->items_ordered[1]=0;
	new1->items_ordered[2]=0;
	if(!start1)
	{
		start1=new1;
		new1->id=100;
		new1->next=NULL;
	}
	else
	{
		for(ptr1=start1;(ptr1);prev1=ptr1,ptr1=ptr1->next);
		prev1->next=new1;
		new1->id=prev1->id+1;
		new1->next=ptr1;
	}
	printf("\nStockist ID is - %d\n",new1->id);
	return EXIT_SUCCESS;
}

int check_status(int id)
{
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nPRODUCT ID   PRODUCT NAME    QUANTITY   ROL    UNIT PRICE\n");
	int f;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		if(ptr2->status_indicator== 'Y')
		{
                        printf("\n%d---%10s---%3d---%d---%5.2lf\n",ptr2->id,ptr2->name,ptr2->quantity,ptr2->rol,ptr2->unit_price);
			f=1;
		}
	}
	if(f==0)
	{
		printf("\nThere are no products that need urgent supply\n");
		return EXIT_FAILURE;
	}
	int n=0,a;
	char s[SIZE];
	char x[SIZE];
	while(n!=3)
	{
		printf("\nEnter product ID to add products or press 2 to exit -\n");
		scanf("%s",s);
		if(valid_integer(s))
		{
			continue;
		}
		a=atoi(s);
		if(a==2)
		{
			break;
		}
		for(ptr2=start2;(ptr2) && ptr2->id!=a;ptr2=ptr2->next);
		if(!ptr2)
		{
			printf("\nProduct ID not found\n");
			continue;
		}
        	for(ptr=start;(ptr) && ptr->id!=id;ptr=ptr->next);
        	if(!ptr)
         	{
	        	printf("\nSupplier ID %d not found\n",id);
	        	return EXIT_FAILURE;
        	}
		ptr->items_supplied[n]=a;
		while(1)
		{
			printf("\nEnter product quantity -\n");
			scanf("%s",x);
			if(valid_integer(x))
			{
				continue;
			}
			break;
		}
		ptr2->quantity=atoi(x)+ptr2->quantity;
		if(ptr2->quantity > ptr2->rol)
		{
			ptr2->status_indicator='N';
		}
		printf("\nEnter product unit_price -\n");
		scanf("%lf",&ptr2->unit_price);
		n++;
	}
	printf("\n");
	return EXIT_SUCCESS;
}
//  FOR DELETE STOCKIST


/********************************************
 * *FUNCTION NAME : del_stockist 
 *
 * *DESCRIPTION   : This function delete the stockist information by taking data  *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int del_stockist()
{
	if(!start1)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	char x[SIZE];
	while(1)
	{
		printf("\nEnter stockist ID to delete -\n");
		scanf("%s",x);
		if(valid_integer(x))
			continue;
		break;
	}
	int f=atoi(x);
	if(f==start1->id)
	{
		ptr1=start1;
		start1=start1->next;
		free(ptr1);
	}
	else
	{
		for(ptr1=start1;(ptr1)&& ptr1->id!=f;prev1=ptr1,ptr1=ptr1->next);
		if(!ptr1)
		{
			printf("\nStockist id %d not found for deletion\n",f);
			return EXIT_FAILURE;
		}
		prev1->next=ptr1->next;
		free(ptr1);
		printf("\nStockist ID %d deleted successfuly\n",f);
	}
	return EXIT_SUCCESS;
}

// FOR EDIT STOCKIST

/********************************************
 * *FUNCTION NAME : edit_stockist 
 *
 * *DESCRIPTION   : This function edits the stockist information by taking data
 *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int edit_stockist()
{
	if(!start1)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	char edit[SIZE];
	while(1)
	{
		printf("\nEnter the stockist ID for editing -\n");
		scanf("%s",edit);
		if(valid_integer(edit))
			continue;
		break;
	}
	for(ptr1=start1;(ptr1)&& ptr1->id!=atoi(edit);prev1=ptr1,ptr1=ptr1->next);
	if(!ptr1)
	{
		printf("\nStockist id %d not found for editing\n",atoi(edit));
		return EXIT_FAILURE;
	}
	printf("\nOld name is - %s\nOld contact no is - %lld\n",ptr1->name,ptr1->contact_no);
	char name[SIZE];
	char contact_no[SIZE];
	while(1)
	{
		printf("\nEnter new name-\n");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(new1->name,name);
	while(1)
	{
		printf("\nEnter new contact no.-\n");
		scanf("%s",contact_no);
		if(valid_contact_num(contact_no))
			continue;
		break;
	}
	new1->contact_no=atoll(contact_no);
	return EXIT_SUCCESS;
       	
}


///  FOR VIEW STOCKIST


/********************************************
 * *FUNCTION NAME : view_stockist 
 *
 * *DESCRIPTION   : This function view the stockist  information by taking data
 *                  as input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int view_stockist()
{
	if(!start1)
	{
		printf("\n Empty List\n");
		return EXIT_FAILURE;
	}
	printf("\nStockist ID       Stockist NAME    Stockist CONTACT\n");
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
		printf("\n %d--%s --%s---%lld----%d, %d, %d\n",ptr1->id,ptr1->name,ptr1->password,ptr1->contact_no,ptr1->items_ordered[0],ptr1->items_ordered[1],ptr1->items_ordered[2]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}


/**********  End of STOCKIST **********/


/********************************************
 * *FUNCTION NAME : add_product 
 *
 * *DESCRIPTION   : This function add the product information by taking data as   *                  input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/


int add_product()
{
	if((new2=(prd*)calloc(1,sizeof(prd)))==NULL)
	{
		printf("\nMemory Allocation Failed...\n");
		return EXIT_FAILURE;
	}
	char name[SIZE];
	while(1)
	{
		printf("\nEnter product Name -\n");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(new2->name,name);
	char rol[SIZE];
	while(1)
	{
		printf("\nEnter the ROL -\n");
		scanf("%s",rol);
		if(valid_integer(rol))
			continue;
		break;
	}
	new2->rol=atoi(rol);
	new2->quantity=0;
	new2->unit_price=0;
	new2->status_indicator='N';
	if(!start2)
	{
		start2=new2;
		new2->id=300;
		new2->next=NULL;
	}
	else
	{
		for(ptr2=start2;(ptr2);prev2=ptr2,ptr2=ptr2->next);
		new2->id=prev2->id+1;
		prev2->next=new2;
		new2->next=ptr2;
	}
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : del_product 
 *
 * *DESCRIPTION   : This function delete the product  information by taking data  *                  as input from the  user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/



int del_product()
{
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	char x[SIZE];
	while(1)
	{
		printf("\nEnter Product Id to delete -\n");
		scanf("%s",x);
		if(valid_integer(x))
			continue;
		break;
	}
	int f=atoi(x);
	if(f==start2->id)
	{
		ptr2=start2;
		start2=start2->next;
		free(ptr2);
	}
	else
	{
		for(ptr2=start2;(ptr2)&& ptr2->id!=f;prev2=ptr2,ptr2=ptr2->next);
		if(!ptr2)
		{
			printf("\nProduct id %d not found for deletion\n",f);
			return EXIT_FAILURE;
		}
		prev2->next=ptr2->next;
		free(ptr2);
	}
	printf("Product ID %d deleted successfully\n",f);
	return EXIT_SUCCESS;

}


/********************************************
 * *FUNCTION NAME : edit_product 
 *
 * *DESCRIPTION   : This function edit the product information by taking data as  *                  input from the  user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/



int edit_product()
{
	if(!start2)
	{
		printf("\n Empty List\n");
		return EXIT_FAILURE;
	}
	char edit[SIZE];
	while(1)
	{
		printf("\nEnter the Product ID for editing -\n");
		scanf("%s",edit);
		if(valid_integer(edit))
			continue;
		break;
	}
	for(ptr2=start2;(ptr2)&& ptr2->id!=atoi(edit);prev2=ptr2,ptr2=ptr2->next);
	if(!ptr2)
	{
		printf("\nProduct id %d not found for editing\n",atoi(edit));
		return EXIT_FAILURE;
	}
	printf("\nOld name is - %s\nOld ROL is - %d\nOld quantity is - %d\nOld unit_price is - %lf\n",ptr2->name,ptr2->rol,ptr2->quantity,ptr2->unit_price);
	char name[SIZE];
	char rol[SIZE];
	char quantity[SIZE];
	while(1)
	{
		printf("\nEnter new name -\n");
		scanf("%s",name);
		if(valid_name(name))
			continue;
		break;
	}
	strcpy(ptr2->name,name);
	while(1)
	{
		printf("\nEnter new ROL -\n");
		scanf("%s",rol);
		if(valid_integer(rol))
			continue;
		break;
	}
	ptr2->rol=atoi(rol);
	while(1)
	{
		printf("\nEnter new quantity -\n");
		scanf("%s",quantity);
		if(valid_integer(quantity))
			continue;
		break;
	}
	ptr2->quantity=atoi(quantity);
	printf("\nEnter new unit price -\n");
	scanf("%lf",&ptr2->unit_price);
	printf("Product ID %d edited successfully\n",atoi(edit));
	return EXIT_SUCCESS;

}


/********************************************
 * *FUNCTION NAME : view_product 
 *
 * *DESCRIPTION   : This function view the product information by taking data as  *                  input from the user with respective validations.
 *
 * *RETURNS       : No Returns
 *
 *
 *
 *
*********************************************/



int view_product()
{
	if(!start2)
	{
		printf("\nEmpty List\n");
		return EXIT_FAILURE;
	}
	printf("\nProduct ID       Product NAME      ROL    QUANTITY   UNIT_PRICE \n");
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		printf("\n%d--%s --%d --%d --%lf---%c\n",ptr2->id,ptr2->name,ptr2->rol,ptr2->quantity,ptr2->unit_price,ptr2->status_indicator);
	}
	printf("\n");
	return EXIT_SUCCESS;
}


/******************** FILE READ WRITEs  ***********/


/********************************************
 * *FUNCTION NAME : file_to_list_supplier 
 *
 * *DESCRIPTION   : This function allocate memory for the supplier to open and 
 *                   read the file from beginning till end of file and put each
 *                   supplier into the list.
 *
 * *RETURNS       : No Returns 
 *
 *
 *
*********************************************/


int file_to_list_supplier()
{
	FILE *p;
	tr t1;
	if((p=fopen("Supplier","rb"))==NULL)
	{
		printf("\nSupplier File is not there to read from\n");
		return EXIT_FAILURE;
	}
	fread(&t1,sizeof(tr),1,p);
	while(!feof(p))
	{
		if((new=(sud*)calloc(1,sizeof(sud)))==NULL)
		{
			printf("\nMemory Allocation Failed...\n");
			return EXIT_FAILURE;
		}
		new->id=t1.id;
		strcpy(new->name,t1.name);
		strcpy(new->password,t1.password);
		new->contact_no=t1.contact_no;
		new->items_supplied[0]=t1.items_supplied[0];
		new->items_supplied[1]=t1.items_supplied[1];
		new->items_supplied[2]=t1.items_supplied[2];
		if(!start)
		{
			start=last=new;
			new->next=NULL;
		}
		else
		{
			last->next=new;
			last=new;
			new->next=NULL;
		}
		fread(&t1,sizeof(tr),1,p);
	}
	fclose(p);
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : list_to_file_supplier 
 *
 * *DESCRIPTION   : This function is used to write supplier data into the file
 * 		    by traversing the list.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int list_to_file_supplier()
{
	tr t2;
	if(!start)
	{
		printf("\nSupplier List is empty...\n");
		return EXIT_FAILURE;
	}
	FILE *p1;
	if((p1=fopen("Supplier","wb"))==NULL)
	{
		printf("\nSupplier File is not there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr=start;(ptr);prev=ptr,ptr=ptr->next)
	{
		t2.id=ptr->id;
		strcpy(t2.name,ptr->name);
		strcpy(t2.password,ptr->password);
		t2.contact_no=ptr->contact_no;
		t2.items_supplied[0]=ptr->items_supplied[0];
		t2.items_supplied[1]=ptr->items_supplied[1];
		t2.items_supplied[2]=ptr->items_supplied[2];
		fwrite(&t2,sizeof(tr),1,p1);
//		free(prev);
	}
	fclose(p1);
//	free(prev);
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : file_to_list_stockist 
 *
 * *DESCRIPTION   : This function allocate memory for the stockist to open and
 *                  read the file from beginning till end of file and put each
 *                  stockist into the list.
 *
 * *RETURNS       : No Returns 
 *
 *
 *
*********************************************/


int file_to_list_stockist()
{
	FILE *p;
	tr1 t1;
	if((p=fopen("Stockist","rb"))==NULL)
	{
		printf("\nStockist File is not there to read from\n");
		return EXIT_FAILURE;
	}
	fread(&t1,sizeof(tr1),1,p);
	while(!feof(p))
	{
		
		if((new1=(std *)calloc(1,sizeof(std)))==NULL)
		{
			printf("\nMemory Allocation Failed\n");
			return EXIT_FAILURE;
		}
		new1->id=t1.id;
		strcpy(new1->name,t1.name);
		strcpy(new1->password,t1.password);
		new1->contact_no=t1.contact_no;
		new1->items_ordered[0]=t1.items_ordered[0];
		new1->items_ordered[1]=t1.items_ordered[1];
		new1->items_ordered[2]=t1.items_ordered[2];
		if(!start1)
		{
			start1=last1=new1;
			new1->next=NULL;
		}
		else
		{
			last1->next=new1;
			last1=new1;
			new1->next=NULL;
		}
		fread(&t1,sizeof(tr1),1,p);
	}
	fclose(p);
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : list_to_file_stockist 
 *
 * *DESCRIPTION   : This function is used to write stockist data into the file
 * 		    by traversing the list.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int list_to_file_stockist()
{
	tr1 t2;
	if(!start1)
	{
		printf("\nStockist List is empty\n");
		return EXIT_FAILURE;
	}
	FILE *p1;
	if((p1=fopen("Stockist","wb"))==NULL)
	{
		printf("\nStockist File is not there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr1=start1;(ptr1);prev1=ptr1,ptr1=ptr1->next)
	{
		t2.id=ptr1->id;
		strcpy(t2.name,ptr1->name);
		strcpy(t2.password,ptr1->password);
		t2.contact_no=ptr1->contact_no;
		t2.items_ordered[0]=ptr1->items_ordered[0];
		t2.items_ordered[1]=ptr1->items_ordered[1];
		t2.items_ordered[2]=ptr1->items_ordered[2];
		fwrite(&t2,sizeof(tr1),1,p1);
//		free(prev1);
	}
	fclose(p1);
//	free(prev1);
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : file_to_list_product 
 *
 * *DESCRIPTION   : This function allocate memory for the admin,supplier or 
 *                  stockist to open and read the file from beginning till end of *                  file and put each supplier into the list.
 *
 * *RETURNS       : No Returns 
 *
 *
 *
*********************************************/


int file_to_list_product()
{
	FILE *p;
	tr2 t1;
	if((p=fopen("Product","rb"))==NULL)
	{
		printf("\nProduct File is not there to read from\n");
		return EXIT_FAILURE;
	}
	fread(&t1,sizeof(tr2),1,p);
	while(!feof(p))
	{
		if((new2=(prd*)calloc(1,sizeof(prd)))==NULL)
		{
			printf("\nMemory Allocation Failed\n");
			return EXIT_FAILURE;
		}
		new2->id=t1.id;
		strcpy(new2->name,t1.name);
		new2->rol=t1.rol;
		new2->quantity=t1.quantity;
		new2->unit_price=t1.unit_price;
		new2->status_indicator=t1.status_indicator;
		if(!start2)
		{
			start2=last2=new2;
			new2->next=NULL;
		}
		else
		{
			last2->next=new2;
			last2=new2;
			new2->next=NULL;
		}
		fread(&t1,sizeof(tr2),1,p);
	}
	fclose(p);
	return EXIT_SUCCESS;
}


/********************************************
 * *FUNCTION NAME : list_to_file_product 
 *
 * *DESCRIPTION   : This function is used to write product data into the file
 * 		    by traversing the list.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int list_to_file_product()
{
	tr2 t2;
	prd *pr;
	if(!start2)
	{
		printf("\nProduct List is empty\n");
		return EXIT_FAILURE;
	}
	FILE *p1;
	if((p1=fopen("Product","wb"))==NULL)
	{
		printf("\nProduct File is not there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr2=start2;(ptr2);prev2=ptr2,ptr2=ptr2->next)
	{
		t2.id=ptr2->id;
		strcpy(t2.name,ptr2->name);
		t2.rol=ptr2->rol;
		t2.quantity=ptr2->quantity;
		t2.unit_price=ptr2->unit_price;
		t2.status_indicator=ptr2->status_indicator;
		fwrite(&t2,sizeof(tr2),1,p1);
//		free(prev2);
	}
	fclose(p1);
//	free(prev2);
	return EXIT_SUCCESS;
}

/********************************************
 * *FUNCTION NAME : file_to_list_transaction 
 *
 * *DESCRIPTION   : This function allocate memory for the admin to open and 
 *                   read the file from beginning till end of file and put each
 *                   transaction into the list.
 *
 * *RETURNS       : No Returns 
 *
 *
 *
*********************************************/


int file_to_list_transaction()
{
	FILE *p;
	tr4 t1;
	if((p=fopen("Transaction_file","rb"))==NULL)
	{
		printf("\nTransaction File is not there to read from\n");
		return EXIT_FAILURE;
	}
	fread(&t1,sizeof(tr4),1,p);
	while(!feof(p))
	{
		if((new3=(tra *)calloc(1,sizeof(tra)))==NULL)
		{
			printf("\n Memory Allocation failed\n");
			return EXIT_FAILURE;
		}
		new3->stockist_id=t1.stockist_id;
		new3->product_id=t1.product_id;
		new3->product_quantity=t1.product_quantity;
		strcpy(new3->product_name,t1.product_name);
                strcpy(new3->stockist_name,t1.stockist_name);
		if(!start3)
		{
			start3=last3=new3;
			new3->next=NULL;
		}
		else
		{
			last3->next=new3;
			last3=new3;
			new3->next=NULL;
		}
		fread(&t1,sizeof(tr4),1,p);
	}
	fclose(p);
	return EXIT_SUCCESS;
}

/********************************************
 * *FUNCTION NAME : list_to_file_transaction 
 *
 * *DESCRIPTION   : This function is used to write transaction data into the file
 * 		    by traversing the list.
 *
 * *RETURNS       : No Returns
 *
 *
 *
*********************************************/


int list_to_file_transaction()
{
	tr4 t2;
	if(!start3)
	{
		printf("\nTransaction List is Empty \n");
		return EXIT_FAILURE;
	}
	FILE *p1;
	if((p1=fopen("Transaction_file","wb"))==NULL)
	{
		printf("\nTransaction File is not there to read from\n");
		return EXIT_FAILURE;
	}
	for(ptr3=start3;(ptr3);prev3=ptr3,ptr3=ptr3->next)
	{
		t2.stockist_id=ptr3->stockist_id;
		t2.product_id=ptr3->product_id;
		t2.product_quantity=ptr3->product_quantity;
		strcpy(t2.product_name,ptr3->product_name);
                strcpy(t2.stockist_name,ptr3->stockist_name);
		fwrite(&t2,sizeof(tr4),1,p1);
//		free(prev3);
	}
	fclose(p1);
//	free(prev3);
	return EXIT_SUCCESS;
}



/*********************************************************
 * *  FILENAME   : display_report
 *
 * * DESCRIPTION : This function generates various reports about the product and
 *                 stockist details using the database.
 *
 *
 * * RETURNS     : Returns report
 *
 * 
 * 
 ********************************************************/

int display_report()
{
	if(!start3)
	{
		printf("Transaction file is empty\n");
		return EXIT_FAILURE;
	}
	printf("Transactions file\n");
	printf("PRODUCT ID     STOCKIST ID    PRODUCT NAME    STOCKIST NAME     PRODUCT QUANTITY\n");
	for(ptr3=start3;(ptr3);ptr3=ptr3->next)
	{
        printf("%d------------    %d-----------  %s--------------  %s-----------------   %d\n",ptr3->product_id, ptr3->stockist_id, ptr3->product_name, ptr3->stockist_name, ptr3->product_quantity);
	}
	return EXIT_SUCCESS;
}

//stockist_order_items


/*********************************************************
 * *  FILENAME   : display_report_item
 *
 * * DESCRIPTION : This function generates various reports about the product on
 * high demand details using the database.
 *
 *
 * * RETURNS     : Returns report
 *
 * 
 * 
 ********************************************************/

int display_report_item()
{
	if(!start3 || !start2)
	{
		printf("Product/Transaction file is empty\n");
		return EXIT_FAILURE;
	}
	int count;
	for(ptr2=start2;(ptr2);ptr2=ptr2->next)
	{
		count=0;
		for(ptr3=start3;(ptr3);ptr3=ptr3->next)
		{
			if(ptr2->id==ptr3->product_id)
			{
				count++;
			}
		}
		if(count>=5)
		{
			printf("%s is in high demand\n",ptr2->name);
		}
	}
	return EXIT_SUCCESS;
}


/*********************************************************
 **  FILENAME   : display_report_stockist
 *
 * * DESCRIPTION : This function generates various reports about the frequent
 *                 transaction details using the database.
 *
 *
 * * RETURNS     : Returns report
 *
 * 
 * 
 ********************************************************/


int display_report_stockist()
{
	if(!ptr3)
	{
		printf("Transaction file s empty\n");
		return EXIT_FAILURE;
	}
	int count;
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
		count=0;
		for(ptr3=start3;(ptr3);ptr3=ptr3->next)
		{
			if(ptr1->id == ptr3->stockist_id)
			{
				count++;
			}
		}
		if(count>=5)
		{
			printf("%s (%d) has made frequent transactions\n",ptr1->name,ptr1->id);
		}
	}
	return EXIT_SUCCESS;
}

/*********************************************************
 * *  FILENAME   : verify(int k,int id,char *pass1)
 *
 * * DESCRIPTION : This function verifies the password.
 *
 *
 * * RETURNS     : returns 1 if the password and ID are
 *                 verified else 0
 *
 * 
 * 
 ********************************************************/
int verify(int k,int id,char *pass1)
{
	if(k==1)
	{
		for(ptr=start;(ptr);ptr=ptr->next)
		{
	//		printf("%s  %s",ptr->password,pass1);
			if((!strcmp(ptr->password,pass1))&&(ptr->id==id))
			{
				return 1;
			}
		}
	}
	if(k==2)
	{
		for(ptr1=start1;(ptr1);ptr1=ptr1->next)
		{
			if((!strcmp(ptr1->password,pass1))&&(ptr1->id==id))
			{
				return 1;
			}
		}
	}
	printf("\nIncorrect Password\n");
	system("read a");
	return 0;
}
