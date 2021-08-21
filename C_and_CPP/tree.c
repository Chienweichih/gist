
uint8_t get_highest_bit_position(uint32_t x)
{
    uint8_t n = 31;

    if (x == 0) { return 32;}

    if ((x >> 16) == 0) { n = n-16; x=x << 16;}
    if ((x >> 24) == 0) { n = n-8; x=x << 8;}
    if ((x >> 28) == 0) { n = n-4; x=x << 4;}
    if ((x >> 30) == 0) { n = n-2; x=x << 2;}
    if ((x >> 31) == 0) { n = n-1;}

    return n;
}

void setIn8bitArray(uint8_t * array, uint32_t index)
{
    array[index >> 3] |= (1 << (index & 0x07));
}

bool getIn8bitArray(uint8_t * array, uint32_t index)
{
    return (0 != (array[index >> 3] & (1 << (index & 0x07))));
}

//
// level |           TreeIndex            |          index
//   0   |               01               |
//   1   |       02              03       |
//   2   |   04      05      06      07   |
//   3   | 08  09  10  11  12  13  14  15 | 00 01 02 03 04 05 06 07
//
// length = 16 / 8
//
bool setBitsInTree(uint8_t * ptrTree, uint32_t length, uint32_t index)
{
    uint8_t  level = (get_highest_bit_position(length << 3) - 1);
    uint32_t treeIndex = ((1 << level) + index);

    while (treeIndex != 1)
    {
        if (true == getIn8bitArray(ptrTree, treeIndex))
        {
            if (treeIndex == ((1 << level) + index))
            {
                return true; // already set
            }
            break;
        }
        else
        {
            setIn8bitArray(ptrTree, treeIndex);
        }

        // parent node
        treeIndex >>= 1;
    }

    // no need to set root node

    return false;
}

// if no next, return UINT32_MAX
uint32_t findNextInTree(uint8_t * ptrTree, uint32_t length, uint32_t index)
{
    uint8_t  move  = 0;
    uint8_t  level = (get_highest_bit_position(length << 3) - 1);
    uint32_t treeIndex = ((1 << level) + index);

    if (true == getIn8bitArray(ptrTree, treeIndex))
    {
        return index;
    }

    // search right up
    while (treeIndex != 1)
    {
        if (0x00 == (treeIndex & 0x01)) // left node
        {
            // check right node
            ++treeIndex;
            if (true == getIn8bitArray(ptrTree, treeIndex))
            {
                break;
            }
        }

        // parent node
        treeIndex >>= 1;
        ++move;
    }

    if (treeIndex == 1)
    {
        return UINT32_MAX;
    }

    // search down left right
    while (move != 0)
    {
        // left child node
        treeIndex <<= 1;
        --move;

        if (true != getIn8bitArray(ptrTree, treeIndex))
        {
            ++treeIndex;
        }
    }

    // treeIndex to index
    return (treeIndex - (1 << level));
}

int main(void)
{
    const uint32_t totalElemetnCnt = 122057;
    const uint32_t paddingElementCnt = (totalElemetnCnt & (totalElemetnCnt - 1))? 
        (1 << (get_highest_bit_position(totalElemetnCnt) + 2)): (totalElemetnCnt << 1); 
    const uint32_t totalTreeNode = (paddingElementCnt >> 3);

    uint8_t myTree[totalTreeNode];
    uint32_t test[] = {0, 2, 7, 59, 200, 4257, 35761, 21153, 122055};

    // clean
    memset((void *)myTree, 0, totalTreeNode * sizeof(uint8_t));

    // set
    for (uint8_t i = 0; i < 9; ++i)
    {
        printf("set   %8d\n", test[i]);
        setBitsInTree(myTree, totalTreeNode, test[i]);
    }

    // search
    uint32_t index = 0;
    index = findNextInTree(myTree, totalTreeNode, index);
    while (index < totalElemetnCnt)
    {
        printf("found %8d\n", index);
        index = findNextInTree(myTree, totalTreeNode, index + 1);
    }
}

