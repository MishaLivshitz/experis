#include <iostream>


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int pid = fork();
    if(pid == 0)
    {
        execvp(argv[1],argv);
    }
    else
    {
        wait(0);
        std::cout << '!' << std::endl;
    }
    
    
    return 1;
}