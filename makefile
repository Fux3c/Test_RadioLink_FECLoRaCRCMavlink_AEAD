build: ## Builds html files of wiring for FC-1 and FC-2
	@echo "Generating FC-1 wiring"
	wireviz FC-1/*.yaml --format h
	@echo "Generating FC-2 wiring"
	wireviz FC-2/*.yaml --format h
help: ## Show help message
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
