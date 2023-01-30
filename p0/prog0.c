
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

// global variables to save to and use
user_t* user_list;
char* filename = "users.txt";
int user_count;
int change = 0;

/**
 * @brief user interface
 * 
 * @return int 
 */
int main(){
    int lines = 1;
    char c;
    //open file to read it
    FILE *file = fopen(filename, "r");
    //count how many lines are in the file
    for(c = getc(file); c != EOF; c = getc(file)){
        if(c == '\n'){
            lines++;
        }
    }

    fclose(file);//close the file

    //create memory space for the user_list with the amount of lines in the file
    user_list = (user_t *)malloc(lines*sizeof(user_t));
    user_count = read_users(user_list, filename);   //read the file to the user_list
    if(user_count != -1){
        printf("File \"users.txt\" loaded successfully.\n");
    } else {
        printf("File \"users.txt\" loaded unsuccessfully.\n");
        return 0;
    }

    int index;
    //3 attempts to log in
    for(int i = 0; i < 3; i++){
        printf("Enter login credentials:\n");
        //user input for username
        printf("username: ");
        char username[100];
        scanf("%99[^\n]", username);
        getchar();
        //user input for passwors
        char password[100];
        printf("password: ");
        scanf("%99[^\n]", password);
        getchar();

        index = find_user(user_list, username, password, user_count);   //search to see if match
        //if match break the for loop
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
    //if user does not have proper priveledges
    if(user_list[index].val == 48){
        printf("You do not have administrator access rights.  You cannot access the file. \n\n");
        return 0;
    }

    int loop_needed = -1;
    //loop through the menu for user interaction
    while(loop_needed == -1){
        printf("\n");
        printf("Select an operation:\n");
        printf("1: Add a new user\n");
        printf("2: Reset Password of an existing user\n");
        printf("3: Logout\n");
        //take user input for menu option
        int option = 0;
        scanf("%d", &option);
        getchar();
        //adding new user
        if(option == 1){
            //take user input for new username
            printf("username: ");
            char username[100];
            scanf("%99[^\n]", username);
            getchar();
            //take user input for their priviledges
            char user_privilege;
            printf("Enter user privileges (1 for admin, 0 for user): ");
            scanf("%c", &user_privilege);
            getchar();
            //if valid input(1 or 0)
            if(user_privilege == 48 | user_privilege == 49){
                //create new password
                char* pass;
                new_password(&pass);
                user_t new_user;
                //create memory for the username and password to be saved
                new_user.username = malloc(strlen(username) + 1);
                new_user.password = malloc(strlen(pass) + 1);
                //copy to the user_t struct
                strcpy(new_user.username, username);
                strcpy(new_user.password, pass);
                new_user.val = user_privilege;
                //increase # of users and reallocate memory for a bigger list
                user_count++;
                user_list = (user_t*)realloc(user_list, user_count * sizeof(user_t));
                if(user_list == NULL){
                    printf("error");
                    return -1;
                }
                //save new user
                user_list[user_count - 1] = new_user;

                change = 1;
                printf("User added successfully: ");
                puts(username);

            } else //invalid input
                printf("User unsuccessfully added\n\n");
        //resetting password    
        }else if(option == 2){
            //take user input for user resetting password
            printf("Enter username: ");
            char username[100];
            scanf("%99[^\n]", username);
            getchar();
            //search for username
            int found = find_username(user_list, username, user_count);
            if(found != -1){    //change password
                reset_password(&user_list[found]);
                printf("password reset successfully.\n\n");
                change = 1;
            }else   //not found
                printf("Unable to find username.\n\n");
            
        //logging out and updating file
        }else if(option == 3){
            loop_needed = 0;    //exit the while loop
            printf("Updating the data file ...\n");
            // if the user_list was changed in any way
            if(change == 1){
                int saved = save_users(user_list, filename, user_count);
                if(saved != 0)
                    printf("Unable to save file\n");
            }
            
            printf("logout complete\n\n");
        //invalid menu input
        }else{
            printf("Unvalid input. Try again.\n\n");
        }

    }

}

