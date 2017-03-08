#include <stdio.h>

unsigned int bitPosition(int x, int y)
{
    return 64 - (x * 8 + y + 1);
}

int main()
{   unsigned long long ConfiguratieMatrice, mutare;
    unsigned int Ci = 0, Li = 0, Cf = 0, Lf = 0;
    int i, N;

    scanf("%llu", &ConfiguratieMatrice);
    scanf("%d", &N);
    
    for(i = 0; i < N; i++)
    {    
        scanf("%llu", &mutare);
        Ci = mutare & 7;
        Li = (mutare >> 3) & 7;
        Cf = (mutare >> 6) & 7;
        Lf = (mutare >> 9) & 7; 
        
        unsigned long long bitInitial = bitPosition(Li, Ci);
        unsigned long long bitFinal = bitPosition(Lf, Cf);

        /*Se testeaza daca avem soldat pe pozitia initiala(pe pozitia bitInitial este 1)
        si daca pozitiile initiale si cele finale sunt alceleasi */
        if(((ConfiguratieMatrice>>bitInitial) & (unsigned long long)1)== 0 || (bitInitial == bitFinal))
            continue;
        else
        {
            //Se dezactiveaza soldatul de pe pozitia initiala
            ConfiguratieMatrice = ConfiguratieMatrice & ( ~ ((unsigned long long)1 << bitInitial));
            //Daca exista soldat in pozitia finala punem 0 , daca nu exista punem 1
            ConfiguratieMatrice = ConfiguratieMatrice ^ (unsigned long long)((unsigned long long)1 << bitFinal);
        }
    }

    printf("%llu \n", ConfiguratieMatrice);
    return 0;
}
