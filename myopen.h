int myopen(char *filename ,int curinode)
{
  int inode;
  inode=FileS_namei(filename,curinode);
	if(inode==-1)
		{
				printf("Error: File or directory name already exists");
				return -1;		
		}  
	return inode;
}


