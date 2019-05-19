main: main.o option.o help.o dbcreate.o dbupdate.o dbquery.o dbdelete.o dblist.o dbadd.o
	gcc -g -o main main.o option.o help.o dbcreate.o dbupdate.o dbquery.o dbdelete.o dblist.o dbadd.o
main.o : main.c main.h student2.h
	gcc -g -c main.c main.h 
option.o : option.c option.h
	gcc -g -c option.c option.h
help.o : help.c help.h
	gcc -g -c help.c help.h
dbcreate.o : dbcreate.c dbcreate.h 
	gcc -g -c dbcreate.c dbcreate.h
dbupdate.o : dbupdate.c dbupdate.h
	gcc -g -c dbupdate.c dbupdate.h
dbquery.o : dbquery.c dbquery.h
	gcc -g -c dbquery.c dbquery.h
dbdelete.o : dbdelete.c dbdelete.h
	gcc -g -c dbdelete.c dbdelete.h
dblist.o : dblist.c dblist.h
	gcc -g -c dblist.c dblist.h
dbadd.o : dbadd.c dbadd.h
	gcc -g -c dbadd.c dbadd.h
