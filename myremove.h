int myremove(char *filename, int curinode)		
{
	int i,j,inode,n;
	long int loc1,loc2;
	FILE *disk,*disk1;

	MyDir new,dir,blank;
	DiskInode di,cur;
		
       	if(strcmp(filename,"..")==0 || strcmp(filename,".")==0)
	{
		printf("\nError: cannot remove '%s': Is a directory",filename);		
		return -1;
	}

	inode= FileS_namei(filename,curinode); 
	if(inode==-1)
		{
			printf("\nError: cannot remove : No such file or directory");
			return -1;		
		}

  disk = fopen("devfs","r+");

  if(!disk)
    {
      printf("\nError: Unable to MOUNT ");
      return -1;
    }
	
	loc1=((inode-1)*128)+20180;
  	fseek(disk,loc1,SEEK_SET);
  	fread(&di,sizeof(struct diskinode),1,disk);
	if(di.type!=2)
	{
		printf("\nError: File is not regular file, unable to delete");		
		return -1;
	}	
	printf("\nDo you want to remove regular file '%s'? (y/n) ",filename);
	fflush(NULL);	
	if(getchar()=='y')
		{
	 		n=di.number_of_dblock;
			for(i=0;i<n;i++)
				datafree(di.db.dblock[i]);
			inodefree(inode); 
			loc1=((curinode-1)*128)+20180;
 			fseek(disk,loc1,SEEK_SET);
  		fread(&cur,sizeof(struct diskinode),1,disk);
			loc2=(cur.db.dblock[0]*4096)+1330900;
  		fseek(disk,loc2,SEEK_SET);	
			
			
	
			blank.inum=-1;
			blank.lname=0;
			strcpy(blank.fname,"\0");
			while(1)
			{				
				fread(&dir,sizeof(struct dir),1,disk);
				if(dir.inum==inode)				
				{
					

					while(1)
					{
						fread(&dir,sizeof(struct dir),1,disk);
						
							fseek(disk,-40L,SEEK_CUR);
							fwrite(&dir,sizeof(struct dir),1,disk);
							fwrite(&blank,sizeof(struct dir),1,disk);
							
						if(dir.lname==0)
							break;
					}
					cur.size=cur.size-20;
										
					loc1=((curinode-1)*128)+20180;
				 	fseek(disk,loc1,SEEK_SET);
		  			fwrite(&cur,sizeof(struct diskinode),1,disk);
					
					fclose(disk);
					return 0;
				}		
			}
		}
		fclose(disk);
		return 0;							
}

