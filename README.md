nm -u pour voir fonctions externes

ps -ax | grep minishell
18818 pts/1    S+     0:00 /usr/bin/valgrind.bin --leak-check=full ./minishell
18856 pts/0    S+     0:00 grep --color=auto minishell
user42@salty-VirtualBox:~/Documents$ kill -3 18818