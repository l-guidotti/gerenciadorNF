#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

typedef struct {
    int id;	
    int numeroNota;
    char fornecedor[100];
    float valor;
    char caminhoPDF[200];
} NotaFiscal;

void adicionarNotaFiscal(NotaFiscal notas[], int *contador);
void listarNotasFiscais(NotaFiscal notas[], int contador);
void salvarNotasFiscais(NotaFiscal notas[], int contador, const char *nomeArquivo);
void buscarNotaFiscal(NotaFiscal notas[], int contador);
void buscarNotaFiscal(NotaFiscal notas[], int contador);

// Fun��o principal com o menu de op��es
int main() {
	setlocale(LC_ALL, "Portuguese");
    NotaFiscal notas[100];
    int contador = 0;
    int opcao;

    // Carrega as notas fiscais do arquivo ao iniciar
    carregarNotasFiscais(notas, &contador, "notas_fiscais.txt");

    do {printf("             -------------------------------------------    ");
        printf("\n	 >>>| Sistema de Gerenciamento de Notas Fiscais |<<< 	\n");
        printf("             -------------------------------------------    \n");
        printf("			1. ADICIONAR NOTA FISCAL\n");
        printf("			2. LISTAR NOTAS FISCAIS\n");
        printf("			3. BUSCAR NOTAS FISCAIS\n"); 
        printf("			4. SAIR\n\n");
        printf("			Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarNotaFiscal(notas, &contador);
                break;
            case 2:
                listarNotasFiscais(notas, contador);
                break;
            case 3:
                buscarNotaFiscal(notas, contador);
                break;
            case 4:
                salvarNotasFiscais(notas, contador, "notas_fiscais.txt");
                printf("\n			TENHA UM BOM TRABALHO!");
                printf("\n\n			SAINDO...\n");
                break;
            default:
                printf("\nOp��o inv�lida! Tente novamente.\n");
        }
    } while(opcao != 4);

    return 0;
}

// Fun��o para adicionar uma nova nota fiscal
void adicionarNotaFiscal(NotaFiscal notas[], int *contador) {
    NotaFiscal novaNota;
    novaNota.id = *contador + 1; 			//Incrementa o ID

    printf("\nDigite o n�mero da nota fiscal: ");
    scanf("%d", &novaNota.numeroNota); 		// Solicita o n�mero da nota fiscal

    printf("Digite o nome do fornecedor: ");
    scanf(" %[^\n]", novaNota.fornecedor);  // Solicita o nome do forncedor 

    printf("Digite o valor da nota fiscal: ");
    scanf("%f", &novaNota.valor);  			// Solicita o valor da nota fiscal

    printf("Digite o caminho para o PDF da nota fiscal: ");
    scanf(" %[^\n]", novaNota.caminhoPDF);  // Solicita o caminho em que est� armazenado o PDF da nota fiscal

    notas[*contador] = novaNota; 			// Insere a nota fiscal na lista
    (*contador)++;							// Contador recebe +1 como � ponteiro afeta diretamente a vari�vel original

    printf("\nNota fiscal adicionada com sucesso!\n");
}

// Fun��o para listar todas as notas fiscais
void listarNotasFiscais(NotaFiscal notas[], int contador) { //Nesse caso o contador serve para informar a quantidade de notas fiscais armazenadas no array 'notas'
	int i;
	printf("		      ------------------------");
    printf("\n		  >>>| Lista de Notas Fiscais |<<<\n");
    printf("		      ------------------------\n\n");
    for (i = 0; i < contador; i++) {						// For para garantir que sejam impressas todas as notas fiscais armazenadas no array 'notas' em senqu�ncia
        printf("ID: %d | N�mero: %d | Fornecedor: %s | Valor: %.2f | PDF: %s\n", // Imprime todos os dados j� cadastrados e armazenados no array 'notas'
               notas[i].id, notas[i].numeroNota, notas[i].fornecedor, notas[i].valor, notas[i].caminhoPDF);
    }
    printf("\n");
}

// Fun��o para salvar as notas fiscais em um arquivo de texto
void salvarNotasFiscais(NotaFiscal notas[], int contador, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); // Utilizado para abrir um arquivo 'fopen'. 'w' indica que o arquivo ser� aberto para escrita (write)
    int i;
    if (arquivo == NULL) {
        printf("			ERRO AO ABRIR O ARQUIVO PARA ESCRITA!\n");
        return;
    }

    for (i = 0; i < contador; i++) { 
        fprintf(arquivo, "%d,%d,%s,%.2f,%s\n", notas[i].id, notas[i].numeroNota, notas[i].fornecedor, notas[i].valor, notas[i].caminhoPDF);
    }  //'fprint' escreve direto no arquivo ao inv�s do terminal

    fclose(arquivo);  // Fecha o arquivo
    printf("\n			DADOS SALVOS COM SUCESSO!\n");
}

// Fun��o para carregar as notas fiscais de um arquivo de texto
void carregarNotasFiscais(NotaFiscal notas[], int *contador, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("			ERRO AO ABRIR ARQUIVO DE LEITURA.\n");
        return;
    }

    *contador = 0;
    while (fscanf(arquivo, "%d,%d,%99[^,],%f,%199[^\n]\n", &notas[*contador].id, &notas[*contador].numeroNota, notas[*contador].fornecedor, &notas[*contador].valor, notas[*contador].caminhoPDF) == 5) {
        (*contador)++;
    }

    fclose(arquivo);
}

// Fun��o para buscar uma nota fiscal por ID ou n�mero da nota
void buscarNotaFiscal(NotaFiscal notas[], int contador) {
    int opcao, idBusca, numeroBusca,i;
    int encontrado = 0;

	printf("		      ------------------------");
    printf("\n		  >>>| Buscar Notas Fiscais |<<<\n");
    printf("		      ------------------------\n\n");
    printf("			1. BUSCAR POR ID\n");
    printf("			2. BUSCAR POR N�MERO DA NOTA FISCAL\n");
    printf("			ESCOLHA UMA OP��O: ");
    scanf("%d", &opcao);
    
    while (opcao != 1 && opcao != 2 && opcao != 3){
    	printf("		      ------------------------");
    	printf("\n		  >>>| Buscar Notas Fiscais |<<<\n");
    	printf("		      ------------------------\n\n");
    	printf("			OP��O INV�LIDA!\n");
    	printf("			1. BUSCAR POR ID\n");
    	printf("			2. BUSCAR POR N�MERO DA NOTA FISCAL\n");
    	printf("			3. SAIR PARA O MENU PRINCIPAL\n");
    	printf("			ESCOLHA UMA OP��O: ");
    	scanf("%d", &opcao);
	}

    switch(opcao) {
        case 1:
            printf("			DIGITE O ID DA NOTA FISCAL: ");
            scanf("%d", &idBusca);

            for (i = 0; i < contador; i++) {
                if (notas[i].id == idBusca) {
                    printf("ID: %d | N�mero: %d | Fornecedor: %s | Valor: %.2f | PDF: %s\n",
                           notas[i].id, notas[i].numeroNota, notas[i].fornecedor, notas[i].valor, notas[i].caminhoPDF);
                    encontrado = 1;
                    break;
                }
            }
            break;

        case 2:
            printf("			DIGITE O N�MERO DA NOTA FISCAL: ");
            scanf("%d", &numeroBusca);

            for (i = 0; i < contador; i++) {
                if (notas[i].numeroNota == numeroBusca) {
                    printf("ID: %d | N�mero: %d | Fornecedor: %s | Valor: %.2f | PDF: %s\n",
                           notas[i].id, notas[i].numeroNota, notas[i].fornecedor, notas[i].valor, notas[i].caminhoPDF);
                    encontrado = 1;
                    break;
                }
            }
            break;
        
        case 3:
        	return; 
            break;
            
        default:
            printf("			OP��O INV�LIDA!\n");
        	return;    
    }

    if (!encontrado) {
    	printf("\n");
        printf("		!!!	NOTA FISCAL N�O ENCONTRADA.  !!!\n");
    }
}



