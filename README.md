# PSE em Ação — Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

Atividade de Estudos Programada (AEP) — 2º semestre de 2026  
Universidade Cesumar (UniCesumar) · Engenharia de Software · Maringá – PR

## Integrantes

- Guilherme Kauan Amaro Somensi
- Pedro Henrique Morezzi
- Roberto Quirino de Alvarenga Junior

## Sobre o projeto

O **PSE em Ação** é uma aplicação de terminal, escrita em linguagem C, que registra e acompanha **ações coletivas** do Programa Saúde na Escola (PSE). O tema de demonstração escolhido pelo grupo é a **verificação da situação vacinal**, mas o sistema aceita ações de qualquer tema.

Questão norteadora: como uma aplicação em C pode ajudar uma equipe escolar e de saúde a planejar, registrar e acompanhar ações coletivas do PSE, apresentando informações claras e preservando a privacidade dos estudantes?

### Limites éticos

- O sistema usa **somente dados fictícios e coletivos**.
- Não cadastre nomes, diagnósticos, prontuários ou qualquer dado individual de estudantes. O programa exibe um aviso nesse sentido ao iniciar.
- O programa não faz diagnóstico, triagem, prescrição nem recomendação de tratamento.

## Funcionalidades

| Opção | Funcionalidade | Descrição |
|---|---|---|
| 1 | Cadastrar ação | Código (único), escola, tema, data prevista (dd/mm/aaaa), público-alvo, responsável e participantes previstos. A situação inicial é *Planejada*. |
| 2 | Listar ações | Tabela com número, código, escola, tema, data, situação e participantes previstos e efetivos. |
| 3 | Pesquisar ação | Por código (busca exata) ou por escola/tema (busca parcial), sem diferenciar maiúsculas de minúsculas. |
| 4 | Atualizar situação | *Planejada*, *Realizada* ou *Cancelada*. Se realizada, registra os participantes efetivos e, nas ações de vacinação, os dados coletivos de alunos avaliados, em situação regular e que necessitam de verificação. |
| 5 | Gerar resumo geral | Ações por situação, participantes previstos e efetivos das ações realizadas, percentual de participação e totais da verificação vacinal. |
| 0 | Encerrar | Fecha o programa. Os dados **não são salvos**. |

### Validações

- Código de ação repetido (sem diferenciar maiúsculas de minúsculas).
- Campos obrigatórios vazios e textos acima do tamanho máximo.
- Quantidades negativas, zero onde não é permitido ou não numéricas.
- Data inexistente (inclui ano bissexto) ou fora do formato dd/mm/aaaa.
- Opção inexistente no menu.
- Verificação vacinal: avaliados ≤ efetivos e regulares + a verificar = avaliados.
- Limite de armazenamento de 100 ações, com mensagem ao atingi-lo.

## Como compilar e executar

**Requisitos:** compilador `gcc` (ou compatível) com suporte ao padrão C99. Não é necessária nenhuma biblioteca além da padrão.

Na pasta onde está o arquivo `pse_em_acao.c`, execute:

```bash
gcc -std=c99 -Wall -Wextra -o pse_em_acao pse_em_acao.c
./pse_em_acao
```

No Windows (MinGW ou similar), o executável é `pse_em_acao.exe`:

```bat
gcc -std=c99 -Wall -Wextra -o pse_em_acao pse_em_acao.c
pse_em_acao.exe
```

Nenhum aviso é esperado na compilação.

## Exemplo de uso

```text
====================================
  PSE EM ACAO - Saude na Escola
====================================
1 - Cadastrar acao
2 - Listar acoes
3 - Pesquisar acao
4 - Atualizar situacao da acao
5 - Gerar resumo geral
0 - Encerrar
Escolha uma opcao: 1

=== CADASTRAR ACAO ===
Codigo da acao (ex.: VAC001): VAC001
Escola: Escola Municipal Sol
Tema (ex.: Vacinacao): Vacinacao
Data prevista (dd/mm/aaaa): 15/03/2026
Publico-alvo (ex.: 6o ano): 6o ano
Responsavel: Maria Souza
Quantidade prevista de participantes: 80
[OK] Acao "VAC001" cadastrada com situacao Planejada.
```

Depois de atualizar a ação para *Realizada* (70 participantes efetivos; 70 avaliados, 60 regulares e 10 a verificar), o resumo geral mostra:

```text
=== RESUMO GERAL ===
Total de acoes cadastradas.........: 1
Acoes planejadas...................: 0
Acoes realizadas...................: 1
Acoes canceladas...................: 0
Participantes previstos (realizadas): 80
Participantes efetivos (realizadas): 70
Percentual de participacao.........: 87.5%
--- Verificacao vacinal (dados coletivos das acoes realizadas) ---
Alunos avaliados...................: 70
Alunos com situacao regular........: 60
Alunos que necessitam verificacao..: 10
```

## Estrutura do repositório

```text
AEP-PSE-EM-ACAO/
├── README.md          # este arquivo
├── pse_em_acao.c      # código-fonte do sistema
└── docs/              # documentação das entregas (PDF)
```

## Decisões de projeto

- Leitura de dados com `fgets` (em vez de `scanf`) para evitar falhas com entradas inválidas.
- Armazenamento em vetores na memória, com capacidade de 100 ações.
- Programa dividido em funções com responsabilidades específicas (leitura, validação, cadastro, listagem, pesquisa, atualização e resumo), mantendo a função `main` apenas como controle do menu.
- Mensagens sem acentos, para funcionar em qualquer terminal.
- O percentual de participação considera somente as ações realizadas.

## Limitações e melhorias futuras

- Os dados são perdidos ao encerrar o programa.
- O limite é de 100 ações, e não há opção para editar os dados cadastrados nem para excluir uma ação.
- A data é validada quanto ao formato e à existência, mas não é comparada com a data atual.

Melhorias possíveis: salvar os dados em arquivo, permitir editar e excluir ações, ordenar a listagem, filtrar o resumo por escola e criar testes automatizados.

## Vídeo de apresentação

https://www.youtube.com/watch?v=cSBQ6I9d6Dc

## Referências

- BRASIL. Decreto nº 6.286, de 5 de dezembro de 2007. Institui o Programa Saúde na Escola — PSE e dá outras providências. Diário Oficial da União: Brasília, DF, 6 dez. 2007.
- BRASIL. Ministério da Saúde. Caderno Temático do Programa Saúde na Escola: Verificação da Situação Vacinal. Brasília: Ministério da Saúde, 2022.
