#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/stats.h"

struct statsU {
	int length;
	int users;
	int bots;
	int organizations;
};

struct statsC {
	int length;
};

struct statsR {
	int length;
};


// Funções de inicialização //

StatsU initStatsU (){
	StatsU s = malloc(sizeof(struct statsU));
	s->length = 0;
	s->users = 0;
	s->bots = 0;
	s->organizations = 0;
	return s;
}


StatsC initStatsC (){
	StatsC s = malloc(sizeof(struct statsC));
	s->length = 0;
	return s;
}


StatsR initStatsR (){
	StatsR s = malloc(sizeof(struct statsR));
	s->length = 0;
	return s;
}


// Funções de introdução/alteração de valores//

StatsU incUsers (StatsU s){
	s->users++;
	return s;
}

StatsU incBots (StatsU s){
	s->bots++;
	return s;
}

StatsU incOrganizations (StatsU s){
	s->organizations++;
	return s;
}

// Define (StatsUsers) s->length como n.
StatsU setStatsUlength (StatsU s, int n){
	s->length = n;
	return s;
}

// Define (StatsCommits) s->length como n.
StatsC setStatsClength (StatsC s, int n){
	s->length = n;
	return s;
}

// Define (StatsRepos) s->length como n.
StatsR setStatsRlength (StatsR s, int n){
	s->length = n;
	return s;
}


// Funções de obtenção de valores//


int getNbots (StatsU s) {
	return (s->bots);
}

int getNusers (StatsU s) {
	return (s->users);
}

int getNorganizations (StatsU s) {
	return (s->organizations);
}

int getUlength (StatsU s) {
	return (s->length);
}

int getClength (StatsC s) {
	return (s->length);
}

int getRlength (StatsR s) {
	return (s->length);
}



// Funções de frees //

void freeStatsU (StatsU s){
	free(s);
}

void freeStatsC (StatsC s){
	free(s);
}

void freeStatsR (StatsR s){
	free(s);
}