
enum ACCESS{
    USER,
    ADMIN
};

struct User{
    char* username;
    char* password;
    int val;
};

typedef struct User user_t;

void new_password(char** pass);
void reset_password(user_t *u);
int read_users(user_t *user_list, char* filename);
int save_users(user_t *user_list, char* filename, int size);
int find_username(user_t *user_list, char* username, int size);
int find_user(user_t *user_list, char* username, char*password, int size);

