#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/tuple.h"
#include "./../include/stats.h"
#include "./../include/users.h"
#include "./../include/commits.h"
#include "./../include/repos.h"



struct tupleU {
	StatsU s;
	USERS cat;
};

struct tupleC {
	StatsC s;
	COMMITS cat;
};

struct tupleR {
	StatsR s;
	REPOS cat;
};


TupleU createTupleU (StatsU stats, USERS c){
	TupleU tuple = malloc (sizeof (struct tupleU));
	tuple->s = stats;
	tuple->cat = c;
	return tuple;
}


TupleC createTupleC(StatsC stats, COMMITS c){
	TupleC tuple = malloc(sizeof(struct tupleC));
	tuple->s = stats;
	tuple->cat = c;
	return tuple;
}


TupleR createTupleR(StatsR stats, REPOS c){
	TupleR tuple = malloc(sizeof(struct tupleR));
	tuple->s = stats;
	tuple->cat = c;
	return tuple;
}


// GET STATS //

StatsU getStatsUsers (TupleU t){
	return (t->s);
}

StatsC getStatsCommits (TupleC t){
	return (t->s);
}

StatsR getStatsRepos (TupleR t){
	return (t->s);
}

// GET CATS //

USERS getUSERS (TupleU t){
	return (t->cat);
}

COMMITS getCOMMITS (TupleC t){
	return (t->cat);
}

REPOS getREPOS (TupleR t){
	return (t->cat);
}


// Frees //


void freeTupleU (TupleU t){
	freeStatsU(t->s);
	freeUsers(t->cat);
	free (t);
}

void freeTupleC (TupleC t){
	freeStatsC(t->s);
	freeCommits(t->cat);
	free (t);
}


void freeTupleR (TupleR t){
	freeStatsR(t->s);
	freeRepos(t->cat);
	free (t);
}