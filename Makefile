BUILD_DIR = build
DIST_DIR = dist
APP_NAME = zombie_survivors

# Caminho do executável compilado 
EXEC_PATH = $(BUILD_DIR)/Debug/$(APP_NAME)

# --- Construção do nome de exportação ---
EXPORT_NAME = $(APP_NAME)

# Se a versão for passada, anexa ao nome
ifdef VERSION
    EXPORT_NAME := $(EXPORT_NAME)-v$(VERSION)
endif

# Se um sufixo for passado, anexa ao final
ifdef SUFFIX
    EXPORT_NAME := $(EXPORT_NAME)$(SUFFIX)
endif
# ----------------------------------------

# Define o caminho final de exportação direto para Linux
EXPORT_DIR = $(DIST_DIR)
EXPORT_DEST = $(EXPORT_DIR)/$(EXPORT_NAME)

all:
	@cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)

run: all
	@./$(EXEC_PATH)

export: all
	@echo "Criando pasta de distribuição para Linux..."
	@mkdir -p $(EXPORT_DIR)
	@cp $(EXEC_PATH) $(EXPORT_DEST)
	@echo "> Exportado com sucesso para: $(EXPORT_DEST)"

clean:
	@rm -rf $(BUILD_DIR) $(DIST_DIR)

.PHONY: all run export clean