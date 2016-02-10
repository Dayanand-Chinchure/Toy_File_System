int alloc()
{

	int i;
	FILE *disk; 
	disk = fopen("devfs","r+");
	
	fread(&sb,sizeof(struct superblock),1,disk);
  	if(!disk)
	{
	    printf("\nError: Unable to MOUNT ");
	    return -1;
	}

	if(sb.no_of_free_dblock==0)
	{
		fclose(disk);	
		return -1;
	}
	for(i=0;i<NUM_OF_DATA_dblock;i++)
		if(sb.free_block_list[i]=='0')
		{
			sb.no_of_free_dblock--;
			sb.free_block_list[i]='1';		
			fseek(disk,0L,SEEK_SET);			
			fwrite(&sb,sizeof(struct superblock),1,disk);
			fclose(disk);
			return i;	 		
		}
}


