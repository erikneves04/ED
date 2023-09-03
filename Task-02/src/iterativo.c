long long int fatorial_iterativo(int atual)
{
    int resultado = 1;

    while (atual > 0)
    {
        resultado *= atual;
        atual--;
    }

    return resultado;
}

long long int fibonacci_iterativo(int atual)
{
    int i, aux; 
    int b = 1;
    int a = 0; 

    if (atual == 0)
        return 0;
    else if (atual == 1)
        return 1;

    for ( i = 0; atual > i+1; i++){
        aux = a + b;
        a = b;
        b = aux;
    }
    return aux;
}