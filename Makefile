
help:
	@echo "build - сборка программы и библиотеки"
	@echo "run   - запуск программы"
	@echo "clean - удаление всех временных файлов"

build: pushkinMain.exe libpuskin.so

pushkinMain.exe: pushkinMain.o libpuskin.so
	gcc -o pushkinMain.exe pushkinMain.o -ldl

libpuskin.so: pushkin.o
	gcc -shared -fPIC -o libpushkin.so pushkin.o

%.o:%.c
	gcc -c $< -o $@

clean:
	rm -f *.o *.so *.exe *~