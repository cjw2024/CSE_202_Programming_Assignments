
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "user.h"

int main(int argc, char** argv){
    user_t user;
    user.password = argv[1];
    puts(user.password);
    reset_password(&user);
    //new_password(argv[1]);
    puts(user.password);

    char* filename = "users.txt";
    user_t* user_list = (user_t *)malloc(sizeof(user_t));;
    int user_count = read_users(user_list, filename);
    printf("%d\n", user_count);
    //puts(user_list[99].username);
    //puts(user_list[99].password);
}

void new_password(char* pass){
    int i = 0;
    int length = (rand() % 3) + 8;
    //printf("%d\n", length);
    int n = 94;
    srand(time(0));
    for(; i < length; i++){
        *(pass + i) = (char) (rand() % n + 32);
        //printf("%c\n", *(pass + i));
    }
    *(pass + i) = '\0';
};

void reset_password(user_t *u){
    new_password(u->password);
};

int read_users(user_t *user_list, char* filename){

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char **buffer = (char **)malloc(sizeof(char*));
    int n = 0;
    size_t size;

    while(getline(&buffer[n], &size, file) != -1){
        n++;
        buffer = (char **)realloc(buffer, (n+1) * sizeof(char*));
    }

    fclose(file);

    for(int i = 0; i < n; i++){
        //printf("%s", buffer[i]);
        char* user = strtok(buffer[i], " ");
        char* pass = strtok(NULL, " ");

        user_list[i].username = malloc(strlen(user) + 1);
        user_list[i].password = malloc(strlen(pass) + 1);
        
        strcpy(user_list[i].username, user);
        strcpy(user_list[i].password, pass);
        printf("%s\n", user_list[i].username);
        printf("%s\n", user_list[i].password);
    }
    
    return n;
};

int save_users(user_t *user_list, char* filename, int size){

};

int find_username(user_t *user_list, char* username, int size){

};

int find_user(user_t *user_list, char* username, char*password, int size){

};
