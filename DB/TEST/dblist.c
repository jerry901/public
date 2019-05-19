#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student2.h"

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int dblist(int argc, char *argv[])
{
    int fd;
    struct student rec;
    struct flock lock;
	off_t end_position;

   if (argc < 3) {
        fprintf(stderr,  "USAGE : %s -l filename\n", argv[0]);
        exit(1);
   }

   if ((fd = open(argv[2], O_RDONLY)) == -1) {
        perror(argv[2]);
        exit(2);
    }
    end_position = lseek(fd, 0, SEEK_END);

	lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

	lseek(fd, (START_ID)*sizeof(rec), SEEK_SET);

	if (fcntl(fd,F_SETLKW, &lock) == -1) {   /* 읽기 잠금 */
        perror("fcntl returned -1\n");
        exit(3); 
    }
	while(read(fd, &rec, sizeof(rec)) != -1){
		if(lseek(fd, 0, SEEK_CUR) == end_position){
			printf("학번:%d\t 이름:%s\t 점수:%d\n", 
		                 rec.id, rec.name, rec.score);
			break;
		}

		if(rec.name[0] != '$' && rec.id != 0)
		     printf("학번:%d\t 이름:%s\t 점수:%d\n", 
		                 rec.id, rec.name, rec.score);
	}

	lock.l_type = F_UNLCK;
	fcntl(fd,F_SETLK, &lock);    /* 잠금 해제 */
   
    close(fd);

	return 0; 
}
