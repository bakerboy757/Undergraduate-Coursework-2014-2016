#Proj1
Implement the top utility in the xv6 operating system

Added new system call getprocs(int, struct uproc*) which takes a new structure uproc which is a derivative of the proc struct

Added top.c which calls getprocs which is a wrapper for the newly added sys_getprocs function defined in sysproc.c. sys_getprocs calls
gettables in proc.c which observes and stores processees from the ptable to then be formatted and outputted by top.c


