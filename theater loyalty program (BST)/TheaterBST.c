#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19

typedef struct customer{

    char name[MAXLEN + 1];
    int points;
} customer;

typedef struct treenode{

    customer *cPtr;  //customer pointer
    int size;      // the size variable in the treenode will store the total number
                  // of nodes in the subtree rooted at that node, including itself.
    struct treenode * left;
    struct treenode *right;
} treenode;

treenode *root;

treenode *create_treenode(customer *customers);
customer *create_customer(char name[], int points);
void display(treenode *node);
void add(char name[], int points);
void recur_add(treenode* current_node, treenode* node_tobeAdded);
void search(char name[]);
void recur_search(treenode *node, char name[], int depth);
void del(char name[]);
treenode * delete_search(treenode *node, char name[]);
void deletefixerupper(treenode * node, char name[]);
void deleteNode(treenode **node);
void sub(char name[], int loyal_points);
void recur_sub(treenode *current_node, char name[], int loyal_points);
int count_smaller(char name[]);
treenode *count_search(treenode *node, char name[]);
int recur_count(treenode *node, char name[]);



treenode *create_treenode(customer *customers){
    treenode *ret = (treenode*)malloc(sizeof(treenode));
    ret->cPtr = customers;
    ret->left=ret->right = NULL;
    ret->size = 1; //change if arg change
    return ret;
}

customer *create_customer(char name[], int points){
    customer *ret = (customer*)malloc(sizeof(customer));
    strcpy(ret->name, name);
    ret->points = points;
    return ret;
}

//inorder print
void display(treenode * node){
    if(node == NULL)return;
    display(node->left);
    printf("%s %d %d\n", node->cPtr->name, node->cPtr->points, node->size);
    display(node->right);
}

void add(char name[], int points){
    customer* customers = create_customer(name, points); //uses the helper functions create
    treenode * node = create_treenode(customers);///to create the treenode and customer

    if(root == NULL){ 
        root = node;
        root->size=1;
    }
    else{
        recur_add(root, node);
    }
    
}

void recur_add(treenode *current_node, treenode *node_tobeAdded){


    if(strcmp(node_tobeAdded->cPtr->name, current_node->cPtr->name) <= 0){
        if(current_node->left == NULL){     //base case
            current_node->left = node_tobeAdded;
        }else{
            recur_add(current_node->left, node_tobeAdded);
        }
        
    }

    else if(strcmp(node_tobeAdded->cPtr->name, current_node->cPtr->name) > 0){
        if(current_node->right ==NULL){     //base case 
            current_node->right = node_tobeAdded;
        }else{
            recur_add(current_node->right, node_tobeAdded);
        }
    }
    current_node->size++;
}

void search(char name[]){
    if(root == NULL){
        printf("%s not found\n", name);
    }
    else if(strcmp(root->cPtr->name, name) == 0){
        printf("%s %d %d", root->cPtr->name, root->cPtr->points, 1);  //is the root dept 1 or is it considered 0
    }
    else{
        recur_search(root, name, 1);
    }
}

void recur_search(treenode *node, char name[], int depth){
    //to search and BST we have to tranc=verse the tree if we reach the end of the tree print not found
    if(node == NULL){
        printf("%s not found\n", name);
        return;
    }
    else if(strcmp(node->cPtr->name, name) == 0){   //we found jason borne aka the person
        printf("%s %d %d\n", node->cPtr->name, node->cPtr->points, depth);    //fix depth
    }
    else if((strcmp(node->cPtr->name, name) < 0)){
        recur_search(node->left, name, depth+1);
    }
    else{
        recur_search(node->right, name, depth + 1);
    }      
}


void del(char name[]){
    //store the variable we want to delete
    treenode * ret = delete_search(root, name);
    if(ret != NULL){
        deleteNode(&ret);
        printf("%s deleted\n", name);
    }
    else{
        //if(root == NULL)
            printf("%s not found\n", name);
            deletefixerupper(root, name);
    }
}


treenode * delete_search(treenode * node, char name[]){

    //could not find node in root
    if(node == NULL)return NULL;

    //we have found it
    if(strcmp(node->cPtr->name, name) == 0){
        return node;
    }
    //
    if(strcmp(name, node->cPtr->name) < 0){
        return delete_search(node->left, name);
    }
    else { //if(strcmp(name, node->cPtr->name) > 0)
        return delete_search(node->right, name);
    }
    node->size--;
}
void deletefixerupper(treenode * node, char name[]){
    if(node ==NULL) 
        return;
    if(strcmp(name, node->cPtr->name)<=0){
        deletefixerupper(node->left, name);
    }
    else{
        deletefixerupper(node->right, name);
    }
    node->size++;
}

void deleteNode(treenode ** node){


    //base case covered in delete_search

    //case 1: the node to be deleted is a leaf or the end of the tree struct

    if((*node)->left == NULL && (*node)->right == NULL){
        free(*node);
        *node = NULL;
    }

    //case 2: the node to be deleted has on child
    else if((*node)->left == NULL){
        treenode *temp = (*node);
        (*node) = (*node)->right;
        temp->right = NULL;
        free(temp->cPtr);
        free(temp);
    }
    else if((*node)->right == NULL){
        treenode *temp = (*node);
        (*node) = (*node)->left;
        temp->left = NULL;
        free(temp->cPtr);
        free(temp);
    }

    //case 3: the node to be deleted has 2 children
    else{
        treenode * previous = NULL;
        treenode * current = (*node)->right;

        //following each other down the BST and copyind the data
        while(current->left != NULL){
            previous = current;
            current = current->left;
        }

        //copying data
        (*node)->size = current->size;
        (*node)->cPtr = current->cPtr;

        //reconnecting the children before we remove the select node
        //right once and then way lefttt
        if(previous != NULL){
            previous->left = current->right;
        }
        else{
            (*node)->right = current->right;
        }
        current->right = NULL;

        //deleting current
        free(current);

    }
}

void sub(char name[], int loyalty_points){

    if(root == NULL) return;

    recur_sub(root, name, loyalty_points);
}

void recur_sub(treenode *current_node, char name[], int loyal_points){

    if(current_node == NULL) return; //base case

    if(strcmp(name, current_node->cPtr->name) == 0){ // if wee found the person
        current_node->cPtr->points -= loyal_points;
        printf("%s %d", current_node->cPtr->name, current_node->cPtr->points);
    }

    else if(strcmp(name, current_node->cPtr->name) < 0){
        recur_sub(current_node->left, current_node->cPtr->name, current_node->cPtr->points);
    }
   else if(strcmp(name, current_node->cPtr->name) > 0){
        recur_sub(current_node->right, current_node->cPtr->name, current_node->cPtr->points);
   }

}
int count_smaller(char name[]){

    treenode *node_start = count_search(root, name);

    return recur_count(node_start->left, name);
}
treenode *count_search(treenode *node, char name[]){
     //could not find node in root
    if(node == NULL)return NULL;

    //we have found it
    if(strcmp(node->cPtr->name, name) == 0){
        return node;
    }
    //
    if(strcmp(name, node->cPtr->name) < 0){
        return count_search(node->left, name);
    }
    else { //if(strcmp(name, node->cPtr->name) > 0)
        return count_search(node->right, name);
    }
}
int recur_count(treenode *node, char name[]){
    if(node==NULL)
        return 0;
    return 1+recur_count(node->left, name) +  recur_count(node->right, name);
}


//count the number of customer whose names come alphabetically
//helper functions to update data struct

int main(void){

    int number_of_commands;
    char input_line[50];
    root = NULL;
    char Command[20]; //takes in the input command
    char name[20];  //take the name of the input
    int loyalty_points = 0;
    char input_number[5];
    int i,j,k;
    

    scanf("%d", &number_of_commands);
    fflush(stdin);
    for(int index = 0; index < number_of_commands;index++ ){
        fgets(input_line, 49, stdin); //stdin is keyboard


        for(i =0; input_line[i] != ' '; i++){
            Command[i]=input_line[i];
        }
        Command[++i] = '\0';
        for(j=i; input_line[j] != ' ' && input_line[j] != '\n'; j++){
            name[j-i] = input_line[j];
        }
        name[j-i]='\0';
        

        if(strcmp(Command, "add") == 0){

            for(k =j; input_line[k]!= '\n'; k++){ //when the press enter
                input_number[k-j] = input_line[k];
            }
            input_line[k-j-1] = '\0';
            loyalty_points = strtol(input_number, NULL,10);
            add(name,loyalty_points);
            input_number[0] = input_number[1] = input_number[2] = input_number[3] = input_number[4] = '\0';  //make a for loop later
            
        }

        if(strcmp(Command, "search") == 0){
            search(name);
        }


        if(strcmp(Command, "del") == 0){
            del(name);
        }
        if(strcmp(Command, "count_smaller") == 0){
            printf("%d\n", count_smaller(name));
        }
        if(strcmp(Command, "sub")==0){
            for(k =j; input_line[k]!= '\n'; k++){ //when the press enter
                input_number[k-j] = input_line[k];
            }
            input_line[k-j-1] = '\0';
            loyalty_points = strtol(input_number, NULL,10);
            sub(name,loyalty_points);
            input_number[0] = input_number[1] = input_number[2] = input_number[3] = input_number[4] = '\0';
        }

        ///else if(if its not add then its search) 241
            //if for string comparsion //if(strcmp(c0mmand, "search"))
        //else if for delete
        // taking the command and the customer name
   }
    display(root);

    return EXIT_SUCCESS;
}
