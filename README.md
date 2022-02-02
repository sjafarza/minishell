nm -u pour voir fonctions externes

ps -ax | grep minishell
18818 pts/1    S+     0:00 /usr/bin/valgrind.bin --leak-check=full ./minishell
18856 pts/0    S+     0:00 grep --color=auto minishell
user42@salty-VirtualBox:~/Documents$ kill -3 18818


export pwett="  ''$pwett "
echo $pwett

export A='      bonjour je suis splited '
echo @$A@

export A=a B=b C=c
env
unset A  B C
env
export "d$e"=ert

export "d"=ert
export "d$"=ert

echo 1 | cat | echo 2 | cat

1;$?;0;2;1

unset PATH
export PATH=/home/user42/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

export E=e HO=ho

$E'c'"$HO"