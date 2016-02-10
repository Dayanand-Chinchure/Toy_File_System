
File system Description :

                                          
                                         ----------------------------
                                           OVERVIEW OF FILE SYSTEM
                                         ---------------------------- 
     ______________________________________________________________________________________________________________
     |	    | 		|	    |			|							  |
     |	SB  |   Block	|   Inode   |	  Inode 	|		        Data Block			  |
     |	    |	Array	|   Array   |	Structures	|							  |			  
     |______|___________|___________|___________________|_________________________________________________________|
     
        24      9913        10240         1269760                                 40603648          (* size in bytes)
        
        
File system specification : (* size in bytes)

	1) 1 Block_size = 4096
	2) 1 Inode Structure_size = 124
	3) Max file_size =  
		        a) 1 Direct data_block structure + pointer to extended data_block = 2
		        b) Max blocks allocate = 10 
                        c) 1 Block_size = 4096 
                      = (2*10*4096)
                      = 81920  
                      
        4) Max file count = Total number of blocks
        5) Max files in 1 directory   
               = (Max size of 1 file) / (size of  1 directory structure)
               = 81920 / 20
               = 4096 files in 1 Directory (Max)
               
        6) Max Directory count = 9913
                      
	
Calculation : 

	1) Total file system size = 41943040
	
	2) 1 Block_size = 4096
	
	3) Total number of blocks 
	       = (Total file system size) / (size of 1 block)
	       = 41943040 / 4096
	       = 10240 blocks
	       
	4) Total number of Inodes = Total number of blocks
	
	5) Total number of blocks for file system 
	       = (Super block_size + Indoe structure_size) / (1 block size)
	       = 1289937 / 4096
	       = 315 blocks
	
	6) Total Data block size 
	       = (Total file system size ) - (Super block_size + Indoe structure_size)
	       = 41943040 - 1289937
	       = 40603648 
	       = 38.72 MB              
	    
	7) Offset
	
		a) Superblock offset = 0
		b) Block array offset = 23
		c) Inode array offset = 9936
		d) Inode structure offset = 20180
		e) Data block offset = 30139                       
