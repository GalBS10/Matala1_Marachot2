//Things I have used:
// - the solution of moed A of Marachot1

//People I have helped(a little):
// - yuval yordezinchki
// - Matan adar


#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "AdptArray.h"

#define SIZE 20;

typedef struct AdptArray_{

int ArrSize;
PElement* pelemArr;//the way we hold the objects in the adptarray.

//pointers to functions
//different function for each kind of object.
DEL_FUNC df;
COPY_FUNC cf;
PRINT_FUNC pf;

}AdptArray , *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){//creating a new AdptArray.

    PAdptArray PAarr = (PAdptArray)malloc(sizeof(AdptArray));
    if(!PAarr){ return NULL; }
    //initialization
    PAarr->ArrSize =0;
    PAarr->cf = cf;
    PAarr->df = df;
    PAarr->pf = pf;
    PAarr->pelemArr = NULL;
    
    return PAarr;

}

void DeleteAdptArray(PAdptArray PAarr){

    if(!PAarr){//if we didn't get a pointer to a PElement array then we exit.
        exit(1);
    }

    for(int i=0; i<PAarr->ArrSize;i++){

        if(PAarr->pelemArr[i] != NULL){//deleting only if there is no NULL there.

            (*PAarr->df)(PAarr->pelemArr[i]);  //deleting the element with the suitable del func.

        }

    }

    free(PAarr->pelemArr);
    free(PAarr);

}

Result SetAdptArrayAt(PAdptArray PAarr, int index, PElement pelem){

    if(PAarr == NULL || pelem == NULL){
        return FAIL;
    }
    if(index < 0){
        return FAIL;
    }
    
    if(index >= PAarr->ArrSize){ // we want tp declare on a new Array

        PElement* newArr = (PElement*)calloc((index+1),sizeof(PElement));
        if(!newArr){return FAIL;}

        for(int i=0; i<PAarr->ArrSize; i++){
            newArr[i] = PAarr->pelemArr[i];
        }
        if(PAarr->pelemArr!=NULL){ //checking if we already set an array because otherwise we will try to free a NULL.
            free(PAarr->pelemArr);
        }
        PAarr->pelemArr = newArr;
    }

    if(PAarr->pelemArr[index]!=NULL){

        (*PAarr->df)(PAarr->pelemArr[index]);  //deleting the element with the suitable del func.

    }

    PAarr->pelemArr[index] = (*PAarr->cf)(pelem);
    if(index>PAarr->ArrSize){
        PAarr->ArrSize = index+1;
    }  //else stay the same size as befor.
    
    return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray PAarr, int index){

if(!PAarr){

    return NULL;
    
}

if(PAarr->pelemArr[index] == NULL || index >= PAarr->ArrSize){
    
    return NULL;

}

return (*PAarr->cf)(PAarr->pelemArr[index]);

}

int GetAdptArraySize(PAdptArray PAarr){
    if(!PAarr){
        return -1;
    }
    return PAarr->ArrSize;
}

void PrintDB(PAdptArray PAarr){
    if(!PAarr){printf("PAarr is null");}
    printf("PAarr : [\n");
    for(int i=0; i<PAarr->ArrSize; i++){
        
        if(PAarr->pelemArr[i]!=NULL){
            printf("%d. ",i);
            (*PAarr->pf)(PAarr->pelemArr[i]);
        }
    }
     printf("]\n");
}