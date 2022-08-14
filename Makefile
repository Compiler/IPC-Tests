BIN = bin/

fork: $@/*
	gcc $@/* -o $(BIN)/$@_output
	./$(BIN)/$@_output
