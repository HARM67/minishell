#include "minishell.h"

int main()
{
	int rt;
	int	rt2;
	pid_t	father;

	father = fork();
	if (father)
	{
		rt2 = wait(&rt);
		printf("Je suis le pere et le pid de mon fils est %d et il m'a r'envoye %d\n", father, rt);
	}
	else
	{
		sleep(1);
		printf("Je suis le fils\n");
	}
	return (0);
}
