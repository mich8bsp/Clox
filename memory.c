#include <stdlib.h>
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    /**
     * oldSize == 0, newSize != 0 -> allocate
     * oldSize != 0, newSize == 0 -> free
     * oldSize != 0, newSize != 0 -> shrink or grow existing allocation
    */
   if(newSize == 0){
       free(pointer);
       return NULL;
   }

   void* result = realloc(pointer, newSize);
   if(result == NULL){
       exit(1); //allocation fail, abort
   }
   return result;
}