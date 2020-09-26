#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

typedef struct banda{
    char nomeDoInstrumento [50];
    char nomeDoMusico [100];
    int anoDeCompra;
    float precoDeCompra;
    struct banda *proximo;
}tipoNo;

typedef struct lista{
    tipoNo *head;
    tipoNo *fim;
}tipoLista;

void cadastrar(tipoLista *lista);
int menu();
void escolha(tipoLista *lista, int opc);
void imprimirInstrumentos(tipoLista *lista);
void calculaMedia(tipoLista *lista);
void buscarMusico(tipoLista *lista);
void exlcuirInstrumento(tipoLista *lista);

int main() 
{
   setlocale(LC_ALL, "");
   
   tipoLista *lista = (tipoLista*)malloc(sizeof(tipoLista));
    if(!lista){
        printf("Impossível alocar lista");
    }else {
        lista->head = NULL;
        lista->fim = NULL;
    }
   
   int opcao;
   
   do{
    opcao = menu();
    escolha(lista, opcao);
   }while(opcao != 6);
   
    return 0;
}

int menu(){
  int opc;

    printf("\n\n---------- CADASTRO DE INSTRUMENTOS - BANDA MOLEJO ----------\n");
    printf("\nDigite um número para escolher a opção desejada: ");
    printf("\n1 - Cadastrar instrumento");
    printf("\n2 - Deletar instrumento");
    printf("\n3 - Imprimir todos os instrumentos cadastrados");
    printf("\n4 - Buscar por músico");
    printf("\n5 - Saber idade média dos instrumentos cadastrados");
    printf("\n6- Sair do programa\n\n");
    scanf("%d%*c", &opc);
    system("cls || clear");
    
    return opc;
}

void cadastrar(tipoLista *lista){
    
    tipoNo *novoNo = (tipoNo*)malloc(sizeof(tipoNo));
    if(!novoNo){
        printf("Impossível alocar");
    } else{
        printf("Músico: ");
        gets(novoNo->nomeDoMusico);
        fflush(stdin);
        printf("Nome do instrumento: ");
        gets(novoNo->nomeDoInstrumento);
        fflush(stdin);
        volta: printf("Ano de compra do instrumento (yyyy): ");
        scanf("%4d%*c", &novoNo->anoDeCompra);
        if (novoNo->anoDeCompra > 2020){
            printf("ANO INVÁLIDO\n");
            goto volta;
        }else{
        printf("Preço de compra: ");
        scanf("%f%*c", &novoNo->precoDeCompra);
        }
        fflush(stdin);
        
    novoNo->proximo = lista->head;
   	lista->head = novoNo;  
    }
}


void escolha(tipoLista *lista, int opc){  
    switch(opc){
        case 1:
            cadastrar(lista);
            break;
            
        case 2:
            exlcuirInstrumento(lista);
            break;
           
            
        case 3:
            imprimirInstrumentos(lista);
            break;
         
        case 4:
            buscarMusico(lista);
            break;
        
        case 5:
            calculaMedia(lista);
            break;
            
        case 6: 
            printf("\nPROGRAMA ENCERRADO COM SUCESSO!\n");
            break;
            
        default:
            printf("\nCÓDIGO INVÁLIDO!\n");
            break;
    } 
}

void imprimirInstrumentos(tipoLista *lista){
    
    printf("\n\n ---------- LISTAGEM DE INSTRUMENTOS ----------");
    tipoNo *aux = lista->head;
    if(lista->head == NULL){
        printf("\nNENHUM ELEMENTO NA LISTA!\nPOR FAVOR, ESCOLHA A OPÇÃO 1 PARA CADASTRO\n");
    }else{
        while(aux != NULL){
            printf("\n - %s", aux->nomeDoInstrumento);
            aux = aux->proximo;
        }    
        printf ("\n\nPressione qualquer tecla para continuar...\n");
        getchar();
    }
}

void calculaMedia(tipoLista *lista){
    int cont = 0;
    float soma = 0;
    tipoNo *aux = lista->head;
    
    if(aux == NULL){
        printf("\nNENHUM ELEMENTO NA LISTA!\nPOR FAVOR, ESCOLHA A OPÇÃO 1 PARA CADASTRO\n");
        printf ("\nPressione qualquer tecla para continuar...\n");
        getchar();
    }else{
        while(aux != NULL){
        soma += aux->anoDeCompra;
        cont++;
        aux = aux->proximo;
    }
    printf("\n\nIdade média dos instrumentos: %.1f anos", soma/cont);
    printf ("\nPressione qualquer tecla para continuar...\n");
    getchar();
    }
}

void buscarMusico(tipoLista *lista){
    char nome [100];
    int flag = 0;
    
    tipoNo *aux = lista->head;
    if(lista->head == NULL){
        printf("\nNENHUM ELEMENTO NA LISTA!\nPOR FAVOR, ESCOLHA A OPÇÃO 1 PARA CADASTRO\n");
    }else{
        printf("\n\nPor qual músico gostaria de procurar? ");
        gets(nome);
        
        while(aux != NULL){
            if (strcmp(aux->nomeDoMusico, nome) == 0){
                printf("------------------");
                printf("\nNome do instrumento: %s", aux->nomeDoInstrumento);
                printf("\nAno de compra: %d", aux->anoDeCompra);
                printf("\nPreço de compra: %1.f", aux->precoDeCompra); 
                printf("\n");
                flag = 1;
            }
        	aux = aux->proximo;
        }
        if(!flag){
            printf("Dado não encontrado. Vereifique o nome a ser procurado.");
        }
    	printf ("\nPressione qualquer tecla para continuar...\n");
        getchar();
    }
}

void exlcuirInstrumento(tipoLista *lista){
    char nomeInstrumento[50];
    char nomeMusico[100];
    int flag = 0;
    
    tipoNo *anterior, *atual;
    
    printf("\nDigite o nome do instrumento que deseja deletar: ");
    gets(nomeInstrumento);
    fflush(stdin);
    printf("\nDe qual músico é esse instrumento? ");
    gets(nomeMusico);
    fflush(stdin);
    
    if(lista->head == NULL){
        printf("\nLISTA SEM NENHUM INSTRUMENTO CADASTRADO!");
    }else {
       anterior = lista->head;
       atual = lista->head;
       while(atual != NULL){
           if (strcmp(atual->nomeDoMusico, nomeMusico) == 0 && strcmp(atual->nomeDoInstrumento, nomeInstrumento)  == 0){
               if(atual == lista->head){
                   lista->head = lista->head->proximo;
                   free(atual);
                   printf("\nINSTRUMENTO DELETADO COM SUCESSO!");
                   flag = 1;
                   break;
               }else{
                   if(atual == lista->fim){
                       lista->fim = anterior;
                   }
                   anterior->proximo = atual->proximo;
                   free(atual);
                   printf("\nINSTRUMENTO DELETADO COM SUCESSO!");
                   flag=1;
                   break;
               }
           }else{
               anterior = atual;
               atual = atual->proximo;
           }
       }
       if(!flag){
           printf("\nNENHUM DADO ENCONTRADO!");
       }
        printf ("\nPressione qualquer tecla para continuar...\n");
        getchar();
    }
}

