
//typedef struct idx *IDX;

//typedef struct ids *IDS;


void query1(TupleU tu, int num);

void query2(TupleC tc, TupleR tr, int num);

void query3(TupleU tu, TupleC tc, int num);

void query4(TupleU tu, TupleC tc, int num);

void query5(TupleU tu, TupleC tc, int n, char *date, char *time, int num);

void query6(TupleU tu, TupleC tc, TupleR tr, int n, char *language, int num);

void query7(TupleC tc, TupleR tr, char *date, int num);

void query8(TupleR tr, int n, char *date, int num);

void query9(TupleU tu, TupleC tc, int n, int num);

void query10(TupleC tc, TupleU tu, int n, int num);

void query(TupleU tu, TupleC tc, TupleR tr, const char* file);