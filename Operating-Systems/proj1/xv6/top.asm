
_top:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
#include "spinlock.h"

void sort(struct uproc *, int);
char *getstate(int);
int main()
{
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	53                   	push   %ebx
   4:	83 e4 f0             	and    $0xfffffff0,%esp
   7:	83 ec 40             	sub    $0x40,%esp
    int max = 2, i, proccount;
   a:	c7 44 24 30 02 00 00 	movl   $0x2,0x30(%esp)
  11:	00 
    char state[16];
    struct uproc *table = malloc(max * sizeof(struct uproc));
  12:	8b 44 24 30          	mov    0x30(%esp),%eax
  16:	c1 e0 02             	shl    $0x2,%eax
  19:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
  20:	29 c2                	sub    %eax,%edx
  22:	89 d0                	mov    %edx,%eax
  24:	89 04 24             	mov    %eax,(%esp)
  27:	e8 da 09 00 00       	call   a06 <malloc>
  2c:	89 44 24 34          	mov    %eax,0x34(%esp)
    proccount = getprocs(max, table);
  30:	8b 44 24 34          	mov    0x34(%esp),%eax
  34:	89 44 24 04          	mov    %eax,0x4(%esp)
  38:	8b 44 24 30          	mov    0x30(%esp),%eax
  3c:	89 04 24             	mov    %eax,(%esp)
  3f:	e8 ee 05 00 00       	call   632 <getprocs>
  44:	89 44 24 38          	mov    %eax,0x38(%esp)
    if(proccount < 0){
  48:	83 7c 24 38 00       	cmpl   $0x0,0x38(%esp)
  4d:	79 19                	jns    68 <main+0x68>
       printf(0, "Error");
  4f:	c7 44 24 04 e6 0a 00 	movl   $0xae6,0x4(%esp)
  56:	00 
  57:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
  5e:	e8 b7 06 00 00       	call   71a <printf>
       exit();
  63:	e8 2a 05 00 00       	call   592 <exit>
    }
    //reallocate space for table if there are more processes than we anticipated
    if(proccount > max){
  68:	8b 44 24 38          	mov    0x38(%esp),%eax
  6c:	3b 44 24 30          	cmp    0x30(%esp),%eax
  70:	7e 4a                	jle    bc <main+0xbc>
       free(table);
  72:	8b 44 24 34          	mov    0x34(%esp),%eax
  76:	89 04 24             	mov    %eax,(%esp)
  79:	e8 4f 08 00 00       	call   8cd <free>
       max = proccount;
  7e:	8b 44 24 38          	mov    0x38(%esp),%eax
  82:	89 44 24 30          	mov    %eax,0x30(%esp)
       table = malloc(max * sizeof(struct uproc));
  86:	8b 44 24 30          	mov    0x30(%esp),%eax
  8a:	c1 e0 02             	shl    $0x2,%eax
  8d:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
  94:	29 c2                	sub    %eax,%edx
  96:	89 d0                	mov    %edx,%eax
  98:	89 04 24             	mov    %eax,(%esp)
  9b:	e8 66 09 00 00       	call   a06 <malloc>
  a0:	89 44 24 34          	mov    %eax,0x34(%esp)
       proccount = getprocs(max, table);
  a4:	8b 44 24 34          	mov    0x34(%esp),%eax
  a8:	89 44 24 04          	mov    %eax,0x4(%esp)
  ac:	8b 44 24 30          	mov    0x30(%esp),%eax
  b0:	89 04 24             	mov    %eax,(%esp)
  b3:	e8 7a 05 00 00       	call   632 <getprocs>
  b8:	89 44 24 38          	mov    %eax,0x38(%esp)
    }
    //sort uprocs by size
    //sort(table, proccount);
    for(i = 0; i < proccount; i++){
  bc:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%esp)
  c3:	00 
  c4:	e9 a8 00 00 00       	jmp    171 <main+0x171>
       //gets enum type and translates to char
       strcpy(state, getstate(table[i].state));
  c9:	8b 44 24 3c          	mov    0x3c(%esp),%eax
  cd:	c1 e0 02             	shl    $0x2,%eax
  d0:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
  d7:	29 c2                	sub    %eax,%edx
  d9:	8b 44 24 34          	mov    0x34(%esp),%eax
  dd:	01 d0                	add    %edx,%eax
  df:	8b 40 04             	mov    0x4(%eax),%eax
  e2:	89 04 24             	mov    %eax,(%esp)
  e5:	e8 9a 00 00 00       	call   184 <getstate>
  ea:	89 44 24 04          	mov    %eax,0x4(%esp)
  ee:	8d 44 24 20          	lea    0x20(%esp),%eax
  f2:	89 04 24             	mov    %eax,(%esp)
  f5:	e8 55 02 00 00       	call   34f <strcpy>
       printf(0, "%d  %s  %d  %s\n", table[i].pid, state, table[i].sz, table[i].name);
  fa:	8b 44 24 3c          	mov    0x3c(%esp),%eax
  fe:	c1 e0 02             	shl    $0x2,%eax
 101:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 108:	29 c2                	sub    %eax,%edx
 10a:	8b 44 24 34          	mov    0x34(%esp),%eax
 10e:	01 d0                	add    %edx,%eax
 110:	8d 48 0c             	lea    0xc(%eax),%ecx
 113:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 117:	c1 e0 02             	shl    $0x2,%eax
 11a:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 121:	29 c2                	sub    %eax,%edx
 123:	8b 44 24 34          	mov    0x34(%esp),%eax
 127:	01 d0                	add    %edx,%eax
 129:	8b 50 08             	mov    0x8(%eax),%edx
 12c:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 130:	c1 e0 02             	shl    $0x2,%eax
 133:	8d 1c c5 00 00 00 00 	lea    0x0(,%eax,8),%ebx
 13a:	29 c3                	sub    %eax,%ebx
 13c:	8b 44 24 34          	mov    0x34(%esp),%eax
 140:	01 d8                	add    %ebx,%eax
 142:	8b 00                	mov    (%eax),%eax
 144:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 148:	89 54 24 10          	mov    %edx,0x10(%esp)
 14c:	8d 54 24 20          	lea    0x20(%esp),%edx
 150:	89 54 24 0c          	mov    %edx,0xc(%esp)
 154:	89 44 24 08          	mov    %eax,0x8(%esp)
 158:	c7 44 24 04 ec 0a 00 	movl   $0xaec,0x4(%esp)
 15f:	00 
 160:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 167:	e8 ae 05 00 00       	call   71a <printf>
       table = malloc(max * sizeof(struct uproc));
       proccount = getprocs(max, table);
    }
    //sort uprocs by size
    //sort(table, proccount);
    for(i = 0; i < proccount; i++){
 16c:	83 44 24 3c 01       	addl   $0x1,0x3c(%esp)
 171:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 175:	3b 44 24 38          	cmp    0x38(%esp),%eax
 179:	0f 8c 4a ff ff ff    	jl     c9 <main+0xc9>
       //gets enum type and translates to char
       strcpy(state, getstate(table[i].state));
       printf(0, "%d  %s  %d  %s\n", table[i].pid, state, table[i].sz, table[i].name);
    }
   exit();
 17f:	e8 0e 04 00 00       	call   592 <exit>

00000184 <getstate>:
}
char *getstate(int num){
 184:	55                   	push   %ebp
 185:	89 e5                	mov    %esp,%ebp
   if(num == 0)
 187:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
 18b:	75 07                	jne    194 <getstate+0x10>
      return "UNUSED";
 18d:	b8 fc 0a 00 00       	mov    $0xafc,%eax
 192:	eb 46                	jmp    1da <getstate+0x56>
   if(num == 1)
 194:	83 7d 08 01          	cmpl   $0x1,0x8(%ebp)
 198:	75 07                	jne    1a1 <getstate+0x1d>
      return "EMBRYO";
 19a:	b8 03 0b 00 00       	mov    $0xb03,%eax
 19f:	eb 39                	jmp    1da <getstate+0x56>
   if(num == 2)
 1a1:	83 7d 08 02          	cmpl   $0x2,0x8(%ebp)
 1a5:	75 07                	jne    1ae <getstate+0x2a>
      return "SLEEPING";
 1a7:	b8 0a 0b 00 00       	mov    $0xb0a,%eax
 1ac:	eb 2c                	jmp    1da <getstate+0x56>
   if(num == 3)
 1ae:	83 7d 08 03          	cmpl   $0x3,0x8(%ebp)
 1b2:	75 07                	jne    1bb <getstate+0x37>
      return "RUNNABLE";
 1b4:	b8 13 0b 00 00       	mov    $0xb13,%eax
 1b9:	eb 1f                	jmp    1da <getstate+0x56>
   if(num == 4)
 1bb:	83 7d 08 04          	cmpl   $0x4,0x8(%ebp)
 1bf:	75 07                	jne    1c8 <getstate+0x44>
      return "RUNNING";
 1c1:	b8 1c 0b 00 00       	mov    $0xb1c,%eax
 1c6:	eb 12                	jmp    1da <getstate+0x56>
   if(num == 5)
 1c8:	83 7d 08 05          	cmpl   $0x5,0x8(%ebp)
 1cc:	75 07                	jne    1d5 <getstate+0x51>
      return "ZOMBIE";
 1ce:	b8 24 0b 00 00       	mov    $0xb24,%eax
 1d3:	eb 05                	jmp    1da <getstate+0x56>

   return "INVALID";
 1d5:	b8 2b 0b 00 00       	mov    $0xb2b,%eax
}
 1da:	5d                   	pop    %ebp
 1db:	c3                   	ret    

000001dc <sort>:
void sort(struct uproc *table, int max){
 1dc:	55                   	push   %ebp
 1dd:	89 e5                	mov    %esp,%ebp
 1df:	83 ec 30             	sub    $0x30,%esp
   int i, j;
   struct uproc temp;
   for(i = 0; i < max; i++){
 1e2:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 1e9:	e9 2e 01 00 00       	jmp    31c <sort+0x140>
      for(j = i+1; j < max; j++){
 1ee:	8b 45 fc             	mov    -0x4(%ebp),%eax
 1f1:	83 c0 01             	add    $0x1,%eax
 1f4:	89 45 f8             	mov    %eax,-0x8(%ebp)
 1f7:	e9 10 01 00 00       	jmp    30c <sort+0x130>
         if(table[i].sz < table[j].sz){
 1fc:	8b 45 fc             	mov    -0x4(%ebp),%eax
 1ff:	c1 e0 02             	shl    $0x2,%eax
 202:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 209:	29 c2                	sub    %eax,%edx
 20b:	8b 45 08             	mov    0x8(%ebp),%eax
 20e:	01 d0                	add    %edx,%eax
 210:	8b 50 08             	mov    0x8(%eax),%edx
 213:	8b 45 f8             	mov    -0x8(%ebp),%eax
 216:	c1 e0 02             	shl    $0x2,%eax
 219:	8d 0c c5 00 00 00 00 	lea    0x0(,%eax,8),%ecx
 220:	29 c1                	sub    %eax,%ecx
 222:	8b 45 08             	mov    0x8(%ebp),%eax
 225:	01 c8                	add    %ecx,%eax
 227:	8b 40 08             	mov    0x8(%eax),%eax
 22a:	39 c2                	cmp    %eax,%edx
 22c:	0f 83 ca 00 00 00    	jae    2fc <sort+0x120>
            temp = table[i];
 232:	8b 45 fc             	mov    -0x4(%ebp),%eax
 235:	c1 e0 02             	shl    $0x2,%eax
 238:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 23f:	29 c2                	sub    %eax,%edx
 241:	8b 45 08             	mov    0x8(%ebp),%eax
 244:	01 d0                	add    %edx,%eax
 246:	8b 10                	mov    (%eax),%edx
 248:	89 55 dc             	mov    %edx,-0x24(%ebp)
 24b:	8b 50 04             	mov    0x4(%eax),%edx
 24e:	89 55 e0             	mov    %edx,-0x20(%ebp)
 251:	8b 50 08             	mov    0x8(%eax),%edx
 254:	89 55 e4             	mov    %edx,-0x1c(%ebp)
 257:	8b 50 0c             	mov    0xc(%eax),%edx
 25a:	89 55 e8             	mov    %edx,-0x18(%ebp)
 25d:	8b 50 10             	mov    0x10(%eax),%edx
 260:	89 55 ec             	mov    %edx,-0x14(%ebp)
 263:	8b 50 14             	mov    0x14(%eax),%edx
 266:	89 55 f0             	mov    %edx,-0x10(%ebp)
 269:	8b 40 18             	mov    0x18(%eax),%eax
 26c:	89 45 f4             	mov    %eax,-0xc(%ebp)
            table[i] = table[j];
 26f:	8b 45 fc             	mov    -0x4(%ebp),%eax
 272:	c1 e0 02             	shl    $0x2,%eax
 275:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 27c:	29 c2                	sub    %eax,%edx
 27e:	8b 45 08             	mov    0x8(%ebp),%eax
 281:	01 d0                	add    %edx,%eax
 283:	8b 55 f8             	mov    -0x8(%ebp),%edx
 286:	c1 e2 02             	shl    $0x2,%edx
 289:	8d 0c d5 00 00 00 00 	lea    0x0(,%edx,8),%ecx
 290:	29 d1                	sub    %edx,%ecx
 292:	8b 55 08             	mov    0x8(%ebp),%edx
 295:	01 ca                	add    %ecx,%edx
 297:	8b 0a                	mov    (%edx),%ecx
 299:	89 08                	mov    %ecx,(%eax)
 29b:	8b 4a 04             	mov    0x4(%edx),%ecx
 29e:	89 48 04             	mov    %ecx,0x4(%eax)
 2a1:	8b 4a 08             	mov    0x8(%edx),%ecx
 2a4:	89 48 08             	mov    %ecx,0x8(%eax)
 2a7:	8b 4a 0c             	mov    0xc(%edx),%ecx
 2aa:	89 48 0c             	mov    %ecx,0xc(%eax)
 2ad:	8b 4a 10             	mov    0x10(%edx),%ecx
 2b0:	89 48 10             	mov    %ecx,0x10(%eax)
 2b3:	8b 4a 14             	mov    0x14(%edx),%ecx
 2b6:	89 48 14             	mov    %ecx,0x14(%eax)
 2b9:	8b 52 18             	mov    0x18(%edx),%edx
 2bc:	89 50 18             	mov    %edx,0x18(%eax)
            table[j] = temp;
 2bf:	8b 45 f8             	mov    -0x8(%ebp),%eax
 2c2:	c1 e0 02             	shl    $0x2,%eax
 2c5:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 2cc:	29 c2                	sub    %eax,%edx
 2ce:	8b 45 08             	mov    0x8(%ebp),%eax
 2d1:	01 d0                	add    %edx,%eax
 2d3:	8b 55 dc             	mov    -0x24(%ebp),%edx
 2d6:	89 10                	mov    %edx,(%eax)
 2d8:	8b 55 e0             	mov    -0x20(%ebp),%edx
 2db:	89 50 04             	mov    %edx,0x4(%eax)
 2de:	8b 55 e4             	mov    -0x1c(%ebp),%edx
 2e1:	89 50 08             	mov    %edx,0x8(%eax)
 2e4:	8b 55 e8             	mov    -0x18(%ebp),%edx
 2e7:	89 50 0c             	mov    %edx,0xc(%eax)
 2ea:	8b 55 ec             	mov    -0x14(%ebp),%edx
 2ed:	89 50 10             	mov    %edx,0x10(%eax)
 2f0:	8b 55 f0             	mov    -0x10(%ebp),%edx
 2f3:	89 50 14             	mov    %edx,0x14(%eax)
 2f6:	8b 55 f4             	mov    -0xc(%ebp),%edx
 2f9:	89 50 18             	mov    %edx,0x18(%eax)
         }
         if(table[i].sz == table[j].sz){
 2fc:	8b 45 fc             	mov    -0x4(%ebp),%eax
 2ff:	c1 e0 02             	shl    $0x2,%eax
 302:	8b 45 f8             	mov    -0x8(%ebp),%eax
 305:	c1 e0 02             	shl    $0x2,%eax
}
void sort(struct uproc *table, int max){
   int i, j;
   struct uproc temp;
   for(i = 0; i < max; i++){
      for(j = i+1; j < max; j++){
 308:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
 30c:	8b 45 f8             	mov    -0x8(%ebp),%eax
 30f:	3b 45 0c             	cmp    0xc(%ebp),%eax
 312:	0f 8c e4 fe ff ff    	jl     1fc <sort+0x20>
   return "INVALID";
}
void sort(struct uproc *table, int max){
   int i, j;
   struct uproc temp;
   for(i = 0; i < max; i++){
 318:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 31c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 31f:	3b 45 0c             	cmp    0xc(%ebp),%eax
 322:	0f 8c c6 fe ff ff    	jl     1ee <sort+0x12>
            

         }
      }
   }
}
 328:	c9                   	leave  
 329:	c3                   	ret    

0000032a <stosb>:
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
 32a:	55                   	push   %ebp
 32b:	89 e5                	mov    %esp,%ebp
 32d:	57                   	push   %edi
 32e:	53                   	push   %ebx
  asm volatile("cld; rep stosb" :
 32f:	8b 4d 08             	mov    0x8(%ebp),%ecx
 332:	8b 55 10             	mov    0x10(%ebp),%edx
 335:	8b 45 0c             	mov    0xc(%ebp),%eax
 338:	89 cb                	mov    %ecx,%ebx
 33a:	89 df                	mov    %ebx,%edi
 33c:	89 d1                	mov    %edx,%ecx
 33e:	fc                   	cld    
 33f:	f3 aa                	rep stos %al,%es:(%edi)
 341:	89 ca                	mov    %ecx,%edx
 343:	89 fb                	mov    %edi,%ebx
 345:	89 5d 08             	mov    %ebx,0x8(%ebp)
 348:	89 55 10             	mov    %edx,0x10(%ebp)
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}
 34b:	5b                   	pop    %ebx
 34c:	5f                   	pop    %edi
 34d:	5d                   	pop    %ebp
 34e:	c3                   	ret    

0000034f <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, char *t)
{
 34f:	55                   	push   %ebp
 350:	89 e5                	mov    %esp,%ebp
 352:	83 ec 10             	sub    $0x10,%esp
  char *os;

  os = s;
 355:	8b 45 08             	mov    0x8(%ebp),%eax
 358:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while((*s++ = *t++) != 0)
 35b:	90                   	nop
 35c:	8b 45 08             	mov    0x8(%ebp),%eax
 35f:	8d 50 01             	lea    0x1(%eax),%edx
 362:	89 55 08             	mov    %edx,0x8(%ebp)
 365:	8b 55 0c             	mov    0xc(%ebp),%edx
 368:	8d 4a 01             	lea    0x1(%edx),%ecx
 36b:	89 4d 0c             	mov    %ecx,0xc(%ebp)
 36e:	0f b6 12             	movzbl (%edx),%edx
 371:	88 10                	mov    %dl,(%eax)
 373:	0f b6 00             	movzbl (%eax),%eax
 376:	84 c0                	test   %al,%al
 378:	75 e2                	jne    35c <strcpy+0xd>
    ;
  return os;
 37a:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 37d:	c9                   	leave  
 37e:	c3                   	ret    

0000037f <strcmp>:

int
strcmp(const char *p, const char *q)
{
 37f:	55                   	push   %ebp
 380:	89 e5                	mov    %esp,%ebp
  while(*p && *p == *q)
 382:	eb 08                	jmp    38c <strcmp+0xd>
    p++, q++;
 384:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 388:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
 38c:	8b 45 08             	mov    0x8(%ebp),%eax
 38f:	0f b6 00             	movzbl (%eax),%eax
 392:	84 c0                	test   %al,%al
 394:	74 10                	je     3a6 <strcmp+0x27>
 396:	8b 45 08             	mov    0x8(%ebp),%eax
 399:	0f b6 10             	movzbl (%eax),%edx
 39c:	8b 45 0c             	mov    0xc(%ebp),%eax
 39f:	0f b6 00             	movzbl (%eax),%eax
 3a2:	38 c2                	cmp    %al,%dl
 3a4:	74 de                	je     384 <strcmp+0x5>
    p++, q++;
  return (uchar)*p - (uchar)*q;
 3a6:	8b 45 08             	mov    0x8(%ebp),%eax
 3a9:	0f b6 00             	movzbl (%eax),%eax
 3ac:	0f b6 d0             	movzbl %al,%edx
 3af:	8b 45 0c             	mov    0xc(%ebp),%eax
 3b2:	0f b6 00             	movzbl (%eax),%eax
 3b5:	0f b6 c0             	movzbl %al,%eax
 3b8:	29 c2                	sub    %eax,%edx
 3ba:	89 d0                	mov    %edx,%eax
}
 3bc:	5d                   	pop    %ebp
 3bd:	c3                   	ret    

000003be <strlen>:

uint
strlen(char *s)
{
 3be:	55                   	push   %ebp
 3bf:	89 e5                	mov    %esp,%ebp
 3c1:	83 ec 10             	sub    $0x10,%esp
  int n;

  for(n = 0; s[n]; n++)
 3c4:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 3cb:	eb 04                	jmp    3d1 <strlen+0x13>
 3cd:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 3d1:	8b 55 fc             	mov    -0x4(%ebp),%edx
 3d4:	8b 45 08             	mov    0x8(%ebp),%eax
 3d7:	01 d0                	add    %edx,%eax
 3d9:	0f b6 00             	movzbl (%eax),%eax
 3dc:	84 c0                	test   %al,%al
 3de:	75 ed                	jne    3cd <strlen+0xf>
    ;
  return n;
 3e0:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 3e3:	c9                   	leave  
 3e4:	c3                   	ret    

000003e5 <memset>:

void*
memset(void *dst, int c, uint n)
{
 3e5:	55                   	push   %ebp
 3e6:	89 e5                	mov    %esp,%ebp
 3e8:	83 ec 0c             	sub    $0xc,%esp
  stosb(dst, c, n);
 3eb:	8b 45 10             	mov    0x10(%ebp),%eax
 3ee:	89 44 24 08          	mov    %eax,0x8(%esp)
 3f2:	8b 45 0c             	mov    0xc(%ebp),%eax
 3f5:	89 44 24 04          	mov    %eax,0x4(%esp)
 3f9:	8b 45 08             	mov    0x8(%ebp),%eax
 3fc:	89 04 24             	mov    %eax,(%esp)
 3ff:	e8 26 ff ff ff       	call   32a <stosb>
  return dst;
 404:	8b 45 08             	mov    0x8(%ebp),%eax
}
 407:	c9                   	leave  
 408:	c3                   	ret    

00000409 <strchr>:

char*
strchr(const char *s, char c)
{
 409:	55                   	push   %ebp
 40a:	89 e5                	mov    %esp,%ebp
 40c:	83 ec 04             	sub    $0x4,%esp
 40f:	8b 45 0c             	mov    0xc(%ebp),%eax
 412:	88 45 fc             	mov    %al,-0x4(%ebp)
  for(; *s; s++)
 415:	eb 14                	jmp    42b <strchr+0x22>
    if(*s == c)
 417:	8b 45 08             	mov    0x8(%ebp),%eax
 41a:	0f b6 00             	movzbl (%eax),%eax
 41d:	3a 45 fc             	cmp    -0x4(%ebp),%al
 420:	75 05                	jne    427 <strchr+0x1e>
      return (char*)s;
 422:	8b 45 08             	mov    0x8(%ebp),%eax
 425:	eb 13                	jmp    43a <strchr+0x31>
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
 427:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 42b:	8b 45 08             	mov    0x8(%ebp),%eax
 42e:	0f b6 00             	movzbl (%eax),%eax
 431:	84 c0                	test   %al,%al
 433:	75 e2                	jne    417 <strchr+0xe>
    if(*s == c)
      return (char*)s;
  return 0;
 435:	b8 00 00 00 00       	mov    $0x0,%eax
}
 43a:	c9                   	leave  
 43b:	c3                   	ret    

0000043c <gets>:

char*
gets(char *buf, int max)
{
 43c:	55                   	push   %ebp
 43d:	89 e5                	mov    %esp,%ebp
 43f:	83 ec 28             	sub    $0x28,%esp
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 442:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 449:	eb 4c                	jmp    497 <gets+0x5b>
    cc = read(0, &c, 1);
 44b:	c7 44 24 08 01 00 00 	movl   $0x1,0x8(%esp)
 452:	00 
 453:	8d 45 ef             	lea    -0x11(%ebp),%eax
 456:	89 44 24 04          	mov    %eax,0x4(%esp)
 45a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 461:	e8 44 01 00 00       	call   5aa <read>
 466:	89 45 f0             	mov    %eax,-0x10(%ebp)
    if(cc < 1)
 469:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 46d:	7f 02                	jg     471 <gets+0x35>
      break;
 46f:	eb 31                	jmp    4a2 <gets+0x66>
    buf[i++] = c;
 471:	8b 45 f4             	mov    -0xc(%ebp),%eax
 474:	8d 50 01             	lea    0x1(%eax),%edx
 477:	89 55 f4             	mov    %edx,-0xc(%ebp)
 47a:	89 c2                	mov    %eax,%edx
 47c:	8b 45 08             	mov    0x8(%ebp),%eax
 47f:	01 c2                	add    %eax,%edx
 481:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 485:	88 02                	mov    %al,(%edx)
    if(c == '\n' || c == '\r')
 487:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 48b:	3c 0a                	cmp    $0xa,%al
 48d:	74 13                	je     4a2 <gets+0x66>
 48f:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 493:	3c 0d                	cmp    $0xd,%al
 495:	74 0b                	je     4a2 <gets+0x66>
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 497:	8b 45 f4             	mov    -0xc(%ebp),%eax
 49a:	83 c0 01             	add    $0x1,%eax
 49d:	3b 45 0c             	cmp    0xc(%ebp),%eax
 4a0:	7c a9                	jl     44b <gets+0xf>
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
 4a2:	8b 55 f4             	mov    -0xc(%ebp),%edx
 4a5:	8b 45 08             	mov    0x8(%ebp),%eax
 4a8:	01 d0                	add    %edx,%eax
 4aa:	c6 00 00             	movb   $0x0,(%eax)
  return buf;
 4ad:	8b 45 08             	mov    0x8(%ebp),%eax
}
 4b0:	c9                   	leave  
 4b1:	c3                   	ret    

000004b2 <stat>:

int
stat(char *n, struct stat *st)
{
 4b2:	55                   	push   %ebp
 4b3:	89 e5                	mov    %esp,%ebp
 4b5:	83 ec 28             	sub    $0x28,%esp
  int fd;
  int r;

  fd = open(n, O_RDONLY);
 4b8:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 4bf:	00 
 4c0:	8b 45 08             	mov    0x8(%ebp),%eax
 4c3:	89 04 24             	mov    %eax,(%esp)
 4c6:	e8 07 01 00 00       	call   5d2 <open>
 4cb:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(fd < 0)
 4ce:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 4d2:	79 07                	jns    4db <stat+0x29>
    return -1;
 4d4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 4d9:	eb 23                	jmp    4fe <stat+0x4c>
  r = fstat(fd, st);
 4db:	8b 45 0c             	mov    0xc(%ebp),%eax
 4de:	89 44 24 04          	mov    %eax,0x4(%esp)
 4e2:	8b 45 f4             	mov    -0xc(%ebp),%eax
 4e5:	89 04 24             	mov    %eax,(%esp)
 4e8:	e8 fd 00 00 00       	call   5ea <fstat>
 4ed:	89 45 f0             	mov    %eax,-0x10(%ebp)
  close(fd);
 4f0:	8b 45 f4             	mov    -0xc(%ebp),%eax
 4f3:	89 04 24             	mov    %eax,(%esp)
 4f6:	e8 bf 00 00 00       	call   5ba <close>
  return r;
 4fb:	8b 45 f0             	mov    -0x10(%ebp),%eax
}
 4fe:	c9                   	leave  
 4ff:	c3                   	ret    

00000500 <atoi>:

int
atoi(const char *s)
{
 500:	55                   	push   %ebp
 501:	89 e5                	mov    %esp,%ebp
 503:	83 ec 10             	sub    $0x10,%esp
  int n;

  n = 0;
 506:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 50d:	eb 25                	jmp    534 <atoi+0x34>
    n = n*10 + *s++ - '0';
 50f:	8b 55 fc             	mov    -0x4(%ebp),%edx
 512:	89 d0                	mov    %edx,%eax
 514:	c1 e0 02             	shl    $0x2,%eax
 517:	01 d0                	add    %edx,%eax
 519:	01 c0                	add    %eax,%eax
 51b:	89 c1                	mov    %eax,%ecx
 51d:	8b 45 08             	mov    0x8(%ebp),%eax
 520:	8d 50 01             	lea    0x1(%eax),%edx
 523:	89 55 08             	mov    %edx,0x8(%ebp)
 526:	0f b6 00             	movzbl (%eax),%eax
 529:	0f be c0             	movsbl %al,%eax
 52c:	01 c8                	add    %ecx,%eax
 52e:	83 e8 30             	sub    $0x30,%eax
 531:	89 45 fc             	mov    %eax,-0x4(%ebp)
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
 534:	8b 45 08             	mov    0x8(%ebp),%eax
 537:	0f b6 00             	movzbl (%eax),%eax
 53a:	3c 2f                	cmp    $0x2f,%al
 53c:	7e 0a                	jle    548 <atoi+0x48>
 53e:	8b 45 08             	mov    0x8(%ebp),%eax
 541:	0f b6 00             	movzbl (%eax),%eax
 544:	3c 39                	cmp    $0x39,%al
 546:	7e c7                	jle    50f <atoi+0xf>
    n = n*10 + *s++ - '0';
  return n;
 548:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 54b:	c9                   	leave  
 54c:	c3                   	ret    

0000054d <memmove>:

void*
memmove(void *vdst, void *vsrc, int n)
{
 54d:	55                   	push   %ebp
 54e:	89 e5                	mov    %esp,%ebp
 550:	83 ec 10             	sub    $0x10,%esp
  char *dst, *src;
  
  dst = vdst;
 553:	8b 45 08             	mov    0x8(%ebp),%eax
 556:	89 45 fc             	mov    %eax,-0x4(%ebp)
  src = vsrc;
 559:	8b 45 0c             	mov    0xc(%ebp),%eax
 55c:	89 45 f8             	mov    %eax,-0x8(%ebp)
  while(n-- > 0)
 55f:	eb 17                	jmp    578 <memmove+0x2b>
    *dst++ = *src++;
 561:	8b 45 fc             	mov    -0x4(%ebp),%eax
 564:	8d 50 01             	lea    0x1(%eax),%edx
 567:	89 55 fc             	mov    %edx,-0x4(%ebp)
 56a:	8b 55 f8             	mov    -0x8(%ebp),%edx
 56d:	8d 4a 01             	lea    0x1(%edx),%ecx
 570:	89 4d f8             	mov    %ecx,-0x8(%ebp)
 573:	0f b6 12             	movzbl (%edx),%edx
 576:	88 10                	mov    %dl,(%eax)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
 578:	8b 45 10             	mov    0x10(%ebp),%eax
 57b:	8d 50 ff             	lea    -0x1(%eax),%edx
 57e:	89 55 10             	mov    %edx,0x10(%ebp)
 581:	85 c0                	test   %eax,%eax
 583:	7f dc                	jg     561 <memmove+0x14>
    *dst++ = *src++;
  return vdst;
 585:	8b 45 08             	mov    0x8(%ebp),%eax
}
 588:	c9                   	leave  
 589:	c3                   	ret    

0000058a <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
 58a:	b8 01 00 00 00       	mov    $0x1,%eax
 58f:	cd 40                	int    $0x40
 591:	c3                   	ret    

00000592 <exit>:
SYSCALL(exit)
 592:	b8 02 00 00 00       	mov    $0x2,%eax
 597:	cd 40                	int    $0x40
 599:	c3                   	ret    

0000059a <wait>:
SYSCALL(wait)
 59a:	b8 03 00 00 00       	mov    $0x3,%eax
 59f:	cd 40                	int    $0x40
 5a1:	c3                   	ret    

000005a2 <pipe>:
SYSCALL(pipe)
 5a2:	b8 04 00 00 00       	mov    $0x4,%eax
 5a7:	cd 40                	int    $0x40
 5a9:	c3                   	ret    

000005aa <read>:
SYSCALL(read)
 5aa:	b8 05 00 00 00       	mov    $0x5,%eax
 5af:	cd 40                	int    $0x40
 5b1:	c3                   	ret    

000005b2 <write>:
SYSCALL(write)
 5b2:	b8 10 00 00 00       	mov    $0x10,%eax
 5b7:	cd 40                	int    $0x40
 5b9:	c3                   	ret    

000005ba <close>:
SYSCALL(close)
 5ba:	b8 15 00 00 00       	mov    $0x15,%eax
 5bf:	cd 40                	int    $0x40
 5c1:	c3                   	ret    

000005c2 <kill>:
SYSCALL(kill)
 5c2:	b8 06 00 00 00       	mov    $0x6,%eax
 5c7:	cd 40                	int    $0x40
 5c9:	c3                   	ret    

000005ca <exec>:
SYSCALL(exec)
 5ca:	b8 07 00 00 00       	mov    $0x7,%eax
 5cf:	cd 40                	int    $0x40
 5d1:	c3                   	ret    

000005d2 <open>:
SYSCALL(open)
 5d2:	b8 0f 00 00 00       	mov    $0xf,%eax
 5d7:	cd 40                	int    $0x40
 5d9:	c3                   	ret    

000005da <mknod>:
SYSCALL(mknod)
 5da:	b8 11 00 00 00       	mov    $0x11,%eax
 5df:	cd 40                	int    $0x40
 5e1:	c3                   	ret    

000005e2 <unlink>:
SYSCALL(unlink)
 5e2:	b8 12 00 00 00       	mov    $0x12,%eax
 5e7:	cd 40                	int    $0x40
 5e9:	c3                   	ret    

000005ea <fstat>:
SYSCALL(fstat)
 5ea:	b8 08 00 00 00       	mov    $0x8,%eax
 5ef:	cd 40                	int    $0x40
 5f1:	c3                   	ret    

000005f2 <link>:
SYSCALL(link)
 5f2:	b8 13 00 00 00       	mov    $0x13,%eax
 5f7:	cd 40                	int    $0x40
 5f9:	c3                   	ret    

000005fa <mkdir>:
SYSCALL(mkdir)
 5fa:	b8 14 00 00 00       	mov    $0x14,%eax
 5ff:	cd 40                	int    $0x40
 601:	c3                   	ret    

00000602 <chdir>:
SYSCALL(chdir)
 602:	b8 09 00 00 00       	mov    $0x9,%eax
 607:	cd 40                	int    $0x40
 609:	c3                   	ret    

0000060a <dup>:
SYSCALL(dup)
 60a:	b8 0a 00 00 00       	mov    $0xa,%eax
 60f:	cd 40                	int    $0x40
 611:	c3                   	ret    

00000612 <getpid>:
SYSCALL(getpid)
 612:	b8 0b 00 00 00       	mov    $0xb,%eax
 617:	cd 40                	int    $0x40
 619:	c3                   	ret    

0000061a <sbrk>:
SYSCALL(sbrk)
 61a:	b8 0c 00 00 00       	mov    $0xc,%eax
 61f:	cd 40                	int    $0x40
 621:	c3                   	ret    

00000622 <sleep>:
SYSCALL(sleep)
 622:	b8 0d 00 00 00       	mov    $0xd,%eax
 627:	cd 40                	int    $0x40
 629:	c3                   	ret    

0000062a <uptime>:
SYSCALL(uptime)
 62a:	b8 0e 00 00 00       	mov    $0xe,%eax
 62f:	cd 40                	int    $0x40
 631:	c3                   	ret    

00000632 <getprocs>:
SYSCALL(getprocs)
 632:	b8 16 00 00 00       	mov    $0x16,%eax
 637:	cd 40                	int    $0x40
 639:	c3                   	ret    

0000063a <putc>:
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
 63a:	55                   	push   %ebp
 63b:	89 e5                	mov    %esp,%ebp
 63d:	83 ec 18             	sub    $0x18,%esp
 640:	8b 45 0c             	mov    0xc(%ebp),%eax
 643:	88 45 f4             	mov    %al,-0xc(%ebp)
  write(fd, &c, 1);
 646:	c7 44 24 08 01 00 00 	movl   $0x1,0x8(%esp)
 64d:	00 
 64e:	8d 45 f4             	lea    -0xc(%ebp),%eax
 651:	89 44 24 04          	mov    %eax,0x4(%esp)
 655:	8b 45 08             	mov    0x8(%ebp),%eax
 658:	89 04 24             	mov    %eax,(%esp)
 65b:	e8 52 ff ff ff       	call   5b2 <write>
}
 660:	c9                   	leave  
 661:	c3                   	ret    

00000662 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
 662:	55                   	push   %ebp
 663:	89 e5                	mov    %esp,%ebp
 665:	56                   	push   %esi
 666:	53                   	push   %ebx
 667:	83 ec 30             	sub    $0x30,%esp
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
 66a:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  if(sgn && xx < 0){
 671:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
 675:	74 17                	je     68e <printint+0x2c>
 677:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
 67b:	79 11                	jns    68e <printint+0x2c>
    neg = 1;
 67d:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
    x = -xx;
 684:	8b 45 0c             	mov    0xc(%ebp),%eax
 687:	f7 d8                	neg    %eax
 689:	89 45 ec             	mov    %eax,-0x14(%ebp)
 68c:	eb 06                	jmp    694 <printint+0x32>
  } else {
    x = xx;
 68e:	8b 45 0c             	mov    0xc(%ebp),%eax
 691:	89 45 ec             	mov    %eax,-0x14(%ebp)
  }

  i = 0;
 694:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  do{
    buf[i++] = digits[x % base];
 69b:	8b 4d f4             	mov    -0xc(%ebp),%ecx
 69e:	8d 41 01             	lea    0x1(%ecx),%eax
 6a1:	89 45 f4             	mov    %eax,-0xc(%ebp)
 6a4:	8b 5d 10             	mov    0x10(%ebp),%ebx
 6a7:	8b 45 ec             	mov    -0x14(%ebp),%eax
 6aa:	ba 00 00 00 00       	mov    $0x0,%edx
 6af:	f7 f3                	div    %ebx
 6b1:	89 d0                	mov    %edx,%eax
 6b3:	0f b6 80 c0 0d 00 00 	movzbl 0xdc0(%eax),%eax
 6ba:	88 44 0d dc          	mov    %al,-0x24(%ebp,%ecx,1)
  }while((x /= base) != 0);
 6be:	8b 75 10             	mov    0x10(%ebp),%esi
 6c1:	8b 45 ec             	mov    -0x14(%ebp),%eax
 6c4:	ba 00 00 00 00       	mov    $0x0,%edx
 6c9:	f7 f6                	div    %esi
 6cb:	89 45 ec             	mov    %eax,-0x14(%ebp)
 6ce:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 6d2:	75 c7                	jne    69b <printint+0x39>
  if(neg)
 6d4:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 6d8:	74 10                	je     6ea <printint+0x88>
    buf[i++] = '-';
 6da:	8b 45 f4             	mov    -0xc(%ebp),%eax
 6dd:	8d 50 01             	lea    0x1(%eax),%edx
 6e0:	89 55 f4             	mov    %edx,-0xc(%ebp)
 6e3:	c6 44 05 dc 2d       	movb   $0x2d,-0x24(%ebp,%eax,1)

  while(--i >= 0)
 6e8:	eb 1f                	jmp    709 <printint+0xa7>
 6ea:	eb 1d                	jmp    709 <printint+0xa7>
    putc(fd, buf[i]);
 6ec:	8d 55 dc             	lea    -0x24(%ebp),%edx
 6ef:	8b 45 f4             	mov    -0xc(%ebp),%eax
 6f2:	01 d0                	add    %edx,%eax
 6f4:	0f b6 00             	movzbl (%eax),%eax
 6f7:	0f be c0             	movsbl %al,%eax
 6fa:	89 44 24 04          	mov    %eax,0x4(%esp)
 6fe:	8b 45 08             	mov    0x8(%ebp),%eax
 701:	89 04 24             	mov    %eax,(%esp)
 704:	e8 31 ff ff ff       	call   63a <putc>
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
 709:	83 6d f4 01          	subl   $0x1,-0xc(%ebp)
 70d:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 711:	79 d9                	jns    6ec <printint+0x8a>
    putc(fd, buf[i]);
}
 713:	83 c4 30             	add    $0x30,%esp
 716:	5b                   	pop    %ebx
 717:	5e                   	pop    %esi
 718:	5d                   	pop    %ebp
 719:	c3                   	ret    

0000071a <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, char *fmt, ...)
{
 71a:	55                   	push   %ebp
 71b:	89 e5                	mov    %esp,%ebp
 71d:	83 ec 38             	sub    $0x38,%esp
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
 720:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  ap = (uint*)(void*)&fmt + 1;
 727:	8d 45 0c             	lea    0xc(%ebp),%eax
 72a:	83 c0 04             	add    $0x4,%eax
 72d:	89 45 e8             	mov    %eax,-0x18(%ebp)
  for(i = 0; fmt[i]; i++){
 730:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 737:	e9 7c 01 00 00       	jmp    8b8 <printf+0x19e>
    c = fmt[i] & 0xff;
 73c:	8b 55 0c             	mov    0xc(%ebp),%edx
 73f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 742:	01 d0                	add    %edx,%eax
 744:	0f b6 00             	movzbl (%eax),%eax
 747:	0f be c0             	movsbl %al,%eax
 74a:	25 ff 00 00 00       	and    $0xff,%eax
 74f:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    if(state == 0){
 752:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 756:	75 2c                	jne    784 <printf+0x6a>
      if(c == '%'){
 758:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 75c:	75 0c                	jne    76a <printf+0x50>
        state = '%';
 75e:	c7 45 ec 25 00 00 00 	movl   $0x25,-0x14(%ebp)
 765:	e9 4a 01 00 00       	jmp    8b4 <printf+0x19a>
      } else {
        putc(fd, c);
 76a:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 76d:	0f be c0             	movsbl %al,%eax
 770:	89 44 24 04          	mov    %eax,0x4(%esp)
 774:	8b 45 08             	mov    0x8(%ebp),%eax
 777:	89 04 24             	mov    %eax,(%esp)
 77a:	e8 bb fe ff ff       	call   63a <putc>
 77f:	e9 30 01 00 00       	jmp    8b4 <printf+0x19a>
      }
    } else if(state == '%'){
 784:	83 7d ec 25          	cmpl   $0x25,-0x14(%ebp)
 788:	0f 85 26 01 00 00    	jne    8b4 <printf+0x19a>
      if(c == 'd'){
 78e:	83 7d e4 64          	cmpl   $0x64,-0x1c(%ebp)
 792:	75 2d                	jne    7c1 <printf+0xa7>
        printint(fd, *ap, 10, 1);
 794:	8b 45 e8             	mov    -0x18(%ebp),%eax
 797:	8b 00                	mov    (%eax),%eax
 799:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 7a0:	00 
 7a1:	c7 44 24 08 0a 00 00 	movl   $0xa,0x8(%esp)
 7a8:	00 
 7a9:	89 44 24 04          	mov    %eax,0x4(%esp)
 7ad:	8b 45 08             	mov    0x8(%ebp),%eax
 7b0:	89 04 24             	mov    %eax,(%esp)
 7b3:	e8 aa fe ff ff       	call   662 <printint>
        ap++;
 7b8:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 7bc:	e9 ec 00 00 00       	jmp    8ad <printf+0x193>
      } else if(c == 'x' || c == 'p'){
 7c1:	83 7d e4 78          	cmpl   $0x78,-0x1c(%ebp)
 7c5:	74 06                	je     7cd <printf+0xb3>
 7c7:	83 7d e4 70          	cmpl   $0x70,-0x1c(%ebp)
 7cb:	75 2d                	jne    7fa <printf+0xe0>
        printint(fd, *ap, 16, 0);
 7cd:	8b 45 e8             	mov    -0x18(%ebp),%eax
 7d0:	8b 00                	mov    (%eax),%eax
 7d2:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 7d9:	00 
 7da:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 7e1:	00 
 7e2:	89 44 24 04          	mov    %eax,0x4(%esp)
 7e6:	8b 45 08             	mov    0x8(%ebp),%eax
 7e9:	89 04 24             	mov    %eax,(%esp)
 7ec:	e8 71 fe ff ff       	call   662 <printint>
        ap++;
 7f1:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 7f5:	e9 b3 00 00 00       	jmp    8ad <printf+0x193>
      } else if(c == 's'){
 7fa:	83 7d e4 73          	cmpl   $0x73,-0x1c(%ebp)
 7fe:	75 45                	jne    845 <printf+0x12b>
        s = (char*)*ap;
 800:	8b 45 e8             	mov    -0x18(%ebp),%eax
 803:	8b 00                	mov    (%eax),%eax
 805:	89 45 f4             	mov    %eax,-0xc(%ebp)
        ap++;
 808:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
        if(s == 0)
 80c:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 810:	75 09                	jne    81b <printf+0x101>
          s = "(null)";
 812:	c7 45 f4 33 0b 00 00 	movl   $0xb33,-0xc(%ebp)
        while(*s != 0){
 819:	eb 1e                	jmp    839 <printf+0x11f>
 81b:	eb 1c                	jmp    839 <printf+0x11f>
          putc(fd, *s);
 81d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 820:	0f b6 00             	movzbl (%eax),%eax
 823:	0f be c0             	movsbl %al,%eax
 826:	89 44 24 04          	mov    %eax,0x4(%esp)
 82a:	8b 45 08             	mov    0x8(%ebp),%eax
 82d:	89 04 24             	mov    %eax,(%esp)
 830:	e8 05 fe ff ff       	call   63a <putc>
          s++;
 835:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
 839:	8b 45 f4             	mov    -0xc(%ebp),%eax
 83c:	0f b6 00             	movzbl (%eax),%eax
 83f:	84 c0                	test   %al,%al
 841:	75 da                	jne    81d <printf+0x103>
 843:	eb 68                	jmp    8ad <printf+0x193>
          putc(fd, *s);
          s++;
        }
      } else if(c == 'c'){
 845:	83 7d e4 63          	cmpl   $0x63,-0x1c(%ebp)
 849:	75 1d                	jne    868 <printf+0x14e>
        putc(fd, *ap);
 84b:	8b 45 e8             	mov    -0x18(%ebp),%eax
 84e:	8b 00                	mov    (%eax),%eax
 850:	0f be c0             	movsbl %al,%eax
 853:	89 44 24 04          	mov    %eax,0x4(%esp)
 857:	8b 45 08             	mov    0x8(%ebp),%eax
 85a:	89 04 24             	mov    %eax,(%esp)
 85d:	e8 d8 fd ff ff       	call   63a <putc>
        ap++;
 862:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 866:	eb 45                	jmp    8ad <printf+0x193>
      } else if(c == '%'){
 868:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 86c:	75 17                	jne    885 <printf+0x16b>
        putc(fd, c);
 86e:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 871:	0f be c0             	movsbl %al,%eax
 874:	89 44 24 04          	mov    %eax,0x4(%esp)
 878:	8b 45 08             	mov    0x8(%ebp),%eax
 87b:	89 04 24             	mov    %eax,(%esp)
 87e:	e8 b7 fd ff ff       	call   63a <putc>
 883:	eb 28                	jmp    8ad <printf+0x193>
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
 885:	c7 44 24 04 25 00 00 	movl   $0x25,0x4(%esp)
 88c:	00 
 88d:	8b 45 08             	mov    0x8(%ebp),%eax
 890:	89 04 24             	mov    %eax,(%esp)
 893:	e8 a2 fd ff ff       	call   63a <putc>
        putc(fd, c);
 898:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 89b:	0f be c0             	movsbl %al,%eax
 89e:	89 44 24 04          	mov    %eax,0x4(%esp)
 8a2:	8b 45 08             	mov    0x8(%ebp),%eax
 8a5:	89 04 24             	mov    %eax,(%esp)
 8a8:	e8 8d fd ff ff       	call   63a <putc>
      }
      state = 0;
 8ad:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  int c, i, state;
  uint *ap;

  state = 0;
  ap = (uint*)(void*)&fmt + 1;
  for(i = 0; fmt[i]; i++){
 8b4:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 8b8:	8b 55 0c             	mov    0xc(%ebp),%edx
 8bb:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8be:	01 d0                	add    %edx,%eax
 8c0:	0f b6 00             	movzbl (%eax),%eax
 8c3:	84 c0                	test   %al,%al
 8c5:	0f 85 71 fe ff ff    	jne    73c <printf+0x22>
        putc(fd, c);
      }
      state = 0;
    }
  }
}
 8cb:	c9                   	leave  
 8cc:	c3                   	ret    

000008cd <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
 8cd:	55                   	push   %ebp
 8ce:	89 e5                	mov    %esp,%ebp
 8d0:	83 ec 10             	sub    $0x10,%esp
  Header *bp, *p;

  bp = (Header*)ap - 1;
 8d3:	8b 45 08             	mov    0x8(%ebp),%eax
 8d6:	83 e8 08             	sub    $0x8,%eax
 8d9:	89 45 f8             	mov    %eax,-0x8(%ebp)
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 8dc:	a1 dc 0d 00 00       	mov    0xddc,%eax
 8e1:	89 45 fc             	mov    %eax,-0x4(%ebp)
 8e4:	eb 24                	jmp    90a <free+0x3d>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
 8e6:	8b 45 fc             	mov    -0x4(%ebp),%eax
 8e9:	8b 00                	mov    (%eax),%eax
 8eb:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 8ee:	77 12                	ja     902 <free+0x35>
 8f0:	8b 45 f8             	mov    -0x8(%ebp),%eax
 8f3:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 8f6:	77 24                	ja     91c <free+0x4f>
 8f8:	8b 45 fc             	mov    -0x4(%ebp),%eax
 8fb:	8b 00                	mov    (%eax),%eax
 8fd:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 900:	77 1a                	ja     91c <free+0x4f>
free(void *ap)
{
  Header *bp, *p;

  bp = (Header*)ap - 1;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 902:	8b 45 fc             	mov    -0x4(%ebp),%eax
 905:	8b 00                	mov    (%eax),%eax
 907:	89 45 fc             	mov    %eax,-0x4(%ebp)
 90a:	8b 45 f8             	mov    -0x8(%ebp),%eax
 90d:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 910:	76 d4                	jbe    8e6 <free+0x19>
 912:	8b 45 fc             	mov    -0x4(%ebp),%eax
 915:	8b 00                	mov    (%eax),%eax
 917:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 91a:	76 ca                	jbe    8e6 <free+0x19>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
 91c:	8b 45 f8             	mov    -0x8(%ebp),%eax
 91f:	8b 40 04             	mov    0x4(%eax),%eax
 922:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 929:	8b 45 f8             	mov    -0x8(%ebp),%eax
 92c:	01 c2                	add    %eax,%edx
 92e:	8b 45 fc             	mov    -0x4(%ebp),%eax
 931:	8b 00                	mov    (%eax),%eax
 933:	39 c2                	cmp    %eax,%edx
 935:	75 24                	jne    95b <free+0x8e>
    bp->s.size += p->s.ptr->s.size;
 937:	8b 45 f8             	mov    -0x8(%ebp),%eax
 93a:	8b 50 04             	mov    0x4(%eax),%edx
 93d:	8b 45 fc             	mov    -0x4(%ebp),%eax
 940:	8b 00                	mov    (%eax),%eax
 942:	8b 40 04             	mov    0x4(%eax),%eax
 945:	01 c2                	add    %eax,%edx
 947:	8b 45 f8             	mov    -0x8(%ebp),%eax
 94a:	89 50 04             	mov    %edx,0x4(%eax)
    bp->s.ptr = p->s.ptr->s.ptr;
 94d:	8b 45 fc             	mov    -0x4(%ebp),%eax
 950:	8b 00                	mov    (%eax),%eax
 952:	8b 10                	mov    (%eax),%edx
 954:	8b 45 f8             	mov    -0x8(%ebp),%eax
 957:	89 10                	mov    %edx,(%eax)
 959:	eb 0a                	jmp    965 <free+0x98>
  } else
    bp->s.ptr = p->s.ptr;
 95b:	8b 45 fc             	mov    -0x4(%ebp),%eax
 95e:	8b 10                	mov    (%eax),%edx
 960:	8b 45 f8             	mov    -0x8(%ebp),%eax
 963:	89 10                	mov    %edx,(%eax)
  if(p + p->s.size == bp){
 965:	8b 45 fc             	mov    -0x4(%ebp),%eax
 968:	8b 40 04             	mov    0x4(%eax),%eax
 96b:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 972:	8b 45 fc             	mov    -0x4(%ebp),%eax
 975:	01 d0                	add    %edx,%eax
 977:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 97a:	75 20                	jne    99c <free+0xcf>
    p->s.size += bp->s.size;
 97c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 97f:	8b 50 04             	mov    0x4(%eax),%edx
 982:	8b 45 f8             	mov    -0x8(%ebp),%eax
 985:	8b 40 04             	mov    0x4(%eax),%eax
 988:	01 c2                	add    %eax,%edx
 98a:	8b 45 fc             	mov    -0x4(%ebp),%eax
 98d:	89 50 04             	mov    %edx,0x4(%eax)
    p->s.ptr = bp->s.ptr;
 990:	8b 45 f8             	mov    -0x8(%ebp),%eax
 993:	8b 10                	mov    (%eax),%edx
 995:	8b 45 fc             	mov    -0x4(%ebp),%eax
 998:	89 10                	mov    %edx,(%eax)
 99a:	eb 08                	jmp    9a4 <free+0xd7>
  } else
    p->s.ptr = bp;
 99c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 99f:	8b 55 f8             	mov    -0x8(%ebp),%edx
 9a2:	89 10                	mov    %edx,(%eax)
  freep = p;
 9a4:	8b 45 fc             	mov    -0x4(%ebp),%eax
 9a7:	a3 dc 0d 00 00       	mov    %eax,0xddc
}
 9ac:	c9                   	leave  
 9ad:	c3                   	ret    

000009ae <morecore>:

static Header*
morecore(uint nu)
{
 9ae:	55                   	push   %ebp
 9af:	89 e5                	mov    %esp,%ebp
 9b1:	83 ec 28             	sub    $0x28,%esp
  char *p;
  Header *hp;

  if(nu < 4096)
 9b4:	81 7d 08 ff 0f 00 00 	cmpl   $0xfff,0x8(%ebp)
 9bb:	77 07                	ja     9c4 <morecore+0x16>
    nu = 4096;
 9bd:	c7 45 08 00 10 00 00 	movl   $0x1000,0x8(%ebp)
  p = sbrk(nu * sizeof(Header));
 9c4:	8b 45 08             	mov    0x8(%ebp),%eax
 9c7:	c1 e0 03             	shl    $0x3,%eax
 9ca:	89 04 24             	mov    %eax,(%esp)
 9cd:	e8 48 fc ff ff       	call   61a <sbrk>
 9d2:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(p == (char*)-1)
 9d5:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 9d9:	75 07                	jne    9e2 <morecore+0x34>
    return 0;
 9db:	b8 00 00 00 00       	mov    $0x0,%eax
 9e0:	eb 22                	jmp    a04 <morecore+0x56>
  hp = (Header*)p;
 9e2:	8b 45 f4             	mov    -0xc(%ebp),%eax
 9e5:	89 45 f0             	mov    %eax,-0x10(%ebp)
  hp->s.size = nu;
 9e8:	8b 45 f0             	mov    -0x10(%ebp),%eax
 9eb:	8b 55 08             	mov    0x8(%ebp),%edx
 9ee:	89 50 04             	mov    %edx,0x4(%eax)
  free((void*)(hp + 1));
 9f1:	8b 45 f0             	mov    -0x10(%ebp),%eax
 9f4:	83 c0 08             	add    $0x8,%eax
 9f7:	89 04 24             	mov    %eax,(%esp)
 9fa:	e8 ce fe ff ff       	call   8cd <free>
  return freep;
 9ff:	a1 dc 0d 00 00       	mov    0xddc,%eax
}
 a04:	c9                   	leave  
 a05:	c3                   	ret    

00000a06 <malloc>:

void*
malloc(uint nbytes)
{
 a06:	55                   	push   %ebp
 a07:	89 e5                	mov    %esp,%ebp
 a09:	83 ec 28             	sub    $0x28,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
 a0c:	8b 45 08             	mov    0x8(%ebp),%eax
 a0f:	83 c0 07             	add    $0x7,%eax
 a12:	c1 e8 03             	shr    $0x3,%eax
 a15:	83 c0 01             	add    $0x1,%eax
 a18:	89 45 ec             	mov    %eax,-0x14(%ebp)
  if((prevp = freep) == 0){
 a1b:	a1 dc 0d 00 00       	mov    0xddc,%eax
 a20:	89 45 f0             	mov    %eax,-0x10(%ebp)
 a23:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 a27:	75 23                	jne    a4c <malloc+0x46>
    base.s.ptr = freep = prevp = &base;
 a29:	c7 45 f0 d4 0d 00 00 	movl   $0xdd4,-0x10(%ebp)
 a30:	8b 45 f0             	mov    -0x10(%ebp),%eax
 a33:	a3 dc 0d 00 00       	mov    %eax,0xddc
 a38:	a1 dc 0d 00 00       	mov    0xddc,%eax
 a3d:	a3 d4 0d 00 00       	mov    %eax,0xdd4
    base.s.size = 0;
 a42:	c7 05 d8 0d 00 00 00 	movl   $0x0,0xdd8
 a49:	00 00 00 
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 a4c:	8b 45 f0             	mov    -0x10(%ebp),%eax
 a4f:	8b 00                	mov    (%eax),%eax
 a51:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 a54:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a57:	8b 40 04             	mov    0x4(%eax),%eax
 a5a:	3b 45 ec             	cmp    -0x14(%ebp),%eax
 a5d:	72 4d                	jb     aac <malloc+0xa6>
      if(p->s.size == nunits)
 a5f:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a62:	8b 40 04             	mov    0x4(%eax),%eax
 a65:	3b 45 ec             	cmp    -0x14(%ebp),%eax
 a68:	75 0c                	jne    a76 <malloc+0x70>
        prevp->s.ptr = p->s.ptr;
 a6a:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a6d:	8b 10                	mov    (%eax),%edx
 a6f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 a72:	89 10                	mov    %edx,(%eax)
 a74:	eb 26                	jmp    a9c <malloc+0x96>
      else {
        p->s.size -= nunits;
 a76:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a79:	8b 40 04             	mov    0x4(%eax),%eax
 a7c:	2b 45 ec             	sub    -0x14(%ebp),%eax
 a7f:	89 c2                	mov    %eax,%edx
 a81:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a84:	89 50 04             	mov    %edx,0x4(%eax)
        p += p->s.size;
 a87:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a8a:	8b 40 04             	mov    0x4(%eax),%eax
 a8d:	c1 e0 03             	shl    $0x3,%eax
 a90:	01 45 f4             	add    %eax,-0xc(%ebp)
        p->s.size = nunits;
 a93:	8b 45 f4             	mov    -0xc(%ebp),%eax
 a96:	8b 55 ec             	mov    -0x14(%ebp),%edx
 a99:	89 50 04             	mov    %edx,0x4(%eax)
      }
      freep = prevp;
 a9c:	8b 45 f0             	mov    -0x10(%ebp),%eax
 a9f:	a3 dc 0d 00 00       	mov    %eax,0xddc
      return (void*)(p + 1);
 aa4:	8b 45 f4             	mov    -0xc(%ebp),%eax
 aa7:	83 c0 08             	add    $0x8,%eax
 aaa:	eb 38                	jmp    ae4 <malloc+0xde>
    }
    if(p == freep)
 aac:	a1 dc 0d 00 00       	mov    0xddc,%eax
 ab1:	39 45 f4             	cmp    %eax,-0xc(%ebp)
 ab4:	75 1b                	jne    ad1 <malloc+0xcb>
      if((p = morecore(nunits)) == 0)
 ab6:	8b 45 ec             	mov    -0x14(%ebp),%eax
 ab9:	89 04 24             	mov    %eax,(%esp)
 abc:	e8 ed fe ff ff       	call   9ae <morecore>
 ac1:	89 45 f4             	mov    %eax,-0xc(%ebp)
 ac4:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 ac8:	75 07                	jne    ad1 <malloc+0xcb>
        return 0;
 aca:	b8 00 00 00 00       	mov    $0x0,%eax
 acf:	eb 13                	jmp    ae4 <malloc+0xde>
  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 ad1:	8b 45 f4             	mov    -0xc(%ebp),%eax
 ad4:	89 45 f0             	mov    %eax,-0x10(%ebp)
 ad7:	8b 45 f4             	mov    -0xc(%ebp),%eax
 ada:	8b 00                	mov    (%eax),%eax
 adc:	89 45 f4             	mov    %eax,-0xc(%ebp)
      return (void*)(p + 1);
    }
    if(p == freep)
      if((p = morecore(nunits)) == 0)
        return 0;
  }
 adf:	e9 70 ff ff ff       	jmp    a54 <malloc+0x4e>
}
 ae4:	c9                   	leave  
 ae5:	c3                   	ret    
