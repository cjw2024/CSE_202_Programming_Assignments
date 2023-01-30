
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "user.h"

/**
 * @brief creates a new password
 * 
 * @param pass location of string pass to save new password
 */
void new_password(char **pass){
    //random length from 8-10
    int length = (rand() % 3) + 8;
    //free the memory for pass
    *pass = (char*)malloc(length+1);
    int i = 0;
    int n = 93; //how many valid ascii values there are
    srand(time(0));

    //add randome ascii value
    for(; i < length; i++){
        *(*pass + i) = (char) (rand() % n + 33);    // +33 goes to first valid ascii
    }

    //end the new password
    *(*pass + i) = '\0';
};

/**
 * @brief resets the password of a user_t
 * 
 * @param u the user who is resetting password
 */
void reset_password(user_t *u){
    new_password(&u->password);
};

/**
 * @brief read users from a given file
 * 
 * @param user_list the list of users to save to
 * @param filename the name of the file reading from
 * @return int, the number of users read
 */
int read_users(user_t *user_list, char* filename){
    //Open the file to read from it
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    //Create memory for the buffer to read from the file
    char **buffer = (char **)malloc(sizeof(char*));
    int n = 0;
    size_t size;

    //save to the buffer and reallocate the memory so it saves properly
    while(getline(&buffer[n], &size, file) != -1){
        n++;
        buffer = (char **)realloc(buffer, (n+1) * sizeof(char*));
    }

    fclose(file);   //close the file

    //iterate throw the array buffer to save to user_list
    for(int i = 0; i < n; i++){
        // break apart each line into user_t values
        char* user = strtok(buffer[i], " ");
        char* pass = strtok(NULL, " ");
        char* num = strtok(NULL, " ");

        //free memory for the username and password to be saved
        user_list[i].username = malloc(strlen(user) + 1);
        user_list[i].password = malloc(strlen(pass) + 1);
        //copy over username and password
        strcpy(user_list[i].username, user);
        strcpy(user_list[i].password, pass);
        user_list[i].val = (int) num[0];    //save the priviledge
    }
    
    return n;
};

/**
 * @brief Saves users from the user_list to a file
 * 
 * @param user_list the list of user_t
 * @param filename the list of the file saving to
 * @param size the amount of user_t
 * @return int, 0 if saved properly
 */
int save_users(user_t *user_list, char* filename, int size){
    //open file to write to it
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    //iterate throw user_t and print to the file
    int i = 0;
    for(; i < size-1; i++){
        fprintf(file, "%s %s %c\n", user_list[i].username, user_list[i].password, user_list[i].val);
    }
    fprintf(file, "%s %s %c", user_list[i].username, user_list[i].password, user_list[i].val);

    fclose(file);   //close the file
    return 0;
};

/**
 * @brief search for a username in the user_list
 * 
 * @param user_list list of user_t
 * @param username the username searching for
 * @param size the amount of user_t in user_list
 * @return int, index of the username if found
 */
int find_username(user_t *user_list, char* username, int size){
    //iterate through the user list to find the username
    for(int i = 0; i < size; i++){
        if(strcmp(username, user_list[i].username) == 0){
            return i;
        }
    }

    return -1;  //not found
};

/**
 * @brief find a user by searching for username and password
 * 
 * @param user_list list of user_t
 * @param username the username searching for
 * @param password the password comparing to match
 * @param size the amount of user_t in user_list
 * @return int the index of the user
 */
int find_user(user_t *user_list, char* username, char* password, int size){
    //search for the username
    int user_index = find_username(user_list, username, size);
    
    //username found
    if(user_index != -1){
        if(strcmp(user_list[user_index].password, password) == 0){
            return user_index;  //password match
        } else {
            return -1;  //password does not match
        }
    } 

    return -1;  //not found
};
