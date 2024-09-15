# myls
My own implementation of some of the functionality of the `ls` function in the linux terminal

It supports all of the following options `-atucifd1`

## Compilation Command
`gcc myls.c util.c -o myls`

## Example Output
``` 
omar@Ubuntu22:~/Desktop/myls/proj$ gcc myls.c util.c -o myls
omar@Ubuntu22:~/Desktop/myls/proj$ ./myls /home/omar . -lif
/home/omar:
786438  drwx------ 5 omar omar 4096  18:16 05 يول snap         
786527  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Music        
786522  drwxr-xr-x 9 omar omar 4096  17:34 10 سبت Desktop      
786528  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Pictures     
786524  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Templates    
786523  drwxr-xr-x 2 omar omar 4096  17:40 10 سبت Downloads    
786526  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Documents    
786525  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Public       
797510  -rw-rw-r-- 1 omar omar 41    17:24 16 يول githubtoken  
786529  drwxr-xr-x 2 omar omar 4096  20:47 28 يون Videos       

.:
806397  -rwxrwxr-x 1 omar omar 21872 04:53 15 سبت myls    
806156  -rw-rw-r-- 1 omar omar 3738  04:42 15 سبت myls.c  
806150  -rw-rw-r-- 1 omar omar 4788  04:44 15 سبت util.c  
806149  -rw-rw-r-- 1 omar omar 1060  04:41 15 سبت util.h  

omar@Ubuntu22:~/Desktop/myls/proj$
```
           
