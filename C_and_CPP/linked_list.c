
typedef struct node {
    int val;
    struct node * next;
} node_t;

void insert_after(node_t * target, node_t * target_prev) {
    target->next = target_prev->next;
    target_prev->next = target;
}

node_t* get_new_node(int data) {
    node_t * new_node = (node_t *)malloc(sizeof(node_t));
    new_node->val = data;
    new_node->next = NULL;
    return new_node;
}

void print_list(node_t * head) {
    node_t * temp = head;
    while (temp != NULL) {
        printf("%d\t", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {

    node_t * head = get_new_node(12);
    insert_after(get_new_node(99), head);

    //for test sorting
    insert_after(get_new_node(7), head->next);

    print_list(head);

    // add new node
    insert_after(get_new_node(37), head);

    print_list(head);

    //sort
    node_t * sorted_list = (node_t *)malloc(sizeof(node_t));
    sorted_list->next = head;
    head = head->next;
    sorted_list->next->next = NULL;

    while (head != NULL) {
        node_t * temp = head;
        head = head->next;

        node_t * target_prev = sorted_list;
        while (target_prev->next != NULL && target_prev->next->val < temp->val) {
            target_prev = target_prev->next;
        }
        insert_after(temp, target_prev);
    }

    head = sorted_list->next;
    free(sorted_list);

    print_list(head);

    // release head memory
    node_t * temp = head;
    while (temp != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }

    return 0;
}
