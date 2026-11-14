#include <stdio.h>

int total = 0;
char codigo[100][20];
char escola[100][60];
char tema[100][60];
char data[100][11];
char publico[100][60];
char responsavel[100][60];
int previstos[100];
int situacao[100];
int efetivos[100];
int avaliados[100];
int regulares[100];
int aVerificar[100];

char linha[256];
int tam;

void lerLinha() {
    linha[0] = '\0';
    fgets(linha, 256, stdin);
    tam = 0;
    while (linha[tam] != '\n' && linha[tam] != '\0') {
        tam++;
    }
    linha[tam] = '\0';
}

int valorDigito(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }
    return -1;
}

char minuscula(char c) {
    switch (c) {
        case 'A': return 'a';
        case 'B': return 'b';
        case 'C': return 'c';
        case 'D': return 'd';
        case 'E': return 'e';
        case 'F': return 'f';
        case 'G': return 'g';
        case 'H': return 'h';
        case 'I': return 'i';
        case 'J': return 'j';
        case 'K': return 'k';
        case 'L': return 'l';
        case 'M': return 'm';
        case 'N': return 'n';
        case 'O': return 'o';
        case 'P': return 'p';
        case 'Q': return 'q';
        case 'R': return 'r';
        case 'S': return 's';
        case 'T': return 't';
        case 'U': return 'u';
        case 'V': return 'v';
        case 'W': return 'w';
        case 'X': return 'x';
        case 'Y': return 'y';
        case 'Z': return 'z';
    }
    return c;
}

int converterNumero() {
    int numero = 0;
    if (tam == 0 || tam > 9) {
        return -1;
    }
    for (int i = 0; i < tam; i++) {
        if (valorDigito(linha[i]) == -1) {
            return -1;
        }
        numero = numero * 10 + valorDigito(linha[i]);
    }
    return numero;
}

int lerInteiro(char mensagem[], int minimo, int maximo) {
    int numero;
    printf("%s", mensagem);
    lerLinha();
    numero = converterNumero();
    while (numero < minimo || numero > maximo) {
        if (numero == -1) {
            printf("  [ERRO] Digite apenas numeros inteiros.\n");
        } else {
            printf("  [ERRO] Valor fora da faixa permitida (%d a %d).\n", minimo, maximo);
        }
        printf("%s", mensagem);
        lerLinha();
        numero = converterNumero();
    }
    return numero;
}

void lerTexto(char mensagem[], char destino[], int maximo) {
    printf("%s", mensagem);
    lerLinha();
    while (tam == 0 || tam > maximo) {
        if (tam == 0) {
            printf("  [ERRO] Campo obrigatorio. Digite novamente.\n");
        } else {
            printf("  [ERRO] Texto muito longo (maximo %d caracteres). Digite novamente.\n", maximo);
        }
        printf("%s", mensagem);
        lerLinha();
    }
    for (int i = 0; i <= tam; i++) {
        destino[i] = linha[i];
    }
}

int dataValida() {
    int dia, mes, ano, diasDoMes;

    if (tam != 10 || linha[2] != '/' || linha[5] != '/') {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && valorDigito(linha[i]) == -1) {
            return 0;
        }
    }

    dia = valorDigito(linha[0]) * 10 + valorDigito(linha[1]);
    mes = valorDigito(linha[3]) * 10 + valorDigito(linha[4]);
    ano = valorDigito(linha[6]) * 1000 + valorDigito(linha[7]) * 100 + valorDigito(linha[8]) * 10 + valorDigito(linha[9]);

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasDoMes = 30;
    } else if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) {
        diasDoMes = 29;
    } else if (mes == 2) {
        diasDoMes = 28;
    } else {
        diasDoMes = 31;
    }

    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12 || dia < 1 || dia > diasDoMes) {
        return 0;
    }
    return 1;
}

void lerData(char destino[]) {
    printf("Data prevista (dd/mm/aaaa): ");
    lerLinha();
    while (dataValida() == 0) {
        printf("  [ERRO] Data invalida. Use o formato dd/mm/aaaa (exemplo: 15/03/2026).\n");
        printf("Data prevista (dd/mm/aaaa): ");
        lerLinha();
    }
    for (int i = 0; i <= tam; i++) {
        destino[i] = linha[i];
    }
}

int iguais(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && minuscula(a[i]) == minuscula(b[i])) {
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 1;
    }
    return 0;
}

int contem(char texto[], char termo[]) {
    int j;
    for (int i = 0; texto[i] != '\0'; i++) {
        j = 0;
        while (termo[j] != '\0' && minuscula(texto[i + j]) == minuscula(termo[j])) {
            j++;
        }
        if (termo[j] == '\0') {
            return 1;
        }
    }
    return 0;
}

int buscarCodigo(char cod[]) {
    for (int i = 0; i < total; i++) {
        if (iguais(codigo[i], cod) == 1) {
            return i;
        }
    }
    return -1;
}

void mostrarSituacao(int s) {
    if (s == 2) {
        printf("Realizada");
    } else if (s == 3) {
        printf("Cancelada");
    } else {
        printf("Planejada");
    }
}

void mostrarColuna(char texto[], int largura) {
    int i = 0;
    while (i < largura && texto[i] != '\0') {
        printf("%c", texto[i]);
        i++;
    }
    while (i < largura) {
        printf(" ");
        i++;
    }
    printf(" ");
}

void mostrarNumero(int n) {
    if (n < 10) {
        printf("    ");
    } else if (n < 100) {
        printf("   ");
    } else if (n < 1000) {
        printf("  ");
    } else if (n < 10000) {
        printf(" ");
    }
    printf("%d", n);
}

void cadastrar() {
    printf("\n=== CADASTRAR ACAO ===\n");
    if (total == 100) {
        printf("[ERRO] Limite de armazenamento atingido (100 acoes). Nao e possivel cadastrar.\n");
        return;
    }

    lerTexto("Codigo da acao (ex.: VAC001): ", codigo[total], 19);
    while (buscarCodigo(codigo[total]) != -1) {
        printf("  [ERRO] Ja existe uma acao com o codigo %c%s%c. Informe outro codigo.\n", '"', codigo[total], '"');
        lerTexto("Codigo da acao (ex.: VAC001): ", codigo[total], 19);
    }
    lerTexto("Escola: ", escola[total], 59);
    lerTexto("Tema (ex.: Vacinacao): ", tema[total], 59);
    lerData(data[total]);
    lerTexto("Publico-alvo (ex.: 6o ano): ", publico[total], 59);
    lerTexto("Responsavel: ", responsavel[total], 59);
    previstos[total] = lerInteiro("Quantidade prevista de participantes: ", 1, 100000);
    situacao[total] = 1;

    printf("[OK] Acao %c%s%c cadastrada com situacao Planejada.\n", '"', codigo[total], '"');
    total++;
}

void listar() {
    if (total == 0) {
        printf("\nNenhuma acao cadastrada ainda.\n");
        return;
    }

    printf("\n=== ACOES CADASTRADAS (%d) ===\n", total);
    printf("No   Codigo     Escola                 Tema                 Data        Situacao    Prev  Efet\n");
    printf("---- ---------- ---------------------- -------------------- ----------- ---------- ----- -----\n");

    for (int i = 0; i < total; i++) {
        if (i + 1 < 10) {
            printf("%d    ", i + 1);
        } else if (i + 1 < 100) {
            printf("%d   ", i + 1);
        } else {
            printf("%d  ", i + 1);
        }
        mostrarColuna(codigo[i], 10);
        mostrarColuna(escola[i], 22);
        mostrarColuna(tema[i], 20);
        printf("%s  ", data[i]);
        mostrarSituacao(situacao[i]);
        printf("  ");
        mostrarNumero(previstos[i]);
        printf(" ");
        if (situacao[i] == 2) {
            mostrarNumero(efetivos[i]);
        } else {
            printf("    -");
        }
        printf("\n");
    }
}

void mostrarAcao(int i) {
    printf("  Codigo.............: %s\n", codigo[i]);
    printf("  Escola.............: %s\n", escola[i]);
    printf("  Tema...............: %s\n", tema[i]);
    printf("  Data prevista......: %s\n", data[i]);
    printf("  Publico-alvo.......: %s\n", publico[i]);
    printf("  Responsavel........: %s\n", responsavel[i]);
    printf("  Participantes prev.: %d\n", previstos[i]);
    printf("  Situacao...........: ");
    mostrarSituacao(situacao[i]);
    printf("\n");

    if (situacao[i] == 2) {
        printf("  Participantes efet.: %d\n", efetivos[i]);
        if (contem(tema[i], "vacin") == 1) {
            printf("  Alunos avaliados...: %d\n", avaliados[i]);
            printf("  Situacao regular...: %d\n", regulares[i]);
            printf("  A verificar........: %d\n", aVerificar[i]);
        }
    }
}

void pesquisar() {
    char termo[60];
    int tipo, achou;
    int achadas = 0;

    printf("\n=== PESQUISAR ACAO ===\n");
    if (total == 0) {
        printf("Nenhuma acao cadastrada ainda.\n");
        return;
    }

    printf("1 - Por codigo\n");
    printf("2 - Por escola\n");
    printf("3 - Por tema\n");
    tipo = lerInteiro("Escolha o tipo de pesquisa: ", 1, 3);
    lerTexto("Termo de busca: ", termo, 59);

    for (int i = 0; i < total; i++) {
        achou = 0;
        if (tipo == 1) {
            achou = iguais(codigo[i], termo);
        } else if (tipo == 2) {
            achou = contem(escola[i], termo);
        } else {
            achou = contem(tema[i], termo);
        }

        if (achou == 1) {
            achadas++;
            printf("\n--- Resultado %d ---\n", achadas);
            mostrarAcao(i);
        }
    }

    if (achadas == 0) {
        printf("Nenhuma acao encontrada para %c%s%c.\n", '"', termo, '"');
    } else {
        printf("\n%d acao(oes) encontrada(s).\n", achadas);
    }
}

void atualizar() {
    char cod[20];
    int i, nova;

    printf("\n=== ATUALIZAR SITUACAO ===\n");
    if (total == 0) {
        printf("Nenhuma acao cadastrada ainda.\n");
        return;
    }

    lerTexto("Codigo da acao: ", cod, 19);
    i = buscarCodigo(cod);
    if (i == -1) {
        printf("[ERRO] Nenhuma acao encontrada com o codigo %c%s%c.\n", '"', cod, '"');
        return;
    }

    printf("Situacao atual de %c%s%c: ", '"', codigo[i], '"');
    mostrarSituacao(situacao[i]);
    printf("\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    nova = lerInteiro("Nova situacao: ", 1, 3);

    efetivos[i] = 0;
    avaliados[i] = 0;
    regulares[i] = 0;
    aVerificar[i] = 0;

    if (nova == 2) {
        efetivos[i] = lerInteiro("Quantidade efetiva de participantes: ", 0, 100000);

        if (contem(tema[i], "vacin") == 1) {
            printf("Acao de vacinacao: informe os dados COLETIVOS da verificacao vacinal.\n");
            do {
                avaliados[i] = lerInteiro("  Alunos avaliados: ", 0, efetivos[i]);
                regulares[i] = lerInteiro("  Alunos com situacao regular: ", 0, avaliados[i]);
                aVerificar[i] = lerInteiro("  Alunos que necessitam de verificacao: ", 0, avaliados[i]);
                if (regulares[i] + aVerificar[i] != avaliados[i]) {
                    printf("  [ERRO] Regulares + a verificar (%d) deve ser igual aos avaliados (%d). Informe novamente.\n",
                           regulares[i] + aVerificar[i], avaliados[i]);
                }
            } while (regulares[i] + aVerificar[i] != avaliados[i]);
        }
    }

    situacao[i] = nova;
    printf("[OK] Situacao da acao %c%s%c atualizada para ", '"', codigo[i], '"');
    mostrarSituacao(nova);
    printf(".\n");
}

void resumo() {
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int somaPrevistos = 0, somaEfetivos = 0, somaAvaliados = 0, somaRegulares = 0, somaVerificar = 0;

    printf("\n=== RESUMO GERAL ===\n");
    if (total == 0) {
        printf("Nenhuma acao cadastrada ainda.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        if (situacao[i] == 1) {
            planejadas++;
        } else if (situacao[i] == 3) {
            canceladas++;
        } else {
            realizadas++;
            somaPrevistos += previstos[i];
            somaEfetivos += efetivos[i];
            somaAvaliados += avaliados[i];
            somaRegulares += regulares[i];
            somaVerificar += aVerificar[i];
        }
    }

    printf("Total de acoes cadastradas.........: %d\n", total);
    printf("Acoes planejadas...................: %d\n", planejadas);
    printf("Acoes realizadas...................: %d\n", realizadas);
    printf("Acoes canceladas...................: %d\n", canceladas);
    printf("Participantes previstos (realizadas): %d\n", somaPrevistos);
    printf("Participantes efetivos (realizadas): %d\n", somaEfetivos);
    if (realizadas > 0) {
        printf("Percentual de participacao.........: %.1f%%\n", 100.0 * somaEfetivos / somaPrevistos);
    } else {
        printf("Percentual de participacao.........: nao calculado\n");
    }
    printf("--- Verificacao vacinal (dados coletivos das acoes realizadas) ---\n");
    printf("Alunos avaliados...................: %d\n", somaAvaliados);
    printf("Alunos com situacao regular........: %d\n", somaRegulares);
    printf("Alunos que necessitam verificacao..: %d\n", somaVerificar);
}

int main() {
    int opcao;

    printf("AVISO: use somente dados ficticios e coletivos.\n");
    printf("Nao informe nomes, diagnosticos ou dados individuais de estudantes.\n");

    do {
        printf("\n====================================\n");
        printf("  PSE EM ACAO - Saude na Escola\n");
        printf("====================================\n");
        printf("1 - Cadastrar acao\n");
        printf("2 - Listar acoes\n");
        printf("3 - Pesquisar acao\n");
        printf("4 - Atualizar situacao da acao\n");
        printf("5 - Gerar resumo geral\n");
        printf("0 - Encerrar\n");
        printf("Escolha uma opcao: ");
        lerLinha();
        opcao = converterNumero();

        switch (opcao) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: pesquisar(); break;
            case 4: atualizar(); break;
            case 5: resumo(); break;
            case 0: printf("\nEncerrando o programa. Os dados nao foram salvos.\n"); break;
            default: printf("[ERRO] Opcao inexistente no menu. Escolha um numero de 0 a 5.\n"); break;
        }
    } while (opcao != 0);

    return 0;
}
