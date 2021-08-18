#include <unistd.h>

void yaz(int sayi[], int boyut)
{
    for (int i = boyut - 1; i >= 0; i--)
    {
        char a = sayi[i] + '0';
        write(1, &a, 1);
    }
    write(1, ", ", 2);
}

void sayac(int left, int basamakta, int sayi[], int boyut)
{
    int max = 10 - basamakta;
    for (int i = left + 1; i < max; i++)
    {
        if (basamakta)
        {
            sayi[basamakta] = i;
            sayac(i, basamakta - 1, sayi, boyut);
        }
        else
        {
            sayi[basamakta] = i;
            yaz(sayi, boyut);
        }
    }
}

void diz(int basamak)
{
    int sayi[basamak];
    sayac(-1, basamak - 1, sayi, basamak);
}

int main()
{
    diz(9);
}