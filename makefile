game.exe: main.c .\bin\gl.a
	gcc main.c -o game.exe -I .\include .\bin\libglfw3.a .\bin\gl.a -lgdi32
.\bin\gl.a: .\src\gl.c
	gcc -c .\src\gl.c -o .\bin\gl.a -I .\include
clean:
	del /Q /F game.exe

