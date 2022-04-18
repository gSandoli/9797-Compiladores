# 9797-Compiladores

#### Diogo Alves de Almeida (ra95108@uem.br)

#### Gabriel Saboto Sandoli (ra105421@uem.br)

## Versions

#### Machine

```sh
# uname -a

# local
Linux 5.13.0-28-generic #31~20.04.1-Ubuntu SMP Wed Jan 19 14:08:10 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux

# docker
Linux 5.10.76-linuxkit #1 SMP Mon Nov 8 10:21:19 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
```

#### Flex

```sh
# flex --version

# local e docker
flex 2.6.4
```

#### Bison

```sh
# bison --version

# local e docker
bison (GNU Bison) 3.5.1
Escrito por Robert Corbett e Richard Stallman.

Copyright © 2020 Free Software Foundation, Inc.
Este é um software livre; veja o código fonte para condições de cópia.
NÃO HÁ QUALQUER GARANTIA; nem mesmo para COMERCIALIZAÇÃO ou de ADEQUAÇÃO A
QUALQUER PROPÓSITO EM PARTICULAR.
```

#### Clang

```sh
# clang --version

# local e docker
clang version 10.0.0-4ubuntu1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

## Docker

Foi criado esse procedimento para poder ser realizado as atividades no macOS.

```sh
# cria imagem com nome "environment-compiler-9797" e container com nome "diogo"
make container

# copia arquivos para o container em execução e acessar container em execução via /bin/bash
make cp
```

## Build

```sh
make build
```

## Test

```sh
# testa o arquivo test.s
make test
```

## Build and Test

```sh
make
```

## Run

```sh
./sc [FILE]
```
