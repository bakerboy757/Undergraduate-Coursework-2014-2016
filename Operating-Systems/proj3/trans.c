#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#define MAXSIZE 100
#define MAXCHARS 4096

typedef struct shmem{
  char buffer[MAXCHARS];
  int length;
}shmem;

int main(int argc, char * argv[]){

  FILE *fin;
  FILE *fout;
  int pipefd[2];//carry data from parent to child
  int cpipefd[2];//carry data from child to parent
  pid_t pid;
  shmem *shared_mem;
  int fd;
  int block_id = 0;
  int temp;
  if(argc != 3){
    printf("Invalid number of arguments %d\n", argc);
    exit(EXIT_FAILURE);
  }
  if(pipe(pipefd) == -1){
    perror("pipefd");
    exit(EXIT_FAILURE);
  }
  if(pipe(cpipefd) == -1){
    perror("cpipefd");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if(pid < 0){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0){
    //child
    if((fout=fopen(argv[2], "w")) == NULL){
      perror("fopen fout");
      exit(EXIT_FAILURE);
    }
    close(cpipefd[0]);//close read end
    close(pipefd[1]);//close unused write end
    fd = shm_open("/myshmem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1){
      perror("shm_open");
      exit(EXIT_FAILURE);
    }
    if(ftruncate(fd, sizeof(shmem)) == -1){
      perror("ftruncate");
      exit(EXIT_FAILURE);
    }
    shared_mem = mmap(NULL, sizeof(shmem),
                 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shared_mem == MAP_FAILED){
      perror("mmap");
      exit(EXIT_FAILURE);
    }
    do{
      read(pipefd[0], &block_id, sizeof(block_id));
      read(pipefd[0], &shared_mem->length, sizeof(shared_mem->length));

      if(block_id < 0){
        perror("child read");
        exit(EXIT_FAILURE);
      }
      else if (block_id == 0){
        //parent is done
        if(write(cpipefd[1], &block_id, sizeof(block_id)) < 0){
          perror("child write 0");
          exit(EXIT_FAILURE);
        }
        fclose(fout);
        close(pipefd[0]);//done reading
        close(cpipefd[1]);
        //printf("ending child...");
        exit(EXIT_SUCCESS); 
      }
      else{
        fwrite(shared_mem->buffer, 1, shared_mem->length, fout);
        //need to now open other pipe for writing
        if(write(cpipefd[1], &block_id, sizeof(block_id)) < 0){
          perror("child write");
          exit(EXIT_FAILURE);
        }
      }
    }while(block_id != 0);
  }
  else{
    //parent
    close(cpipefd[1]);//close write end
    close(pipefd[0]);//closed unused read end

    if((fin=fopen(argv[1], "r")) == NULL){
      perror("fopen fin");
      exit(EXIT_FAILURE);
    }
    fd = shm_open("/myshmem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1){
      perror("shm_open");
      exit(EXIT_FAILURE);
    }
    if(ftruncate(fd, sizeof(shmem)) == -1){
      perror("ftruncate");
      exit(EXIT_FAILURE);
    }
    shared_mem = mmap(NULL, sizeof(shmem),
                 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shared_mem == MAP_FAILED){
      perror("mmap");
      exit(EXIT_FAILURE);
    }
    while(1){
      shared_mem->length = 0;
      shared_mem->length = fread(shared_mem->buffer, 1, MAXCHARS, fin);
      ++block_id;
      if(shared_mem->length == 0)
        block_id = 0;//done reading
      temp = block_id;
      if(write(pipefd[1], &block_id, sizeof(block_id)) < 0){
         perror("parent write block_id");
       	 printf("block_id: %d", block_id);
         exit(EXIT_FAILURE);
      }
      if(write(pipefd[1], &shared_mem->length, sizeof(shared_mem->length)) < 0){  
         perror("parent write length");
         exit(EXIT_FAILURE);
      }
      read(cpipefd[0], &block_id, sizeof(block_id));
      if(block_id != temp){
        perror("block_id from child incorrect");
        exit(EXIT_FAILURE);
      }
      if(block_id == 0){
        //printf("ending parent...");
        close(pipefd[1]);
        close(cpipefd[0]);
        fclose(fin);
        exit(EXIT_SUCCESS);
      }
    }
  }
  return 0;
}
