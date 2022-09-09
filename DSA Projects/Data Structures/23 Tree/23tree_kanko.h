#include<stdio.h>
#include<stdlib.h>

typedef struct tree23{
    char binary;
    int val1, val2;
    struct tree23 * p1, * p2, * p3;
} tree23;

void display(tree23 *head){
    if(head == NULL) return;

    if(head->binary == 1){
        printf("%d ", head->val1);
        display(head->p1);
        display(head->p2);
    }

    if(head->binary == 0){
        printf("%d|%d ", head->val1, head->val2);
        display(head->p1);
        display(head->p2);
        display(head->p3);
    }
}

int search(tree23 *head, int key){
    if(head == NULL) return 0;

    if(head->binary == 1){
        if (head->val1 == key) return 1;
        else return (search(head->p1, key) || search(head->p2, key));
    }

    if(head->binary == 0){
        if (head->val1 == key || head->val2 == key) return 1;
        else return (search(head->p1, key) || search(head->p1, key) || search(head->p3, key));
    }
}

tree23 * createNode(int val){
    tree23 * temp;
    temp = (tree23 *)malloc(sizeof(tree23));

    if(temp == NULL) return NULL;
    temp->binary = 1;
    temp->val1 = val;
    temp->p1 = temp->p2 = temp->p3 = NULL;

    return temp;
}

tree23 * splitter(tree23 * head, tree23 * toBeInserted){
    if(head->binary = 1){
        if(toBeInserted->val1 < head->val1){
            head->p3 = head->p2;
            head->p2 = toBeInserted->p2;
            head->p1 = toBeInserted->p1;
            head->val2 = head->val1;
            head->val1 = toBeInserted->val1;
            head->binary = 0;
        }

        if(toBeInserted->val1 > head->val1){
            head->p2 = toBeInserted->p1;
            head->p3 = toBeInserted->p2;
            head->val2 = toBeInserted->val1;
            head->binary = 0;
        }
    }
    if(head->binary = 0){
        if(toBeInserted->val1 < head->val1){
            tree23 * temp = createNode(head->val1);
            temp->binary = 1;
            temp->p1 = toBeInserted;
            temp->p2 = head;

            head->binary = 1;
            head->val1 = head->val2;
            head->p1 = head->p2;
            head->p2 = head->p3;

            return temp;
        }

        if(toBeInserted->val1 > head->val2){
            tree23 * temp = createNode(head->val2);
            temp->binary = 1;
            temp->p2 = toBeInserted;
            temp->p1 = head;

            head->binary = 1;

            return temp;
        }

        tree23 * temp = createNode(toBeInserted->val1);

        tree23 * tempLeft = createNode(head->val1);
        tree23 * tempRight = createNode(head->val2);

        temp->p1 = tempLeft;
        temp->p2 = tempRight;
        
        temp->p1->p1 = head->p1;
        temp->p1->p2 = toBeInserted->p1;
        temp->p2->p1 = toBeInserted->p2;
        temp->p2->p2 = head->p3;

        return temp;
    }
}

tree23 * insert(tree23 *head, int val){
    if(head == NULL) return createNode(val);
    if(head->p1 == NULL){
        if(head->binary == 1){
            head->binary = 0;
            head->val2 = val;
            return head;
        }
        if(head->binary == 0){
            return splitter(head, createNode(val));
        }
    }

    if(head->binary == 1) {
        if(head->val1 > val){
            tree23 * temp = insert(head->p1, val);
            return splitter(head, temp);
        } else if (head ->val1 < val){
            tree23 * temp = insert(head->p2, val);
            return splitter(head, temp);
        }
    }

    if(head->binary == 0) {
        if(head->val1 > val){
            tree23 * temp = insert(head->p1, val);
            return splitter(head, temp);
        } else if (head ->val2 < val){
            tree23 * temp = insert(head->p3, val);
            return splitter(head, temp);
        }
        else {
            tree23 * temp = insert(head->p2, val);
            return splitter(head, temp);
        }
    }
}
