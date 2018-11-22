#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

void no_new_line (char * current_line){
char line_len=strlen(current_line);
    if(current_line[line_len-1] == '\n'){
        current_line[line_len-1] = '\0';
    }
}

void program_error (){
	char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}


int main (int argc, char *argv[]){

char *current_line;
size_t store = 100;
char *bin_ = "/bin/";
char *user = "/usr/bin/";
char *args[100];

current_line = (char *)malloc(store * sizeof(char));

    if( argc == 1) {
        
        while(1) {
            printf("wish> ");
            getline(&current_line, &store, stdin);
		 	no_new_line(current_line);
            int i =0;
            char *token = strtok(current_line, " ");
            char *lists[5] ={NULL,NULL, NULL, NULL, NULL};
            	
            	while(token != NULL){
                	args[i] = token;
                	i =i +1;
                	token = strtok(NULL, " ");
									}
               	
               	for(int j=1; j<i;j++){
                    lists[j]=args[j];
                          			}
                          
                char  *path_A = malloc(strlen(bin_)+ strlen(args[0]) +1 ); 
                strcat(path_A, bin_);
                strcat(path_A,args[0]); 
                char  *path_B = malloc(strlen(user)+ strlen(args[0]) +1 );
                strcat(path_B, user);
                strcat(path_B, args[0]);
            

                if(strcmp(args[0],"exit")==0){
                    exit(0);
                         					}
                else if(strcmp(args[0],"cd")==0){
	                if (chdir(args[1])==0){
	                    printf("%s\n","you entered the folder" );
	                             			}
                    else{
	                    program_error(); 
	                    }
                         						}
                else {
			        pid_t pid = fork();
			        if(pid==0){
			            if(access(path_A,X_OK)==0){
			                lists[0]=path_A;
			                int fd = open("test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							dup2(fd, 1);   
							dup2(fd, 2);   
							close(fd);
							execv(path_A,lists);
			                    				}
			            else if(access(path_B,X_OK)==0){
			                lists[0]=path_B;                        
			                execv(path_B,lists);
			                    }
			            else{
			                program_error(); 
			                }
			               	  }
			        else{
			            wait(NULL);
			            }
                     }
				}
        
					}
    
    else if(argc == 2){
        FILE *fp = fopen(argv[1], "r"); 
		
		if (fp == NULL){ 			
			printf("File is empty\n");
			return 0;
			   }
		else{
			
			while(getline(&current_line, &store, fp) != -1){ 
			 no_new_line(current_line);
                int i =0;
                char *token = strtok(current_line, " ");
                char *lists[5] ={NULL,NULL, NULL, NULL, NULL};
              	
              	while(token != NULL){
                  args[i] = token;
                  i =i +1;
                  token = strtok(NULL, " ");
              						}
                
                for(int j=1; j<i;j++){
                     lists[j]=args[j];
                          			 }
                    
                char  *path_A = malloc(strlen(bin_)+ strlen(args[0]) +1 ); 
                strcat(path_A, bin_);
                strcat(path_A,args[0]); 
                char  *path_B = malloc(strlen(user)+ strlen(args[0]) +1 );
                strcat(path_B, user);
                strcat(path_B, args[0]);
            

                if(strcmp(args[0],"exit")==0){
                             exit(0);
                         						}
                else if(strcmp(args[0],"cd")==0){
	                if (chdir(args[1])==0){
	                    printf("%s\n","Folder opened" );
	                             			}
                    else{
	                    program_error();
	                    }
                         						}
                else {
			        pid_t pid = fork();
			        if(pid==0){
			            if(access(path_A,X_OK)==0){
			                lists[0]=path_A;
			                execv(path_A,lists);
			                    				}
			            else if(access(path_B,X_OK)==0){
			                lists[0]=path_B;                        
			                execv(path_B,lists);
			                    }
			            else{
			                printf("%s\n","No access for paths" );
			                    }
			                }
			        else{
			            wait(NULL);
			                }
                         }
	}
}

fclose(fp); 		
}

return 0;
}
