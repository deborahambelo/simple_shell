#ifndef __SHELL_H
#define __SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
/* open */
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/* FLAGS */
#define F_BUFF 1
#define F_CMD_L 2
#define F_CMDS 4

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/*linked lists*/
size_t display_list(const list_t *lst)
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);

char *get_first_av(void);

/*function with all the logical part that will work with the main */
int execcmd(char *input, char **cmdList,
                    char *cmd, int __attribute__((unused))read, char *firstArg);
void semi_op(char *input, int read, char *firstArg);
void LogicalOr(char *inputSemicolon, int read, char *firstArg);
int LogicalAnd(char *inputOr, int read, char *firstArg, int prevFlag);
/* Special functions */
void __attribute__((constructor)) allocate_dynamic_environ(void);
void __attribute__((destructor)) deallocate_dynamic_environ(void);

char *_getenv(char *name);

/* replacement variables */
void handle_var_replacement(char **commands);
int *process_exit_code();
void set_process_exit_code(int code);

/* builtins */
void env(void);
int _setenv(char *name, char *value);
int _unsetenv(char *name);
int _cd(char *path);
int _alias(char **commands);
int _help(char **commands);
int _history(void);
/* helper global vars builtin functions */
list_t **get_alias_head();
list_t **get_history_addrss();
list_t **get_last_cmd_addrss();
void handle_history(char *buff);
void free_history(void);
void write_history(void);
void update_count_lines(void);
int *get_history_lines_count();

/* builtins utils */
int validate_env_name(char *name);
int is_valid_env_var_name(char *name);
int get_env_index(char *name);
void set_alias(char *alias_pair);
int is_set_alias(char *alias_pair);
int handle_alias_args(char **commands, list_t **out_addrs);
/* functions that is part of help */
int read_line(const int fd, char **line);
int f_read_line(char **str, char **line, int fd);

/* own implementations */
char *_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *stream);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);

/* Command handlers */
int pathhandler(char **commands);
char *get_path(char *dir, char *filename);
char **parse_input(char *input, char *delimiter);
int count_args(char *input, char *delimiter);

/* Memory management */
void *alloc_mem(unsigned int bytes);
char *dup_str(char *s);
void free_dbp(char **dp);
void release_memory(char *buffer, char **cmds_list, char **cmd_args, int flags);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);   ???

/* handle_builtins */
int processBuiltins(char **args);

/* handle_enter */
int is_empty_command(char **commands);
/* handle comments in input */
char *rmvcom(char *input);

/* Exit handlers */
int check_exit_cmd(char *user_input, char **cmds_list, char **user_cmds);
int calcstatus(char *input_buffer);

/* Error handlers */
void dispatch_error(char *msg);
void pbuiltin_err(char *error_msg, char *argument);

/* strings functions */
int get_string_length(const char *str);
char *duplicate_string(const char *str);
char *find_character(const char *str, int ch);
char *concatenate_strings(char *dest, const char *src);
char *concatenate_strings_n(char *dest, const char *src, size_t n);
int compare_strings(const char *str1, const char *str2);
char *number_to_string(int num);
int comp_nstrings(const char *str1, const char *str2, size_t n);
int _puts(char *str);  ???

/* strings01 */
char *string_concat(char const *str1, char const *str2);
char *string_subtract(char const *str, unsigned int start, size_t length);
void free_memory(void **array);
void delete_string_array(char **array);

/*dollSpecial*/
void ExitcodeProSet(int program);

/*Get_history_lines_count*/
void adjust_COUNTLINE(void);

/*Handle_var_replacement*/
void process_VariableReplace(char **c_md);

/*help*/
int rd_ln(const int fd, char **ln);
int     f_read_line(char **str, char **ln, int fd);
int _help(char **command);

/*Own_memory*/
void *_realloc(void *data_ptr, unsigned int previous_size,
                unsigned int updated_size);

/*puts*/
int _print_str(char *str);

/*Strcpy*/
char *_strcpy(char *dest, char *src);

/*Strncpy*/
char *bounded_strncpy(char *dest, char *src, int n);

/*Strtok*/
char *_strtok(char *str, char *delimiter);
int is_delimiter_char(char b, char *delimiter);

/*Write_history*/
void write_history(void);

#endif /* __SHELL_H */
