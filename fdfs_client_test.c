#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "make_log.h"

#define FDFS_TEST_MUDULE "test"
#define FDFS_TEST_PROC   "fdfs_test"

#define FILE_ID_LEN     (256)

int main(int argc, char *argv[])
{
    pid_t pid;
    char *file_name = NULL;
    char file_id[FILE_ID_LEN] = { 0 };
    int fd[2];

    file_name = argv[1];

    if (argc < 2){
        printf("./file argv error\n");
        exit(1);
    }

    if (pipe(fd) < 0){
        printf("pipe error\n");
        exit(1);
    }

    if ((pid = fork()) < 0){
        printf("fork error\n");
        exit(1);
    }
    else if (pid == 0){
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        execlp("fdfs_upload_file", "fdfs_upload_file", "./conf/client.conf", file_name, NULL);
        LOG(FDFS_TEST_MUDULE, FDFS_TEST_PROC, "exec fdfs_upload_file error");
    }
    else {
        close(fd[1]);

        wait(NULL);

        read(fd[0], file_id, FILE_ID_LEN);

        LOG(FDFS_TEST_MUDULE, FDFS_TEST_PROC, "file_id = {%s}", file_id);
    }

	return 0;
}
