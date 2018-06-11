#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

/*Estrutura agenda */
typedef struct agenda
{
    char registro[10];
    char nome[50];
    char email[30];
    int telefone;
    float p1, p2, p3, media;
    char classe[10];
}agenda;

/*Varivaies globais*/
FILE *arq;
agenda contato;

/*Funcao menu, onde retorna alguma opcao*/
char menu()
{
    system("cls");
    printf("***************  Lista de Alunos: ***************\n");
    printf("\n");
    printf("[1] - Adicionar aluno\n");
    printf("[2] - Mostrar lista de alunos\n");
    printf("[3] - Procurar aluno pelo Nome\n");
    printf("[4] - Procurar aluno pelo Registro\n");
    printf("[5] - Modificar aluno\n");
    printf("[6] - Remover aluno\n");
    printf("[7] - Mostra lista da classe\n");
    printf("[0] - Sair\n");
    printf("\n");
    printf("> ");
    return (toupper(getche()));
}

/*Funcao que serve para verificar se no arquivo "banco.bin", já existe nome do contato, retornando 1*/
int verifica(char nome[]){
    fread(&contato,sizeof(agenda),1,arq);
    while(!feof(arq)){
        if (strcmp(contato.nome,nome) == 0){
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&contato,sizeof(agenda),1,arq);
    }

    return 0;
}

/*Funcao que serve para verificar se no arquivo "banco.bin", já existe o registro do aluno, retornando 1*/
int verifica_registro(char registro[]){
    fread(&contato,sizeof(agenda),1,arq);
    while(!feof(arq)){
        if (strcmp(contato.registro,registro) == 0){
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&contato,sizeof(agenda),1,arq);
    }

    return 0;
}

int verifica_classe(char classe[]){
    fread(&contato,sizeof(agenda),1,arq);
    while(!feof(arq)){
        if (strcmp(contato.classe,classe) == 0){
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&contato,sizeof(agenda),1,arq);
    }

    return 0;
}

/*Funcao que serve para verificar se no arquivo "banco.bin", já existe telefone do contato, retornando 1*/
int verifica_num(int num){
    fread(&contato,sizeof(agenda),1,arq);
    while(!feof(arq)){
        if (contato.telefone == num){
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&contato,sizeof(agenda),1,arq);
    }
    return 0;
}

/*Funcao para add contatos na agenda*/
void adicionar_contato(){

    char nome[50];
    char registro[10];
    char email[30];
    float p1, p2, p3, media;
    char classe[10];

    arq = fopen("banco.bin","a+b");
    if (arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o registro do aluno: ");
    fflush(stdin);
    gets(registro);

    printf("\n\n");
    printf("Digite a qual classe pertence o aluno: ");
    fflush(stdin);
    gets(classe);

    printf("\n\n");
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);

    printf("\n\n");
    printf("Digite o email: ");
    fflush(stdin);
    gets(email);

    if(verifica_registro(registro) == 1){

        if(verifica(nome) == 1){

            printf("\nNome ja existente.\n");
        }
        printf("\nRegistro ja existente.\n");
    }
    else{

        strcpy(contato.registro,registro);
        strcpy(contato.classe,classe);
        strcpy(contato.nome,nome);
        strcpy(contato.email,email);

        printf("\n\n");
        printf("Digite as notas da P1, P2 e P3 respectivamente: ");
        scanf("%f", &contato.p1);
        scanf("%f", &contato.p2);
        scanf("%f", &contato.p3);

        contato.media = ((contato.p1 + contato.p2 + contato.p3)/3);

        printf("\n\n");
        printf("Digite o telefone: ");
        scanf("%d", &contato.telefone);
        fwrite(&contato,sizeof(agenda),1,arq);
    }
    fclose(arq);
}

/*Funcao para modificar contato*/
void modificar(){
    char nome[50];
    char email[30];
    char registro[10];
    float p1, p2, p3;

    arq = fopen("banco.bin","r+b");
    if (arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite nome do aluno: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1){

        printf("\nDigite o novo nome do aluno: ");
        fflush(stdin);
        gets(nome);
        strcpy(contato.nome,nome);

        printf("\nDigite o novo registro do aluno: ");
        fflush(stdin);
        gets(registro);
        strcpy(contato.registro,registro);

        printf("\nDigite um novo numero de telefone do aluno: ");
        scanf("%d", &contato.telefone);

        printf("\nDigite o novo email do aluno: ");
        fflush(stdin);
        gets(email);
        strcpy(contato.email,email);

        printf("\nDigite as notas da P1, P2 e P3 respectivamente: ");
        scanf("%f", &contato.p1);
        scanf("%f", &contato.p2);
        scanf("%f", &contato.p3);

        contato.media = ((contato.p1 + contato.p2 + contato.p3)/3);

        fwrite(&contato,sizeof(agenda),1,arq);
    }

    else{
        printf("\nNome nao existe.\n");
    }

    fclose(arq);
}

/*Funcao para remover contato*/
void remover_contato()
{
    char nome[50];
    FILE *tmp;

    arq = fopen("banco.bin","r+b");
    if (arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    tmp = fopen("banco.txt","a+b");

    printf("\n\n");
    printf("Digite nome do contato: ");
    fflush(stdin);
    gets(nome);

    fread(&contato,sizeof(agenda),1,arq);
    while (!feof(arq)){

        if (strcmp(contato.nome,nome) != 0){ //compara o nome, para exceder

           fwrite(&contato,sizeof(agenda),1,tmp); //grava no arquivo temp
        }
        fread(&contato,sizeof(agenda),1,arq); //lê arquivo

    }
    fclose(arq);
    fclose(tmp);

    system("del banco.bin");
    system("ren banco.txt banco.bin");
}

/*Procura contato pelo nome*/
void procura_nome(){

    char nome[50];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1){
        fread(&contato,sizeof(agenda),1,arq);
        printf("\n\n");
        printf("----------------------------------------------------------------------\n");
        printf("REGISTRO            |            ALUNOS          |            TELEFONE\n");
        printf("%-20s             %-20s         %8d\n", contato.registro, contato.nome, contato.telefone);
        printf("----------------------------------------------------------------------\n");
        printf("EMAIL               |            P1              |            P2\n");
        printf("%-20s             %.1f                          %.1f\n", contato.email, contato.p1, contato.p2);
        printf("----------------------------------------------------------------------\n");
        printf("P3                  |            MEDIA            |           CLASSE\n");
        printf("%.1f                              %.1f                          %-20s\n", contato.p3, contato.media,contato.classe);
        printf("----------------------------------------------------------------------\n");
    }

    else
    {
        printf("\nContato nao existe.\n");
    }

    fclose(arq);
}

/*Procura contato pelo telefone*/
void procura_num()
{
    char registro[10];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o numero do registro: ");
    fflush(stdin);
    gets(registro);

    if (verifica_registro(registro) == 1)
    {
        fread(&contato,sizeof(agenda),1,arq);
        printf("\n\n");
        printf("----------------------------------------------------------------------\n");
        printf("REGISTRO            |            ALUNOS          |            TELEFONE\n");
        printf("%-20s             %-20s         %8d\n", contato.registro, contato.nome, contato.telefone);
        printf("----------------------------------------------------------------------\n");
        printf("EMAIL               |            P1              |            P2\n");
        printf("%-20s             %.1f                          %.1f\n", contato.email, contato.p1, contato.p2);
        printf("----------------------------------------------------------------------\n");
        printf("P3                  |            MEDIA            |           CLASSE\n");
        printf("%.1f                              %.1f                          %-20s\n", contato.p3, contato.media,contato.classe);
        printf("----------------------------------------------------------------------\n");

    }

    else
    {
        printf("\nContato nao existe.\n");
    }

    fclose(arq);
}

void procura_classe()
{
    char classe[10];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o nome da classe: ");
    fflush(stdin);
    gets(classe);

    if(verifica_classe(classe) == 1){
        while(verifica_classe(classe) == 1){
            fread(&contato,sizeof(agenda),1,arq);
            printf("\n\n");
            printf("----------------------------------------------------------------------\n");
            printf("REGISTRO            |            ALUNOS          |            TELEFONE\n");
            printf("%-20s             %-20s         %8d\n", contato.registro, contato.nome, contato.telefone);
            printf("----------------------------------------------------------------------\n");
            printf("EMAIL               |            P1              |            P2\n");
            printf("%-20s             %.1f                          %.1f\n", contato.email, contato.p1, contato.p2);
            printf("----------------------------------------------------------------------\n");
            printf("P3                  |            MEDIA            |           CLASSE\n");
            printf("%.1f                              %.1f                          %-20s\n", contato.p3, contato.media,contato.classe);
            printf("----------------------------------------------------------------------\n");
        }
    }

    else
    {
        printf("\Classe nao existe.\n");
    }


    fclose(arq);
}

/*Lista contatos*/
void mostrar_lista()
{
    arq = fopen("banco.bin","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

        printf("\n\n");
        printf("----------------------------------------------------------------------\n");
        printf("REGISTRO            |            ALUNOS          |            TELEFONE\n");
        printf("----------------------------------------------------------------------\n");
        printf("EMAIL               |            P1              |            P2\n");
        printf("----------------------------------------------------------------------\n");
        printf("P3                  |            MEDIA            |           CLASSE\n");
        printf("----------------------------------------------------------------------\n");

    fread(&contato,sizeof(agenda),1,arq);
    while (!feof(arq))
    {
        printf("**********************************************************************\n");
        printf("----------------------------------------------------------------------\n");
        printf("%-20s           %-20s           %8d\n", contato.registro, contato.nome, contato.telefone);
        printf("----------------------------------------------------------------------\n");
        printf("%-20s           %.1f                            %.1f\n", contato.email, contato.p1, contato.p2);
        printf("----------------------------------------------------------------------\n");
        printf("%.1f                              %.1f                          %-20s\n", contato.p3, contato.media,contato.classe);
        printf("----------------------------------------------------------------------\n");
        fread(&contato,sizeof(agenda),1,arq);
    }
        printf("----------------------------------------------------------------------\n");

    fclose(arq);
}

/*Funcao principal*/
int main()
{
    char op;

    do
    {
        op = menu();

        switch(op)
        {
            case '1': adicionar_contato(); break;
            case '2': mostrar_lista(); break;
            case '3': procura_nome(); break;
            case '4': procura_num(); break;
            case '5': modificar(); break;
            case '6': remover_contato(); break;
            case '7': procura_classe(); break;
        }

        printf("\n");
        system("PAUSE");

    }while (op != '0');

    return 0;
}
