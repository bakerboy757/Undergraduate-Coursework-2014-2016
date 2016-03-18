#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#define BUFFERSIZE 4096
#define MAXSIZE 100
#define MAXCHARS 512

typedef struct shmem{
  char buffer[BUFFERSIZE];
  //int id;
  int length;
}shmem;

int shmem_id = 0;

int main(int argc, char * argv[]){

  FILE *fin;
  FILE *fout;
  int count = 0;
  int pipefd[2];//carry data from parent to child
  int cpipefd[2];//carry data from child to parent
  pid_t pid;
  shmem *shared_mem;
  int fd;
  char c;
  int block_id = 0;
  int temp;
  int EOF_flag = 0;
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
        //printf("writing %d to parent...\n", block_id);
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
        //printf("child recieved: %d and %d\n", block_id, shared_mem->length);
        //output shared mem to fout
        //printf("%s", shared_mem->buffer);
        fwrite(shared_mem->buffer, 1, shared_mem->length, fout);

        //fprintf(fout, "%s", shared_mem->buffer);
        //need to now open other pipe for writing
        //printf("writing %d to parent...\n", block_id);

        if(write(cpipefd[1], &block_id, sizeof(block_id)) < 0){
          perror("child write");
          exit(EXIT_FAILURE);
        }
        //raise(SIGSTOP);
      }
    }while(block_id != 0);
  }
  else{
    //parent
    //while(!EOF_flag){}
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
      //while((c = fgetc(fin)) != EOF && shared_mem->length < MAXCHARS){
        //shared_mem->buffer[++shared_mem->length] = (char) c;
        //need to make it so we pick up where we left off
      //}
      shared_mem->length = fread(shared_mem->buffer, 1, MAXCHARS, fin);
      //printf("%s", shared_mem->buffer);
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
      //waitpid(pid, NULL, WUNTRACED);
      read(cpipefd[0], &block_id, sizeof(block_id));
//      printf("block_id sent back from child: %d\n", block_id);
      if(block_id != temp){
        perror("block_id from child incorrect");
        exit(EXIT_FAILURE);
      }
      if(block_id == 0){
        printf("ending parent...");
        close(pipefd[1]);
        close(cpipefd[0]);
        fclose(fin);
        exit(EXIT_SUCCESS);
      }
      //kill(pid, SIGCONT);
    }
  }
   //printf("how did i get here?\n");
  
  //TODO: create two procs(parent and child) using fork
  //these two procs will share two pipes
    //one that carries data from parent to child
    //one that carries data from child to parent
  //child and parent will share 4KB of memory
  
  //step by step:
    //parent proc reads a block of 4KB data from input file and places contents into 4KB shared memory
      //last block of the data might be less than 4KB if the file sizeis not a mulitple of 4KB 
    //parent sends block number and and block length to the child through the its established pipe
    
   //child recieves block number and block length from pipe and writes that data from shared memory
   //child then sends the block number back to the parent through the other pipe

   //parent ensures the block number recieved from the child via pipe is correct
   //and then continues the transfer of the next block
   //this LOOPS until all of the input file has been written to the output file
   //parent sends block number 0 and block length 0 to child 
   //when child recieves block number 0 the child sends block number 0 to parent and then exits child
   //when parent recieves block number 0, parent exits

  //use linux pipe() to creaet pipes
  //use shm_open and mmap to acces shared mem 
  //block lengths and number should be sent and recieved as int
  //block number starts at 1  
  //should have error checking for 
  return 0;
}
