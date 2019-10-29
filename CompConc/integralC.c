#include <stdio.h>
#include <math.h>

double func(double x){
    return (sqrt(1+pow(x, 4)));
}
double integral(double a, double b, int n){
    double h = (b-a)/n;
    double resultado = 0;
    for(int i=0; i<n; i++){
        resultado += h*func((a + h/2) + i*h);
    }
    return resultado;
}
int main()
{
    double a, b, erro;
    int n;
    printf("intervalo [a, b]:\n");
    printf("a:\n");
    scanf("%lf", &a);
    printf("b:\n");
    scanf("%lf", &b);
    printf("erro maximo\n");
    scanf("%lf", &erro);
    n = ceil(sqrt(1/erro));
    printf("\n \n resultado: %lf", integral(a, b, n));
    



    

    return 0;
}

