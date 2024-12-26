#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct base das passagens
typedef struct
{
    int id;
    char aeorigem[4], aedestino[4];
    char cidorigem[50], ciddestino[50];
    char data[20];
    char horapartida[6], horachegada[6];
    float valor;
} passagem;

// struct com as váriaveis que determinam tempo
typedef struct
{
    int dia;
    int mes;
    int ano;
    int hora, horach;
    int min, minch;
} data;

// struct com o idanterior, o total de passagens e um vetor para a struct de
// tempo e base de passagens
typedef struct
{
    int idanterior;
    int totpassagens;
    passagem vet[100];
    data vetor[100];
} passagens;

void importarbd(passagens *lista)
{
    FILE *arq;
    arq = fopen("passagens.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        exit(0);
    }

    // a -> signifca que a lista esta apontando para o conteudii da variavel,
    // nesse caso para o conteúdo do total de passagens
    fscanf(arq, "%d", &lista->totpassagens);
    fscanf(arq, "%d", &lista->idanterior);

    for (int i = 0; i < lista->totpassagens; i++)
    {
        // %*c é semelhante a um getc(), pois ele come um char e descarta
        fscanf(arq, "%d %*c", &lista->vet[i].id);
        // ele esta scaneando até achar o ;
        fscanf(arq, "%[^;] %*c", lista->vet[i].aeorigem);
        fscanf(arq, "%[^;] %*c", lista->vet[i].aedestino);
        fscanf(arq, "%[^;] %*c", lista->vet[i].cidorigem);
        fscanf(arq, "%[^;] %*c", lista->vet[i].ciddestino);
        fscanf(arq, "%d %*c", &lista->vetor[i].dia);
        fscanf(arq, "%d %*c", &lista->vetor[i].mes);
        fscanf(arq, "%d %*c", &lista->vetor[i].ano);
        fscanf(arq, "%d %*c", &lista->vetor[i].hora);
        fscanf(arq, "%d %*c", &lista->vetor[i].min);
        fscanf(arq, "%d %*c", &lista->vetor[i].horach);
        fscanf(arq, "%d %*c", &lista->vetor[i].minch);
        fscanf(arq, "%f", &lista->vet[i].valor);
        // se o id for maior que o id anterior, o id anterior tem o mesmo valor que
        // o id
        if (lista->vet[i].id > lista->idanterior)
        {
            lista->idanterior = lista->vet[i].id;
        }
    }

    fclose(arq);
}

void listarpassagens(passagens *lista)
{

    if (lista->totpassagens == 0)
    {
        printf("Nenhuma passagem cadastrada. \n\n");
    }
    else
    {
        printf("Possuemn %d passagens cadastardas. \n", lista->totpassagens);
        for (int i = 0; i < lista->totpassagens; i++)
        {
            printf("\nO id e: %d", lista->vet[i].id);
            printf("\nO aeroporte de origem e: %s", lista->vet[i].aeorigem);
            printf("\nO aeroporte de destino e: %s", lista->vet[i].aedestino);
            printf("\nAcidade de origem e: %s", lista->vet[i].cidorigem);
            printf("\nA cidade de destino e: %s", lista->vet[i].ciddestino);
            // a função %02d ela printa o número com um zero antes dele quando ele é
            // menor do que 10
            printf("\nA data e: %02d/%02d/%d", lista->vetor[i].dia,
                   lista->vetor[i].mes, lista->vetor[i].ano);
            printf("\nA hora de partida e: %02d:%02d", lista->vetor[i].hora,
                   lista->vetor[i].min);
            printf("\nA hora de chegada e: %02d:%02d", lista->vetor[i].horach,
                   lista->vetor[i].minch);
            printf("\nO valor da passagem e: %.2f\n\n", lista->vet[i].valor);
        }
    }
}

void pesquisarpassagem(passagens *lista)
{

    char string[80];
    int opcao;

    printf("\n\n1. Id\n");
    printf("2. Aeroporto de origem\n");
    printf("3. Aeroporto de destino\n");
    printf("4. Cidade de origem\n");
    printf("5. Cidade de destino\n");
    printf("\nDigite opcao de pesquisa voce deseja: ");
    scanf("%d", &opcao);

    printf("\nDigite a chave de pesquisa: ");
    scanf("%s", string);

    // uma booleana para definir se acchou oiu não a afirmação necessária, no caso
    // quando true é pq achou
    bool achou = false;

    // variável que é trocada por i em cada for para que possa printar apenas uma
    // vez no final da função
    int pos;

    switch (opcao)
    {

    case 1:
        for (int i = 0; !achou && i < lista->totpassagens; i++)
        {
            // atoi é para transformar strings em numeros
            int id = atoi(string);
            if (id == lista->vet[i].id)
            {
                pos = i;
                achou = true;
            }
        }
        break;

    case 2:
        for (int i = 0; !achou && i < lista->totpassagens; i++)
        {
            // strcasecmp ignora letras maiúsculas e minúsculas e compara as duas, no
            // caso de 0 elas são iguais.
            if (strcasecmp(string, lista->vet[i].aeorigem) == 0)
            {
                pos = i;
                achou = true;
            }
        }
        break;

    case 3:
        for (int i = 0; !achou && i < lista->totpassagens; i++)
        {
            // strcasecmp ignora letras maiúsculas e minúsculas e compara as duas, no
            // caso de 0 elas são iguais.
            if (strcasecmp(string, lista->vet[i].aedestino) == 0)
            {
                pos = i;
                achou = true;
            }
        }
        break;

    case 4:
        for (int i = 0; !achou && i < lista->totpassagens; i++)
        {
            if (strcasecmp(string, lista->vet[i].cidorigem) == 0)
            {
                pos = i;
                achou = true;
            }
        }
        break;

    case 5:
        for (int i = 0; !achou && i < lista->totpassagens; i++)
        {
            if (strcasecmp(string, lista->vet[i].ciddestino) == 0)
            {
                pos = i;
                achou = true;
            }
        }
        break;
    }

    if (achou)
    {
        printf("\nO id e: %d", lista->vet[pos].id);
        printf("\nO aeroporte de origem e: %s", lista->vet[pos].aeorigem);
        printf("\nO aeroporte de destino e: %s", lista->vet[pos].aedestino);
        printf("\nAcidade de origem e: %s", lista->vet[pos].cidorigem);
        printf("\nA cidade de destino: %s", lista->vet[pos].ciddestino);
        printf("\nA data e: %02d/%02d/%d", lista->vetor[pos].dia,
               lista->vetor[pos].mes, lista->vetor[pos].ano);
        printf("\nA hora de partida e: %02d:%02d", lista->vetor[pos].hora,
               lista->vetor[pos].min);
        printf("\nA hora de chegada e: %02d:%02d", lista->vetor[pos].horach,
               lista->vetor[pos].minch);
        printf("\nO valor da passagem e: %.2f\n\n", lista->vet[pos].valor);
    }
    else
    {
        printf("Passagem nao encontrada.\n\n");
    }
}

void cadastrarpassagem(passagens *lista)
{

    int x = 4, y = 4;

    char bf[80];

    while (y > 3)
    {
        printf("Digite o aeroporto de origem (3 letras): ");
        scanf(" %[^\n]", lista->vet[lista->totpassagens].aeorigem);
        y = strlen(lista->vet[lista->totpassagens].aeorigem);
    }

    while (x > 3)
    {
        printf("Digite o aeroporto de destino (3 letras): ");
        scanf(" %[^\n]", lista->vet[lista->totpassagens].aedestino);
        x = strlen(lista->vet[lista->totpassagens].aedestino);
    }

    printf("Digite a cidade de origem: ");
    scanf(" %[^\n]", lista->vet[lista->totpassagens].cidorigem);

    printf("Digite a cidade de destino: ");
    scanf(" %[^\n]", lista->vet[lista->totpassagens].ciddestino);

    int aux;
    // variavel criada para apenas facilitar a visualização dos whiles
    do
    {
        printf("Digite o dia : ");
        scanf(" %d", &lista->vetor[lista->totpassagens].dia);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].dia;
    }
    while (!(0 < aux && aux <= 31));

    do
    {
        printf("Digite o mes : ");
        scanf(" %d", &lista->vetor[lista->totpassagens].mes);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].mes;
    }
    while (!(0 < aux && aux <= 12));

    do
    {
        printf("Digite o ano : ");
        scanf(" %d", &lista->vetor[lista->totpassagens].ano);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].ano;
    }
    while (!(2023 < aux && aux <= 9999));

    do
    {
        printf("Digite a hora de partida :");
        scanf(" %d", &lista->vetor[lista->totpassagens].hora);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].hora;
    }
    while (!(0 <= aux && aux < 24));

    do
    {
        printf("Digite os minutos de partida :");
        scanf(" %d", &lista->vetor[lista->totpassagens].min);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].min;
    }
    while (!(0 <= aux && aux <= 59));

    do
    {
        printf("Digite a hora de chegada: ");
        scanf(" %d", &lista->vetor[lista->totpassagens].horach);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].horach;
    }
    while (!(0 <= aux && aux < 24));

    do
    {
        printf("Digite os minutos de chegada:");
        scanf(" %d", &lista->vetor[lista->totpassagens].minch);
        fgets(bf, 80, stdin);
        aux = lista->vetor[lista->totpassagens].minch;
    }
    while (!(0 <= aux && aux <= 59));

    printf("Digite o valor da passagem: ");
    scanf("%f", &lista->vet[lista->totpassagens].valor);

    printf("\nPassagem pasastrada com sucesso !!\n\n");

    // adiciona o total de passagens e o valor do id anterior
    lista->vet[lista->totpassagens++].id = ++lista->idanterior;
}

void salvarArquivo(passagens lista)
{
    FILE *arq;
    arq = fopen("passagens.txt", "w");

    fprintf(arq, "%d\n", lista.totpassagens);
    fprintf(arq, "%d\n", lista.idanterior);
    for (int i = 0; i < lista.totpassagens; i++)
    {
        fprintf(arq, "%d;", lista.vet[i].id);
        fprintf(arq, "%s;", lista.vet[i].aeorigem);
        fprintf(arq, "%s;", lista.vet[i].aedestino);
        fprintf(arq, "%s;", lista.vet[i].cidorigem);
        fprintf(arq, "%s;", lista.vet[i].ciddestino);
        fprintf(arq, "%02d/", lista.vetor[i].dia);
        fprintf(arq, "%02d/", lista.vetor[i].mes);
        fprintf(arq, "%d;", lista.vetor[i].ano);
        fprintf(arq, "%02d:", lista.vetor[i].hora);
        fprintf(arq, "%02d;", lista.vetor[i].min);
        fprintf(arq, "%02d:", lista.vetor[i].horach);
        fprintf(arq, "%02d;", lista.vetor[i].minch);
        fprintf(arq, "%.2f\n", lista.vet[i].valor);
    }
    fclose(arq);
}

void editarpassgaem(passagens *lista)
{

    int id;
    char bf[80];

    // a variável bf foi criada para limpar o buffer caso o usuário digite letra
    // no local de numeros
    printf("\n\nDigite o ID da passagem: ");
    scanf("%d", &id);

    bool achou = false;

    for (int i = 0; i < lista->totpassagens; i++)
    {
        if (id == lista->vet[i].id)
        {
            achou = true;

            printf("\nO aeroporte de origem e: %s", lista->vet[i].aeorigem);
            printf("\nO aeroporte de destino e: %s", lista->vet[i].aedestino);
            printf("\nAcidade de origem e: %s", lista->vet[i].cidorigem);
            printf("\nA cidade de destino: %s", lista->vet[i].ciddestino);
            printf("\nA data e: %02d/%02d/%d", lista->vetor[i].dia,
                   lista->vetor[i].mes, lista->vetor[i].ano);
            printf("\nA hora de partida e: %02d:%02d", lista->vetor[i].hora,
                   lista->vetor[i].min);
            printf("\nA hora de chegada e: %02d:%02d", lista->vetor[i].horach,
                   lista->vetor[i].minch);
            printf("\nO valor da passagem e: %.2f\n\n", lista->vet[i].valor);

            printf("\n\nDigite as novas informacoes!!");

            int y = 4, x = 4;

            while (y > 3)
            {
                printf("\n\nDigite o aeroporto de origem (3 letras): ");
                scanf(" %[^\n]", lista->vet[i].aeorigem);
                y = strlen(lista->vet[i].aeorigem);
            }

            while (x > 3)
            {
                printf("Digite o aeroporto de destino (3 letras): ");
                scanf(" %[^\n]", lista->vet[i].aedestino);
                x = strlen(lista->vet[i].aedestino);
            }

            printf("Digite a cidade de origem: ");
            scanf(" %[^\n]", lista->vet[i].cidorigem);

            printf("Digite a cidade de destino: ");
            scanf(" %[^\n]", lista->vet[i].ciddestino);

            int aux;
            // variavel criada para apenas facilitar a visualização dos whiles
            do
            {
                printf("Digite o dia : ");
                scanf(" %d", &lista->vetor[i].dia);
                aux = lista->vetor[i].dia;
                fgets(bf, 80, stdin);
            }
            while (!(0 < aux && aux <= 31));

            do
            {
                printf("Digite o mes : ");
                scanf(" %d", &lista->vetor[i].mes);
                aux = lista->vetor[i].mes;
                fgets(bf, 80, stdin);
            }
            while (!(0 < aux && aux <= 12));

            do
            {
                printf("Digite o ano : ");
                scanf(" %d", &lista->vetor[i].ano);
                aux = lista->vetor[i].ano;
                fgets(bf, 80, stdin);
            }
            while (!(2023 < aux && aux <= 9999));

            do
            {
                printf("Digite a hora de partida :");
                scanf(" %d", &lista->vetor[i].hora);
                aux = lista->vetor[i].hora;
                fgets(bf, 80, stdin);
            }
            while (!(0 <= aux && aux < 24));

            do
            {
                printf("Digite os minutos de partida :");
                scanf(" %d", &lista->vetor[i].min);
                aux = lista->vetor[i].min;
                fgets(bf, 80, stdin);
            }
            while (!(0 <= aux && aux <= 59));

            do
            {
                printf("Digite a hora de chegada: ");
                scanf(" %d", &lista->vetor[i].horach);
                aux = lista->vetor[i].horach;
                fgets(bf, 80, stdin);
            }
            while (!(0 <= aux && aux < 24));

            do
            {
                printf("Digite os minutos de chegada:");
                scanf(" %d", &lista->vetor[i].minch);
                aux = lista->vetor[i].minch;
                fgets(bf, 80, stdin);
            }
            while (!(0 <= aux && aux <= 59));

            printf("Digite o valor da passagem: ");
            scanf("%f", &lista->vet[i].valor);

            printf("\nPassagem editada com sucesso !!\n\n");
        }
    }
    if (achou == false)
    {
        printf("\nPassagem nao encontrada\n\n");
    }
}

void excluirpassagem(passagens *lista)
{

    int id;
    printf("Digite o Id da passagem: ");
    scanf("%d", &id);

    for (int i = 0; i < lista->totpassagens; i++)
    {
        if (id == lista->vet[i].id)
        {
            // a troca da passagem da posição i pela última passagem.
            lista->vet[i] = lista->vet[--lista->totpassagens];
            printf("Passagem excluida com sucesso !!\n\n");
        }
    }
    if (lista->totpassagens == 0)
        lista->idanterior = 0;
}

int main(void)
{

    int opcao = 0;

    // passagens é uma strcut que contêm outras structs
    passagens lista;

    importarbd(&lista);

    while (opcao != 6)
    {

        printf("\tSeja bem vindo ao Menu de Passagens !!\n\n");
        printf("1. Listar todas as passagens.\n");
        printf("2. Pesquisar uma passagem\n");
        printf("3. Cadastrar uma passagem\n");
        printf("4. Editar uma passagem\n");
        printf("5. Excluir uma passagem\n");
        printf("6. sair do programa\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // limpar o buffer, com o fgets que limpa tudo que possui na linha do buffer
        char bf[80];
        fgets(bf, 80, stdin);

        switch (opcao)
        {

        case 1:
            listarpassagens(&lista);
            break;
        case 2:
            pesquisarpassagem(&lista);
            break;
        case 3:
            cadastrarpassagem(&lista);
            salvarArquivo(lista);
            break;
        case 4:
            editarpassgaem(&lista);
            salvarArquivo(lista);
            break;
        case 5:
            excluirpassagem(&lista);
            salvarArquivo(lista);
            break;
        case 6:
            printf("Programa encerrado.");
            return 0;
            break;
        default:
            printf("\nOpcao invalida. selecione outra opcao.\n\n");
            break;
        }
    }
}
