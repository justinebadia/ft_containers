NAME = ft_containers

all	:
	./test.sh

map:
	./test.sh map

vector:
	./test.sh vector

stack:
	./test.sh stack

clean:
ifneq ( $(wildcard /tests/diff/ft), "")
	rm -rf tests/diff/
else
	@echo -n "no diff to delete"
endif

fclean: clean

re: clean all