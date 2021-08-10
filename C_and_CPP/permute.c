#define NUMBERS 24 // 4!
int elements[] = {6, 7, 8, 9};
int iter = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *result, int l, int r)
{
    int i;

    if (l == r)
    {
        result[iter] = 0;
        for (i = 0; i <= r; ++i)
        {
            result[iter] *= 10;
            result[iter] += elements[i];
        }
        printf("%d, %d\n", iter, result[iter]);
        ++iter;
        return;
    }

    for (i = l; i <= r; ++i)
    {
        swap(&elements[l], &elements[i]);
        permute(result, l + 1, r);
        swap(&elements[l], &elements[i]);
    }
}

int main(void)
{
    int min = 0xFFFF, ans_a = 0, ans_b = 0;
    int p_elements[NUMBERS];

    permute(p_elements, 0, 3);

    for (int i = 0; i < NUMBERS; ++i) // a
    {
        for (int j = i + 1; j < NUMBERS; ++j) // b
        {
            int a = p_elements[i];
            int b = p_elements[j];
            if (min > ((a > b)? (a - b): (b - a)))
            {
                min = ((a > b)? (a - b): (b - a));
                ans_a = a;
                ans_b = b;
            }
        }
    }

    printf("the ans is %d (%d %d)\n", min, ans_a, ans_b);
}
