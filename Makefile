build: ## Build the binary
	g++ -c main.cpp
	g++ main.o -o rcktsim.out -lsfml-graphics -lsfml-window -lsfml-system
	
run: build ## Build and run the binary
	./rcktsim.out


.PHONY: help
help: ## Print this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

