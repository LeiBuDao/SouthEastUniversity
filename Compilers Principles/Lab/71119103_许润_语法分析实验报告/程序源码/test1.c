{
    while (i <= 100)
    {
        if (i == 2)
            sum = sum + i;
        else if (i > 5)
            do
            {
                sum = sum * (2 - sum) / 2 + 1;
                if (sum < 0)
                    break;
            } while (i < 0);
        if (i <= 2 * (i + 1))
            sum = 1;
        else
            sum = 0;
        i = i + 2;
    }
}
