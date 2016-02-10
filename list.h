void list(int cur_inode)
{
	int blk_pos,blk1;
	MyDir dir;
	char par[20],child[20],slash[30];
	DiskInode di[NUM_OF_INODE],td;	
	FILE *fp,*fp1;	
	fp = fopen("devfs","r");
  	
	if(!fp)
	{
	    printf("\nError: Unable to MOUNT ");
	    exit(1);
	}
		fseek(fp,20180L+(cur_inode-1)*128,SEEK_SET); 	
		
		
		
			fread(&di[cur_inode-1],sizeof(struct diskinode),1,fp);
		
			blk_pos=di[cur_inode-1].db.dblock[0];
			fseek(fp,1330900+blk_pos*4096,SEEK_SET);
			

			printf("Name\t\tInode\ttype\n-------------------------------------");
			do{
				fread(&dir,sizeof(MyDir),1,fp);
				if(strlen(dir.fname)==0)
				{
					break;
				}

				printf("\n%s \t\t%d",dir.fname,dir.inum);
				fp1 = fopen("devfs","r");
				fseek(fp1,20180L+(dir.inum-1)*128,SEEK_SET);	
				fread(&td,sizeof(struct diskinode),1,fp1);			
				printf("\t%d",td.type);
				fclose(fp1);
																	
			}while(1);	
		

}

