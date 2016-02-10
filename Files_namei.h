int FileS_namei(char path[30],int cur_inode)
{
	int cur_inum=-1,blk_pos,i,j,k,flg=0;
	char temp[10][30];
	DiskInode di[NUM_OF_INODE];
	MyDir dir;
	FILE *fp;	
	fp = fopen("devfs","r");
  	
	if(strcmp(path,"/")==0)
		return sb.root_index;
	if(path[0]=='/')
	{
		for(i=1,k=0,j=0;path[i]!='\0';i++)
		{
			if(path[i]=='/')
			{
				temp[k][j]='\0';
				k++;
				j=0;
				
			}
			else
			temp[k][j++]=path[i];
		}
		temp[k][j]='\0';
		
		cur_inum=sb.root_index;

		
		j=0;		
		while(1)
		{
			fseek(fp,20180L+(cur_inum-1)*128,SEEK_SET); 
			fread(&di[cur_inum-1],sizeof(struct diskinode),1,fp);
		
			blk_pos=di[cur_inum-1].db.dblock[0];
			fseek(fp,1330900+blk_pos*4096,SEEK_SET);
			

			
			do{
				i=fread(&dir,sizeof(MyDir),1,fp);
								
				if(strlen(dir.fname)==0)
				{
					flg=1;
					break;
				}				
				if(strcmp(dir.fname,temp[j])==0)
				{	
					flg=0;
					break;
				}
													
			}while(1);	
			if(flg==1)
			{
				
				return cur_inode;
			}
			if(flg==0)
				cur_inum=dir.inum;
			j++;
			if(j>k)
			{
				
				return cur_inum;
			}
		}					
	}
	else
	{
	for(i=0,k=0,j=0;path[i]!='\0';i++)
		{
			if(path[i]=='/')
			{
				temp[k][j]='\0';
				k++;
				j=0;
				
			}
			else
			temp[k][j++]=path[i];
		}
		temp[k][j]='\0';
		cur_inum=cur_inode;
		j=0;		
		while(1)
		{
			fseek(fp,20180L+(cur_inode-1)*128,SEEK_SET); 	
			fread(&di[cur_inode-1],sizeof(struct diskinode),1,fp);
		
			blk_pos=di[cur_inode-1].db.dblock[0];
			fseek(fp,1330900+blk_pos*4096,SEEK_SET);
			

			
			do{
				i=fread(&dir,sizeof(MyDir),1,fp);
								
				if(strlen(dir.fname)==0)
				{
					flg=1;
					break;
				}				
				if(strcmp(dir.fname,temp[j])==0)
				{	
					flg=0;
					break;
				}
													
			}while(1);	
			if(flg==1)
			{
				
				return cur_inum;
			}			
			if(flg==0)
				cur_inode=dir.inum;
			j++;
			if(j>k)
			{
				
				return cur_inode;
			}
		}				
	
	}		

}

