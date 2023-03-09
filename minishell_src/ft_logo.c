#include "./inc/minishell.h"

extern t_data data;

void    ft_logo(void)
{
    const char *logo;
	
	logo = "\t\t\t\t\t\t\t\t\t\t      |\
	\n|   /██      /██ /██████ /██   /██ /██████  /██████  /██   /██ /████████ /██       /██ \t      |\
	\n|  | ███    /███|_  ██_/| ███ | ██|_  ██_/ /██__  ██| ██  | ██| ██_____/| ██      | ██ \t      |\
	\n|  | ████  /████  | ██  | ████| ██  | ██  | ██  \\__/| ██  | ██| ██      | ██      | ██ \t      |\
	\n|  | ██ ██/██ ██  | ██  | ██ ██ ██  | ██  |  ██████ | ████████| █████   | ██      | ██ \t      |\
	\n|  | ██  ███| ██  | ██  | ██  ████  | ██   \\____  ██| ██__  ██| ██__/   | ██      | ██ \t      |\
	\n|  | ██\\  █ | ██  | ██  | ██\\  ███  | ██   /██  \\ ██| ██  | ██| ██      | ██      | ██ \t      |\
	\n|  | ██ \\/  | ██ /██████| ██ \\  ██ /██████|  ██████/| ██  | ██| ████████| ████████| ████████  |\
	\n|  |__/     |__/|______/|__/  \\__/|______/ \\______/ |__/  |__/|________/|________/|________/  | ";
	printf("\e[32;1m ---------------------------------------------------------------------------------------------\n|\
	%s\n|\t\t\t\t\t\t\t\t\t\t\t      |\n ---------------------------------------------------------------------------------------------\n\n\e[0m", logo);
    
}