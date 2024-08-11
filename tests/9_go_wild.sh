# **************************************************************************** #
#                                     WILD                                     #
# **************************************************************************** #

ls | wc -l | xargs echo

yes "no" | head -n 10

/bin/echo -e "\033[33mHello, world!\033[0m"

/bin/echo '\1$42' > tmp_redir_out
ls -la | grep tmp_redir_out | awk '{print $1 $2}'
cat -e tmp_redir_out
rm tmp_redir_out

sleep 0 | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat

>tmp_out | echo 1
cat tmp_out
rm -f tmp_out

echo 1 | >tmp_out
cat tmp_out
rm -f tmp_out

grep 1 < filedoesnotexist | echo 1 | grep 1 | head -1 | cat | ls

/usr/bin/env -i bash -c "env" | wc -l

echo 'echo $1' > tmp_test_sh
bash tmp_test_sh $test
echo 'echo $2' > tmp_test_sh
bash tmp_test_sh $test
rm -f tmp_test_sh

export pipe_var=1 | echo $pipe_var
echo $pipe_var

echo $PATH
echo $HOME
unset PATH HOME
echo $PATH
echo $HOME

echo "env | /usr/bin/wc -l" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "ls" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "unset PATH" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit.

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit.
 
echo hello world

echo "hello world"

echo 'hello world'

echo hello'world'
echo hello""world
echo ''

echo "$PWD"

echo '$PWD'

echo "aspas ->'"

echo "aspas -> ' "

echo 'aspas ->"'

echo 'aspas -> " '

echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<"

echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'

echo "exit_code ->$? user ->$USER home -> $HOME"

echo 'exit_code ->$? user ->$USER home -> $HOME'

echo "$"

echo '$'

echo $

echo $?

echo $?HELLO

pwd

pwd oi.

export hello

export HELLO=123

export A-

export HELLO=123 A

export HELLO="123 A-"

export hello world

export HELLO-=123

export =

export 123

unset

unset HELLO

unset HELLO1 HELLO2

unset HOME

unset PATH

unset SHELL

cd $PWD

cd $PWD hi 

cd 123123

exit 123

exit 298

exit +100

exit "+100"

exit +"100"

exit -100

exit "-100"

exit -"100"

exit hello

exit 42 world

$PWD

$EMPTY

$EMPTY echo hi

./test_files/invalid_permission

./missing.out

missing.out

"aaa"

test_files

./test_files

/test_files

minishell.h

$

$?

README.md

unset HELLO=

unset  A-

export HELLO=123 A- WORLD=456

unset  HELLO A- WORLD

export UNO=1 DOS-2 TRES=3 || env | grep TRES

export | sort | grep -v SHLVL | grep -v "declare -x _" | grep -v "PS.="

exit 9223372036854775807

exit 9223372036854775808

exit -9223372036854775807

exit -9223372036854775808

exit -9223372036854775809

env | sort | grep -v SHLVL | grep -v ^_

cat ./test_files/infile_big | grep oi

cat minishell.h | grep ");"$

export GHOST=123 | env | grep GHOST

grep hi <./test_files/infile

grep hi "<infile" <         ./test_files/infile

echo hi < ./test_files/infile bye bye

grep hi <./test_files/infile_big <./test_files/infile

echo <"./test_files/infile" "bonjour       42"

cat <"./test_files/file name with spaces"

cat <./test_files/infile_big ./test_files/infile

cat <"1""2""3""4""5"

echo <"./test_files/infile" <missing <"./test_files/infile"

echo <missing <"./test_files/infile" <missing

cat <"./test_files/infile"

echo <"./test_files/infile_big" | cat <"./test_files/infile"

echo <"./test_files/infile_big" | cat "./test_files/infile"

echo <"./test_files/infile_big" | echo <"./test_files/infile"

echo hi | cat <"./test_files/infile"

echo hi | cat "./test_files/infile"

cat <"./test_files/infile" | echo hi

cat <"./test_files/infile" | grep hello

cat <"./test_files/infile_big" | echo hi

cat <missing

cat <missing | cat

cat <missing | echo oi

cat <missing | cat <"./test_files/infile"

echo <123 <456 hi | echo 42

ls >./outfiles/outfile01

ls >         ./outfiles/outfile01

echo hi >         ./outfiles/outfile01 bye

ls >./outfiles/outfile01 >./outfiles/outfile02

ls >./outfiles/outfile01 >./test_files/invalid_permission

ls >"./outfiles/outfile with spaces"

ls >"./outfiles/outfile""1""2""3""4""5"

ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"

ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission

cat <"./test_files/infile" >"./outfiles/outfile01"

echo hi >./outfiles/outfile01 | echo bye

echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye

echo hi | echo >./outfiles/outfile01 bye

echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02

echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02

echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye

echo hi >./test_files/invalid_permission | echo bye

echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye

echo hi | echo bye >./test_files/invalid_permission

echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission

echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01

cat <"./test_files/infile" >./test_files/invalid_permission

cat >./test_files/invalid_permission <"./test_files/infile"

cat <missing >./outfiles/outfile01

cat >./outfiles/outfile01 <missing

cat <missing >./test_files/invalid_permission

cat >./test_files/invalid_permission <missing

cat >./outfiles/outfile01 <missing >./test_files/invalid_permission

ls >>./outfiles/outfile01

ls >>      ./outfiles/outfile01

ls >>./outfiles/outfile01 >./outfiles/outfile01

ls >./outfiles/outfile01 >>./outfiles/outfile01

ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02

ls >>./outfiles/outfile01 >>./outfiles/outfile02

ls >>./test_files/invalid_permission

ls >>./test_files/invalid_permission >>./outfiles/outfile01

ls >>./outfiles/outfile01 >>./test_files/invalid_permission

ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02

ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02

ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing

echo hi >>./outfiles/outfile01 | echo bye

echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye

echo hi | echo >>./outfiles/outfile01 bye

echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02

echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02

echo hi >>./test_files/invalid_permission | echo bye

echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye

echo hi | echo bye >>./test_files/invalid_permission

echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission

cat <minishell.h>./outfiles/outfile

cat <minishell.h|ls

|

| echo oi

| |

| $

| >

>

>>

>>>

<

<<

echo hi <

cat    <| ls

echo hi | >

echo hi | > >>

echo hi | < |

echo hi |   |

echo hi |  "|"