#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define NUM_OF_DATA_dblock 9913
#define NUM_OF_INODE 10240
#define INODE_TABLE_SIZE 320 
#define TOTAL_dblock 10240
#define BLOCK_SIZE 4096		 
#define DIRECTORY_SIZE 10		
char cmdprompt[30];

typedef struct datablock
{
  unsigned int dblock[10];
}DataBlock;

typedef struct diskinode{
  int inum;
  int type;     	
  int number_of_dblock;     
  unsigned int size;        
  DataBlock db;           
  DataBlock *idb;          
  short int d_link;
  char iname[16];
  char future_use[48];
}DiskInode;

typedef struct dir{
  short int inum;
  short int lname;
  char fname[16];
}MyDir;

MyDir currentDir;

typedef struct superblock
{
	char free_block_list[NUM_OF_DATA_dblock];
  	char free_inode_list[NUM_OF_INODE];
  	int fs_size;
  unsigned int no_of_free_dblock;
  unsigned int disk_inode_list_size;
  unsigned int no_of_free_inodes_disk;
  	   int flag;
  	   int root_index;
 
}SuperBlock;
SuperBlock sb;
