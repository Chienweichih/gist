#define INPUT_MAX 4

// [money, count]
int input[INPUT_MAX][2] = {
    {45, (8 * 2) - 2}, // x - x
    {35, 2}, // x - s
    {30, 4},
    {20, 1}  // b - x
};

int main(void)
{
    int count, money, discount;

    count = 0;
    money = 0;

    for (int i = 0; i < INPUT_MAX; ++i)
    {
        count += input[i][1];
        money += input[i][0] * input[i][1];
    }

    if (count >= 51)
    {
        discount = money * 30 / 100;
    }
    else if (count >= 41)
    {
        discount = money * 25 / 100;
    }
    else if (count >= 31)
    {
        discount = money * 20 / 100;
    }
    else if (count >= 21)
    {
        discount = money * 15 / 100;
    }
    else if (count >= 11)
    {
        discount = money * 10 / 100;
    }
    else
    {
        discount = 0;
    }

    printf("count %d, money %d, discount %d, result %d\n", count, money, discount, money - discount);
}
