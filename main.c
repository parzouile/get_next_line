char	*get_next_line(int fd);
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    int fd = open("note", O_RDONLY);


    char *s;
    // s = get_next_line(fd);
    // printf("[%s]", s);
    // s = get_next_line(fd);
    // printf("[%s]", s);
    // s = get_next_line(fd);
    // printf("[%s]", s);

    s = get_next_line(fd);
    printf("[%s]", s);
    free(s);
    while (s)
    {
        s = get_next_line(fd);
        printf("[%s]", s);    
        free(s);
    }
    close(fd);
}