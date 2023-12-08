SOURCE=$(wildcard *.c)
all:
	@make clean
	@echo "> Compiling mini-redis ($(words $(SOURCE)) files)"
	@gcc -Wall $(SOURCE) -o mini-redis

clean:
	@[ -f mini-redis ] && rm mini-redis || exit 0
	@[ -f *.o ] && rm *.o || exit 0
	@[ -f *.gch ] && rm *.gch || exit 0

run:
	@make all
	@./mini-redis
	@make clean
