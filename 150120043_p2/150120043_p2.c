// umut bayar 150120043

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//created struct
struct Node{
 short reCall,currValue,height;
    struct Node *leftChild,*rightChild,*Parent,*grandParent;
};
//memory space allocated and initial values assigned null
struct Node *createNode(short land){
    struct Node *node=(struct Node *)malloc(sizeof(struct Node)*2);
    node->currValue=land;
    node->height=1;
    node->leftChild=node->rightChild=NULL;
    return node;
}
struct Node *root=NULL;

//created variables to calculate costs 
short rotateNumberAvl=0;
short rotateNumberSplay=0;
short compareNumberAvl=0;
short compareNumberSplay=0;

//created a function that calculates the height of the tree
short height(struct Node *pointer){
    if(pointer==NULL){
        return 0;
    }
    else
    return pointer->height;
}
/*created the function to determine the larger one that will determine 
whether the value moves to the right or to the left*/
short bigOne(short x,short y){
   	return (x>y) ? x: y ;
}
// alternative to choose the big one
short bOne(short x,short y){
	if(x>y)
        return x;
    else
        return y;
}
//created function to rotate tree left
struct Node* leftRotate(struct Node* rotateElement1){
	struct Node *rotateElement2 = rotateElement1->rightChild;
    struct Node *temp = rotateElement2->leftChild;
    rotateElement2->leftChild = rotateElement1;
    rotateElement1->rightChild = temp;
//assign height value
    rotateElement1->height = bigOne(height(rotateElement1->rightChild), height(rotateElement1->leftChild)) + 1;
    rotateElement2->height = bigOne(height(rotateElement2->rightChild), height(rotateElement2->leftChild)) + 1;

    return rotateElement2;
}
//created function to rotate tree right
struct Node* rightRotate(struct Node *rotateElement2){
    struct Node *rotateElement1 = rotateElement2->leftChild;
    struct Node *temp = rotateElement1->rightChild;
    rotateElement1->rightChild = rotateElement2;
    rotateElement2->leftChild = temp;
    //assign height value
    rotateElement2->height = bigOne(height(rotateElement2->rightChild),height(rotateElement2->leftChild)) + 1;
    rotateElement1->height = bigOne(height(rotateElement1->rightChild),height(rotateElement1->leftChild)) + 1;

    return rotateElement1;
}
struct Node *orderFunc(struct Node *pointer , short currValue){
    while(pointer!=NULL){	
    if (currValue < pointer->currValue)
        pointer->leftChild  = orderFunc(pointer->leftChild, currValue);
    else if (currValue > pointer->currValue){
     return  pointer->rightChild = orderFunc(pointer->rightChild, currValue);
    }
    else 
    return pointer;
}
while (pointer==NULL){
	return ;
}
}
//Created function for avl tree
struct Node *AVL(struct Node* pointer, short currValue){
    if (pointer == NULL){
        return  createNode(currValue);
    }
    if (pointer->currValue > currValue ){
    	compareNumberAvl++;
        pointer->leftChild  = AVL(pointer->leftChild, currValue);
    }
    else if (  pointer->currValue<currValue){
    	compareNumberAvl++;
        pointer->rightChild = AVL(pointer->rightChild, currValue);
    }
    else {
    	compareNumberAvl++;
    return pointer;
}
	pointer->height = 1 + bigOne(height(pointer->leftChild), height(pointer->rightChild));
    short balance;
	if(pointer==NULL)
    return 0;
    else
    balance=height(pointer->leftChild) - height(pointer->rightChild);
    // left left 
    if(balance>1 &&  pointer->leftChild->currValue>currValue){
    	rotateNumberAvl++;
    	compareNumberAvl++;
        return rightRotate(pointer);
    }
    // Right Right 
    if(balance<-1 && pointer->rightChild->currValue<currValue ){
    	rotateNumberAvl++;
    	compareNumberAvl++;
        return leftRotate(pointer);
    }
    // left Right 
    if(balance>1 && currValue > pointer->leftChild->currValue){
    	rotateNumberAvl++;
    	compareNumberAvl++;
        pointer->leftChild = leftRotate(pointer->leftChild);
        return rightRotate(pointer);
    }
    // Right left 
    if(balance<-1 && pointer->rightChild->currValue>currValue ){
    	rotateNumberAvl++;
    	compareNumberAvl++;
        pointer->rightChild = rightRotate(pointer->rightChild);
        return leftRotate(pointer);
    }
    return pointer;
}
//Created function for Splay tree
struct Node *splay(struct Node *pointer, short currValue) {
    // root is NULL or currValue is present at root
    if (pointer->currValue==currValue || pointer == NULL )
        return pointer; 
 
    // currValue lies in left 
    if (  currValue<pointer->currValue) {
    	compareNumberSplay++;
        // currValue is not here
        if (pointer->leftChild == NULL){
            return pointer;
}
        // (left left)
        if (  currValue<pointer->leftChild->currValue) {
        	compareNumberSplay++;
        	rotateNumberSplay+=2;
            // First currValue should be root
            pointer->leftChild->leftChild = splay(pointer->leftChild->leftChild, currValue);
            pointer = rightRotate(pointer);
        } else if (currValue>pointer->leftChild->currValue) // (left Right)
        {
        	compareNumberSplay++;
        	rotateNumberSplay+=2;
            pointer->leftChild->rightChild = splay(pointer->leftChild->rightChild, currValue); 
            if (pointer->leftChild->rightChild != NULL)
                pointer->leftChild = leftRotate(pointer->leftChild);
        }
        return (pointer->leftChild == NULL) ? pointer : rightRotate(pointer);
    } else // currValue lies in rightChild 
    {
    		compareNumberSplay++;
        // currValue is not in tree
        if (pointer->rightChild == NULL)
            return pointer;
        // (Right left)
        if (  currValue<pointer->rightChild->currValue) {
        	compareNumberSplay++;
        	rotateNumberSplay+=2;
            // Bring the currValue as root of right-left
            pointer->rightChild->leftChild = splay(pointer->rightChild->leftChild, currValue);
            if (pointer->rightChild->leftChild != NULL)           
                pointer->rightChild = rightRotate(pointer->rightChild);
        } else if ( currValue>pointer->rightChild->currValue)// (Right Right)
        {
        	compareNumberSplay++;
        	rotateNumberSplay+=2;
            // Bring the currValue as root of right right and do first rotation
            pointer->rightChild->rightChild = splay(pointer->rightChild->rightChild, currValue);
            pointer = leftRotate(pointer);
        }
        return (pointer->rightChild == NULL) ? pointer : leftRotate(pointer);
    }
}
void preorder(struct Node *pointer){
    if(pointer==NULL)
        return;
    else{
    printf("%hu ",pointer->currValue);
    preorder(pointer->leftChild);
    preorder(pointer->rightChild);
}
}
void inorder(struct Node *pointer){
    if(pointer==NULL)
        return;
    else{
    preorder(pointer->leftChild);
    printf("%hu ",pointer->currValue);
    preorder(pointer->rightChild);
}
}
void postorder(struct Node *pointer){
    if(pointer==NULL)
        return;
    else{
    preorder(pointer->leftChild);
    preorder(pointer->rightChild);
	printf("%hu ",pointer->currValue);
}
}
int main(){
     FILE* file;
    file = fopen("input1.txt", "r");
    //Check if file is empty
    if (file == NULL) {
    }
    //readed digits from file
    short currValue;
    printf("AVL tree: \n");
     while (fscanf(file,"%hu",&currValue)==1){
     	root=AVL(root,currValue);
	 }
    //closed input file
    fclose(file);
    preorder(root);
    printf("\ntotal cost: %hu",rotateNumberAvl+compareNumberAvl);
    printf("\n");
    file = fopen("input1.txt", "r");
    //Check if file is empty
    if (file == NULL) {
    }
    printf("\n");
    //readed digits from file
    short data1;
    printf("Splay tree: \n");
     while (fscanf(file,"%hu",&data1)==1){
     	root=splay(root,data1);
	 }
    //closed input file
    fclose(file);
    //called preorder function for sequence
    preorder(root);
	printf("\ntotal cost: %hu",rotateNumberSplay+compareNumberSplay);
}
