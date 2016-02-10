void mountFS(int sizeinmb,int blksize)
{
	FILE *fp,*fp1;
	  
	int i,j;
	int no_of_inodes,size_on_disk_inodes,size_on_disk_blk,size_of_inodestruct;
	  
	DiskInode di[NUM_OF_INODE];
	MyDir rt;
	  
	fp1 = fopen("devfs","r+");
  	if(!fp1)
	{
	    printf("\n Error : Unable to MOUNT ");
	    exit(1);
	}
	fread(&sb,sizeof(struct superblock),1,fp1);
	printf("%d",sb.fs_size);
	if(sb.fs_size==0)
	{
		fp = fopen("devfs","w+");
		
		sb.fs_size = sizeinmb*1024*1024;
		sb.no_of_free_dblock = NUM_OF_DATA_dblock;		
		sb.no_of_free_inodes_disk = NUM_OF_INODE;		
		size_on_disk_inodes = sb.no_of_free_inodes_disk   / blksize;
		size_on_disk_blk    = sb.no_of_free_dblock / blksize;
		size_of_inodestruct = sb.no_of_free_inodes_disk*128 / blksize;
		sb.disk_inode_list_size = INODE_TABLE_SIZE;
		printf("\nsize in mb for File System = %f\n", (float)(24+(size_on_disk_inodes+size_on_disk_blk+size_of_inodestruct)*blksize)/(1024*1024));  

	  	
		
		i=0;  	
		sb.free_block_list[i] = '1';
		for(i=1;i<sb.no_of_free_dblock;i++)    
		{
			sb.free_block_list[i] = '0';
		
		}
	
		i=0;
		sb.free_inode_list[i] = '1';
		for(i=1;i<sb.no_of_free_inodes_disk;i++)    
		{
			sb.free_inode_list[i] = '0';
		
		}
	
		sb.no_of_free_dblock--;	
		sb.no_of_free_inodes_disk--;
		sb.root_index=1;		
			
		fwrite(&sb,sizeof(struct superblock),1,fp);
			
		i=0;
		di[i].inum=1;		
		strcpy(di[i].iname,"root");		
		di[i].type=1;
		di[i].number_of_dblock=1;
		di[i].size=40;
		di[i].d_link=0;
		di[i].db.dblock[0]=0;	
		for(j=1;j<10;j++)
			di[i].db.dblock[j]=-1;
		di[i].idb=NULL;
		for(j=0;j<48;j++)
			di[i].future_use[j]='\0';
		
		fwrite(&di[i],sizeof(struct diskinode),1,fp);
		
		
		for(i=1;i<NUM_OF_INODE;i++)    
		{
			di[i].inum=i+1;
			strcpy(di[i].iname,"\0");	
			di[i].type=-1;
			di[i].number_of_dblock=0;
			di[i].size=0;
			di[i].d_link=0;
		
		

			for(j=0;j<10;j++)
			{
				di[i].db.dblock[j]=-1;
			
			}
			di[i].idb=NULL;
		
			for(j=0;j<48;j++)
				di[i].future_use[j]='\0';
		
			fwrite(&di[i],sizeof(struct diskinode),1,fp);
		}
	
		
		rt.inum=1;
		rt.lname=1;
		strcpy(rt.fname,".");		
		fwrite(&rt,sizeof(struct dir),1,fp);

		rt.inum=1;
		rt.lname=2;
		strcpy(rt.fname,"..");		
		fwrite(&rt,sizeof(struct dir),1,fp);
	
		fseek(fp,(blksize-(sizeof(struct dir)*2)),SEEK_CUR);		
		
		for(i=0;i<9912*4096;i++)
		{
			fprintf(fp,"%c",'\0');
		}
		printf("\nFILE INITIALIZED\n");
		fclose(fp);
	}
	else
		printf("\nFILE LOADED\n");
		fclose(fp1);
}

