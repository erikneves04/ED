long long int fatorial_recursivo(int atual)
{
    if (atual == 0)
        return 1;

    return atual * fatorial_recursivo(atual - 1);
}

long long int fibonacci_recursivo(int atual)
{
    if (atual == 0)
        return 0;
    if (atual == 1)
        return 1;

    return fibonacci_recursivo(atual - 1) + fibonacci_recursivo(atual - 2);
}