
typedef struct commit *Commit;

Commit insertCommit(int repo_id, int author_id, int commiter_id, char *commit_at, char *message);

int cmpCommits(const void* a, const void* b);


int getCommitRepoId (Commit c);

int getCommitAuthorId (Commit c);

int getCommitCommiterId (Commit c);

char* getCommitCommitAt (Commit c);

char* getCommitMessage (Commit c);


void freeCommit (Commit c);