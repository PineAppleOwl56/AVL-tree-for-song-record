// Daniil Belousov
// 2491827
// Practice assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avltree.h"
#include "rotation.h"
#include "queue.h"

int main(int argc, char *argv[]) {
    struct Tree *SongsTree;
    int option;
    // initializing the initial tree with the data stored in the external file
    SongsTree= readData(argv[1]);
    // displaying the menu and based on the user choice perform the function
    printf("Welcome to Song Indexing");
    do{
        printf("\n-----------------------------------------------------------------------------\n"
                "1. Display the full index of songs\n"
                "2. Display the songs of popular artist\n"
                "3. Display the oldest song\n"
                "4. Exit\n\n"
                "Option: ");
        scanf("%d", &option);
        printf("\n");
        switch(option) {
            case 1:
                displaySongs(SongsTree);
                break;
            case 2:
                popularArtist(SongsTree);
                break;
            case 3:
               oldestSong(SongsTree);
                break;
            case 4:
                break;
            default:
                printf("Unknown command, please choose one of the given options");
        }
        }while(option!=4);

    return 0;
}




struct Tree *readData(char filename[]){
    struct Tree *SongTree=NULL;
    int checkpoint1=0,checkpoint2=0,release_year, flag;
    char inputuser[10], line[100], *token, song_name[20], song_genre[20],album_name[20],artist_name[20], release_date[20];

    FILE *inFile;
    //opening the file and asking the user to reenter the file name if the file from the command line does not exist otherwise printing that everything is fine
    //if the user can not open the file, there is an escape word that stops the program running
    inFile=fopen(filename, "r");
    if (inFile==NULL){
        printf("\nThis file does not exist,if you want to leave, enter 'exit'\nOtherwise please enter the filename again: ");
        while (checkpoint1!=1){
            fflush(stdin);
            scanf("%s", inputuser);
            inFile = fopen(inputuser, "r");
            // checking the file based on the users input if it still does not exist, asks to reenter the name
            if (inFile == NULL){
                if (strcmp(inputuser, "exit")==0)
                    exit(-10);
                printf("\nThis file does not exist,if you want to leave, enter 'exit'\nOtherwise please enter the filename again: ");
            }
            else
                checkpoint1=1;
        }
    }
    else
        printf("The %s file has been loaded successfully\n\n", filename);
    while (fgets(line, 100, inFile)){      // getting the stracture filled with the data from the file by the usage of strings
        token = strtok(line, ";");      // recording cutting the string in peaces and assigning to the corresponding structure parts
        flag=1;
        while( token != NULL ) {
            if (flag == 1)
                strcpy(song_name, token);
            else if (flag == 2)
                strcpy(song_genre, token);
            else if (flag == 3)
                strcpy(album_name, token);
            else if(flag==4)
                strcpy(artist_name,token);
            else if(flag==5)
                release_year = atoi(token);
            else if(flag==6) {
                if (token[strlen(token)-1]=='\n') // the lust peace of the string has the new line sign on the end, so we replace it with the end of the string
                    token[strlen(token)-1]='\0';
                strcpy(release_date, token);

            }
            token = strtok(NULL, ";");
            flag++;
        }
        // sending the information from the file string to the function so that it will be stored in the avl tree
        SongTree= insertSong(SongTree,song_name,song_genre,album_name,artist_name,release_year,release_date);
    }
    fclose(inFile);
    return SongTree;
}

struct Tree *insertSong(struct Tree *SongTree, char song_name[], char song_genre[], char album_name[], char artist_name[], int release_year, char release_date[])
    {
        struct Tree *Another, *k; // the node that corresponds to the song whose author is already in the list
        //creating the new node for the new author, allocating the memory for the node and store the songs' information in it
        if (SongTree == NULL)
        {

            SongTree = (struct Tree*)malloc(sizeof(struct Tree));
            if (SongTree == NULL)
                printf("Out of memory space!!!\n");
            else
            {
                strcpy(SongTree->song_name, song_name);
                strcpy(SongTree->song_genre, song_genre);
                strcpy(SongTree->album_name, album_name);
                strcpy(SongTree->artist_name, artist_name);
                SongTree->release_year=release_year;
                strcpy(SongTree->release_date, release_date);
                SongTree->height = 0;
                SongTree->left = SongTree->right = SongTree->list =NULL;
            }
        }
        // comparing the name of the author to the nodes in the tree
        // if the authors name is alphabetically smaller than the nodes authors name, we move to the left of the tree
        else if (strcmp(SongTree->artist_name, artist_name)>0)
        {
            SongTree->left = insertSong(SongTree->left,song_name,song_genre,album_name,artist_name,release_year,release_date);
            // we come back from the place we inserted the new author and count the height of the node, if it is equal to two, we do the balancing
            // based on the type of the balance problem
            if (AVLTreeHeight(SongTree->left) - AVLTreeHeight(SongTree->right) == 2) {
                if (strcmp(SongTree->artist_name, artist_name)>0)
                    SongTree = SingleRotateWithLeft(SongTree);
                else
                    SongTree = DoubleRotateWithLeft(SongTree);
            }
        }
            // comparing the name of the author to the nodes in the tree
            // if the authors name is alphabetically bigger than the nodes authors name, we move to the left of the tree
        else if (strcmp(SongTree->artist_name, artist_name)<0) {
            SongTree->right = insertSong(SongTree->right,song_name,song_genre,album_name,artist_name,release_year,release_date);
            //we come back from the place we inserted the new author and count the height of the node, if it is equal to two, we do the balancing
            //based on the type of the balance problem
            if (AVLTreeHeight(SongTree->right) - AVLTreeHeight(SongTree->left) == 2){
                if (strcmp(SongTree->artist_name, artist_name)<0)
                    SongTree = SingleRotateWithRight(SongTree);
                else
                    SongTree = DoubleRotateWithRight(SongTree);
            }
        }
        // we also check if the name of the new author is equal to the authors name that is stored in the tree already
        // if so, we create the new node and connect it to the tree's author node
        else if(strcmp(SongTree->artist_name, artist_name)==0){
            Another = (struct Tree*)malloc(sizeof(struct Tree));
            if (Another == NULL)
                printf("Out of memory space!!!\n");
            else
            {
                strcpy(Another->song_name, song_name);
                strcpy(Another->song_genre, song_genre);
                strcpy(Another->album_name, album_name);
                strcpy(Another->artist_name, artist_name);
                Another->release_year=release_year;
                strcpy(Another->release_date, release_date);
                Another->height = SongTree->height;
                Another->left = Another->right = Another->list =NULL;
                if(SongTree->list==NULL)
                    SongTree->list=Another;
                else {
                    k = SongTree;
                    while(k->list!=NULL)
                        k=k->list;
                    k->list=Another;
                }

            }

        }
        //in every recursion we set the height value of each node in the end, so we can do the balancing properly
        SongTree->height = Max(AVLTreeHeight(SongTree->left), AVLTreeHeight(SongTree->right)) + 1;
        return SongTree;
    }


// displaying the songs in the alphabetical order
// as the tree is stored in alphabetical order, display the name from the most left to the most right leafs of the tree
void displaySongs(struct Tree * t){
    struct Tree *more;
    if (t != NULL){
        more=t->list;
        displaySongs(t->left);
        printf("%s;%s;%s;%s;%d;%s\n",t->song_name, t->song_genre,t->album_name, t->artist_name, t->release_year, t->release_date);
        // if there is more than one son for one's author, display all the authors songs and move to the next author
        while (more!=NULL) {
            printf("%s;%s;%s;%s;%d;%s\n", more->song_name, more->song_genre, more->album_name, more->artist_name,more->release_year, more->release_date);
            more=more->list;
        }
        displaySongs(t->right);
    }
}




void popularArtist(struct Tree *SongsTree){
    struct queue *second, *first;
    int finished=0, count;
    first=Createqueue();
    second=Createqueue();
    struct Tree *t, *p, *k;
    t=SongsTree;
    // in this function I go through all the nodes and have two stacks, one is for the all tree nodes, and the second is for the node
    // with the biggest amount of songs
    while(finished!=1){
        count=0;
        if(t!=NULL){
            first=push(t, first);
            p=t;
            while(p->list!=NULL) {
                count++;
                p=p->list;
            }
            //comparing the number of songs of ones author to the one that we have inputted in the stack and if the new node is bigger
            // than replacing the stacks stored node
            if(second->count<count){
                second->head->next=NULL;
                second=push(t,second);
                second->count=count;
            }
            t=t->left;
        }
        else if(first->head->next!=NULL){
            t=pop(first);
            t=t->right;
        }
        else
            finished=1;
    }
    k=second->head->next->node;
    while(k!=NULL){
        printf("%s;%s;%s;%s;%d;%s\n", k->song_name, k->song_genre, k->album_name, k->artist_name,k->release_year, k->release_date);
        k=k->list;
    }
    free(first);
    free(second);
}
/*
 * This functions complexity is O(n^2) with push, pop, and Createqueue function of complexity O(n)
 * this function could have been written differently, with the use of recursion and send the node with the biggest number of
 * songs to the main function to be displayed, or instead of stack adt, a queue could be used, if there was a recursion, the stack/queue
 * adt would not have been needed, because we could simply return the node and compare it to the ones coming before it in the tree
 */

void oldestSong(struct Tree *SongTree){
    struct queue* line;
    struct Tree *t, *k, *p;
    int finished=0;
    line=Createqueue();
    t=k=SongTree;
    //traverse the whole tree and store the node with the minimal release year in the pointer k
     while(finished!=1){
        if(t!=NULL){
            line=push(t, line);
            p=t->list;
            while(p!=NULL) {
                line = push(p, line);
                p=p->list;
            }
            t=t->left;
        }
        else if(line->head->next!=NULL){
            t=pop(line);
            if (t->release_year<k->release_year)
                k=t;
            t=t->right;
        }
        else
            finished=1;
    }
    printf("%s;%s;%s;%s;%d;%s\n", k->song_name, k->song_genre, k->album_name, k->artist_name,k->release_year, k->release_date);
    free(line);
}

/*
 * This functions complexity is O(n^2) with push, pop, and Createqueue function of complexity O(n)
 * this function is similar to the function before it so:
 * the function could have been written differently, with the use of recursion
 */