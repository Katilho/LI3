#include "stats.h"
#include "users.h"
#include "commits.h"
#include "repos.h"

typedef struct tupleU *TupleU;

typedef struct tupleC *TupleC;

typedef struct tupleR *TupleR;


// Funcoes de uniao de stats e catalogos //

TupleU createTupleU (StatsU stats, USERS c);

TupleC createTupleC(StatsC stats, COMMITS c);

TupleR createTupleR(StatsR stats, REPOS c);


// Funcoes de obtencao de stats e catalogos //

StatsU getStatsUsers (TupleU t);

StatsC getStatsCommits (TupleC t);

StatsR getStatsRepos (TupleR t);

USERS getUSERS (TupleU t);

COMMITS getCOMMITS (TupleC t);

REPOS getREPOS (TupleR t);


// Frees //

void freeTupleU (TupleU t);

void freeTupleC (TupleC t);

void freeTupleR (TupleR t);
