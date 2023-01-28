
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "user.h"

//char* filename = "users.txt";
//user_t* user_list;
//user_t user;

/*int main(int argc, char** argv){
    user.password = (char*)malloc(sizeof(char));
    user.password = "no";
    puts(user.password);
    reset_password(&user);
    //new_password(argv[1]);
    puts(user.password);

    //char* filename = "users.txt";
    user_list = (user_t *)malloc(sizeof(user_t));
    int user_count = read_users(user_list, filename);
    //printf("%d\n", user_count);
    puts(user_list[0].username);
    puts(user_list[0].password);

    for (int i = 0; i < 100; i++){
        printf("%s\n", user_list[i].username);
        printf("%s\n", user_list[i].password);
        //printf("%d\n", user_list[i].val);
        printf("%c\n\n", user_list[i].val);
    }

    //int saved = save_users(user_list, filename, user_count);
    //printf("%d\n", saved);

    char* name = "mar210";
    int index = find_username(user_list, name, user_count);
    printf("%d\n", index);

    char* name2 = "lca213";
    char* pass2 = "`akFzM?_67";
    int index2 = find_user(user_list, name2, pass2, user_count);
    printf("%d\n", index2);

    char* name3 = "lca213";
    char* pass3 = "`akFzM?_6";
    int index3 = find_user(user_list, name3, pass3, user_count);
    printf("%d\n", index3);

}*/

void new_password(char **pass){
    /**pass = NULL;
    int length = (rand() % 3) + 8;
    //*pass = (char*)malloc(length+1);  
    //puts(pass);  
    int i = 0;
    
    char* new[10];
    int n = 94;
    srand(time(0));

    for(; i < length; i++){
        new[i] = (char) (rand() % n + 32);
    }
    new[i] = '\0';

    //*pass = new;
    //puts(*pass);
    strcpy(*pass, new);*/

    int length = (rand() % 3) + 8;
    *pass = (char*)malloc(length+1);
    int i = 0;
    int n = 94;
    srand(time(0));

    for(; i < length; i++){
        *(*pass + i) = (char) (rand() % n + 32);
    }

    *(*pass + i) = '\0';
};

void reset_password(user_t *u){
    new_password(&u->password);
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
        char* num = strtok(NULL, " ");

        user_list[i].username = malloc(strlen(user) + 1);
        user_list[i].password = malloc(strlen(pass) + 1);
        //user_list[i].val = malloc(sizeof(char));
        
        strcpy(user_list[i].username, user);
        strcpy(user_list[i].password, pass);
        //strcpy(user_list[i].val, num[0]);
        user_list[i].val = (int) num[0];

        /*printf("%s\n", user_list[i].username);
        printf("%s\n", user_list[i].password);
        //printf("%d\n", user_list[i].val);
        printf("%c\n\n", user_list[i].val);*/
    }
    
    return n;
};

int save_users(user_t *user_list, char* filename, int size){

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    for(int i = 50; i < size; i++){
        fprintf(file, "%s %s %c\n", user_list[i].username, user_list[i].password, user_list[i].val);
    }

    fclose(file);
    return 0;
};

int find_username(user_t *user_list, char* username, int size){
    
    for(int i = 0; i < size; i++){
        if(strcmp(username, user_list[i].username) == 0){
            return i;
        }
    }

    return -1;
};

int find_user(user_t *user_list, char* username, char* password, int size){

    int user_index = find_username(user_list, username, size);
    
    if(user_index != -1){
        if(strcmp(user_list[user_index].password, password) == 0){
            return user_index;
        } else {
            return -1;
        }
    } 

    return -1;
};
