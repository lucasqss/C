/*Os habitantes de Nlogônia são muito supersticiosos. Uma de suas crenças é que os números das casas de rua que têm um dígito repetido traz sorte ruim para os moradores. Portanto, eles nunca iriam viver em uma casa que tem o número 838 ou 1004, por exemplo.

A rainha de Nlogônia ordenou a construção de uma nova avenida à beira-mar e quer atribuir para as novas casas apenas números sem dígitos repetidos, para evitar desconforto entre os seus súditos. Você foi nomeado por Sua Majestade para escrever um programa que, dado dois inteiros N e M, determine a quantidade máxima possível de casas que podem assumir um número entre N e M inclusive, sem que ocorram dígitos repetidos nestes números.

Entrada

Cada teste é descrito usando uma linha. A linha contém dois inteiros N e M, conforme descrito acima (1 ≤ N ≤ M ≤ 5000).

Saída

Para cada caso de teste imprima um valor inteiro que representa a quantidade máxima possível de números de casa entre N e M inclusive, sem dígitos repetidos.*/





#include <stdio.h>
#define MAX 5000
int main()
{
	int min, max, tot, rem, array[MAX], t[MAX], i, j, k, cont=0;
	while(scanf("%d %d", &min, &max)==2)
	{
		tot = (max-min)+1;
		rem=0;
		for (i = 0; i <tot; ++i)
		{
			array[i] = (min+i);
		}
		for (i = 0; i <tot; i++)
		{
			k=array[i];
			cont=0;
			for (j = 0; j < 5; j++)
			{
				if(k==0)
				{
					break;
				}
				else
				{
					t[j]=k%10;
					k=k/10;
					cont++;
				}
			}
			for(j=0; j<cont; j++)
			{
				for(k=(j+1); k<cont; k++)
				{
					if(t[j]==t[k])
					{
						rem++;
						j=cont+1;
						break;
					}
				}
			}
		}
		printf("%d\n", (tot-rem));
	}
	return 0;
}
