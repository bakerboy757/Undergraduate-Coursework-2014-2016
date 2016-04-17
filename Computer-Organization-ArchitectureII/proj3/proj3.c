/*Tyler Kelly: tck13*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 200

typedef struct{
  char type;
  int addr;
}DataType;

typedef struct{
  int tag;
  int dirtyBit;
  int validBit;
  int timestamp; /*for LRU*/
}CacheType;

int rCurSize = 0;
int BLOCK_SIZE,
    NUMBER_SETS,
    ASSOCIATIVITY,
    OFFSET_BITS,
    INDEX_BITS,
    TAG_BITS,
    REFERENCES;
DataType reference[MAXSIZE];

int getFlag(char *flag, int argc, char *argv[]);
void printThroughText(int num);
void printBackText(int num);
void writeThrough(CacheType**, DataType*);
void writeBack(CacheType**, DataType*);
unsigned getIndex(unsigned int addr);
unsigned getOffset(unsigned int addr);
unsigned getTag(unsigned addr);
int getLRU(CacheType ** cacheC, int index);
void initCache(CacheType **cachePtr);

int main(int argc, char *argv[]){

  if(argc != 7){
    printf("Error: <command> <-b> <number> <-s> <number> <-n> <number>\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  int j = 0;

  CacheType **cache;

  /*assign values*/
  BLOCK_SIZE = getFlag("-b", argc, argv);
  NUMBER_SETS = getFlag("-s", argc, argv);
  ASSOCIATIVITY = getFlag("-n", argc, argv);
  OFFSET_BITS = log(BLOCK_SIZE)/log(2),
  INDEX_BITS = log(NUMBER_SETS)/log(2),
  TAG_BITS = 32 - (OFFSET_BITS + INDEX_BITS);

  /*print values*/
  printf("Block size: %d\n", BLOCK_SIZE);
  printf("Number of sets: %d\n", NUMBER_SETS);
  printf("Associativity: %d\n", ASSOCIATIVITY);
  printf("Number of offset bits: %d\n", OFFSET_BITS);
  printf("Number of index bits: %d\n", INDEX_BITS);
  printf("Number of tag bits: %d\n", TAG_BITS);

  /*store contents of trace file in array of type DataType*/
  while(rCurSize < MAXSIZE-1 && scanf(" %c %d", &reference[rCurSize].type, &reference[rCurSize].addr) > 0)
    rCurSize++;

  REFERENCES = rCurSize;

  /*init cache*/
  cache = (CacheType **) malloc(sizeof(CacheType * ) * NUMBER_SETS);
  for(i = 0; i < NUMBER_SETS; i++)
    cache[i] = (CacheType *) malloc(sizeof(CacheType) * ASSOCIATIVITY);
  for(i = 0; i < NUMBER_SETS; i++){
    for(j = 0; j < ASSOCIATIVITY; j++){
      cache[i][j].validBit = 0;
      cache[i][j].dirtyBit = 0;
      cache[i][j].timestamp = 0;
    }
  }
  /*WRITETHROUGH*/
  printThroughText(REFERENCES);
  writeThrough(cache, reference);

  /*reinit cache*/
  for(i=0;i < NUMBER_SETS; i++){
    free(cache[i]);
  }
  free(cache);
  cache = (CacheType **) malloc(sizeof(CacheType * ) * NUMBER_SETS);
  for(i = 0; i < NUMBER_SETS; i++)
    cache[i] = (CacheType *) malloc(sizeof(CacheType) * ASSOCIATIVITY);
  for(i = 0; i < NUMBER_SETS; i++){
    for(j = 0; j < ASSOCIATIVITY; j++){
      cache[i][j].validBit = 0;
      cache[i][j].dirtyBit = 0;
      cache[i][j].timestamp = 0;
    }
  }

  /*WRITEBACK*/
  printBackText(REFERENCES);
  writeBack(cache, reference);
  

}
void writeThrough(CacheType **cache, DataType *reference){
  int i = 0;
  int j = 0;
  int k = 0;
  int misses = 0;
  int memRef = 0;
  int hits = 0;
  int set=-1;
  int flag = 0;
  int time = 0;
  int spot = 0;
  unsigned index;
  unsigned offset;
  unsigned tag;

  /*iterate over our trace file stored in reference array*/
  for(;i < REFERENCES; i++){
    /*generate fields based off trace file*/
    index = getIndex(reference[i].addr);
    tag = getTag(reference[i].addr);
    offset = getOffset(reference[i].addr);
    set = -1;
    flag = 0;
    /*if any of the valid bits in our block are 1 then set flag to 1*/
    for(j = 0; j < ASSOCIATIVITY; j++){
      if(cache[index][j].validBit && (cache[index][j].tag == tag)){
        set = j;
        break;
      }
    }
    /***************READ SECTION*************/
    if(reference[i].type == 'R'){
      /*if we have a miss*/
      if(set < 0){
        memRef++;
        misses++;
        /*search for available block*/
        for(k=0; k < ASSOCIATIVITY; k++){
          if(!cache[index][k].validBit){
            spot = k;
            flag = 1;
            break;
          }
        }
        /*if no available block then need to use LRU block*/
        if(!flag){
         spot = getLRU(cache, index);
        }
       cache[index][spot].validBit = 1;
       cache[index][spot].tag = tag;
       cache[index][spot].timestamp = ++time;
        
      }
      /*we have a hit*/
      else{
        hits++;
        cache[index][set].timestamp = ++time;
      }
    }

    /*************WRITE SECTION***************/
    else if(reference[i].type == 'W'){
      /*if we have a miss*/
      if(set < 0){
        misses++;
        memRef++;
      }
      /*we have a hit*/
      else{
        hits++;
        memRef++;
        /*updating cache*/
        /*search for available block*/
        cache[index][set].validBit = 1;
        cache[index][set].tag = tag;
        cache[index][set].timestamp = ++time;
      }
    }
  }
  printf("Hits: %d\n", hits);
  printf("Misses: %d\n", misses);
  printf("Memory References: %d\n", memRef);

}
void writeBack(CacheType **cache, DataType *reference){
  int i = 0;
  int j = 0;
  int k = 0;
  int misses = 0;
  int memRef = 0;
  int hits = 0;
  int set=-1;
  int flag = 0;
  int time = 0;
  int spot = 0;
  unsigned index;
  unsigned offset;
  unsigned tag;

  /*iterate over our trace file stored in reference array*/
  for(;i < REFERENCES; i++){
    /*generate fields based off trace file*/
    index = getIndex(reference[i].addr);
    tag = getTag(reference[i].addr);
    offset = getOffset(reference[i].addr);
    set = -1;
    flag = 0;
    /*if any of the valid bits in our block are 1 then set flag to 1*/
    for(j = 0; j < ASSOCIATIVITY; j++){
      if(cache[index][j].validBit && (cache[index][j].tag == tag))
        set = j;
    }
    /***************READ SECTION*************/
    if(reference[i].type == 'R'){
      /*if we have a miss*/
      if(set < 0){
        memRef++;
        misses++;
        /*search for available block*/
        for(k=0; k < ASSOCIATIVITY; k++){
          if(!cache[index][k].validBit){
            spot = k;
            flag = 1;
            break;
          }
        }
        /*if no available block then need to use LRU block*/
        if(!flag){
         spot = getLRU(cache, index);
        }
       cache[index][spot].validBit = 1;
       cache[index][spot].tag = tag;
       cache[index][spot].timestamp = ++time;
       /*if the block being evicted is dirty, update main mem*/
       if(cache[index][spot].dirtyBit)
         memRef++;
      }
      /*we have a hit*/
      else{
        hits++;
        cache[index][set].timestamp = ++time;
      }
      //printf("found: R %d %d %d %d\n", reference[i].addr, tag, index ,offset);
    }

    /*************WRITE SECTION***************/
    else if(reference[i].type == 'W'){
      /*if we have a miss*/
      if(set < 0){
        misses++;
        memRef++;
        /*search for available block*/
        for(k=0; k < ASSOCIATIVITY; k++){
          if(!cache[index][k].validBit){
            spot = k;
            flag = 1;
            break;
          }
        }
        /*if no available block then need to use LRU block*/
        if(!flag){
         spot = getLRU(cache, index);
        }
       cache[index][spot].validBit = 1;
       cache[index][spot].tag = tag;
       cache[index][spot].timestamp = ++time;
       /*if the block being evicted is dirty, update main mem*/
       if(cache[index][spot].dirtyBit)
         memRef++;
       cache[index][spot].dirtyBit = 1;
      }
      /*we have a hit*/
      else{
        hits++;
        /*updating cache*/
        cache[index][set].validBit = 1;
        cache[index][set].dirtyBit = 1;
        cache[index][set].tag = tag;
        cache[index][set].timestamp = ++time;
      }
    }
  }
  printf("Hits: %d\n", hits);
  printf("Misses: %d\n", misses);
  printf("Memory References: %d\n", memRef);



}

/*miscellaneous helper functions*/
unsigned getOffset(unsigned addr){
  unsigned mask;
  mask = (1 << OFFSET_BITS) -1;
  return addr & mask;
}
unsigned getIndex(unsigned addr){
  unsigned mask;
  mask = ((1 << INDEX_BITS) -1) << (OFFSET_BITS);
  return ((addr & mask) >> OFFSET_BITS);
}
unsigned getTag(unsigned addr){
  unsigned mask;
  mask = ((1 << TAG_BITS) -1) << (OFFSET_BITS+INDEX_BITS);
  return ((addr & mask) >> (OFFSET_BITS+INDEX_BITS));
}
int getFlag(char *flag, int argc, char *argv[]){
  int i = 0;
  for(; i < argc; i++){
    if(!strcmp(argv[i],flag))
      return atoi(argv[i + 1]);
  }
}
void printThroughText(int num){
  printf("\n\n****************************************\n");
  printf("Write-through with No Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %d\n", num);
}
void printBackText(int num){
  printf("\n\n****************************************\n");
  printf("Write-back with Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %d\n", num);
}
int getLRU(CacheType ** cacheC, int index){
  int spot = 0;
  int min = cacheC[index][spot].timestamp;
  int i = 0;
  for(;i < ASSOCIATIVITY; i++){
    if(cacheC[index][i].timestamp < min){
      min = cacheC[index][i].timestamp;
      spot = i;
    }
  }
  return spot;

}
