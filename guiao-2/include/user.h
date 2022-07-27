
typedef struct user *User;

User insertUser(int id, char *login, char *type, char *created_at, int followers, int *follower_list, int following, int *following_list, int public_gists, int public_repos);

int cmpUsers(const void* a, const void* b);

// Funcoes de obtencao de valores //

int getUserId (User u);

char* getUserLogin (User u);

char* getUserType (User u);

char* getUserCreatedAt (User u);

int getUserFollowers (User u);

int* getUserFollower_list (User u);

int getUserFollowing (User u);

int* getUserFollowing_list (User u);

int getUserPublic_gists (User u);

int getUserPublic_repos (User u);


void freeUser (User u);