/*
 * newlib_stub.c
 *
 *  Created on: 2014�~8��6��
 *      Author: YunKei
 */

#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include <stm32f4xx_gpio.h>

USART_TypeDef* STDOUT_USART = USART1;
USART_TypeDef* STDERR_USART = USART1;
USART_TypeDef* STDIN_USART = USART1;

//#ifndef STDOUT_USART
//#define STDOUT_USART USART1
//#endif
//
//#ifndef STDERR_USART
//#define STDERR_USART USART1
//#endif
//
//#ifndef STDIN_USART
//#define STDIN_USART USART1
//#endif

#undef errno
extern int errno;

/*
environ
A pointer to a list of environment variables and their values.
For a minimal environment, this empty list is adequate:
*/
char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

void _exit(int status) {
    _write(1, "exit", 4);
    while (1) {
        ;
    }
}

int _close(int file) {
    return -1;
}
/*
execve
Transfer control to a new process. Minimal implementation (for a system without processes):
*/
int _execve(char *name, char **argv, char **env) {
    errno = ENOMEM;
    return -1;
}
/*
fork
Create a new process. Minimal implementation (for a system without processes):
*/

int _fork() {
    errno = EAGAIN;
    return -1;
}
/*
fstat
Status of an open file. For consistency with other minimal implementations in these examples,
all files are regarded as character special devices.
The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
*/
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

/*
getpid
Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
*/

int _getpid() {
    return 1;
}

/*
isatty
Query whether output stream is a terminal. For consistency with the other minimal implementations,
*/
int _isatty(int file) {
    switch (file){
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}


/*
kill
Send a signal. Minimal implementation:
*/
int _kill(int pid, int sig) {
    errno = EINVAL;
    return (-1);
}

/*
link
Establish a new name for an existing file. Minimal implementation:
*/

int _link(char *old, char *new) {
    errno = EMLINK;
    return -1;
}

/*
lseek
Set position in a file. Minimal implementation:
*/
int _lseek(int file, int ptr, int dir) {
    return 0;
}

/*
sbrk
Increase program data space.
Malloc and related functions depend on this
*/
uint32_t heap_loc;
caddr_t _sbrk(int incr) {

    extern char _ebss; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_ebss;
    }
    heap_loc = prev_heap_end = heap_end;

char * stack = (char*) __get_MSP();
     if (heap_end + incr > stack)
     {
         _write (STDERR_FILENO, "Heap and stack collision\n", 25);
         errno = ENOMEM;
         return (caddr_t) -1;
         //abort ();
     }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
read
Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
Returns -1 on error or blocks until the number of characters have been read.
*/

char __io_getchar(){
	int32_t timeout = 336000;
	while (USART_GetFlagStatus(STDIN_USART, USART_FLAG_RXNE) == RESET){
		if(timeout-- < 0){
			return 0;
		}
	}
	return (char)USART_ReceiveData(STDIN_USART);
}

int _read(int file, char *ptr, int len) {
    int n;
    int num = 0;
    switch (file) {
    case STDIN_FILENO:
        for (n = 0; n < len; n++) {
            char c = __io_getchar();
            *ptr++ = c;
            num++;
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return num;
}

/*
stat
Status of a file (by name). Minimal implementation:
int _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
*/

int _stat(const char *filepath, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

/*
times
Timing information for current process. Minimal implementation:
*/

clock_t _times(struct tms *buf) {
    return -1;
}

/*
unlink
Remove a file's directory entry. Minimal implementation:
*/
int _unlink(char *name) {
    errno = ENOENT;
    return -1;
}

/*
wait
Wait for a child process. Minimal implementation:
*/
int _wait(int *status) {
    errno = ECHILD;
    return -1;
}

/*
write
Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
Returns -1 on error or number of bytes sent
*/

int __io_putchar(int ch){

	int32_t timeout = 336000;
	while (USART_GetFlagStatus(STDOUT_USART, USART_FLAG_TXE) == RESET){
		if(timeout-- < 0){
			return 0;
		}

	}
	USART_SendData(STDOUT_USART, ch & 0x01ff);
	return ch;
}

int _write(int file, char *ptr, int len) {
    int n;
    switch (file) {
		case STDOUT_FILENO: /*stdout*/
			for (n = 0; n < len; n++) {
				__io_putchar(*ptr++);
			}
			break;
		case STDERR_FILENO: /* stderr */
			for (n = 0; n < len; n++) {
				__io_putchar(*ptr++);
			}
			break;
		default:
			errno = EBADF;
			return -1;
    }
    return len;
}
