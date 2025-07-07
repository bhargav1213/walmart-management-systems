#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_of_aisles;
int date;
typedef struct item_tag
{
    int aisle_num;
    int item_id;
    int quantity;
    int threshold;
    int expiry;
    int bf;
    struct item_tag *left;
    struct item_tag *right;
    char item_name[50];

} item_node;

typedef struct aisle_tag
{
    int aisle_num;
    char aisle_name[50];
    item_node *item_root;

} aisle_node;

typedef struct bill_tag
{
    int aisle_num;
    int item_id;
    int qty;
    struct bill_tag *next;

} bill_node;

typedef struct bill_tree_tag
{
    int bill_num;
    int bf;
    bill_node *bill_list;
    struct bill_tree_tag *left;
    struct bill_tree_tag *right;

} bill_tree;

item_node *rotate_right(item_node *r)
{
    item_node *tnode = r;
    if ((r == NULL) && (r->left == NULL))
    {
        printf("ERROR\n");
    }
    else
    {
        tnode = r->left;
        r->left = tnode->right;
        tnode->right = r;
    }
    return tnode;
}

item_node *rotate_left(item_node *r)
{
    item_node *tnode = r;
    if ((r == NULL) && (r->right == NULL))
    {
        printf("ERROR\n");
    }
    else
    {
        tnode = r->right;
        r->right = tnode->left;
        tnode->left = r;
    }
    return tnode;
}

item_node *right_balance(item_node *root, int *taller)
{
    item_node *rs = root->right;
    item_node *ls;

    if (rs->bf == 1)
    {
        root->bf = rs->bf = 0;
        root = rotate_left(root);
        *taller = 0;
    }
    else if (rs->bf == -1)
    {
        ls = rs->left;

        if (ls->bf == 0)
        {
            root->bf = rs->bf = 0;
        }
        else if (ls->bf == 1)
        {
            root->bf = -1;
            rs->bf = 0;
        }
        else if (ls->bf == -1)
        {
            root->bf = 0;
            rs->bf = 1;
        }
        ls->bf = 0;
        root->right = rotate_right(rs);
        root = rotate_left(root);
        *taller = 0;
    }
    return root;
}

item_node *left_balance(item_node *root, int *taller)
{
    item_node *ls = root->left;
    item_node *rs;

    if (ls->bf == -1)
    {
        root->bf = rs->bf = 0;
        root = rotate_right(root);
        *taller = 0;
    }
    else if (ls->bf == 1)
    {
        rs = ls->right;

        if (ls->bf == 0)
        {
            root->bf = ls->bf = 0;
        }
        else if (rs->bf == 1)
        {
            root->bf = 0;
            ls->bf = -1;
        }
        else if (rs->bf == -1)
        {
            root->bf = 1;
            rs->bf = 0;
        }
        rs->bf = 0;
        root->left = rotate_left(ls);
        root = rotate_right(root);
        *taller = 0;
    }
    return root;
}

item_node *insert_node(item_node *root, item_node *nptr, int *taller)
{
    if (root == NULL)
    {
        nptr->bf = 0;
        root = nptr;
        *taller = 1;
    }
    else
    {
        if (root->item_id == nptr->item_id)
        {
            printf("DUPLICATE element\n");
        }
        else
        {
            if (root->item_id > nptr->item_id)
            {

                root->left = insert_node(root->left, nptr, taller);
                if (*taller)
                {
                    if (root->bf == 0)
                    {
                        root->bf = -1;
                    }
                    else if (root->bf == 1)
                    {
                        root->bf = 0;
                        *taller = 0;
                    }
                    else if (root->bf == -1)
                    {
                        root = left_balance(root, taller);
                    }
                }
            }
            else
            {
                root->right = insert_node(root->right, nptr, taller);
                if (*taller)
                {
                    if (root->bf == 0)
                    {
                        root->bf = 1;
                    }
                    else if (root->bf == -1)
                    {
                        root->bf = 0;
                        *taller = 0;
                    }
                    else
                    {
                        root = right_balance(root, taller);
                    }
                }
            }
        }
    }
    return root;
}

item_node *delete_node(item_node *root, int item_id, int *shorter)
{
    if (root == NULL)
        return root;

    // If the data to be deleted is smaller than the root's data, then it lies in the left subtree
    if (item_id < root->item_id)
    {
        root->left = delete_node(root->left, item_id, shorter);

        // Update balance factor and perform balancing if needed
        if (*shorter)
        {
            if (root->bf == 0)
            {
                root->bf = 1;
                *shorter = 0;
            }
            else if (root->bf == -1)
            {
                root->bf = 0;
            }
            else if (root->bf == 1)
            {
                if (root->right->bf == 0)
                {
                    *shorter = 0;
                }
                else if (root->right->bf == 1)
                {
                    root = right_balance(root, shorter);
                }
                else
                {
                    root = right_balance(root, shorter);
                }
            }
        }
    }

    // If the data to be deleted is greater than the root's data, then it lies in the right subtree
    else if (item_id > root->item_id)
    {
        root->right = delete_node(root->right, item_id, shorter);

        // Update balance factor and perform balancing if needed
        if (*shorter)
        {
            if (root->bf == 0)
            {
                root->bf = -1;
                *shorter = 0;
            }
            else if (root->bf == 1)
            {
                root->bf = 0;
            }
            else if (root->bf == -1)
            {
                if (root->left->bf == 0)
                {
                    *shorter = 0;
                }
                else if (root->left->bf == -1)
                {
                    root = left_balance(root, shorter);
                }
                else
                {
                    root = left_balance(root, shorter);
                }
            }
        }
    }

    // If item_id is same as root's item_id, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            item_node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
            *shorter = 1;
        }
        else
        {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            item_node *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;

            // Copy the inorder successor's data to this node
            root->item_id = temp->item_id;

            // Delete the inorder successor
            root->right = delete_node(root->right, temp->item_id, shorter);

            // Update balance factor and perform balancing if needed
            if (*shorter)
            {
                if (root->bf == 0)
                {
                    root->bf = -1;
                    *shorter = 0;
                }
                else if (root->bf == 1)
                {
                    root->bf = 0;
                }
                else if (root->bf == -1)
                {
                    if (root->left->bf == 0)
                    {
                        *shorter = 0;
                    }
                    else if (root->left->bf == -1)
                    {
                        root = left_balance(root, shorter);
                    }
                    else
                    {
                        root = left_balance(root, shorter);
                    }
                }
            }
        }
    }

    return root;
}














bill_tree *rotate_right_bill(bill_tree *r)
{
    bill_tree *tnode = r;
    if ((r == NULL) && (r->left == NULL))
    {
        printf("ERROR\n");
    }
    else
    {
        tnode = r->left;
        r->left = tnode->right;
        tnode->right = r;
    }
    return tnode;
}

bill_tree *rotate_left_bill(bill_tree *r)
{
    bill_tree *tnode = r;
    if ((r == NULL) && (r->right == NULL))
    {
        printf("ERROR\n");
    }
    else
    {
        tnode = r->right;
        r->right = tnode->left;
        tnode->left = r;
    }
    return tnode;
}

bill_tree *right_balance_bill(bill_tree *root, int *taller)
{
    bill_tree *rs = root->right;
    bill_tree *ls;

    if (rs->bf == 1)
    {
        root->bf = rs->bf = 0;
        root = rotate_left_bill(root);
        *taller = 0;
    }
    else if (rs->bf == -1)
    {
        ls = rs->left;

        if (ls->bf == 0)
        {
            root->bf = rs->bf = 0;
        }
        else if (ls->bf == 1)
        {
            root->bf = -1;
            rs->bf = 0;
        }
        else if (ls->bf == -1)
        {
            root->bf = 0;
            rs->bf = 1;
        }
        ls->bf = 0;
        root->right = rotate_right_bill(rs);
        root = rotate_left_bill(root);
        *taller = 0;
    }
    return root;
}

bill_tree *left_balance_bill(bill_tree *root, int *taller)
{
    bill_tree *ls = root->left;
    bill_tree *rs;

    if (ls->bf == -1)
    {
        root->bf = rs->bf = 0;
        root = rotate_right_bill(root);
        *taller = 0;
    }
    else if (ls->bf == 1)
    {
        rs = ls->right;

        if (ls->bf == 0)
        {
            root->bf = ls->bf = 0;
        }
        else if (rs->bf == 1)
        {
            root->bf = 0;
            ls->bf = -1;
        }
        else if (rs->bf == -1)
        {
            root->bf = 1;
            rs->bf = 0;
        }
        rs->bf = 0;
        root->left = rotate_left_bill(ls);
        root = rotate_right_bill(root);
        *taller = 0;
    }
    return root;
}

bill_tree *insert_bill_node(bill_tree *root, bill_tree *nptr, int *taller)
{
    if (root == NULL)
    {
        nptr->bf = 0;
        root = nptr;
        *taller = 1;
    }
    else
    {
        if (root->bill_num == nptr->bill_num)
        {
            printf("DUPLICATE element\n");
        }
        else
        {
            if (root->bill_num > nptr->bill_num)
            {

                root->left = insert_bill_node(root->left, nptr, taller);
                if (*taller)
                {
                    if (root->bf == 0)
                    {
                        root->bf = -1;
                    }
                    else if (root->bf == 1)
                    {
                        root->bf = 0;
                        *taller = 0;
                    }
                    else if (root->bf == -1)
                    {
                        root = left_balance_bill(root, taller);
                    }
                }
            }
            else
            {
                root->right = insert_bill_node(root->right, nptr, taller);
                if (*taller)
                {
                    if (root->bf == 0)
                    {
                        root->bf = 1;
                    }
                    else if (root->bf == -1)
                    {
                        root->bf = 0;
                        *taller = 0;
                    }
                    else
                    {
                        root = right_balance_bill(root, taller);
                    }
                }
            }
        }
    }
    return root;
}

bill_tree *delete_node(bill_tree *root, int bill_num, int *shorter)
{
    if (root == NULL)
        return root;

    // If the data to be deleted is smaller than the root's data, then it lies in the left subtree
    if (bill_num < root->bill_num)
    {
        root->left = delete_node(root->left, bill_num, shorter);

        // Update balance factor and perform balancing if needed
        if (*shorter)
        {
            if (root->bf == 0)
            {
                root->bf = 1;
                *shorter = 0;
            }
            else if (root->bf == -1)
            {
                root->bf = 0;
            }
            else if (root->bf == 1)
            {
                if (root->right->bf == 0)
                {
                    *shorter = 0;
                }
                else if (root->right->bf == 1)
                {
                    root = right_balance_bill(root, shorter);
                }
                else
                {
                    root = right_balance_bill(root, shorter);
                }
            }
        }
    }

    // If the data to be deleted is greater than the root's data, then it lies in the right subtree
    else if (bill_num > root->bill_num)
    {
        root->right = delete_node(root->right, bill_num, shorter);

        // Update balance factor and perform balancing if needed
        if (*shorter)
        {
            if (root->bf == 0)
            {
                root->bf = -1;
                *shorter = 0;
            }
            else if (root->bf == 1)
            {
                root->bf = 0;
            }
            else if (root->bf == -1)
            {
                if (root->left->bf == 0)
                {
                    *shorter = 0;
                }
                else if (root->left->bf == -1)
                {
                    root = left_balance_bill(root, shorter);
                }
                else
                {
                    root = left_balance_bill(root, shorter);
                }
            }
        }
    }

    // If bill_num is same as root's bill_num, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            bill_tree *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
            *shorter = 1;
        }
        else
        {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            bill_tree *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;

            // Copy the inorder successor's data to this node
            root->bill_num = temp->bill_num;

            // Delete the inorder successor
            root->right = delete_node(root->right, temp->bill_num, shorter);

            // Update balance factor and perform balancing if needed
            if (*shorter)
            {
                if (root->bf == 0)
                {
                    root->bf = -1;
                    *shorter = 0;
                }
                else if (root->bf == 1)
                {
                    root->bf = 0;
                }
                else if (root->bf == -1)
                {
                    if (root->left->bf == 0)
                    {
                        *shorter = 0;
                    }
                    else if (root->left->bf == -1)
                    {
                        root = left_balance_bill(root, shorter);
                    }
                    else
                    {
                        root = left_balance_bill(root, shorter);
                    }
                }
            }
        }
    }

    return root;
}



















void writeDot(FILE *fp, item_node *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->left != NULL)
    {
        fprintf(fp, "%d -> %d;\n", node->item_id, node->left->item_id);
        writeDot(fp, node->left);
    }

    if (node->right != NULL)
    {
        fprintf(fp, "%d -> %d;\n", node->item_id, node->right->item_id);
        writeDot(fp, node->right);
    }
}

void generateDotFile(item_node *root)
{
    FILE *fp;
    fp = fopen("avl_tree.dot", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp, "digraph AVLTree {\n");
    writeDot(fp, root);
    fprintf(fp, "}\n");

    fclose(fp);
}

void add_item(aisle_node *arr)
{
    int x = 0;

    item_node *new;
    new = (item_node *)malloc(sizeof(item_node));
    printf("enter the aisle number :");
    scanf("%d", &new->aisle_num);
    printf("enter the item name :");
    scanf("%s", new->item_name);
    printf("enter the item_id:");
    scanf("%d", &new->item_id);
    printf("enter the threshold:");
    scanf("%d", &new->threshold);
    printf("enter the expiry date:");
    scanf("%d", &new->expiry);
    printf("enter the quantity:");
    scanf("%d", &new->quantity);
    new->left = NULL;
    new->right = NULL;
    new->bf = 0;
    arr[(new->aisle_num) - 1].item_root = insert_node(arr[(new->aisle_num) - 1].item_root, new, &x);
}

void save_item_data(aisle_node *arr)
{
    item_node *new;
    FILE *fptr;
    int x = 0;
    fptr = fopen("store_data.txt", "r");
    while (!feof(fptr))
    {

        new = (item_node *)malloc(sizeof(item_node));
        fscanf(fptr, "%d", &new->aisle_num);
        fscanf(fptr, "%d", &new->item_id);
        fscanf(fptr, "%s", new->item_name);
        fscanf(fptr, "%d", &new->threshold);
        fscanf(fptr, "%d", &new->expiry);
        fscanf(fptr, "%d", &new->quantity);
        new->left = NULL;
        new->right = NULL;
        new->bf = 0;
        arr[(new->aisle_num) - 1].item_root = insert_node(arr[(new->aisle_num) - 1].item_root, new, &x);
    }
    fclose(fptr);
}

void save_aisle_data(aisle_node *arr)
{
    FILE *fptr;
    int a_num;
    fptr = fopen("aisle_data.txt", "r");
    fscanf(fptr, "%d", &num_of_aisles);
    while (!feof(fptr))
    {
        fscanf(fptr, "%d", &a_num);
        arr[a_num - 1].aisle_num = a_num;
        fscanf(fptr, "%s", arr[a_num - 1].aisle_name);
        arr[a_num - 1].item_root = NULL;
    }

    fclose(fptr);
}

void inorder(item_node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->item_id);
        inorder(root->right);
    }
}

item_node *search(int id, item_node *root)
{
    item_node *nptr = root;
    int flag = 0;
    while (flag == 0)
    {
        if (nptr->item_id > id)
        {
            nptr = nptr->left;
        }
        else if (nptr->item_id < id)
        {
            nptr = nptr->right;
        }
        else if (nptr->item_id == id)
        {
            flag = 1;
        }
        if (nptr->right == NULL && nptr->left == NULL)
        {
            flag = 2;
        }
    }
    if (flag == 2)
    {
        nptr = NULL;
    }

    return nptr;
}

void update_item(aisle_node *arr)
{
    int id, i = 0, flag = 0;
    item_node *nptr;
    printf("enter item to be searched :");
    scanf("%d", &id);

    while (i < num_of_aisles && flag == 0)
    {

        nptr = search(id, arr[i].item_root);
        if (nptr != NULL)
        {
            flag = 1;
        }
        i++;
    }
    if (flag == 0)
    {
        printf("item not found ");
    }
    else
    {
        printf("enter the item name :");
        scanf("%s", nptr->item_name);
        printf("enter the threshold:");
        scanf("%d", &nptr->threshold);
        printf("enter the expiry date:");
        scanf("%d", &nptr->expiry);
        printf("enter the quantity:");
        scanf("%d", &nptr->quantity);
    }
}

void add_aisle(aisle_node *arr, int max_aisles)
{
    if (num_of_aisles < max_aisles)
    {
        int flag = 1;
        num_of_aisles++;
        printf("enter aisle name :");
        scanf("%s", arr[num_of_aisles - 1].aisle_name);
        arr[num_of_aisles - 1].aisle_num = num_of_aisles;
        arr[num_of_aisles - 1].item_root = NULL;
        printf("enter 1 to add item else press any key :");
        scanf("%d", &flag);
        while (flag == 1)
        {
            add_item(arr);
            printf("enter 1 to add item else press any key :");
            scanf("%d", &flag);
        }
    }
    else
    {
        printf("new aisles can't be added:");
    }
}

void update_aisle(aisle_node *arr)
{
    int a_num, opt;
    printf("enter aisle number to be updated :");
    scanf("%d", &a_num);
    printf("enter 1 to update aisle_name :\n");
    printf("enter 2 to add a item :\n");
    printf("enter 3 to update an aisle :\n");
    scanf("%d", &opt);
    if (opt == 1)
    {
        printf("enter new name for aisle :");
        scanf("%s", arr[a_num - 1].aisle_name);
    }
    else if (opt == 2)
    {
        add_item(arr);
    }
    else
    {
        update_item(arr);
    }
}

void check_availbilty(aisle_node *arr)
{
    int i = 0, flag = 0, id, qty, exp;
    item_node *nptr;
    printf("enter item id :");
    scanf("%d", &id);
    printf("enter quantity :");
    scanf("%d", &qty);
    printf("enter expiry :");
    scanf("%d", &exp);

    while (i < num_of_aisles && flag == 0)
    {

        nptr = search(id, arr[i].item_root);
        if (nptr != NULL)
        {
            flag = 1;
        }
        i++;
    }
    if (flag == 0)
    {
        printf("item not found \n");
    }
    else
    {

        if (nptr->expiry > exp && nptr->quantity > qty)
        {
            printf("requried quantity of %s is available before %d \n", nptr->item_name, exp);
        }
        else
        {
            printf("requried quantity of %s is  not available before %d \n", nptr->item_name, exp);
        }
    }
}

void inorder_ct(item_node *root)
{
    if (root != NULL)
    {
        inorder_ct(root->left);
        if (root->threshold > root->quantity)
        {
            printf("item %s reached its threshold \n", root->item_name);
        }
        inorder_ct(root->right);
    }
}

void check_threshold(aisle_node *arr)
{
    int i = 0;
    while (i < num_of_aisles)
    {
        inorder_ct(arr[i].item_root);
        i++;
    }
}

void visit_crf(item_node *root)
{
    int flag, n, year, mon, day, num_days, total_days, exp_year, exp_mon, exp_day;

    year = date / 10000;
    mon = (date % 1000) / 100;
    day = date % 100;
    num_days = year * 360 + mon * 30 + day;
    exp_year = root->expiry / 10000;
    exp_mon = (root->expiry % 1000) / 100;
    exp_day = root->expiry % 100;
    total_days = exp_year * 360 + exp_mon * 30 + exp_day;
    n = total_days - num_days;
    if (n < 7 && n > 0)
    {
        printf("%s expires in %d days \n", root->item_name, total_days - num_days);
        flag = 1;
    }
    if (n < 0)
    {
        printf("%s expired  %d days ago \n", root->item_name, -1 * n);
    }
}

void inorder_crf(item_node *root)
{
    if (root != NULL)
    {

        inorder_crf(root->left);
        visit_crf(root);
        inorder_crf(root->right);
    }
}

void check_ready_to_eat_foods(aisle_node *arr)
{
    int flag = 0, i = 0;
    while (i < num_of_aisles && flag == 0)
    {
        if (strcmp(arr[i].aisle_name, "ready_to_eat") == 0)
        {
            inorder_crf(arr[i].item_root);
        }
        i++;
    }
}

void inorder_range(item_node *root, int max, int min)
{
    if (root != NULL)
    {
        inorder_range(root->left, max, min);
        if (root->item_id > min && root->item_id < max)
        {
            printf("%d ", root->item_id);
        }
        inorder_range(root->right, max, min);
    }
}

void range(aisle_node *arr)
{
    int i = 0, flag = 0, a_num, min, max;
    printf("Enter aisle number :");
    scanf("%d", &a_num);
    printf("enter range (min max) :");
    scanf("%d %d", &min, &max);
    inorder_range(arr[a_num - 1].item_root, max, min);
}



int main()
{
    aisle_node *arr;
    int max_num_aisles = 6, i;
    // printf("today's date :");
    // scanf("%d", &date);
    // printf("enter number of aisle :");
    // scanf("%d",&num_aisles);
    arr = (aisle_node *)malloc(sizeof(aisle_node) * max_num_aisles);
    i = 0;

    save_aisle_data(arr);
    save_item_data(arr);
    int x = 0;

   arr[0].item_root = merge_avl_trees(arr[0].item_root, arr[1].item_root);

    // delete_node(arr[0].item_root,107,&x);
    generateDotFile(arr[0].item_root);

    // range(arr);

    // add_item(arr);

    // while (i < max_num_aisles)
    // {
    //     printf("%s \n",arr[i].aisle_name);
    //     //     inorder(arr[i].item_root);
    //     //     printf("\n");

    //     i++;
    // }
    return 0;
}