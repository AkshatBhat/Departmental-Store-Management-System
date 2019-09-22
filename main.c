#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
int add();
int delete();
int print_bill();
int insert();
int print_table();
int search();
int remov();
int price1;
 sqlite3 *db;
    int rc;
    char *zErrMsg = 0;
 static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
 static int callback2(void *data, int argc, char **argv, char**azColName){
  price1 = atoi(argv[argc-1]); 
 return 0;
 }

struct product
{
	char name[40], type[40];
    int quantity, id;
    int price;
};


int main(int argc, char **argv)
{   
	rc = 0;
  int N;
	rc = sqlite3_open("database.db", &db);
	if(rc)
	{
	  printf("error");}
	else 
	{
		printf("database opened");
		
	}
	printf(" \n \t ==============================================================\n");
    printf("  \t \t \t \t  WELCOME TO \n \t \t \n \t \t \t THE SUPREME DEPARTMENTAL STORE  \n");
	printf("  \t ==============================================================\n");
	printf(" \n \n ");
	while(1)
	{
	printf(" \t \t \t \t   MAIN MENU \n ");
	printf(" \n \n ");
	printf(" \t \t \t  1)Press 1 to CALCULATE BILL \n ");
	printf(" \t \t \t  2)Press 2 to ADD GOODS \n ");
	printf(" \t \t \t  3)Press 3 to DELETE GOODS \n ");
	printf(" \t \t \t  4)Press 4 to DISPLAY ALL GOODS \n ");
	printf(" \t \t \t  5)Press 5 to REMOVE GOODS \n ");
	printf(" \t \t \t  6)Press 6 to SEARCH GOODS \n ");
	printf(" \t \t \t  7)Press 7 to INSERT GOODS \n ");
	printf(" \t \t \t  8)Press 8 to EXIT PROGRAM \n ");
	printf(" \t \t \t  Enter your choice : ");
	scanf("%d",&N);
	switch(N)
	{
	case 1:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   CALCULATE BILL\n");
	printf(" \t ==============================================================\n");
    print_bill();
	break;
	
	case 2:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   ADD GOODS \n");
	printf(" \t ==============================================================\n");
    add();
    break;
	
	case 3:
	printf("\t  ==============================================================\n");
    printf(" \t \t \t \t   DELETE GOODS \n");
	printf(" ==============================================================\n");
    delete();
	break;
	
	case 4:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   DISPLAY ALL GOODS \n");
	printf(" \t ==============================================================\n");
    print_table();
	break;
	
	case 5:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   REMOVE GOODS \n");
	printf(" \t ==============================================================\n");
    remov(); 
	break;
	
	case 6:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   SEARCH GOODS \n");
	printf(" \t ==============================================================\n");
    search();
	break;
	
	case 7:
	printf(" \t ==============================================================\n");
    printf(" \t \t \t \t   INSERT GOODS \n");
	printf(" \t ==============================================================\n");
    insert();
	break;
	
	case 8:
	sqlite3_close(db);
	return 0;
	
	default:
	printf(" Please enter a VALID CHOICE \n");
	}
	}
	
	
  sqlite3_close(db);
    return 0;
}
int add()
{   
  struct product prod;
	char sql[100];
	const char* data = "Callback function called";
  printf("\nENTER NAME OF PRODUCT\n");
  scanf(" %[^\n]s",prod.name);
  printf("ENTER THE QUANTITY OF PRODUCT\n");
  scanf(" %d",&prod.quantity);
	sprintf(sql,"UPDATE Store SET QUANTITY = QUANTITY + %d WHERE PRODUCTNAME = '%s'; \nSELECT * FROM Store ;",prod.quantity,prod.name);
  rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
  else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;
}   
int insert()
{
	struct product prod;
	char sql[100];
	const char* data = "Callback function called";
  printf("\nENTER NAME OF PRODUCT\n");
  scanf(" %[^\n]s",prod.name);
  printf("ENTER PRICE\n");
  scanf("%d",&prod.price);
	printf("\nENTER TYPE\n");
	scanf(" %[^\n]s",prod.type);
  printf("\nENTER THE QUANTITY OF PRODUCT\n");
  scanf(" %d",&prod.quantity);
  printf("\nENTER ID");
  scanf("%d",&prod.id);
	sprintf(sql,"INSERT INTO Store(PRODUCTID, PRODUCTNAME, TYPE, QUANTITY, PRICE) VALUES(%d,'%s', '%s', %d, %d);",prod.id,prod.name,prod.type,prod.quantity,prod.price);
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;
   
}	
int remov()
{ struct product prod;
  char sql[100];
  printf("ENTER THE NAME OF PRODUCT\n");
  scanf(" %[^\n]s",prod.name);
  sprintf(sql,"DELETE FROM Store WHERE PRODUCTNAME = '%s'",prod.name);
  rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;

	}
int search()
{
  struct product prod;
  char sql[100];
  printf("ENTER THE NAME OF PRODUCT\n");
  scanf("%s",prod.name);
  sprintf(sql,"SELECT * FROM Store WHERE PRODUCTNAME = '%s'",prod.name);
  rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;
}
int print_table()
{
  struct product prod;
  char sql[100];
  sprintf(sql,"SELECT * FROM Store");
  rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;

}
int delete()
{
  struct product prod;
  char sql[100];
  const char* data = "Callback function called";
  printf("\nENTER NAME OF PRODUCT\n");
  scanf(" %[^\n]s",prod.name);
  printf("ENTER THE QUANTITY OF PRODUCT\n");
  scanf(" %d",&prod.quantity);
  sprintf(sql," UPDATE Store SET QUANTITY = QUANTITY - %d WHERE PRODUCTNAME = '%s'; \nSELECT * FROM Store ;",prod.quantity,prod.name);
  rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
  else {
      fprintf(stdout, "Operation done successfully\n");
   }
  return 0;
}
int print_bill()
{
  struct product prod[20];
  int i = 0, count = 0, sum = 0, discount = 0 ;
  char sql[100], str[1];
  const char* data = "Callback function called";
  printf("ENTER y TO ADD PRODUCT");
  scanf("%s",str);
  while (str[0]=='y')
  {
    printf("\nENTER NAME OF PRODUCT\n");
    scanf(" %[^\n]s",prod[i].name);
    printf("ENTER THE QUANTITY OF PRODUCT\n");
    scanf(" %d",&prod[i].quantity);
    sprintf(sql," UPDATE Store SET QUANTITY = QUANTITY - %d WHERE PRODUCTNAME = '%s';",prod[i].quantity,prod[i].name);
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);

     }
    else {
      fprintf(stdout, "Operation done successfully\n");
      sprintf(sql,"SELECT PRICE FROM Store WHERE PRODUCTNAME = '%s'",prod[i].name);
      rc = sqlite3_exec(db, sql, callback2, NULL, NULL);  
      count++;
      
   }
    prod[i].price = price1;
	i++;
    printf("ENTER y TO ADD PRODUCT");
    scanf("%s",str);
 }
 
   printf("NO.\t\tNAME\t\t\tAMOUNT\t\tPRICE\n");
   for (i=0;i<count;i++)
   {
    printf("%d\t%s\t\t%d\t\t%d\n",i+1,prod[i].name,prod[i].quantity,prod[i].price);
    sum = sum + prod[i].price*prod[i].quantity;
   }
   if(sum>1999)
   {discount=0.1*sum;
    printf("\nSPECIAL DISCOUNT: %d",discount);
   }   
   printf("\nTOTAL = %d\n",sum-discount);
   
}
//gcc main.c -I"C:\ebs pmds project" -L"C:\ebs pmds project" -lsqlite3
