int fatorial_recursivo(int atual)
{
    if (atual == 0)
        return 1;

    return atual * fatorial_recursivo(atual - 1);
}

int Fibonacci_recursivo(int atual)
{
    if (atual == 0)
        return 0;
    if (atual == 1)
        return 1;

    return Fibonacci_recursivo(atual - 1) + Fibonacci_recursivo(atual - 2);
}