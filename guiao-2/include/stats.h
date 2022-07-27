
typedef struct statsU *StatsU;

typedef struct statsC *StatsC;

typedef struct statsR *StatsR;


// Funções de inicialização //

StatsU initStatsU ();

StatsC initStatsC ();

StatsR initStatsR ();



// Funções de introdução/alteração de valores//

StatsU incUsers (StatsU s);

StatsU incBots (StatsU s);

StatsU incOrganizations (StatsU s);


StatsU setStatsUlength (StatsU s, int n);

StatsC setStatsClength (StatsC s, int n);

StatsR setStatsRlength (StatsR s, int n);


// Funções de obtenção de valores//

int getNbots (StatsU s);

int getNusers (StatsU s);

int getNorganizations (StatsU s);

int getUlength (StatsU s);

int getClength (StatsC s);

int getRlength (StatsR s);



// frees //
void freeStatsU (StatsU s);

void freeStatsC (StatsC s);

void freeStatsR (StatsR s);