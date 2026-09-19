# Emulator MOS6502

Um emulador educativo do processador MOS 6502 escrito em C, com arquitetura simples, tabela de instruções e testes unitários para validar o comportamento básico da CPU.

## Objetivo

Este projeto foi criado para estudar:

- o funcionamento interno do 6502;
- modos de endereçamento;
- flags do processador;
- execução de instruções em nível de máquina;
- estrutura de um emulador simples em C.

Ele está em uma fase de base funcional, com foco em aprendizado e validação de instruções oficiais do 6502.

## Status atual

A base do emulador já inclui as instruções principais do conjunto oficial do 6502, como:

- transferências de registradores;
- aritmética (`ADC`, `SBC`);
- lógica (`AND`, `ORA`, `EOR`);
- comparações (`CMP`, `CPX`, `CPY`);
- manipulação de memória (`LDA/STA`, etc.);
- saltos e branches principais;
- pilha (`PHA`, `PLA`, `PHP`, `PLP`);
- shifts/rotates (`ASL`, `LSR`, `ROL`, `ROR`);
- flags de controle (`CLC`, `SEC`, `CLI`, `SEI`, `CLD`, `SED`, `CLV`);
- `JSR`, `RTS`, `JMP`, `BRK`, `RTI`.

A estrutura do projeto também conta com testes automatizados para validar parte do comportamento da CPU.

## Estrutura do projeto

```text
Emulator-MOS6502/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── bus/
│   ├── cpu/
│   └── instruction/
├── src/
│   ├── bus/
│   ├── cpu/
│   ├── instruction/
│   └── main.c
├── tests/
│   ├── ...
└── build/
```

## Como compilar

Pré-requisitos:

- CMake
- compilador GCC/Clang

No diretório do projeto:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Como executar

O projeto pode ser executado a partir do binário gerado em `build/`:

```bash
./Emulator-MOS6502
```

## Testes

O projeto usa testes em C para validar instruções e comportamentos básicos da CPU. Para rodar a suíte:

```bash
cd build
ctest --output-on-failure
```

## Melhorias planejadas

Este projeto ainda está em evolução. Algumas melhorias importantes que podem ser feitas no futuro incluem:

1. Fidelidade mais precisa do 6502
    - ciclos exatos por instrução;
    - timing de page crossings;
    - detalhes de comportamento de branch e stack.

2. Tratamento mais completo de interrupções
    - IRQ;
    - NMI;
    - RST;
    - comportamento exato do vetor de interrupção.

3. Melhor modelagem de flags e estados
    - validação de `B` e `U` em pontos específicos;
    - comportamento em modo decimal (`D`).

4. Mais cobertura de testes
    - testar todas as instruções oficiais;
    - cobrir casos de page boundary;
    - validar efeitos de flags em todos os caminhos.

5. Separação clara entre CPU, memória e bus
    - facilitar extensões para periféricos e dispositivos externos;
    - permitir a criação de programas de teste mais complexos.

6. Execução de programas reais
    - carregar binários ROM;
    - interpretar programas em Assembly 6502;
    - suporte a debugging mais amigável.

## Observação importante

Este projeto é uma base sólida para aprendizado e desenvolvimento inicial de um emulador 6502, mas ainda não busca ser um emulador “de produção” com fidelidade de hardware completa. A intenção principal é entender a arquitetura e a lógica do processador de forma prática.

## Próximo passo recomendado

O próximo passo ideal é focar em:

- refinamento de ciclos e timings;
- testes de instruções restantes;
- ajustes de fidelidade em branches e interrupções;
- preparação para suportar ROMs e programas reais.

## Contribuição

Sinta-se livre para usar o projeto como base para estudo, extensão ou experimentação. A estrutura foi organizada para facilitar evolução incremental do emulador.
