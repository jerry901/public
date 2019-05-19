#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student2.h"

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int dbquery(int argc, char *argv[])
{
    int fd, id;
    char c;

	struct flock lock;
    struct student rec;

   if (argc < 3) {
        fprintf(stderr,  "USAGE : %s -q filename\n", argv[0]);
        exit(1);
   }

   if ((fd = open(argv[2], O_RDONLY)) == -1) {
        perror(argv[2]);
        exit(2);
    }

    do {
        printf("검색할 학생의 학번 입력:");
        if (scanf("%d", &id) == 1) {
			lock.l_type = F_RDLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = (id-START_ID)*sizeof(rec);
			lock.l_len = sizeof(rec);

			if (fcntl(fd,F_SETLKW, &lock) == -1) {  /* 쓰기 잠금 */
				perror("dbupdate.c : fcntl returned -1");
				exit(3);
			}

            lseek(fd, (id-START_ID)*sizeof(rec), SEEK_SET);
            if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0) && (rec.name[0] != '$')) 
                printf("학번:%d\t 이름:%s\t 점수:%d\n", 
                        rec.id, rec.name, rec.score);
            else printf("검색할 레코드 %d 없음\n", id);

			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);  /* 잠금 해제 */
        }
        else{
			printf("입력 오류\n");
			getchar();
		}  
        printf("계속하겠습니까?(Y/N) : ");
        scanf(" %c", &c);
    } while (c == 'Y');

    close(fd);
	return 0;
}
