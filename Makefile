compiler:
	rm -rf ./out
	mkdir out
	g++ main.cpp -o ./out/main
	./out/main
asm:
	nasm -f elf64 ./out/app.asm -o ./out/app.o
	gcc ./out/app.o -o ./out/a.out -no-pie
	./out/a.out
