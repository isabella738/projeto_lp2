COMPILADOR = gcc

# "-I" é a flag que adiciona o diretório da onde estão os cabecalhos
FLAGS = -Iinclude

# Cria a pasta onde ficam os arquivos objeto
OBJ_DIR = objects

# 'FONTES' referencia todos os arquivos .c do projeto
FONTES = $(shell find source -type f -name "*.c")

# Gera arquivos objetos de todos os arquivos de FONTES
OBJ = $(FONTES:source/%.c=$(OBJ_DIR)/%.o)

#'CABECALHOS' referencia todos os arquivos .h do projeto
CABECALHOS = $(shell find source -type f -name "*.h")

# Regra de compilacao dos .c
$(OBJ_DIR)/%.o: source/%.c $(CABECALHOS)
	$(COMPILADOR) $(FLAGS) -c $< -o $@

# Linkagem; chama todos os arquivos .o
biblioteca: $(OBJ)
	$(COMPILADOR) -o $@ $^
