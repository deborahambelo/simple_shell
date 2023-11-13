#include "shell.h"

void Aliases(char **cmds);
void CmdNotFound(char *input, char **cmdList, char **cmds,
                       char *firstArg);
/**
 *  semi_op- Handle semicolon and logical op
 * @input: first buffer that functions read
 * @read: return of read (open with getline)
 * @firstArg: av[0]
 * Return: 0 on success
*/
void semi_op(char *input, int read, char *firstArg)
{
    char **cmdList = NULL;

    execcmd(input, cmdList, input, read, firstArg);
}
/**
 * LogicalOr - Handle || logical part
 * @inputSemicolon: first buffer that functions read
 * @read: return of read (open with getline)
 * @firstArg: av[0]
 * Return: 0 on success
*/
void LogicalOr(char *inputSemicolon, int read, char *firstArg)
{
    int i, flag, prevFlag = -1;
    char **cmdList2 = parse_input(inputSemicolon, "||");

    for (i = 0; cmdList2[i] != NULL; i++)
    {
        flag =  LogicalAnd(cmdList2[i], read, firstArg, prevFlag);
        prevFlag = flag;
    }
    free_dbp(cmdList2);
}
/**
 * LogicalAnd - Handle && logical part
 * @inputOr: first buffer that functions read
 * @read: return of read (open with getline)
 * @firstArg: av[0]
 * @prev_flag: last flag of ||, it is important to print or not
 * Return: 0 on success
*/
int LogicalAnd(char *inputOr, int read, char *firstArg, int prevFlag)
{
    int j = 0, flag = 1;
    char **cmdList3 = parse_input(inputOr, "&&");

    if (prevFlag == 0)
    {
        j++;
        if (cmdList3[j] == NULL)
            return (-1);
    }

    for (; cmdList3[j] != NULL; j++)
    {
        flag = execcmd(inputOr, cmdList3,
                               cmdList3[j], read, firstArg);
        prevFlag = flag;
    }
    free_dbp(cmdList3);
    return (flag);
}

int execcmd(char *input, char **cmdList,
                    char *cmd, int __attribute__((unused))read, char *firstArg)
{
    char **cmds;
    int childPid, err = 0, flag = 0, *status = processExitCode();

    cmds = parse_input(cmd, " ");
    handleVarReplacement(cmds);
    Aliases(cmds);

    if (check_exit_cmd(input, cmdList, cmds) == -1 ||
        is_empty_command(cmds) == 1 ||
        processBuiltins(cmds) == 1)
    {
        free_dbp(cmds);
        return (-1);
    }

    childPid = fork();
    if (childPid == -1)
    {
        release_memory(input, cmdList, cmds, F_BUFF | F_CMD_L | F_CMDS);
        err_dispatch(firstArg);
    }
    else if (childPid == 0)
    {
        err = handlePath(cmds);
        execve(cmds[0], cmds, __environ);
        if (err != 0)
            CmdNotFound(input, cmdList, cmds, firstArg);
        release_memory(input, cmdList, cmds, F_BUFF | F_CMD_L | F_CMDS);
        err_dispatch(firstArg);
    }
    wait(status);
    *status = WEXITSTATUS(*status);
    if (*status == 2)
        ExitcodeProSet(127);
    free_dbp(cmds);
    return (flag);
}

void CmdNotFound(char *input, char **cmdList, char **cmds,
                       char *firstArg)
{
    setProcessExitCode(127);
    write(2, firstArg, get_string_length(firstArg));
    write(2, ": 1: ", 5);
    write(2, cmds[0], get_string_length(cmds[0]));
    write(2, ": not found\n", 12);
    release_memory(input, cmdList, cmds, F_BUFF | F_CMD_L | F_CMDS);
    exit(127);
}
