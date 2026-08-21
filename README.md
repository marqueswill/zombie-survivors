# zombie-survivors

Implementação do "Jogo do Zumbi" da matéria Introdução ao Desenvolvimento de Jogos (CIC0191)

O jogo tem 7 versões, de acordo com a release atual do desenvolvimento na disciplina:

## Execução

Para executar o jogo, basta clicar no executável desejado na pasta `dist/`. Para executar pelo terminal:

* **Linux**

```bash
./dist/linux/zombie_survivors_v[numero_versao]

```

* **Windows**

```cmd
.\dist\windows\zombie_survivors_v[numero_versao].exe

```

## Desenvolvimento

### Requisitos

* Compilador g++
* make
* cmake
* [SDL](https://wiki.libsdl.org/SDL3/README-linux)

### Setup

Como o projeto utiliza a biblioteca SDL de forma isolada (vendored), o CMake gerencia a compilação da dependência automaticamente. Não é necessária a instalação manual do SDL no sistema operacional.

### Compilando

Na raiz do projeto, utilize o `Makefile` para gerar os arquivos de build e compilar o jogo (incluindo o SDL):

```bash
make

```

### Testing

Para executar o binário recém-compilado:

```bash
make run

```

Para limpar os arquivos gerados pela compilação:

```bash
make clean

```

