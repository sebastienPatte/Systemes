#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


void copie(char* path1, char* path2, int size)
{      
	
    int f1 = open(path1, O_RDONLY);  
      
    //printf("f1 = %d\n", f1); 
      
    if (f1 ==-1) 
    { 
        perror("Error opening file1");  
        printf("path = \"%s\"\n",path1);
                            
    }
    
    int f2 = open(path2, O_WRONLY | O_CREAT);  
      
    //printf("f2 = %d\n", f2); 
      
    if (f2 ==-1) 
    { 
        perror("Error opening file2");  
        printf("path = \"%s\"\n",path2);
                            
    }
    
    int sizeOfRead;
    char buf[size];
    do
    {    
    
    sizeOfRead = read(f1,buf,size);	
	
	write(f2,buf,sizeOfRead);
	
	}while(sizeOfRead !=0);
	
	struct stat statBuf;
	fstat(f1,&statBuf);
	//S_IRWX is a mask for Read Write Read permissions, finished by U for user, G for group and O for Others
	mode_t file_permision = statBuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO); 
   	//printf(" File permission : %o (octal)\n", (unsigned int) file_permision); 
   	chmod(path2,file_permision);
	close(f1);
	close(f2);
} 

char* concatStr(char* s1, char* s2)
{
	char* res;
	res = calloc(strlen(s1)+strlen(s2), sizeof(char));
	strcpy(res,s1);
	strcat(res,s2);
	return res;
}

void copieDossier(char* path1, char* path2, int size)
{
	struct dirent *srcDirent;
	struct stat stElt;
	DIR* dirSrc;
	dirSrc = opendir(path1);

	if(dirSrc !=NULL)
	{
		while((srcDirent = readdir(dirSrc)) != NULL)
		{
			char* fileName = srcDirent->d_name;
			//printf("[%s]\n", fileName);
			
			if(fileName != ".." && *fileName != '.')
			{

				//printf("fileName = |%s|\n", fileName);
				// ajout des "/" à la fin des noms de dossier
				if (strlen(path1)-1>=0 && path1[strlen(path1)-1]!='/')
				{
					path1 = concatStr(path1,"/");
				}
				if (strlen(path2)-1>=0 && path2[strlen(path2)-1]!='/')
				{
					path2 = concatStr(path2,"/");
				}
				
				if(stat(concatStr(path1,fileName),&stElt)==-1)
				{
					perror("Error stat ");
				}

				if(S_ISREG(stElt.st_mode))
				{//si l'élément est un fichier, on le copie
					copie(concatStr(path1,fileName), concatStr(path2,fileName), size);	
				}
				
			}
		}
	}
	closedir(dirSrc);
}

void copieRecursive(char* path1, char* path2, int size)
{
	struct dirent *srcDirent;
	struct stat stElt;
	DIR* dirSrc;
	dirSrc = opendir(path1);

	if(dirSrc !=NULL)
	{
		copieDossier(path1,path2,size);//on copie les fichier du dossier courant
		while((srcDirent = readdir(dirSrc)) != NULL)
		{
			char* pathElt = srcDirent->d_name;
			if(pathElt != ".." && *pathElt != '.') 
			{ // on ignore le dossier courant et le dossier parent
				
				printf("path1+elt = %s %s\n", path1,pathElt);
				if(stat(concatStr(path1,pathElt),&stElt)==-1)
				{
					perror("Error stat ");
				}
				
		
				if(S_ISDIR(stElt.st_mode))
				{ // si Elt est un dossier
					if (strlen(pathElt)-1>=0 && pathElt[strlen(pathElt)-1]!='/')
					{
						pathElt = concatStr(pathElt,"/");
					}
					
					

					printf("folderPath = %s\n", pathElt);
					if(mkdir(concatStr(path2,pathElt),0700) == -1)
					{
						perror("Error mkdir ");
					}
					copieRecursive(concatStr(path1,pathElt),concatStr(path2,pathElt),size);
					
				}
				
			}

		}
	}
}

int main()
{
	int sizeBlock = 1024; //4096
	//copie("file1.txt","file2.txt", sizeBlock);
	

	copieRecursive("folder1/","folder2/",sizeBlock);
}



