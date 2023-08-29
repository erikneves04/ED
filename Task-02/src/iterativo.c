int fatorial_iterativo(int atual)
{
    int resultado = 1;

    while (atual > 0)
    {
        resultado *= atual;
        atual--;
    }

    return resultado;
}

int Fibonacci_iterativo(int atual)
{
    if (atual == 0)
        return 0;
    if (atual == 1)
        return 1;

    return Fibonacci_recursivo(atual - 1) + Fibonacci_recursivo(atual - 2);
}