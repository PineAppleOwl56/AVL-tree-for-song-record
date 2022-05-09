

struct Node{
    struct Tree *node;
    struct Node *next;
};

struct queue{
    struct Node *head;
    int count;
};

struct queue* Createqueue(void);
struct queue* push(struct Tree*, struct queue*);
struct Tree* pop(struct queue*);

struct queue*Createqueue(void){
    struct queue *line;
    //  starting the queue with the dummy node
    line=(struct queue*)malloc(sizeof(struct queue));
    if (line==NULL){
        printf("ERROR");
        exit(-4);
    }
    line->head=(struct Node*)malloc(sizeof(struct Node));
    if (line->head==NULL){
        printf("ERROR");
        exit(-5);
    }
    line->head->next=NULL;
    line->count=0;
    return line;
}

struct queue* push(struct Tree* tree,struct queue*line){
    struct Node *temp;
    // creating the new node and inserting it in the beginning of the stack
    temp=(struct Node*)malloc(sizeof(struct Node));
    if(temp==NULL){
        printf("ERROR");
        exit(-1);
    }
    temp->next=NULL;
    temp->node=tree;
    // if the queue is empty place the node after the dummy node otherwise
    // insert the node after the head and connect what was in the queue before after the new node
    if(line->head->next==NULL){
        line->head->next=temp;
        line->count++;
    }
    else {
        temp->next=line->head->next;
        line->head->next=temp;
    }
    return line;
}
struct Tree* pop(struct queue* line){
    //returning the node that I want to pop and deleting the connection of it in the queue
    struct Node *temp;
    temp=line->head->next;
    line->count--;
    line->head->next=line->head->next->next;
    return temp->node;
}
