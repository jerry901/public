#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student2.h"

/* 학생 정보를 입력받아 데이터베이스 파일에 저장한다. */
int dbcreate(int argc, char *argv[]){
    int fd;
	struct flock lock;
    struct student rec;

    if (argc < 3 || argc > 3) {
        fprintf(stderr,  "USAGE : 1) %s -c filename\n", argv[0]);
        fprintf(stderr,  "        2) %s -c filename < text.txt\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[2],O_WRONLY |O_CREAT, 0640))==-1) {
        perror(argv[2]);
        exit(2);
    }

    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

	if (fcntl(fd,F_SETLKW, &lock) == -1) {  /* 쓰기 잠금 */
		perror("dbadd.c : fcntl returned -1");
		exit(3);
	}

    printf("%-9s %-8s %-4s", "학번",  "이름",  "점수\n"); 
    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) ==  3) {
        lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
        write(fd, &rec, sizeof(rec) );
    }
    printf("record size= %ld\n", sizeof(rec));

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);  /* 잠금 해제 */

    close(fd);

	return 0;
}
