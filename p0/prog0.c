
#include <stdio.h>
#include <stdlib.h>

#include "user.h"

user_t* user_list;
char* filename = "users.txt";

int main(int argc, char** argv){
    //int user_count = read_users(user_list, filename);
    /*if(user_count != -1){
        printf("File "users.txt" loaded successfully.");
    } else {
        printf("File "users.txt" loaded unsuccessfully.");
        return 0;
    }*/

    for(int i = 0; i < 3; i++){
        printf("Enter login credentials:\n");

        char username[100];
        printf("username: ");
        fgets(username, sizeof(username), stdin);

        char password[100];
        printf("password: ");
        fgets(password, sizeof(password), stdin);

        break;
        //puts(username);
        //puts(password);

        //int index = find_user(user_list, username, password, user_count);

        /*if(index != -1)
            break;
        else 
            printf("");
        */
    }

    /*if(index == -1)
        return 0;*/
    
    int loop_needed = -1;

    while(loop_needed == -1){
        printf("\n");
        printf("Select an operation:\n");
        printf("1: Add a new user\n");
        printf("2: Reset Password of an existing user\n");
        printf("3: Logout\n");

        int option;
        scanf("%d", &option);
        //printf("%d\n", option);

        if(option == 1){
            char username[100];
            printf("Enter username: ");
            fgets(username, sizeof(username), stdin);

            printf("Enter user privileges (1 for admin, 0 for user): ");
            int user_privilege;
            scanf("%d", &user_privilege);

            if(user_privilege == 1 | user_privilege == 0){
                printf("User added successfully: ");
                puts(username);

                /*  need to create new password and add to user_list    */

            } else 
                printf("User unsuccessfully added\n");
            
        }else if(option == 2){
            char username[100];
            printf("Enter username: ");
            fgets(username, sizeof(username), stdin);

            /*  need to search for user and reset their password with new password  */

            printf("password reset successfully.");
            
        }else if(option == 3){
            loop_needed = 0;
        }else{

        }

    }



}

