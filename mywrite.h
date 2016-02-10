int mywrite(int inode)
{
  int i,j,fs,n,k;
  long int loc1,loc2;
  char buff[4096];
  FILE *disk;
  MyDir dir;
  DiskInode di,new;
	
  disk = fopen("devfs","r+");
	
  if(!disk)
    {
      printf("\nError: Unable to MOUNT ");
      return -1;
    }
	
  loc1=((inode-1)*128)+20180;
  fseek(disk,loc1,SEEK_SET);
  fread(&di,sizeof(struct diskinode),1,disk);
 

  k=0;
  loc2=(di.db.dblock[k]*4096)+1330900;
  fseek(disk,loc2,SEEK_SET);
  printf("\nEnter Data:\n");
  i=0;	
  while(1)
    {
      buff[i]=getchar();
      if(buff[i]==EOF)
				break;	
      i++;		
      if(i==4096)
			{	
			  loc2=(di.db.dblock[k]*4096)+1330900;
			  fseek(disk,loc2,SEEK_SET);
			  fwrite(&buff,4096,1,disk);
			  k++;			
			  j=alloc();
			  if(j==-1)
			    {
			      printf("\nError: Unable to create file, insufficient memory ");
			      return -1;
			    }
			  di.db.dblock[k]=j;
			  di.number_of_dblock++;
			}				
 		}
  loc2=(di.db.dblock[k]*4096)+1330900;
  fseek(disk,loc2,SEEK_SET);	
  fwrite(&buff,i,1,disk);	
	
  di.size=(k*4096)+i;	
  loc1=((inode-1)*128)+20180;
  fseek(disk,loc1,SEEK_SET);
  fwrite(&di,sizeof(struct diskinode),1,disk);
 
	
  fclose(disk);
  return 0;

}


