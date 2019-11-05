#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


void copie(char* path1, char* path2, int size) {      
	
    int f1 = open(path1, O_RDONLY);  
      
    printf("f1 = %d\n", f1); 
      
    if (f1 ==-1) 
    { 
        printf("Error open file1\n");  
                            
    }
    
    int f2 = open(path2, O_WRONLY | O_CREAT);  
      
    printf("f2 = %d\n", f2); 
      
    if (f2 ==-1) 
    { 
        printf("Error open file2\n");  
                            
    }
    
    int sizeOfRead;
    char buf[size];
    do{    
    
    sizeOfRead = read(f1,buf,size);	
	
	write(f2,buf,sizeOfRead);
	
	}while(sizeOfRead !=0);
	
	struct stat statBuf;
	fstat(f1,&statBuf);
	//S_IRWX is a mask for Read Write Read permissions, finished by U for user, G for group and O for Others
	mode_t file_permision = statBuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO); 
   	printf(" File permission : %o (octal)\n", (unsigned int) file_permision); 
   	chmod(path2,file_permision);
	close(f1);
	close(f2);
} 

int main(){
	int sizeBlock = 1024; //4096
	copie("file1.txt","file2.txt", sizeBlock);
}



