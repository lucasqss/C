/*Richard Phillips Feynman era um físico americano muito famoso e ganhador do Prêmio Nobel de Física. Ele trabalhava em física teórica e também foi pioneiro no campo da computação quântica. Ele visitou a América do Sul por dez meses, dando palestras e aproveitando a vida nos trópicos. Ele também é conhecido pelos livros "Surely You’re Joking, Mr. Feynman!" e "What Do You Care What Other People Think?", que inclui algumas de suas aventuras abaixo do equador.

Sua paixão da vida inteira era resolver e criar quebra-cabeças, trancas e códigos. Recentemente, um fazendeiro idoso da América do Sul, que hospedou o jovem físico em 1949, achou alguns papéis e notas que acredita-se terem pertencido a Feynman. Entre anotações sobre mesóns e eletromagnetismo, havia um guardanapo onde ele escreveu um simples desafio: "quantos quadrados diferentes existem em um quadriculado de N x N quadrados?".

Entrada

A entrada contém diversos casos de teste. Cada caso de teste é composto de uma única linha, contendo apenas um inteiro N, representando o número de quadrados em cada lado do quadriculado (1 ≤ N ≤ 100).
O final da entrada é indicado por uma linha contendo apenas um zero.

Saída

Para cada caso de teste na entrada, seu programa deve imprimir uma única linha, contendo o número de diferentes quadrados para a entrada correspondente.*/




#include <stdio.h>
 
int ContaQuadrados(int n)
{
    int total;
 /*Perceba que há a possibilidade de construir um algoritmo de tempo constante. Basta perceber que estamos fazendo um somatório de termos i^2 ,  0<i<=n. Isto se dá pelo fato de todo grid nxn possuir o numero de quadrados de um grid (n-1)x(n-1) somado aos proprios quadrados unitarios de nxn.*/   
    total = (n*(n+1)*(2*n+1))/6;
    return total;
}
int main()
{
    int num;
    while(1)
    {
        scanf("%d", &num);
        if(num==0)
        {
            break;
        }
        else
            {
                printf("%d\n", ContaQuadrados(num));
            }
    }
    return 0;
}
