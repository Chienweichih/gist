
#define MAX_NUM_ROOT (1024)
#define MAX_NUM      (MAX_NUM_ROOT * MAX_NUM_ROOT)

static uint8_t sieve[MAX_NUM >> 3];

void setPrime(uint32_t i)
{
    sieve[i >> 3] |= (1 << (i & 7));
}

bool isPrime(uint32_t i)
{
    return (0 == (sieve[i >> 3] & (1 << (i & 7))));
}

void printPrime(void)
{
    printf("Prime Number under %d:\n", MAX_NUM);
    for (uint32_t i = 0; i < MAX_NUM; ++i)
    {
        if (isPrime(i))
        {
            printf("%d\n", i);
        }
    }
}

int main(void)
{
    setPrime(0);
    setPrime(1);
    for (uint32_t i = 0; i < MAX_NUM_ROOT; ++i)
    {
        if (isPrime(i))
        {
            uint32_t x = i + i;
            while (x < MAX_NUM)
            {
                setPrime(x);
                x += i;
            }
        }
    }
    printPrime();
}
