#include <stdio.h>
#include <stdlib.h>

FILE *input;
int i, j, k, l, c,a, b, size;
float matriz[100][100], matriz_backup[100][100], x[100][100], mult;


void lerInput(void)
{
//Lê a matriz apresentada em arquivo eal.in
//Presente no arquivo:
/*
4  --> Tamanho da matriz
1.234  5.331  1.231  2.174  6.456 -->L1
1.333  2.346  4.234  3.147  2.502 -->L2
2.204  2.021  6.001  1.125  1.101 -->L3
0.211  7.126  0.234  5.003  2.110 -->L4
0.02 0.25 0.75 0.12               -->S^0
*/

    for (i = 0; i < size; i++)
    {
        for (j = 0; j <= size; j++)
        {
            fscanf(input, "%f", &matriz[i][j]);
            matriz_backup[i][j] = matriz[i][j];
        }
    }
    for (l=0; l<size; l++)
        fscanf(input, "%f", &x[0][l]);

}

void resetar(void) //Limpa a matriz
{
    for (i = 0; i < size; i++)
    {
        for (j = 0; j <= size; j++)
            matriz[i][j] = matriz_backup[i][j];
    }
}


void e1() //Realiza etapa 1
{
    float m21 = matriz[1][0]/matriz[0][0];
    float m31 = matriz[2][0]/matriz[0][0];
    float m41 = matriz[3][0]/matriz[0][0];

    //l2 <- l2-mxy.l1
    for(j=0; j<=size; j++)
    {
        matriz[1][j] = matriz[1][j] - (m21*matriz[0][j]);
    }
    //l3 <- l3-mxy.l1
    for(j=0; j<=size; j++)
    {
        matriz[2][j] = matriz[2][j] - (m31*matriz[0][j]);
    }

    //l4 <- l4-mxy.l1
    for(j=0; j<=size; j++)
    {
        matriz[3][j] = matriz[3][j] - (m41*matriz[0][j]);
    }
}

void e2() //Realiza etapa 2
{
    float m32 = matriz[2][1]/matriz[1][1];
    float m42 = matriz[3][1]/matriz[1][1];

    //l3 <- l3-mxy.l2
    for(j=1; j<=size; j++)
    {
        matriz[2][j] = matriz[2][j] - (m32*matriz[1][j]);
    }

    //l4 <- l4-mxy.l1
    for(j=1; j<=size; j++)
    {
        matriz[3][j] = matriz[3][j] - (m42*matriz[1][j]);
    }
}

void e3() //Realiza etapa 3
{
    float m43 = matriz[3][2]/matriz[2][2];

    //l4 <- l4-mxy.l1
    for(j=2; j<=size; j++)
    {
        matriz[3][j] = matriz[3][j] - (m43*matriz[2][j]);
    }
}

void gauss(void)
{
    /* aplicar algoritmo de eliminacao de Gauss */
    for (k = 0; k < size-1; k++)
    {
        for (i = k+1; i < size; i++)
        {
            mult = matriz[i][k]/matriz[k][k];
            matriz[i][k] = 0;
            for (j = k+1; j <= size; j++)
            {
                matriz[i][j] -= mult * matriz[k][j];
            }

        }
    }
}

void resolvendo(int k) //Encontra a solução
{
    e1();
    e2();
    e3();
    x[k+1][3] = x[k][3] + matriz[3][4]/matriz[3][3];
    resetar();
    e1();
    e2();
    x[k+1][2] = x[k][2] + (1/matriz[2][2])*(matriz[2][4]-(matriz[2][3]*x[k][3]));
    resetar();
    e1();
    x[k+1][1] = x[k][1] + (1/matriz[1][1])*(matriz[1][4]-(matriz[1][2]*x[k][2]+matriz[1][3]*x[k][3]));
    resetar();
    x[k+1][0] = x[k][0] + (1/matriz[0][0])*(matriz[0][4]-(matriz[0][1]*x[k][1]+matriz[0][2]*x[k][2]+matriz[0][3]*x[k][3]));


}

void imprimeMatriz(void) //Imprime Matriz
{
    for (i = 0; i < size; i++)
    {
        for (j = 0; j <= size; j++)
        {
            printf("%.4f\t", matriz[i][j]);
            if (j==size-1)
                printf(" =  ");
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    input = fopen("eal.in", "r"); //Indica arquivo a ser lido
       /* ler input */
    while (fscanf(input, "%d", &size) == 1) //Caso tenha mais de uma matriz no arquivo, ele resolve...
    {
        printf("------------ Matriz -------------------------------------------\n");
        lerInput();
        imprimeMatriz(); //Imprime matriz original
        e1();
        printf("etapa 1\n");
        imprimeMatriz(); //Imprime etapa 1
        e2();
        printf("etapa 2\n");
        imprimeMatriz(); //Imprime etapa 2
        e3();
        printf("etapa 3\n");
        imprimeMatriz(); //Imprime etapa 3
        resetar(); //Limpa Matriz
        gauss(); //Acha a Matriz Triangular Superior
        printf("EALs Triangular \n");
        imprimeMatriz(); //Imprime Triangular
        printf("-------- Solucoes --------");
        for(a=0; a<11; a++) //Realiza k ate 10 e imprime
        {
            resolvendo(a);
            printf("\nS^%d=(", a);
            for(b=0; b<4; b++)
            {
                printf("%.4f ", x[a][b]);
            }
            printf(")");
        }

        printf("\n-------------------------------------------------------------------\n\n");
    }

    return(1);

}
/* RESULTADO APRESENTADO
------------ Matriz -------------------------------------------
1.2340  5.3310  1.2310  2.1740   =  6.4560
1.3330  2.3460  4.2340  3.1470   =  2.5020
2.2040  2.0210  6.0010  1.1250   =  1.1010
0.2110  7.1260  0.2340  5.0030   =  2.1100

etapa 1
1.2340  5.3310  1.2310  2.1740   =  6.4560
-0.0000 -3.4127 2.9042  0.7986   =  -4.4719
-0.0000 -7.5005 3.8024  -2.7579  =  -10.4298
0.0000  6.2145  0.0235  4.6313   =  1.0061

etapa 2
1.2340  5.3310  1.2310  2.1740   =  6.4560
-0.0000 -3.4127 2.9042  0.7986   =  -4.4719
-0.0000 0.0000  -2.5807 -4.5131  =  -0.6013
0.0000  0.0000  5.3121  6.0855   =  -7.1373

etapa 3
1.2340  5.3310  1.2310  2.1740   =  6.4560
-0.0000 -3.4127 2.9042  0.7986   =  -4.4719
-0.0000 0.0000  -2.5807 -4.5131  =  -0.6013
0.0000  0.0000  0.0000  -3.2043  =  -8.3749

EALs Triangular
1.2340  5.3310  1.2310  2.1740   =  6.4560
0.0000  -3.4127 2.9042  0.7986   =  -4.4719
0.0000  0.0000  -2.5807 -4.5131  =  -0.6013
0.0000  0.0000  0.0000  -3.2043  =  -8.3749

-------- Solucoes --------
S^0=(0.0200 0.2500 0.7500 0.1200 )
S^1=(3.2122 2.2267 0.7731 2.7336 )
S^2=(-6.7630 4.8347 -3.7745 5.3473 )
S^3=(-28.0731 4.1843 -12.8928 7.9609 )
S^4=(-42.0816 -3.6143 -26.5819 10.5745 )
S^5=(-13.3480 -22.4510 -44.8417 13.1882 )
S^6=(110.3725 -56.2153 -67.6722 15.8018 )
S^7=(398.1284 -108.7970 -95.0734 18.4155 )
S^8=(935.7728 -184.0860 -127.0454 21.0291 )
S^9=(1825.9625 -285.9719 -163.5881 23.6427 )
S^10=(3188.1587 -418.3445 -204.7016 26.2564 )
-------------------------------------------------------------------
*/
