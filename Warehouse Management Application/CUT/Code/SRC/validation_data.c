#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "../header/header.h"

int valid_name(char *str)
{	
	if(strlen(str)>MAX)
	{
		printf("\nINVALID NAME-(Name should be less than 10 characters.)\n");
		return 1;
	}
	if(strlen(str)==0)
	{
		printf("\nINVALID-(Name should not be empty!)\n");
		return 1;
	}
	int flag=0;
	int i;
	for(i=0;i<strlen(str);i++)
	{
		if(!isalpha(str[i]))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("INVALID NAME-(Name contain only Alphabets.)\n");
		return 1;
	}
	return 0;
}
int valid_contact_num(char *num)
{
	int flag=0,i;
	if(strlen(num)!=MAX)
	{
		printf(" INVALID INPUT-(Contact number should only have 10 digits.)\n");
		return 1;
	}
	for(i=0;i<MAX;i++)
	{
		if(!isdigit(num[i]))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("INVALID INPUT-(Contact number should be in digits.)\n");
		return 1;
	}
	return 0;
}

int valid_integer(char *num)
{
	if(strlen(num)>MAX)
	{
		printf("INVALID-(Interger limit exceeded!)\n");
		return 1;
	}
	int flag=0,i;
	for(i=0;num[i]!='\0';i++)
	{
		if(!isdigit(num[i]))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("INVALID-(Number is always in digit.)\n");
		return 1;
	}
	return 0;
}


int valid_choice(char *num)
{
	int flag=0,i;
	if(strlen(num)!=SIZE1)
	{
		printf("INVALID-(Enter valid input.)\n");
		return 1;
	}
	for(i=0;num[i]!='\0';i++)
	{
		if(!isdigit(num[i]))
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("INVALID-(Number is always in digit.)\n");
		return 1;
	}
	return 0;
}
int valid_password(char *pass)
{
	
	if(strlen(pass)<4)
	{
		return 1;
	}
	int f1=0,f2=0;
	for(int i=0;i<strlen(pass);i++)
	{
		if(pass[i]=='/')
			return 1;
		else if(isupper(pass[i]))
			f1=1;
		else if(isdigit(pass[i]))
			f2=1;
	}
	if(f1==1 && f2==1)
		return 0;
	else
		return 1;
		
}


