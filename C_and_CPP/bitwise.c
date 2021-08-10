int get_highest_bit_position(unsigned char x)
{
    int n = 7;
    if (x == 0) return -1; /* position not found */
    if ((x >> 4) == 0) { n = n-4; x=x << 4;}
    if ((x >> 6) == 0) { n = n-2; x=x << 2;}
    if ((x >> 7) == 0) { n = n-1;}

    return n;
}

int get_lower_bit_position(unsigned char x)
{
    x = x & (-x);
    return get_highest_bit_position(x);
}

int numbers_of_1_in_int(unsigned int x)
{
    int count = 0;
    while (x!=0)
    {
        x = x & (x-1);
        count++;
    }
    return count;
}

bool is_nth_power_of_two(unsigned int x)
{
    return (1 == numbers_of_1_in_int(x)) ? true : false;
}

unsigned int set_bit(unsigned int x, int bitnum)
{
    x = (x | 1 << bitnum);
    return x;
}

unsigned int clear_bit(unsigned int x, int bitnum)
{
    x = x & ~(1<<bitnum);
    return x;
}

int main(void)
{
    unsigned char test = 0x5a;

    printf("test         %02x\n", test);
    printf("highest bit  %02x\n", get_highest_bit_position(test));
    printf("lower bit    %02x\n", get_lower_bit_position(test));
    printf("num of 1     %02x\n", numbers_of_1_in_int(test));
    printf("power of 2   %02x\n", is_nth_power_of_two(test));
    printf("set bit 0    %02x\n", set_bit(test, 0));
    printf("clear bit 1  %02x\n", clear_bit(test, 1));
}
