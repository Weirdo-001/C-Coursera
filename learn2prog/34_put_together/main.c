#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *f = fopen(filename,"r");
  if (f==NULL){
    perror("Could not open file");
    return NULL;
  }
  counts_t * counts_arr = createCounts();
  char * line = NULL;
  size_t size =0;
  char * value = NULL;
  while (getline(&line,&size,f)>=0){
    char *n = strchr(line,'\n');
    if(n != NULL){
      *n = '\0';
    }
    value = lookupValue(kvPairs,line);
    addCount(counts_arr,value);
  }
  free(line);

  if (fclose(f) !=0){
    perror("fail to close the file\n");
    return NULL;
  }

  return counts_arr;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc < 2){
    fprintf(stderr,"no enough arguments");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *  kv_arr = readKVs(argv[1]);
  if (kv_arr==NULL){
    fprintf(stderr,"fail to read the kv_pair file\n");
    return EXIT_FAILURE;
  }
  printf("read kv_pair_sucess!!!\n");
 //count from 2 to argc (call the number you count i)
  for (int i =2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i],kv_arr);
    printf("count sucessful!!!\n");
    if(c == NULL) {return EXIT_FAILURE;}
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    printf("make output file name\n");

    //open the file named by outName (call that f)
    FILE *f = fopen(outName,"w");
    //print the counts from c into the FILE f
    printCounts(c,f);
    printf("witre output file\n");
    //close f
    if(fclose(f) !=0){
      perror("fail to close the file\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c

    freeCounts(c);
    free(outName);
  }
 //free the memory for kv
  freeKVs(kv_arr);

  return EXIT_SUCCESS;
}
