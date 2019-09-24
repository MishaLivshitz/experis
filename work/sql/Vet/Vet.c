
#include <stdio.h>
#include "mySqlHandler.h"
#include <string.h>

#define BUFF_SIZE 2048

typedef enum {  OWNERS = 1,
                PETS,
                ADD_OWNER,
                ADD_PET,
                DEL_OWNER,
                DEL_PET,
                FIND_OWNER,
                FIND_PET,
                UPDATE_OWNER,
                UPDATE_PET,
                EXIT } Options;


int getOption()
{
    int opt;
    puts("Options:");
    puts("1: Get Owners");
    puts("2: Get Pets");
    puts("3: Add owner");
    puts("4: Add pet");
    puts("5: Delete owner");
    puts("6: Delete pet");
    puts("7: Find owner");
    puts("8: Find pet");
    puts("9: Update owner");
    puts("10: Update pet");
    puts("11: Exit");


    puts("Insert your choice");
    scanf("%d", &opt);
    getchar();
    return opt;
}


int main()
{

    MYSQL * MySql = NULL;
    MYSQL_RES * MySqlRes = NULL;
    char buff[BUFF_SIZE] = {0};
    char cond[BUFF_SIZE] = {0};
    int id;

    MySql = MySql_Init(MySql);
    MySql = MySql_connect(MySql,"michael","misha1991", "vet");

    while(1)
    {
        switch (getOption())
        {
        case OWNERS:
            MySqlRes = MySql_GetAll(MySql,MySqlRes,"costumers",NULL);
            MySqlPrintRes(MySqlRes);
            break;

        case PETS:
            MySqlRes = MySql_GetAll(MySql,MySqlRes, "pets", NULL);
            MySqlPrintRes(MySqlRes);
            break;

        case ADD_OWNER:
            puts("Insert ID and 'name', seperated by comma:");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            MySql_Insert(MySql, "costumers", "costumer_no, c_name", buff);
            break;

        case ADD_PET:
            puts("Insert ID , costumer ID and 'name', seperated by comma:");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            MySql_Insert(MySql, "pets", "pet_no, costumer_no, p_name", buff);
            break;

        case DEL_OWNER:
            puts("Insert ID to delete");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            sprintf(cond,"costumer_no = %s", buff);
            MySql_Delete(MySql, "costumers", cond);
            break;

        case DEL_PET:
            puts("Insert ID to delete");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            sprintf(cond,"pet_no = %s", buff);
            MySql_Delete(MySql, "pets", cond);
            break;

        case FIND_OWNER:
            puts("Insert ID to find");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            sprintf(cond,"costumer_no = %s", buff);
            MySqlRes = MySql_GetAll(MySql, MySqlRes, "costumers", cond);
            MySqlPrintRes(MySqlRes);
            break;

        case FIND_PET:
            puts("Insert ID to find");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            sprintf(cond,"pet_no = %s", buff);
            MySqlRes = MySql_GetAll(MySql, MySqlRes, "pets", cond);
            MySqlPrintRes(MySqlRes);
            break;

        case UPDATE_OWNER:
        
            puts("Insert ID to change");
            scanf("%d", &id);
            getchar();
            sprintf(cond,"costumer_no = %d", id);
            puts("Insert columns to update seperated by comma (column = new value)");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
           
            MySql_Update(MySql, "costumers",buff, cond);
            MySqlPrintRes(MySqlRes);
            break;

        case UPDATE_PET:
        
            puts("Insert ID to change");
            scanf("%d",&id);
            getchar();
            sprintf(cond,"pet_no = %d", id);
            puts("Insert columns to update seperated by comma (column = new value)");
            fgets(buff,BUFF_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
           
            MySql_Update(MySql, "pets",buff, cond);
            MySqlPrintRes(MySqlRes);
            break;
        
        case EXIT:
            MySqlClose(MySql,MySqlRes);
            return 1;
            break;

        default:
            puts("No such option\n");
        }

        puts("Press any key to continue...");
        getchar();
    }

}


