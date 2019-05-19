#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "main.h"

int main(int argc, char* argv[]){ 
	int fd;
	int option;
	char c = '\0';

	if(argc < 3){
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃                HOW TO USE                 ┃\n");
		printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		printf("┃ 1) DBopen : \" %s -o [DBname]\"           ┃\n", argv[0]);
		printf("┃ 2) Create : \" %s -c [DBname] < txtfile\" ┃\n", argv[0]);
		printf("┃    ex) %s -o stdb                       ┃\n", argv[0]);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
		return 0;
	}
		
	option = getOption(argv[1]);	

	if(option == OPEN){
		printf("------------------------------------------\n");
		printf("OEPN OPTION\n");

		if ((fd = open(argv[2], O_WRONLY, 0640))==-1) {
		  perror(argv[2]);
		  exit(1);
		}
		else
		{
			printf("FILE OPEN OK.\n");
			close(fd);
		}
	}
	else if(option == CREATE){
		printf("------------------------------------------\n");
		printf("CREATE OPTION\n");
		dbcreate(argc, argv);
		printf("DONE!\n");
		exit(0);
	}
	else{
		fprintf(stderr, "ERROR : invalid option,\n");
		exit(0);
	}
		

	while(1){
		printf("------------------------------------------\n");
		help();
		printf("# DBname: %s #\n", argv[2]);
		printf("(Option)");

		scanf("%c", &c);

		switch(c){
			case 'd' :
				printf("------------------------------------------\n");
				dbdelete(argc, argv);
				getchar();
				break;
			case 'u' :
				printf("------------------------------------------\n");
				dbupdate(argc, argv);
				getchar();
				break;
			case 'l' :
				printf("------------------------------------------\n");
				dblist(argc, argv);
				getchar();
				break;
			case 'a' :
				printf("------------------------------------------\n");
				dbadd(argc, argv);
				getchar();
				break;
			case 'q' :
				printf("------------------------------------------\n");
				dbquery(argc, argv);
				getchar();
				break;
			case  'Q' :
				break;
			default :	
				fprintf(stderr, "ERROR : invalid option,\n");
				break;
		}

		if(c == 'Q')
			break;

		c = '\0';
	}

}
