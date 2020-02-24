/*
 * interpreter.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Omar Yunus
 */
#include "interpreter.h"
#include "shellmemory.h"
#include "kernel.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
int num_P_exec=0;
char **tokenize(char *str)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr =
        (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }

    return ret_arr;
}

int in_file_flag = 0;
int interpret(char *raw_input);

int help()
{
    printf(""
           "COMMAND         DESCRIPTION\n"
           "help            Displays all the commands\n"
           "quit            Exits / terminates the shell with \"Bye!\"\n"
           "set VAR STRING  Assigns a value to shell memory\n"
           "print VAR       Displays the STRING assigned to VAR\n"
           "run SCRIPT.TXT  Executes the file SCRIPT.TXT\n");
    return 0;
}

int quit()
{
    printf("Bye!\n");
    if (in_file_flag == 0)
    {
        shell_memory_destory();
        exit(0);
    }
    return 0;
}

int run(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Script not found.\n");
        return 1;
    }
    int enter_flag_status = in_file_flag;
    in_file_flag = 1;
    while (!feof(file))
    {
        char *line = NULL;
        size_t linecap = 0;
        getline(&line, &linecap, file);

        int status = interpret(line);
        free(line);
        if (status != 0)
        {
            break;
            return status;
        }
    }
    fclose(file);
    in_file_flag = enter_flag_status;
    return 0;
}

int set(const char *key, const char *value)
{
    int status = shell_memory_set(key, value);
    if (status != 0)
        printf("set: Unable to set shell memory.\n");
    return status;
}
int exec(char *programs[],int numProg)//one program exec (have 3 exec functions
{
if(numProg==1){
	printf("One program: %s \n",programs[1]);}
else if(numProg==2){
	printf("The 2 programs are \n %s \n %s \n",programs[1],programs[2]);
}
else if(numProg==3){
	printf("The 3 programs are \n %s \n %s \n %s \n",programs[1],programs[2],programs[3]);
}
else{

}
    return 0;
}





int print(const char *key)
{
    const char *value = shell_memory_get(key);
    if (value == NULL)
    {
        printf("print: Undefiend value.\n");
        return 1;
    }
    printf("%s\n", value);
    return 0;
}

int interpret(char *raw_input)
{
    char **tokens = tokenize(raw_input);

    if (tokens[0] == NULL)
        return 0; // empty command

    if (strcmp(tokens[0], "help") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("help: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(tokens);
        return help();
    }

    if (strcmp(tokens[0], "quit") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("quit: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(raw_input);
        free(tokens);
        return quit();
    };

    if (strcmp(tokens[0], "set") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL))
        	//Error checking validation
        {
            printf("set: Malformed command\n");
            //printf("token1 %s token 2 %s",tokens[1],tokens[2]);
            free(tokens);
            return 1;
        }
        int status = set(tokens[1], tokens[2]);
        free(tokens);
        return status;
    }
    if (strcmp(tokens[0], "exec") == 0)
    {
    	num_P_exec=0;
    	int status=0;

            if ((tokens[1] != NULL && tokens[2] == NULL))
            {
            	num_P_exec=1;
                //printf("set: Malformed command\n");
                //printf("token1 %s token 2 %s",tokens[1],tokens[2]);
            }
            else if ((tokens[1] != NULL) && (tokens[2] != NULL)&&(tokens[3] == NULL)&&(strcmp(tokens[1], strdup(tokens[2]))==0))
                                    {
                                    	status=1;
                                    	printf("Error: Script %s already loaded",tokens[1]);
                                    	free(tokens);
                                    	return status;
                                    	//num_P_exec=2;
                                        //printf("set: Malformed command\n");
                                        //printf("token1 %s token 2 %s",tokens[1],tokens[2]);
                                    }
            else if ((tokens[1] != NULL) && (tokens[2] != NULL)&&(tokens[3] == NULL))
                        {
                        	num_P_exec=2;
                            //printf("set: Malformed command\n");
                            //printf("token1 %s token 2 %s",tokens[1],tokens[2]);
                        }
            else if ((tokens[1] != NULL) && (tokens[2] != NULL) && (tokens[3]!=NULL)&&((strcmp(tokens[1],strdup(tokens[2]))==0)||(strcmp(tokens[1],strdup(tokens[3]))==0)||(strcmp(tokens[3],strdup(tokens[2]))==0))){
            	//num_P_exec=3;
            	status=1;
            	if((strcmp(tokens[1],strdup(tokens[2]))==0)||(strcmp(tokens[1],strdup(tokens[3]))==0)){
            		printf("Error: Script %s already loaded",tokens[1]);//12,13
            	}
            	else{
            		printf("Error: Script %s already loaded",tokens[2]);//23
            	}

            	free(tokens);
            	return status;
            }

            else if ((tokens[1] != NULL) && (tokens[2] != NULL) && (tokens[3]!=NULL))
                                    {
                                    	num_P_exec=3;
                                        //printf("set: Malformed command\n");
                                        //printf("token1 %s token 2 %s",tokens[1],tokens[2]);
                                    }
            else{
            	status=1;
            	printf("error");
            }
            if(status!=1){
            	status = exec(tokens,num_P_exec);
            	free(tokens);
            }

            return status;
        }

    if (strcmp(tokens[0], "print") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("print: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = print(tokens[1]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "run") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("run: Malformed command\n");
            free(tokens);
        }
        int result = run(tokens[1]);
        free(tokens);
        return result;
    }

    printf("Unrecognized command \"%s\"\n", tokens[0]);
    free(tokens);
    return 1;
}

