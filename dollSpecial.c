#include "shell.h"

static int EXIT_CODE;
static int initialExitMis = 1;

/**
 * ExitcodePro - this program gets the address at
 * which EXIT_CODE is stored returned
 * Return: it returns the EXIT_CODE variable addrez
*/

int *ExitcodePro()
{
	if (initialExitMis)
	{
		EXIT_CODE = 0;
		initialExitMis = 0;
	}

	return (&EXIT_CODE);
}

/**
 * ExitcodeProSet - this program sets the value for EXIT_CODE variable
 * @program: parameter for number representing exit code
*/

void ExitcodeProSet(int program)
{
	EXIT_CODE = program;
}
