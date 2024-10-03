CC = gcc
OPTIONS = -W -Wall -g -std=c89 -pedantic -O3 `pkg-config --cflags MLV`
MLV = `pkg-config --libs-only-l MLV` `pkg-config --libs-only-other --libs-only_L MLV`

I = -Iincludes
C = sources
O = objets
EXT = c

TXT_FILES = $(wildcard $(C)/*.$(EXT))
DAT_FILES = $(patsubst $(C)/%.$(EXT), $(O)/%.o, $(TXT_FILES))

Tetris : $(DAT_FILES)
	$(CC) $(OPTIONS) $(DAT_FILES) -o $@ $(MLV)

$(O)/%.o : $(C)/%.$(EXT)
	$(CC) $(OPTIONS) $(I) -$(EXT) $< -o $@

clean :
	rm -rf $(O)/* *~ Tetris
