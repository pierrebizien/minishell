#include "./inc/minishell.h"

void    ft_logo(void)
{
    const char *logo;
	logo = "\e[32;1m \
	\n /██      /██ /██████ /██   /██ /██████  /██████  /██   /██ /████████ /██       /██ \
	\n| ███    /███|_  ██_/| ███ | ██|_  ██_/ /██__  ██| ██  | ██| ██_____/| ██      | ██  \
	\n| ████  /████  | ██  | ████| ██  | ██  | ██  \\__/| ██  | ██| ██      | ██      | ██ \
	\n| ██ ██/██ ██  | ██  | ██ ██ ██  | ██  |  ██████ | ████████| █████   | ██      | ██  \
	\n| ██  ███| ██  | ██  | ██  ████  | ██   \\____  ██| ██__  ██| ██__/   | ██      | ██ \
	\n| ██\\  █ | ██  | ██  | ██\\  ███  | ██   /██  \\ ██| ██  | ██| ██      | ██      | ██ \
	\n| ██ \\/  | ██ /██████| ██ \\  ██ /██████|  ██████/| ██  | ██| ████████| ████████| ████████\
	\n|__/     |__/|______/|__/  \\__/|______/ \\______/ |__/  |__/|________/|________/|________/ ";
		printf("%s\n\n----------------------------------------------------------------------------------------------\n\n\e[0m", logo);
    

}