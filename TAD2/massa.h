typedef struct mas Massa;

Massa* mas_cria(int kg,int g);

void mas_libera(Massa* m);

char* mas_paraString(Massa* m);

int mas_paraGramas(Massa* m);

int mas_soma(Massa *m1,Massa *m2);


