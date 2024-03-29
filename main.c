// The MIT License (MIT)
//
// Copyright (c) 2017 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.a

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
  fork() a child and print a message from the parent and 
  a message from the child
*/

int main( void )
{
  pid_t pid = fork();
  int timeRemaining = 10;

  if( pid == -1 )
  {
    // When fork() returns -1, an error happened.
    perror("fork failed: ");
    exit( EXIT_FAILURE );
  }
  else if ( pid == 0 )
  {
    // When fork() returns 0, we are in the child process.
    
    while(timeRemaining!=0)
    {
    	sleep(1);
    	printf("Time remaining: %d\n", timeRemaining);
    	timeRemaining--;
    }
    
    fflush(NULL);
    exit( EXIT_SUCCESS );
  }
  else 
  {
    // When fork() returns a positive number, we are in the parent
    // process and the return value is the PID of the newly created
    // child process.
    int status;

    // Force the parent process to wait until the child process 
    // exits
    waitpid(pid, &status, 0 );
    printf("Countdown complete\n");
    fflush( NULL );
  }
  
  return EXIT_SUCCESS;
}

