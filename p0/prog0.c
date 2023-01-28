
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

user_t* user_list;
char* filename = "users.txt";
int user_count;
int change = 0;

int main(int argc, char** argv){
    user_list = (user_t *)malloc(100*sizeof(user_t));
    user_count = read_users(user_list, filename);
    if(user_count != -1){
        printf("File \"users.txt\" loaded successfully.\n");
    } else {
        printf("File \"users.txt\" loaded unsuccessfully.\n");
        return 0;
    }
    //printf("%d\n", user_count);

    /*for(int i = 0; i < user_count; i++){
        printf("%c\n", user_list[i].val);
    }*/

    int index;

    for(int i = 0; i < 3; i++){
        //puts(user_list[11].password);
        printf("Enter login credentials:\n");

        printf("username: ");
        char username[100];
        scanf("%99[^\n]", username);
        getchar();

        char password[100];
        printf("password: ");
        scanf("%99[^\n]", password);
        getchar();

        //break;
        //puts(username);
        //puts(password);

        index = find_user(user_list, username, password, user_count);
        //printf("%d\n", index);
        if(index != -1)
            break;
        else{
            if(i != 2)
                printf("Invalid credentials. Try again\n\n");
            else{
                printf("Access denied after three trials.\n\n");
                return 0;
            }     
        }

    }

    //printf("%d\n", index);

    if(user_list[index].val == 48){
        printf("You do not have administrator access rights.  You cannot access the file. \n\n");
        return 0;
    }

    int loop_needed = -1;

    while(loop_needed == -1){
        printf("\n");
        printf("Select an operation:\n");
        printf("1: Add a new user\n");
        printf("2: Reset Password of an existing user\n");
        printf("3: Logout\n");

        int option = 0;
        scanf("%d", &option);
        getchar();
        //printf("%d\n", option);

        if(option == 1){
            printf("username: ");
            char username[100];
            scanf("%99[^\n]", username);
            getchar();

            char user_privilege;
            printf("Enter user privileges (1 for admin, 0 for user): ");
            scanf("%c", &user_privilege);
            getchar();

            if(user_privilege == 48 | user_privilege == 49){
                
                char* pass;
                new_password(&pass);
                user_t new_user;
                new_user.username = malloc(strlen(username) + 1);
                new_user.password = malloc(strlen(pass) + 1);
                
                strcpy(new_user.username, username);
                strcpy(new_user.password, pass);
                new_user.val = user_privilege;

                user_count++;
                user_list = (user_t*)realloc(user_list, user_count * sizeof(user_t));
                if(user_list == NULL){
                    printf("error");
                    return -1;
                }

                user_list[user_count - 1] = new_user;
                printf("%s\n", user_list[user_count-2].username);
                //printf("%s\n", user_list[user_count-1].password);
                //printf("%d\n", user_list[user_count-1].val);

                change = 1;
                printf("User added successfully: ");
                puts(username);

            } else 
                printf("User unsuccessfully added\n\n");
            
        }else if(option == 2){
            printf("Enter username: ");
            char username[100];
            scanf("%99[^\n]", username);
            getchar();

            //int found = 0;
            int found = find_username(user_list, username, user_count);
            if(found != -1){
                //puts(user_list[found].password);
                reset_password(&user_list[found]);
                printf("password reset successfully.\n\n");
                change = 1;
            }else
                printf("Unable to find username.\n\n");
            //puts(user_list[found].password);
            

        }else if(option == 3){
            loop_needed = 0;
            printf("Updating the data file ...\n");

            if(change == 1){
                //int saved = save_users(user_list, filename, user_count);
                //if(saved != 0)
                    printf("Unable to save file\n");
            }
            
            printf("logout complete\n\n");
        }else{

        }

    }



}

