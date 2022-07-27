#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/parsing.h"
#include "./../include/stats.h"
#include "./../include/query.h"


int main (int argc, char const *argv[]) {

    TupleU tu = vusers();
    TupleC tc = vcommits();
    TupleR tr = vrepos();

    query(tu, tc, tr, argv[1]);

    freeTupleU(tu);
    freeTupleC(tc);
    freeTupleR(tr);

    return 0;
}