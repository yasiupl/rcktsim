PREFIX=[Path_to_SFML]

build: ## Build the binary
	g++ -c -g -Wall main.cpp -I$(PREFIX)/include
	g++ main.o -o rcktsim.out -L$(PREFIX)/lib -lsfml-graphics -lsfml-window -lsfml-system
	#g++ -g -L$(PREFIX)/lib -I$(PREFIX)/include -lsfml-graphics -lsfml-window -lsfml-system -o rcktsim.out main.cpp
	
run: build ## Build and run the binary
	LD_LIBRARY_PATH=$(PREFIX)/lib ./rcktsim.out

debug: build
	gdb ./rcktsim.out

.PHONY: help
help: ## Print this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

