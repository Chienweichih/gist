void test_8(const char *input)
{
    char *ptr, *ptr_head, *ptr_tail;

    ptr = (char *)input;
    while (*ptr != '\0')
    {
        ++ptr;
    }
    while (*ptr != '.')
    {
        --ptr;
    }
    --ptr;

    while (1)
    {
        ptr_tail = ptr;
        while ((*ptr != ' ') && (ptr != (char *)input))
        {
            --ptr;
        }
        ptr_head = ptr;
        if (ptr != (char *)input)
        {
            ++ptr;
        }
        while (ptr <= ptr_tail)
        {
            printf("%c", *ptr);
            ++ptr;
        }
        if (ptr_head != (char *)input)
        {
            ptr = ptr_head - 1;
            printf(" ");
        }
        else
        {
            printf(".\n");
            break;
        }
    }
}

void reverseWords(const char* str)
{
    int len = strlen(str);
    char* strCopy = malloc(len + 1);  // Allocate memory for the copy
    strcpy(strCopy, str);  // Copy the original string

    // Split the string into words
    char* words[50];  // Array to hold pointers to the start of each word
    int wordCount = 0;

    // Tokenize the string
    char* token = strtok(strCopy, " .");
    while (token != NULL)
    {
        words[wordCount++] = token;
        token = strtok(NULL, " .");
    }

    // Print words in reverse order
    for (int i = wordCount - 1; i >= 0; i--)
    {
        printf("%s", words[i]);
        if (i > 0)
        {
            printf(" ");  // Print space between words
        }
    }
    printf(".\n");

    // Free the allocated memory
    free(strCopy);
}

void *aligned_malloc(size_t bytes, size_t alignment)
{
    void *p1 ,*p2;

    p1 = (void *) malloc(bytes + alignment + sizeof(size_t));
    if (NULL == p1)
    {
        return NULL;
    }

    size_t addr = (size_t)p1 + alignment + sizeof(size_t);
    p2 = (void *)(addr - (addr % alignment));

    *((size_t *)p2 - 1) = (size_t)p1;

    return p2;
}

void aligned_free(void *p)
{
    free((void *)(*((size_t *) p - 1)));
}

void test_9(void)
{
    int *ptr1 = (int *)aligned_malloc(1024, 32768);
    int *ptr2 = (int *)aligned_malloc(1024, 32768);
    int *ptr3 = (int *)aligned_malloc(1024, 32768);

    printf("%p %p %p\n", (void *)ptr1, (void *)ptr2, (void *)ptr3);

    aligned_free((void *)ptr1);
    aligned_free((void *)ptr2);
    aligned_free((void *)ptr3);
}

int main(void)
{
    const char *input = "The quick brown fox jumps over the lazy dog.";

    // my try
    test_8(input);

    // a better answer
    reverseWords(input);

    test_9();

    printf("Hello World\n");
}
