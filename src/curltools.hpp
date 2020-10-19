#ifndef CURLTOOLS_HPP
#define CURLTOOLS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MemoryStruct {

  MemoryStruct()
  {
      memory = (char*)malloc(1);
      size = 0;
  }
  ~MemoryStruct()
  {
      free(memory);
  }
  char *memory;
  size_t size;
};


static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  MemoryStruct *mem = (MemoryStruct *)userp;

  char *ptr = (char*) realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


#endif // CURLTOOLS_HPP
