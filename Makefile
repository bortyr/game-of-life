build:
	clang++ -O3 -Wall main.cpp -o app.bin
debug:
	clang++ -v -g main.cpp -o app.bin
run:
	clang++ -O3 main.cpp -o app.bin
	./app.bin
clean:
	rm -v app.bin
