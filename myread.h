int myread(int inode)
{
  int i,j;
  long int loc1,loc2;
  char buff,buff1[4096];
  FILE *disk;
  MyDir dir;
  DiskInode di,new;
  int fs=0,n=0;

  disk = fopen("devfs","r+");
	
  if(!disk)
    {
      printf("\nError: Unable to MOUNT ");
      return -1;
    }
	
  loc1=((inode-1)*128)+20180;
  fseek(disk,loc1,SEEK_SET);
  fread(&di,sizeof(struct diskinode),1,disk);
  if(di.size==0)
    {
      printf("Error: File is Empty!!");
      return 0;
    }
  printf("\nData:\n");
  fs=di.size;
  n=di.number_of_dblock;
  j = 0;	
	
  if(n==1)
    {
      loc2=(di.db.dblock[j]*4096)+1330900;
      fseek(disk,loc2,SEEK_SET);
			
      for(i=0;i<fs;i++)
	{
	  fread(&buff,1,1,disk);	
	  printf("%c",buff);
	}
    }
  else
    {
      for(j=0;j<n-1;j++)
	{
	  loc2=(di.db.dblock[j]*4096)+1330900;
	  fseek(disk,loc2,SEEK_SET);	
	  fread(&buff1,4096,1,disk);	
	  printf("%s",buff1);
	  fs-=4096;
	}			
      loc2=(di.db.dblock[j]*4096)+1330900;
      fseek(disk,loc2,SEEK_SET);
      for(i=0;i<fs;i++)
	{
	  fread(&buff,1,1,disk);	
	  printf("%c",buff);
	}	
    }

  fclose(disk);
  return 0;
}

