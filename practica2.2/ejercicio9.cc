#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>


/* ./ejercicio9 file_name */
int main(int argc, char **argv){
	struct stat sb;

	if(stat(argv[1], &sb) == -1){
		fprintf(stderr, "stat: %s\n", strerror(errno));
		return 1;
	}

	printf("Major: %li\n", (long) major(sb.st_dev));
	printf("Minor: %li\n", (long) minor(sb.st_dev));
	printf("Inode: %li\n", (long) sb.st_ino);

	switch(sb.st_mode & S_IFMT){
		case S_IFBLK: 
			printf("Tipo de archivo: block device\n"); 
			break;
		case S_IFCHR: 
			printf("Tipo de archivo: character device\n"); 
			break;
		case S_IFDIR: 
			printf("Tipo de archivo: directory\n"); 
			break;
		case S_IFIFO: 
			printf("Tipo de archivo: FIFO/pipe\n"); 
			break;
		case S_IFLNK: 
			printf("Tipo de archivo: symlink\n"); 
			break;
		case S_IFREG: 
			printf("Tipo de archivo: regular file\n"); 
			break;
		case S_IFSOCK: 
			printf("Tipo de archivo: socket\n"); 
			break;
		default: 
			printf("Tipo de archivo: unkown\n"); 
			break;

	}

	printf("Último Acceso: %s\n", ctime(&sb.st_atime));

	return 0;	

}
