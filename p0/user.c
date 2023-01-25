
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "user.h"

int main(int argc, char** argv){
    
    puts(argv[1]);
    new_password(argv[1]);
    puts(argv[1]);

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

};

int read_users(user_t *user_list, char* filename){

};

int save_users(user_t *user_list, char* filename, int size){

};

int find_username(user_t *user_list, char* username, int size){

};

int find_user(user_t *user_list, char* username, char*password, int size){

};
