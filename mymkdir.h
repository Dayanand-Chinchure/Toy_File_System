int mymkdir(char *filename, int curinode)
{
	int i,j,newinode,newdb;
	long int loc1,loc2;
	FILE *disk;
	MyDir dir;
	DiskInode di,new;
	disk = fopen("devfs","r+");
	
  	if(!disk)
	{
	    printf("\nError: Unable to MOUNT ");
	    return -1;
	}
	
	fread(&sb,sizeof(struct superblock),1,disk);	
	fseek(disk,0L,SEEK_SET);

	if(FileS_namei(filename,curinode) !=curinode)
	{
		printf("Error: File or directory name already exists");
		return -1;		
	}  

	newinode=inodealloc();
	newdb=alloc();
	
	if(newinode==-1)
	{
		printf("\nError: Unable to create file");
		return -1;
	}
	if(newdb==-1)
	{
		printf("\nError: Unable to create file, insufficient memory ");
		return -1;
	}

	loc1=((curinode-1)*128)+20180;
	fseek(disk,loc1,SEEK_SET);
	fread(&di,sizeof(struct diskinode),1,disk);
	loc2=(di.db.dblock[0]*4096)+1330900+di.size;	
	fseek(disk,loc2,SEEK_SET);
	dir.inum=newinode;
	dir.lname=strlen(filename);
	strcpy(dir.fname,filename);
	fwrite(&dir,sizeof(struct dir),1,disk);	

	di.size+=sizeof(struct dir);	
	fseek(disk,loc1,SEEK_SET);
	fwrite(&di,sizeof(struct diskinode),1,disk);	
	
	loc1=((newinode-1)*128)+20180;
	fseek(disk,loc1,SEEK_SET);
	new.inum=newinode;		
	strcpy(new.iname,filename);		
	new.type=1;	
	new.number_of_dblock=1;
	new.size=40;	
	new.d_link=0;
	new.db.dblock[0]=newdb;	
	for(j=1;j<10;j++)
		new.db.dblock[j]=-1;
	new.idb=NULL;
	for(j=0;j<48;j++)
		new.future_use[j]='\0';
	fwrite(&new,sizeof(struct diskinode),1,disk);		

	loc2=(newdb*4096)+1330900;
	fseek(disk,loc2,SEEK_SET);

	dir.inum=newinode;
	dir.lname=1;
	strcpy(dir.fname,".");
	fwrite(&dir,sizeof(struct dir),1,disk);	

	dir.inum=curinode;		
	dir.lname=2;
	strcpy(dir.fname,"..");	
	fwrite(&dir,sizeof(struct dir),1,disk);	

	fclose(disk);
	return newinode;
}
