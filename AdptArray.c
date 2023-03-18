#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "AdptArray.h"

#define SIZE 20;

typedef struct AdptArray_{

int ArrSize;
PElement* pelemArr;
DEL_FUNC df;
COPY_FUNC cf;
PRINT_FUNC pf;

}AdptArray , *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){

    PAdptArray PAarr = (PAdptArray)malloc(sizeof(AdptArray));
    if(!PAarr){ return NULL; }

    PAarr->ArrSize =0;
    PAarr->cf = cf;
    PAarr->df = df;
    PAarr->pf = pf;
    PAarr->pelemArr = NULL;
    
    return PAarr;

}

void DeleteAdptArray(PAdptArray PAarr){

    if(!PAarr){
        exit(1);
    }

    for(int i=0; i<PAarr->ArrSize;i++){

        if(PAarr->pelemArr[i] != NULL){

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