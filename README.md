# zombie-survivors

Implementação do "Jogo do Zumbi" da matéria Introdução ao Desenvolvimento de Jogos (CIC0191)

O jogo tem 7 versões, de acordo com a release atual do desenvolvimento na disciplina:

## Execução

Para executar o jogo, basta acessar a pasta `dist/linux/` e executar o binário gerado. Para executar pelo terminal:

```bash
# Executável padrão exportado
./dist/zombie_survivors

# Executável exportado com flag de versão (ex: versão 1.0)
./dist/zombie_survivors-v1.0
```

## Desenvolvimento

### Requisitos

* g++
* make
* cmake
* SDL2
* Ubuntu 26.04

### Setup

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

### Comandos

Na raiz do projeto, utilize o `Makefile` para gerar os arquivos de build e compilar o jogo:

**Compilar o projeto:**

Gera o executável na pasta `build/`

```bash
make
```

**Compilar e rodar:**

Gera o executável na pasta `build/` e executa ele

```bash
make run
```

**Exportar o jogo:**

Gera o executável na pasta `dist/`

É possível anexar versões ou sufixos ao nome do arquivo exportado usando variáveis

```bash
make export               # Gera: zombie_survivors
make export VERSION=1.0   # Gera: zombie_survivors-v1.0
make export SUFFIX=_test  # Gera: zombie_survivors_test
```

**Limpar arquivos gerados:**

Apaga as pastas `build/` e `dist/`

```bash
make clean
```