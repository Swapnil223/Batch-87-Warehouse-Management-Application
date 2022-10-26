#ifndef HEADER_H
#define HEADER_H

#define SIZE 15
#define MAX 10
#define SIZE1 1

typedef struct supplier_details
{
	int id;
	char name[20];
	char password[20];
	long long int contact_no;
	int items_supplied[3];
	struct supplier_details *next;
}sud;

typedef struct stockist_details
{
	int id;
	char name[20];
	char password[20];
	long long int contact_no;
	int items_ordered[3];
	struct stockist_details *next;
}std;

typedef struct product_details 
{
	int id;
	char name[20];
	int rol;
	int quantity;
	double unit_price;
	char status_indicator;
	struct product_details *next;
}prd;

typedef struct transactions
{
	int stockist_id;
	int product_id;
	int product_quantity;
	char product_name[20];
	char stockist_name[20];
	struct transactions *next;
}tra;

typedef struct temp4
{
	int stockist_id;
	int product_id;
	int product_quantity;
	char product_name[20];
	char stockist_name[20];
}tr4;

typedef struct temp
{
	int id;
	char name[20];
	char password[20];
	long long int contact_no;
	int items_supplied[3];
}tr;

typedef struct temp2
{
	int id;
	char name[20];
	char password[20];
	long long int contact_no;
	int items_ordered[3];
}tr1;

typedef struct temp3
{
	int id;
	char name[20];
	int rol;
	int quantity;
	double unit_price;
	char status_indicator;
}tr2;

//functions from supplier_module.c
int supplier_add_product();
int supplier_edit_product();
int supplier_delete_product();
int supplier_edit_details();
int view_selected_products();
int rol_check();
int check_status();

//functions from stockist_module.c
int order_items(int );
int view_stock();
int request_for_items();
int stockist_edit_details(int );

//functions from admin_file_maintenance.c
int add_supplier();
int del_supplier();
int edit_supplier();
int view_supplier();
int add_stockist();
int del_stockist();
int edit_stockist();
int view_stockist();
int add_product();
int del_product();
int edit_product();
int view_product();

//functions from admin_module.c
int menu(int );
int display_report();
int display_report_item();
int display_report_stockist();
int admin_module();
int verify(int ,int , char *);
int login();
int create();

// FOR file
int file_to_list_supplier();
int list_to_file_supplier();
int file_to_list_stockist();
int list_to_file_stockist();
int file_to_list_product();
int list_to_file_product();
int file_to_list_transaction();
int list_to_file_transaction();

//functions from validation_data.c
int valid_name(char *);
int valid_contact_num(char *num);
int valid_integer(char *num);
int valid_choice(char *num);

#endif 

