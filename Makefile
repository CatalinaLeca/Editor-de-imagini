# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

# define targets
TARGETS = image_editor

build: $(TARGETS)

image_editor: main.c fc.c fc_LOAD.c fc_SELECT.c fc_CROP.c fc_HIST.c fc_EQ.c fc_APPLY.c fc_SAVE.c
	$(CC) $(CFLAGS) main.c fc.c fc_LOAD.c fc_SELECT.c fc_CROP.c fc_HIST.c fc_EQ.c fc_APPLY.c fc_SAVE.c -o image_editor

pack:
	zip -FSr 315CA_LecaMaria-Catalina_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
