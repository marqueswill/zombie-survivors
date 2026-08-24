BUILD_DIR = build
DIST_DIR = dist
APP_NAME = zombie_survivors

# Detecção automática do Sistema Operacional
ifeq ($(OS),Windows_NT)
    TARGET_OS = windows
    EXEC_EXT = .exe
else
    # Assume Linux para outros casos
    TARGET_OS = linux
    EXEC_EXT =
endif

# Caminho do executável compilado
EXEC_PATH = $(BUILD_DIR)/Debug/$(APP_NAME)$(EXEC_EXT)

# --- Construção do nome de exportação ---
EXPORT_BASE = $(APP_NAME)

# Se a versão for passada, anexa ao nome
ifdef VERSION
    EXPORT_BASE := $(EXPORT_BASE)-v$(VERSION)
endif

# Se um sufixo for passado, anexa ao final (antes da extensão)
ifdef SUFFIX
    EXPORT_BASE := $(EXPORT_BASE)$(SUFFIX)
endif

# Adiciona a extensão do sistema operacional (.exe ou vazio)
EXPORT_NAME = $(EXPORT_BASE)$(EXEC_EXT)
# ----------------------------------------

# Define o caminho final de exportação separando por OS
EXPORT_DIR = $(DIST_DIR)/$(TARGET_OS)
EXPORT_DEST = $(EXPORT_DIR)/$(EXPORT_NAME)

all:
	@cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)

run: all
	@./$(EXEC_PATH)

export: all
	@echo "Criando pasta de distribuição para $(TARGET_OS)..."
	@mkdir -p $(EXPORT_DIR)
	@cp $(EXEC_PATH) $(EXPORT_DEST)
	@echo "✔️ Exportado com sucesso para: $(EXPORT_DEST)"

clean:
	@rm -rf $(BUILD_DIR) $(DIST_DIR)

.PHONY: all run export clean