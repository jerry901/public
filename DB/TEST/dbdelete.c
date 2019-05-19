#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student2.h"

int dbdelete(int argc, char *argv[])
{
    int fd, id;
    char c;

	struct flock lock;
    struct student rec;
	char del = '$';

    if (argc < 3) {
        fprintf(stderr,  "USAGE : %s [-d] [DBname]\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[2], O_RDWR)) == -1) {
        perror(argv[2]);
        exit(2);
    }

    do {
        printf("삭제할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {

			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = (id-START_ID)*sizeof(rec);
			lock.l_len = sizeof(rec);

			if (fcntl(fd,F_SETLKW, &lock) == -1) {  /* 쓰기 잠금 */
				perror("dbdelete.c : fcntl returned -1");
				exit(3);
			}

            lseek(fd,  (long) (id-START_ID)*sizeof(rec), SEEK_SET);

            if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0) && rec.name[0] !='$') {
                printf("학번:%8d\t 이름:%4s\t 점수:%4d\n", 
                       rec.id, rec.name, rec.score);
				
				printf("정말 삭제하시겠습니까?(Y/N) : ");
				scanf(" %c",&c);

				if(c == 'Y'){
					lseek(fd, (long) -sizeof(rec), SEEK_CUR);
					write(fd,&del, sizeof(del));
				   	printf(" - 삭제 완료 -\n");
					 
					c = '\0';
				}
				else
				   	printf(" - 삭제 취소 -\n");
            }
            else 
				printf("레코드 %d 없음\n", id);
        }
        else{
			printf("입력오류\n");
			getchar();
		}

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);  /* 잠금 해제 */

        printf("계속하겠습니까?(Y/N) : ");
        scanf(" %c",&c);
    } while (c == 'Y');

    close(fd);
}

