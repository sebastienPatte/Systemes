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
	/*on ouvre le fichier à l'emplacement 'path1' en lecture seule
	  on récupère le file descriptor f1*/
    int f1 = open(path1, O_RDONLY);  
    if (f1 ==-1) 
    { 
        perror("Error opening file1 (function 'copie') ");  
        printf("when path = \"%s\"\n",path1);
    }
    
    /*on ouvre le fichier à l'emplacement 'path2' en lecture/écriture 
      si le fichier n'existe pas, il est créé
	  on récupère le file descriptor f2*/
    int f2 = open(path2, O_WRONLY | O_CREAT);
    if (f2 ==-1) 
    { 
        perror("Error opening file2 (function 'copie') ");  
        printf("when path = \"%s\"\n",path2);
    }
    
    int sizeOfRead;
    char buf[size];
    do
    {    
    	/*copie de blocs de taille maximale 'size' de f1 vers f2
    	  on arrète quand on a lu un bloc plus petit que size (car fin du fichier)*/
	    sizeOfRead = read(f1,buf,size);	
		write(f2,buf,sizeOfRead);
	}while( !(sizeOfRead < size));
	
	//on récupère la structure stat pour f1 dans le buffer 'statBuf'
	struct stat statBuf;
	if(fstat(f1,&statBuf) == -1)
	{
		perror("Error fstat file1 (function 'copie') ");
	}
	
	//on récupère dans 'file_permission' les permissions du fichier à partier de statBuf et grâce au masque S_IRWX[U|G|O]  
	mode_t file_permision = statBuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO); 
   	//on donne ces permissions à f2
   	if(chmod(path2,file_permision) == -1)
   	{
   		perror("Error chmod file2 (function 'copie') ");	
   	}

   	//on ferme f1 et f2
	if(close(f1) == -1)
	{
		perror("Error closing file1 (function 'copie') ");
	}
	if(close(f2) == -1)
	{
		perror("Error closing file2 (function 'copie') ");
	}
} 

char* concatStr(char* s1, char* s2)
{	// on concatène deux char* en copiant s1 dans res puis en y ajoutant s2
	char* res;
	//res a la taille de s1+s2
	res = calloc(strlen(s1)+strlen(s2), sizeof(char));
	strcpy(res,s1);
	strcat(res,s2);
	return res;
}

void copieDossier(char* path1, char* path2, int size)
{
	struct dirent *srcDirent;
	struct stat bufElt;
	DIR* dirSrc;
	dirSrc = opendir(path1);
	if(dirSrc ==NULL)
	{
		perror("Error opendir path1 (function copieDossier) ");
	}
	else
	{
		while((srcDirent = readdir(dirSrc)) != NULL)
		{
			char* fileName = srcDirent->d_name;
			//printf("[%s]\n", fileName);
			
			if(fileName != ".." && *fileName != '.')
			{

				//printf("fileName = |%s|\n", fileName);
				// ajout des "/" à la fin des noms de dossier pour ceux qui n'en ont pas
				if (strlen(path1)-1>=0 && path1[strlen(path1)-1]!='/')
				{
					path1 = concatStr(path1,"/");
				}
				if (strlen(path2)-1>=0 && path2[strlen(path2)-1]!='/')
				{
					path2 = concatStr(path2,"/");
				}
				
				// on récupère la structure stat pour l'élément du répertoire dans le buffer bufElt
				if(stat(concatStr(path1,fileName),&bufElt)==-1)
				{
					perror("Error stat ");
				}

				//on utilise la macro S_ISREG pour voir si l'élément est un fichier
				if(S_ISREG(bufElt.st_mode))
				{//si l'élément est un fichier, on le copie
					copie(concatStr(path1,fileName), concatStr(path2,fileName), size);	
				}
				
			}
		}
	}
	if(closedir(dirSrc) == -1)
	{
		perror("Error closedir path1 (function copieDossier) ");
		printf("when path = %s\n", path1);
	}
}

void copieRecursive(char* path1, char* path2, int size)
{
	struct dirent *srcDirent;
	struct stat bufElt;
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
				if(stat(concatStr(path1,pathElt),&bufElt)==-1)
				{
					perror("Error stat ");
				}
				
		
				if(S_ISDIR(bufElt.st_mode))
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



