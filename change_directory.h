void change_directory(char path[30],int cur_inode)
{
	int blk_pos;
	MyDir dir;
	char par[20],child[20],slash[30];
	DiskInode di[NUM_OF_INODE];	
	cur_inode=FileS_namei(path,cur_inode);
		
	FILE *fp;	
	fp = fopen("devfs","r");
  	
	if(!fp)
	{
	    printf("\nError: Unable to MOUNT ");
	    exit(1);
	}
	
	if(cur_inode==-1)
	{
	
	}
	else
	{

		child[0]='\0';
		
		while(1)
		{
			strcpy(slash,"/");
			fseek(fp,20180L+(cur_inode-1)*128,SEEK_SET); 	// 20180 start of Inode list, +128 for next Inode structure
				
			fread(&di[cur_inode-1],sizeof(DiskInode),1,fp);

			
			if(di[cur_inode-1].type!=1)
			{
				printf("\nInvalid directory\n");
				break;

			}
			strcpy(par,di[cur_inode-1].iname);
			
			strcat(slash,par);
			strcpy(par,slash);
			strcat(par,child);
			strcpy(child,par);
			blk_pos=di[cur_inode-1].db.dblock[0];
			
			
			
			fseek(fp,1330900+blk_pos*4096+sizeof(MyDir),SEEK_SET);
			
			fread(&dir,sizeof(MyDir),1,fp);	
	
			
			
			cur_inode=dir.inum;
			
			if(cur_inode==1)
				break;			
		}
		
		strcpy(par,"root");
		strcat(par,child);
		strcpy(cmdprompt,par);	

	}	
}

