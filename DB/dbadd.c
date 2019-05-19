#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "student2.h"

/* 학번을 입력받아 해당 학생 레코드를 수정한다. */
int dbadd(int argc, char *argv[])
{
    int fd; 
    char c;
	struct flock lock;
    struct student rec, tmp;

    if (argc < 3) {
        fprintf(stderr,  "USAGE : %s [-a] [DBname]\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[2], O_RDWR)) == -1) {
        perror(argv[2]);
        exit(2);
    }

    do {
        printf("데이터를 추가합니다.\n");
		printf("%-9s %-8s %-4s", "학번",  "이름",  "점수\n");
        if (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = (rec.id-START_ID)*sizeof(rec);
			lock.l_len = sizeof(rec);

			if (fcntl(fd,F_SETLKW, &lock) == -1) {  /* 쓰기 잠금 */
				perror("dbadd.c : fcntl returned -1");
				exit(3);
			}

            lseek(fd,  (long) (rec.id-START_ID)*sizeof(rec), SEEK_SET);
            if ((read(fd, &tmp, sizeof(tmp)) > 0) && ((tmp.id == 0) || (tmp.name[0] == '$'))) {
				lseek(fd, (long) -sizeof(rec), SEEK_CUR);
				write(fd, &rec, sizeof(rec));
				printf("학번: %d 이름: %s 점수 : %d\n - 추가 완료 -\n", rec.id, rec.name, rec.score);
            }
            else{ 
				fprintf(stderr, "ERROR: 이미 존재하는 학생입니다.\n");
                printf("학번:%8d\t 이름:%4s\t 점수:%4d\n", 
                       tmp.id, tmp.name, tmp.score);
			}
        }
        else{
			printf("입력오류\n");
		}
        printf("계속하겠습니까?(Y/N) : ");
        scanf(" %c",&c);
    } while (c == 'Y');

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);  /* 잠금 해제 */

    close(fd);

	return 0;
}

