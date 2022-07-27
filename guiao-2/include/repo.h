
typedef struct repo *Repo;

Repo insertRepo(int id, int owner_id, char *full_name, char *license, char *has_wiki, char *description, char *language, char *default_branch, char *created_at, char *updated_at, int forks_count, int open_issues, int stargazers_count, int size);

int cmpRepos(const void* a, const void* b);


int getRepoId(Repo r);

int getRepoOwnerId(Repo r);

char* getRepoFullName(Repo r);

char* getRepoLicense(Repo r);

char* getRepoHasWiki(Repo r);

char* getRepoDescription(Repo r);

char* getRepoLanguage(Repo r);

char* getRepoDefaultBranch(Repo r);

char* getRepoCreatedAt(Repo r);

char* getRepoUpdatedAt(Repo r);

int getRepoForksCount(Repo r);

int getRepoOpenIssues(Repo r);

int getRepoStargazersCount(Repo r);

int getRepoSize(Repo r);


void freeRepo (Repo r);