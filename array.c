#include <stdio.h>
#include <stdlib.h>
#include "array.h"

// basic functions
struct Performance *newPerformance(){
   struct Performance *perf; 
   perf = (struct Performance*) malloc(sizeof(struct Performance));
   // check if array is not empty, set reads, write, mallocd and frees to zero 
   if(perf != 0){
       perf->reads = 0;
       perf->writes = 0;
       perf->mallocs = 0;
       perf->frees = 0;
   }
   else {
       printf("Make newPreformance Error! Malloc Fail!\n");
       exit(0);
   }
       
    return perf;
}

struct Array *newArray( struct Performance *performance, unsigned int width, unsigned int capacity ){
    struct Array *array; 
    array= (struct Array*) malloc(sizeof(struct Array));
    // if array is not empty then set its components and malloc data
    if(array != 0){
       array->width = width;
       array->capacity = capacity;
       array->nel = 0;
       array->data = (void*)malloc(width*capacity);
       performance->mallocs++;
    }
    else {
        printf("Make newArray Error! malloc fail!\n");
        exit(0);
    }
       return array;
}
void readItem( struct Performance *performance, struct Array *array, unsigned int index, void *dest ){ 
   int i = 0;
    if(index >= (array->nel)){
        printf("Read Item Error! array->nel = %d cannot be less than index = %d\n",array->nel, index);
        exit(0);
    }
    else {
        // copy width bytes from memory address data to dest 
        unsigned int newIndex = index * array->width;
         //pointer to data and array
        char* ptr = (char*)array->data + newIndex;
        char* ptr2 = (char*)dest;
        for (i = 0; i < array->width; i++)
        {
         // dest = source 
          *ptr2 = *ptr;
           ptr2++;
           ptr++;
            
        }
        // increment reads
        performance->reads++;
    }

}
void writeItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
    int i = 0;

    if(index > (array->nel) || index >= (array->capacity)){
        printf("Write item Error! neither nel  = %d nor capacity = %d are allowed to exceed or equal index = %d\n", array->nel,array->capacity, index);
        exit(0);
    }
    else{
        // copy width bytes from memory address src to data
        unsigned int newIndex = index * array->width;
         //pointer to data and array
        char* ptr = (char*)src;
        char* ptr2 = (char*)array->data + newIndex;        
        
        for (i = 0; i < array->width; i++)
        {
         // dest = source
          *ptr2 = *ptr;
           ptr2++;
           ptr++;
            
        }
        //increment nel 
        if(index == array->nel){
            array->nel = array->nel + 1;
        }
        // increment writes
        performance->writes++;
    }
}

void contract( struct Performance *performance, struct Array *array ){
    if(array->nel == 0){
        printf("Contract Error! array-> nel cannot be 0");
        exit(0);
    }
    else {
        array->nel--;
    }
}
void freeArray( struct Performance *performance, struct Array *array ){
    free(array->data);      
    free(array);
    performance->frees++;
}
void appendItem( struct Performance *performance, struct Array *array, void *src ){
    
    writeItem(performance,array,array->nel,src);

}
void insertItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
    int i = 0;
    char* dest = (char*)malloc(sizeof(array->width));
    // shift all elements up by one
    for ( i = array->nel; i > index ; i--)
    {
        // read shifted elements 
       readItem(performance,array,i-1,dest);
       // write shifted elements 
       writeItem(performance,array,i,dest);
    }
    // write item into array
    writeItem(performance,array,index,src);
}
void prependItem( struct Performance *performance, struct Array *array, void*src ){
    insertItem(performance,array,0,src);
}
void deleteItem( struct Performance *performance, struct Array *array, unsigned int index ){
    int i = 0;
    char* dest = (char*)malloc(sizeof(array->width));
    // shift elements down by one
    for ( i = index; i < array->nel-1; i++)
    {
        // read shifted elements 
       readItem(performance,array,i+1,dest);
       // write shifted elements 
       writeItem(performance,array,i,dest);
    }
    // decrement # of elements
    contract(performance,array);
}
int findItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){
    int i = 0;
    int index = -1;
    char* dest = (char*)malloc(array->width);
    for ( i = 0; i < array->nel; i++)
    {
        readItem(performance,array,i,dest);
        if((*compar)(dest,target) == 0){
            return i;
        }

    }
    return index;
}
// perform binary search on the items 
int searchItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){
    int middle = 0, right = array->nel-1, left = 0;
    char* dest = (char*)malloc(array->width);
    int result = 0;

    while (left <= right){
        middle = (left + right)/2;
        readItem(performance,array,middle,dest);
        result = (*compar)(dest,target);
        // less than 
        if(result < 0){
            left = middle+1;
        }
        // greater than 
        else if(result > 0){
            right = middle -1;
        }
        else{
            return middle;
        }
    }
    return -1;
}