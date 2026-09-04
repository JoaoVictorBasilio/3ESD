//--------------
// Implementa��o
//--------------

#include "Data.h"
struct data {
    int dia, mes, ano;
};
// fun��es auxiliares

int convDataDiaJuliano(int dia, int mes, int ano) {
    int A, B, C, D, E, F;
    if (mes < 3) {
        ano = ano - 1;
        mes = mes + 12;
    }
    A = (int)(ano / 100);
    B = (int)(A / 4);
    C = 2 - A + B;
    D = (int)(365.25 * (ano + 4716));
    E = (int)(30.6001 * (mes + 1));
    F = D + E + dia + 0.5 + C - 1524.5;
    return (int)(F);
}

tData* convDiaJulianoData(int juliano) {
    int A, B, C, D, E, F, G, H, I, J, K;

    A = juliano;    
        if (A > 2299160) {
            B = (int)((A - 1867216.25) / 36524.25);
            C = A + 1 + B - (int)(B / 4);
        }
        else {
            C = A;
        }
    D = C + 1524;
    E = (int)((D - 122.1) / 365.25);
    F = (int)(E * 365.25);
    G = (int)((D - F) / 30.6001);
    H = D - F - (int)(G * 30.6001);
    if (G < 14) {
        I = G - 1;
    }
    else {
        I = G - 13;
    }
    if (I > 2)
        J = E - 4716;
    else
        J = E - 4715;
    if (J > 0)
        K = J;
    else
        K = abs(J + 1);
    return(dta_cria(H, I, K));
}



// funcoes do TAD Data



tData* dta_cria(int dia, int mes, int ano) {
    tData* dt = (tData*)malloc(sizeof(struct data));
    dt->dia = dia;
    dt->mes = mes;
    dt->ano = ano;
    return dt;
}

/* Fun��o libera � Libera  mem�ria de uma Data criada */
void dta_libera(tData* p) {
    free(p);
}

/* Fun��o acessa - Retorna os valores de uma Data */
void dta_acessa(tData* p, int* dia, int* mes, int* ano) {
    *dia = p->dia;
    *mes = p->mes;
    *ano = p->ano;
    return;

}

/* Fun��o atribui - Atribui novos valores � Data */
void dta_atribui(tData* p, int dia, int mes, int ano)
{
    p->dia = dia;
    p->mes = mes;
    p->dia = ano;
    return;

}

/* Fun��o Intervalo - Retorna a data ap�s X dias */
tData* dta_intervalo(tData* p, int X) {
    int juliano = convDataDiaJuliano(p->dia, p->mes, p->ano);
    juliano += X;
    return convDiaJulianoData(juliano);
}

int dta_diferenca(tData* dt1, tData * dt2){
    
    int juliano1 = convDataDiaJuliano(dt1->dia, dt1->mes, dt1->ano);
    int juliano2 = convDataDiaJuliano(dt2->dia, dt2->mes, dt2->ano);
    return (juliano1>juliano2)?juliano1-juliano2+1:juliano2-juliano1+1;

}

/* Fun��o Exibe � Escreve na tela a data  no formato dd/mm/aaaa */
void dta_exibe(tData* p) {
    printf("%02d/%02d/%04d", p->dia, p->mes, p->ano);
}
/* Fun��o EgetData EsRetorna uma string com a data  no formato dd/mm/aaaa */
char* dta_getData(tData* p){
    char* dt;
    dt = (char*)malloc(11);
    sprintf(dt, "%02d/%02d/%04d", p->dia, p->mes, p->ano);
    return dt;
}

/* Compara duas datas: 0:se são iguais, 1: se a data1 é posterior a data 2, e -1: se a data1 é 
  anterior a data 2*/
int dta_compara(tData* dt1, tData * dt2){
    int juliano1 = convDataDiaJuliano(dt1->dia, dt1->mes, dt1->ano);
    int juliano2 = convDataDiaJuliano(dt2->dia, dt2->mes, dt2->ano);
    if (juliano1 == juliano2)
        return 0;
    if (juliano1>juliano2)
        return 1;
    return -1;
}
char* dta_MesExtenso(tData*p)
{
    char* nomemes;
    switch (p->mes)
    {
    case  1: nomemes = "janeiro"; break;
    case  2: nomemes = "fevereiro"; break;
    case  3: nomemes = "marco"; break;
    case  4: nomemes = "abril"; break;
    case  5: nomemes = "maio"; break;
    case  6: nomemes = "junho"; break;
    case  7: nomemes = "julho"; break;
    case  8: nomemes = "agosto"; break;
    case  9: nomemes = "setembro"; break;
    case 10: nomemes = "outubro"; break;
    case 11: nomemes = "novembro"; break;
    case 12: nomemes = "dezembro"; break;
    default:
        nomemes = "*invalido*";
    }
    return nomemes;
}

// Fim do TAD