default:
	gcc -Wall -Wextra main.c input.c stringutils.c -o main.exe

debug:
	gcc -Wall -Wextra -g main.c input.c stringutils.c -o main.exe

clean:
	del prog.exe