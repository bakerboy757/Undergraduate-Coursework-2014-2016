#include<stdio.h>
#include <stdlib.h>
#define MAX 5
int main(int argc, char *argv[]){
  FILE *fin, *fout;
  char buffer[MAX];
  int length;
  char c;
  size_t bytesRead;
  if((fin=fopen(argv[1], "r")) == NULL){
      perror("fopen");
      exit(EXIT_FAILURE);
  }
  if((fout=fopen(argv[2], "w")) == NULL){
      perror("fopen");
      exit(EXIT_FAILURE);
  }
  while(1){
    length = 0;
    //while((c = fgetc(fin)) != EOF && length < MAX){
     // buffer[length++] = (char) c;
    //}
    length = fread(buffer, 1, MAX, fin);
    if(length == 0){
      break;
    }
    fwrite(buffer, 1, length, fout);
  }
  fclose(fout);
  fclose(fin);
}
