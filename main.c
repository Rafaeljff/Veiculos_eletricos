#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define CARGA 40
#define CONSUMO_TEORICO 0.13333   /**  Consumo é a divisao da capacidade de carga pela distancia percorrida segundo o enunciado ,
                                    é  dito que 40KWh equivale a 300 kms porntanto 40/300=0.133,usei esse valor para o
                                    consumo teorico */
typedef struct
{
    int dia;
    int mes;
    int ano;
} struct_data;

typedef struct
{
    int horas;
    int minutos;

} t_hora;

typedef struct
{

    int numero_ident;
    char designacao[50];
    int estado;
    float carga_bateria;
    int dist_percorrida;
    float custo_carregamento;
    int vezes_requisitada;
    struct_data data_ult_req;



} t_viatura;

typedef struct
{

    t_viatura viatura;

    int dist_prevista;
    char nome[50];
    struct_data data_requisicao;
    t_hora hora_req;

    int dist_real;
    float consumo_real;
    t_hora hora_entrega;
    struct_data data_entrega;

} t_emprestimo;

/**Nova viatura*/
int func_nova_viatura(t_viatura v[],int pos,int *dist);
int verificar_identidade(int num,t_viatura v[],int pos );


/**Registo de carregamento*/
int  verificar_carregamento(t_viatura v[],int pos,int numero_carregamentos);
void carregamento(t_viatura v[],int pos,int viatura);

/**Registo de requisicao*/
int verificar_emprestimo(t_viatura v[],t_emprestimo e[],int pos,int pos2);
void emprestimo(t_viatura v[],t_emprestimo e[],int pos,int pos2);

/**Registo de devolucao*/
void verificar_devolucao(t_viatura v[],t_emprestimo e[],int pos,int pos2,int *dist);
void devolucao(t_viatura v[],t_emprestimo e[],int pos,int pos2,int *dist);

/**Listagem*/
void listagem(t_viatura v[],int pos);
void estado(int estado);

/**Informacoes*/
char menu_informacoes(char escolha);
void informacao_viatura(t_viatura v[],t_emprestimo e[],int pos,int pos2);
void dist_media(t_emprestimo e[],int pos);
void custo_carregamento(t_viatura v[],int pos);
void menor_dist(t_emprestimo e[],int pos);
void data_entrega(t_emprestimo e[],int pos);
void nao_requisitados(t_viatura v[],int pos);
void consumo(t_emprestimo e[],int pos);

/**Gravar*/
void gravar_dados_ficheiro(t_viatura v[],int pos);
void ler_dados_ficheiro(t_viatura v[],int pos);

/**validações e comparações de datas e horas*/
int validar_data(int dia,int mes, int ano);
int comparar_data(int dia,int mes,int ano,int dia2,int mes2,int ano2);
int validar_hora(int hora,int min);
int comparar_hora(int hora,int min,int hora2,int min2);




int main()
{
    t_viatura nova_viatura[10]= {NULL};
    t_emprestimo novo_emprestimo[50]= {NULL};
    int contador_viaturas=0,contador_emprestimos=0,numero_carregamentos=0,dist_percorrida=0;


    char menu;
    do
    {

        system("cls");

        printf("\t\t\tGESTAO DE VEICULOS ELETRICOS" );

        printf("\n\n\n\n\t\tTotal de Viaturas:%d",contador_viaturas);
        printf("\t\tDistancia percorrida(kms):%d",dist_percorrida);

        printf("\n\n\n\t\tRequisicoes de viaturas:%d",contador_emprestimos);
        printf("\t\tTotal de carregamentos:%d",numero_carregamentos);


        printf("\n\n\n\n\n\t1.Nova Viatura\n\n");
        printf("\t2.Registo de Carregamento \n\n");
        printf("\t3.Registo de Requisicao\n\n");
        printf("\t4.Registo de Devolucao\n\n");
        printf("\t5.Listagem\n\n");
        printf("\t6.Informacoes\n\n");
        printf("\t7.Gravar\n\n");
        printf("\t0.Sair\n\n");

        printf("\t\tSelecione a opcao");
        do
        {
            fflush(stdin);
            menu=getch();
        }
        while(menu>'8'||menu<'0');


        switch(menu)
        {
        case '1':

            if (contador_viaturas<10)
            {


                system("cls");
                printf("NOVA VIATURA");
                contador_viaturas=func_nova_viatura(nova_viatura,contador_viaturas,&dist_percorrida);
                getch();
            }

            else
                printf("\nLimite maximo de 10 viaturas excedido!");
            getch();

            break;

        case '2':
            system("cls");
            printf("REGISTO DE CARREGAMENTO");
            if(contador_viaturas!=0)
                numero_carregamentos=verificar_carregamento(nova_viatura,contador_viaturas,numero_carregamentos);

            else
                printf("\n\nNao exitem viaturas inseridas!");

            getch();

            break;
        case '3':
            system("cls");
            printf("REGISTO DE REQUISICOES");
            if(contador_viaturas!=0||contador_emprestimos>49)
                contador_emprestimos=verificar_emprestimo(nova_viatura,novo_emprestimo,contador_viaturas,contador_emprestimos);

            else if(contador_viaturas==0)
                printf("\nNao existem viaturas inseridas!!");

            else
                printf("\nLimite maximo de 50 deslocacoes de frota atingido!!");

            getch();
            break;

        case '4':
            system("cls");
            printf("REGISTO DE DEVOLUCAO");
            verificar_devolucao(nova_viatura,novo_emprestimo,contador_viaturas,contador_emprestimos,&dist_percorrida);
            getch();
            break;

        case '5':
            system("cls");
            printf("LISTAGEM");
            if(contador_viaturas!=0)
                listagem(nova_viatura,contador_viaturas);
            else
                printf("\n\nNao exitem viaturas inseridas!");

            getch();
            break;

        case '6':
            system("cls");
            if(contador_viaturas!=0)
            {
                menu=menu_informacoes(menu);

                switch(menu)
                {
                case '1':
                    informacao_viatura(nova_viatura,novo_emprestimo,contador_viaturas,contador_emprestimos);
                    getch();
                    break;
                case '2':
                    if(contador_emprestimos!=0)
                        dist_media(novo_emprestimo,contador_emprestimos);
                    else
                        printf("\n\nNao existem emprestimos registados!");

                    break;

                case '3':
                    if (numero_carregamentos!=0)
                        custo_carregamento(nova_viatura,contador_viaturas);
                    else
                        printf("\n\nNao existem registos de carregamentos!");
                    break;

                case'4':
                        if (contador_emprestimos!=0)
                            menor_dist(novo_emprestimo,contador_emprestimos);
                        else
                            printf("\n\nNao existem emprestimos registados!");
                    break;

                case'5':
                        if (contador_emprestimos!=0)
                            data_entrega(novo_emprestimo,contador_emprestimos);
                        else
                            printf("\n\nNao existem emprestimos registados!");
                    break;

                case '6':
                    nao_requisitados(nova_viatura,contador_viaturas);

                case '7':
                    if (contador_emprestimos!=0)
                        consumo(novo_emprestimo,contador_emprestimos);
                    else
                        printf("\n\nNao existem emprestimos registados!");
                    break;

                }


            }
            else
                printf("\nNao existem viaturas inseridas!");
            getch();
            break;

        case '7':
            gravar_dados_ficheiro(nova_viatura,contador_viaturas);


            break;
        case '8':
            ler_dados_ficheiro(nova_viatura,contador_viaturas);
            break;
        }
    }
    while(menu!='0');

    return 0;

}




/** FUNCAO func_nova_viatura ***********************************************
* DESCRIÇÃO:Pede os valores da nova viatura
* INPUT: Array de nova_viatura[], contador de viaturas
* RETURN: contador de viaturas+1
******************************************************************/
int func_nova_viatura(t_viatura v[],int pos, int *dist)
{
    do
    {
        printf("\n\nNumero de identificacao: ");
        fflush(stdin);
        scanf("%d", &v[pos].numero_ident);
    }
    while(v[pos].numero_ident<=0||verificar_identidade(v[pos].numero_ident,v,pos)==1);



    printf("\n\ndesignacao:");
    fflush(stdin);
    gets(v[pos].designacao);



    do
    {
        printf("\n\nCarga da bateria(percentagem): ");
        fflush(stdin);
        scanf("%f",&v[pos].carga_bateria);
    }
    while(v[pos].carga_bateria>100||v[pos].carga_bateria<0);


    if(v[pos].carga_bateria>=25)
        v[pos].estado=1;
    else
        v[pos].estado=3;


    printf("\nEstado da viatura:");
    estado(v[pos].estado);

    do
    {
        printf("\n\nDistancia total percorrida pela viatura(kms): ");
        fflush(stdin);
        scanf("%d", &v[pos].dist_percorrida);
    }
    while(v[pos].dist_percorrida<=0||v[pos].dist_percorrida>1000000);



    printf("\n\nNova viatura inserida com sucesso! ");

    *dist=*dist+v[pos].dist_percorrida;
    pos++;
    return pos;
}

/** FUNCAO verificar_identidade ***********************************************
* DESCRIÇÃO:Funcão que verifica se o número de identidade
*        inserido numa nova viatura é repetido
* INPUT: Número de identidade inserido , array nova_viatura[],
*         contador de viaturas
* RETURN: 0 ou 1
******************************************************************/
int verificar_identidade(int num, t_viatura v[], int pos )
{
    int i;
    for (i=0; i<pos; i++)
    {
        if(num==v[i].numero_ident)
        {
            printf("\nNumero de identidade repetido!");
            return 1;
        }
    }
    return 0;
}



/** FUNCAO verificar_carregamento ***********************************
* DESCRIÇÃO:Verifica se existem viaturas por carregar,
            verificando de seguida se a viatura que o utilizador insere é valida para ser
            carregada, caso seja chama a função carregamento
* INPUT:  array nova_viatura[],contador de viaturas
* RETURN:numero de carregamentos total de todas as viaturas
******************************************************************/
int verificar_carregamento(t_viatura v[],int pos,int numero_carregamentos)
{
    int i;
    int encontrar=0;
    int numr;

    printf("\nViaturas por carregar:");


    /** verifica se existem viaturas por carregar**/

    for(i=0; i<pos; i++)
    {

        if(v[i].carga_bateria!=100)
        {
            printf("\nNumero de identificacao:%d   bateria: %.2f(percentagem)",v[i].numero_ident,v[i].carga_bateria);
            encontrar=1;
        }
    }
    /** Fim da verificacao**/



    /** Caso existam viaturas por carregar pede o numero da viatura ao utilizador
    ate que insira um numero de identificao da viatura valido, depois procede ao
    registo de carregamento atraves da funcao carregamento()
     **/
    if(encontrar==1)
    {

        do
        {
            encontrar=0;
            printf("\n\n\nInserir o numero de ident da viatura a carregar:");
            fflush(stdin);
            scanf("%d",&numr);

            for(i=0; i<pos; i++)
            {
                if(numr==v[i].numero_ident&&v[i].carga_bateria!=100)
                {
                    encontrar=1;
                    carregamento(v,pos,i);
                    v[i].estado=1;
                    numero_carregamentos++;

                }

            }
            if (encontrar==0)
                printf("\n\nNumero de identificacao incorreto, insira novamente! ");

        }
        while(encontrar==0);
    }

    else
    {
        printf("\n\nNao existem viaturas por carregar!");
        getch();
    }
    return numero_carregamentos;
}

/** FUNCAO carregamento ***********************************************
* DESCRIÇÃO:Efetua o carregamento de uma determinada viatura
* INPUT:array nova_viatura,contador de viaturas, posicao da viatura em causa
* RETURN:n.a
******************************************************************/
void carregamento(t_viatura v[],int pos,int viatura)
{
    float custo,carga_bateria_kwh;
    float bateria_final;
    int  escolha,autonomia;

    printf("\n\n\nCARREGAMENTO:");
    printf("\nBateria atual da viatura: %.2f(por cento)",v[viatura].carga_bateria);
    do
    {

        printf("\nCarregamento de bateria desejada(em percentagem): ");
        fflush(stdin);
        scanf("%f",&bateria_final);

        if(bateria_final<25)
        {
            printf("\n\nAtencao! A bateria tem de ser carregada pelo menos ate 25(por cento)!");
        }
    }
    while(bateria_final<=v[viatura].carga_bateria||bateria_final<25||bateria_final>100);

    do
    {
        printf("\nCarregamento da bateria(1-normal, 2-rapido): ");
        fflush(stdin);
        scanf("%d",&escolha);

    }
    while(escolha!=1&&escolha!=2);


    carga_bateria_kwh=(bateria_final-v[viatura].carga_bateria)*CARGA/100   ; /** 40kWh=100% bateria */
    autonomia=(bateria_final/100)*300; /** 300kms=100% bateria */



    if(escolha==1)
        custo=0.2* carga_bateria_kwh;

    if(escolha==2)
        custo=0.35* carga_bateria_kwh;

    printf("Carga introduzida na viatura: %.2f KWh\nRespetivo custo:%.2f euros\nAutonomia resultante:%d kms\n\n",carga_bateria_kwh,custo, autonomia);

    v[viatura].custo_carregamento=v[viatura].custo_carregamento+custo;

    v[viatura].carga_bateria=bateria_final;

    printf("\nCarregamento efetuado com sucesso! ");
    getch();


}



/** FUNCAO verificar_emprestimo ***********************************************
* DESCRIÇÃO:Mostra as viaturas que se encontram disponiveis, caso existam
            pergunta ao utilizador a distancia prevista a ser percorrida, caso haja viaturas
            com autonomia para tal pede o numero de ident de uma dessas viaturas executando assim
            a funcao emprestimo
*INPUT:array nova_viatura,array novo_emprestimo, contador de viaturas ,contador de emprestimos
* RETURN:contador de emprestimos+1
******************************************************************/
int verificar_emprestimo(t_viatura v[],t_emprestimo e[],int pos,int pos2)
{
    int i,numr,encontrar=0,distancia;
    printf("\n\nViaturas disponiveis para requisitar:");


    for(i=0; i<pos; i++)
    {
        if(v[i].estado==1)
        {
            /**Mostra as viaturas que se encontram disponiveis*/

            printf("\nNumero de identidade: %d  Autonomia da viatura:%.0f kms",v[i].numero_ident,v[i].carga_bateria*3);
            encontrar=1;
        }
    }


    /**Caso existam viaturas disponiveis executa:*/
    if(encontrar==1)
    {
        encontrar=0;

        do
        {

            /**Pergunta a distancia que o utilizador pretende percorrer*/
            printf("\n\n\nDistancia prevista a ser percorrida (kms): ");
            fflush(stdin);
            scanf("%d",&distancia);

            if(distancia>300)
                printf("\nAtencao! O maximo de distancia prevista a ser percorrida e de 300kms");
            if(distancia<25)
                printf("\nAtencao!A distancia minima de requisicao e 25 kms");
        }
        while(distancia>300||distancia<25);

        /**Mostra as viaturas com  autonomia suficiente para percorrer essa distancia*/
        system("cls");
        printf("\nViaturas com autonomia sufuciente para %d kms:",distancia);
        for(i=0; i<pos; i++)
        {
            if(v[i].estado==1&&(v[i].carga_bateria*3)>=distancia)
            {

                printf("\n\nNumero de identidade: %d  Autonomia:%.0f kms",v[i].numero_ident,v[i].carga_bateria*3);
                encontrar=1;
            }
        }


        if (encontrar==1)
        {
            do
            {
                encontrar=0;

                printf("\n\nInsira o numero de identidade da viatura a requisitar:");
                fflush(stdin);
                scanf("%d",&numr);
                for(i=0; i<pos; i++)
                {

                    if(numr==v[i].numero_ident&&distancia<=(v[i].carga_bateria*3)&&v[i].estado==1)
                    {

                        encontrar=1;
                        e[pos2].dist_prevista=distancia; /** Passa o valor da distancia que o utilizador visa a percorrer para o emprestimo*/
                        emprestimo(v,e,i,pos2);  /** Funcao para registar o emprestimo*/
                        v[i].vezes_requisitada++; /** Conta as vezes que a viatura foi requisitada*/
                        pos2++; /** i de emprestimos*/

                    }
                }
            }
            while(encontrar==0);
        }

        else
        {
            printf("\n\nAtencao!! Nao existem viaturas com autonomia suficiente para percorrer %d kms!!",distancia);
            getch();
        }
    }
    else
        printf("\n\n\nAtencao!! Nao existem viaturas com o estado disponivel para requisitar");

    return pos2;
}
/** FUNCAO emprestimo ***********************************************
* DESCRIÇÃO:regista a informacao referente a um novo emprestimo
INPUT:array nova_viatura,array novo_emprestimo, contador de viaturas ,contador de emprestimos
* RETURN:n.a
*/
void emprestimo(t_viatura v[],t_emprestimo e[],int pos,int pos2)
{
    int validar;

    printf("\n\n\nREQUISICAO");
    printf("\nNumero de identidade da viatura: %d",v[pos].numero_ident);
    printf("\nDistancia prevista a percorrer: %d kms",e[pos2].dist_prevista);
    printf("\nNome do requsitante: ");
    fflush(stdin);
    gets(e[pos2].nome);

    do
    {
        printf("\nInsira a hora da requisicao(hh:mm): ");
        fflush(stdin);
        scanf(" %d:%d",&e[pos2].hora_req.horas,&e[pos].hora_req.minutos);
    }
    while(validar_hora(e[pos2].hora_req.horas,e[pos2].hora_req.minutos)==0);




    do             /**Asegura que a data do novo emprestimo nao e inferior a do ultimo emprestimo*/
    {
        do
        {
            printf("\nData da requisicao(dd/mm/aa): ");
            fflush(stdin);
            scanf("%d/%d/%d",&e[pos2].data_requisicao.dia,&e[pos2].data_requisicao.mes,&e[pos2].data_requisicao.ano);

        }
        while(validar_data(e[pos2].data_requisicao.dia,e[pos2].data_requisicao.mes,e[pos2].data_requisicao.ano)==0);

        validar=comparar_data(v[pos].data_ult_req.dia,v[pos].data_ult_req.mes,v[pos].data_ult_req.ano,e[pos2].data_requisicao.dia,e[pos2].data_requisicao.mes,e[pos2].data_requisicao.ano);

        if (validar==0)
            printf("\n\n\nATENCAO! A data da nova requisicao deve ser igual ou superior a data do ultima requisicao: %d/%d/%d",v[pos].data_ult_req.dia,v[pos].data_ult_req.mes,v[pos].data_ult_req.ano);
    }
    while(validar==0);




    v[pos].estado=2;                    /**coloca a viatura em estado requisitado*/
    e[pos2].viatura=v[pos];             /**Os dados da viatura serao guardados nos dados do emprestimo*/
    v[pos].data_ult_req=e[pos2].data_requisicao;  /**A data da ultima requisicao sera igual a data da nova requisicao*/

    printf("\nRequisicao registada com sucesso!");


}

/** FUNCAO verificar_devolucao ***********************************************
* DESCRIÇÃO:Mostra e verifica se existem viaturas com o estado 2(requisitadas) se sim executa,
            pede o numr da viatura pretendida,incrementa a distancia total percorrida da viatura e chama a funcao devolucao
            para efetuar o registo de devolucao.
*INPUT:array nova_viatura,array novo_emprestimo, contador de viaturas ,contador de emprestimos,dist(distancia total percorrida declarada na main)
* RETURN:n.a
*/

void verificar_devolucao(t_viatura v[],t_emprestimo e[],int pos,int pos2,int *dist)
{
    int i,numr,encontrar=0,distancia=0;
    printf("\nViaturas em estado requisitado:");


    for(i=0; i<pos2; i++)
    {
        if(e[i].viatura.estado==2)
        {
            printf("\nNumero de identificacao da viatura:%d  Data de requisicao:%d/%d/%d ",e[i].viatura.numero_ident,e[i].data_requisicao.dia,e[i].data_requisicao.mes,e[i].data_requisicao.ano);
            encontrar=1;
        }
    }

    if(encontrar==1)
    {
        do
        {
            encontrar=0;
            i=0;
            printf("\n\nInsira o numero de identificacao da viatura a devolver:  ");
            fflush(stdin);
            scanf("%d",&numr);
            for(i=0; i<pos; i++)
            {
                if(numr==v[i].numero_ident&&v[i].estado==2)
                {
                    pos=i;
                    for(i=0; i<pos2; i++)
                    {
                        if(numr==e[i].viatura.numero_ident&&e[i].viatura.estado==2)
                        {
                            pos2=i;
                            devolucao(v,e,pos,pos2,&distancia);
                            *dist=*dist+distancia;
                            encontrar=1;
                        }
                    }
                }
            }
        }
        while(encontrar==0);
    }
    else
        printf("\n\n\nAtencao!! Nao existem viaturas para devolver");

}

/** FUNCAO devolucao ***********************************************
* DESCRIÇÃO:regista a informacao referente a uma devolucao
*INPUT:array nova_viatura,array novo_emprestimo,contador de viaturas ,contador de emprestimos,dist_percorrida)
*RETURN:n.a
*/
void devolucao(t_viatura v[],t_emprestimo e[],int pos,int pos2,int *dist)
{
    int validar;
    float carga_final_bateria;
    carga_final_bateria=(v[pos].carga_bateria-(e[pos2].dist_prevista*100/300));

    printf("\n\n\nDEVOLUCAO");

    printf("\nDistancia prevista na requisicao:%d kms",e[pos2].dist_prevista);

    do
    {
        printf("\nIntroduza a distancia efetivamente percorrida(kms): ");
        fflush(stdin);
        scanf("%d",&e[pos2].dist_real);
        e[pos2].consumo_real=(((v[pos].carga_bateria-carga_final_bateria)*40)/100)/e[pos2].dist_real;

        if(e[pos2].consumo_real>0.25||e[pos2].consumo_real<0.075)
            printf("\nO consumo real %f kWh/Km e muito diferente do consumo teorico %f kWh/Km, insira novamente a distancia percorrida",e[pos2].consumo_real,CONSUMO_TEORICO);

    }
    while(e[pos2].consumo_real>0.25||e[pos2].consumo_real<0.075);
    printf("\nConsumo da viatura %f(kWh/km) ",e[pos2].consumo_real);
    printf("\nData da requisicao: %d/%d/%d  ",e[pos2].data_requisicao.dia,e[pos2].data_requisicao.mes,e[pos2].data_requisicao.ano);
    printf("\nHora:%d:%d h",e[pos2].hora_req.horas,e[pos2].hora_req.minutos);



    do              /***************************************VALIDACAO DE DATAS**************************************************/
    {
        do
        {
            printf("\nInsira a data da devolucao(dd/mm/aa): ");
            fflush(stdin);
            scanf("%d/%d/%d",&e[pos2].data_entrega.dia,&e[pos2].data_entrega.mes,&e[pos2].data_entrega.ano);
        }
        while(validar_data(e[pos2].data_entrega.dia,e[pos2].data_entrega.mes,e[pos2].data_entrega.ano)==0);

        validar=comparar_data(e[pos2].data_requisicao.dia,e[pos2].data_requisicao.mes,e[pos2].data_requisicao.ano,e[pos2].data_entrega.dia,e[pos2].data_entrega.mes,e[pos2].data_entrega.ano);


        if (validar==0)
            printf("\nA data de devolucao tem de ser superior ou igual a data de requisição: %d/%d/%d",e[pos2].data_requisicao.dia,e[pos2].data_requisicao.mes,e[pos2].data_requisicao.ano);
    }
    while(validar==0); /******************A DATA DE DEVOLUÇÃO NÃO PODE SER INFERIOR A DE REQUISICAO*************************/


    do
    {
        printf("\nInsira a hora da devolucao(hh:mm): ");
        fflush(stdin);
        scanf("%d:%d",&e[pos2].hora_entrega.horas,&e[pos].hora_entrega.minutos);

        if(validar==2)
            validar=comparar_hora(e[pos2].hora_req.horas,e[pos2].hora_req.minutos,e[pos2].hora_entrega.horas,e[pos2].hora_entrega.minutos);

        if (validar==2)
            printf("\nA hora da devolucao deve ser superior a hora de requisicao para o mesmo dia");

    }
    while(validar_hora(e[pos2].hora_entrega.horas,e[pos2].hora_entrega.minutos)==0||validar==2);   /**SE O DIA DA DEVOLUÇÃO FOR IGUAL À DA REQUISIÇÃO COMPARA AS HORAS, TENDO DE SER A HORA DE DEVOLUÇÃO MAIOR*/

    /********************  FIM DAS VALIDAÇÕES DAS DATAS E HORAS  ********************/


    *dist=*dist+e[pos2].dist_real;
    v[pos].dist_percorrida=v[pos].dist_percorrida+e[pos2].dist_real;        /** A distancia total é incrementada*/
    v[pos].carga_bateria=carga_final_bateria;



    if(v[pos].carga_bateria<25)
        v[pos].estado=3;         /**Coloca a viatura em estado disponivel ou por carregar dependendo da bateria no final do emprestimo*/
    else
        v[pos].estado=1;


    e[pos2].viatura=v[pos];    /**Os dados da viatura serao guardados nos dados do emprestimo*/


    printf("\nEstado final da viatura: ");
    estado(v[pos].estado);
    printf("\nDevolucao registada com sucesso!");


}






/** FUNCAO listagem
* DESCRICAO: mostra a listagem das viaturas
**/
void listagem(t_viatura v[],int pos)
{


    int i=0;

    for(i=0; i<pos; i++)
    {

        printf("\n\nNumero de identificacao: %d",v[i].numero_ident);
        printf("\nDesignacao: %s",v[i].designacao);
        printf("\nBateria da carga: %.2f por cento",v[i].carga_bateria);
        printf("\nEstado da viatura: ");
        estado(v[i].estado);
        printf("\nDistancia percorrida: %d kms",v[i].dist_percorrida);
        if(v[i].data_ult_req.dia!=0)
            printf("\nData ultima requsicao: %d/%d/%d ",v[i].data_ult_req.dia,v[i].data_ult_req.mes,v[i].data_ult_req.ano);
        printf("\nCusto total dos carregamentos: %.2f euros",v[i].custo_carregamento);
        printf("\nNumero de vezes requsitada: %d ",v[i].vezes_requisitada);


    }

}

void gravar_dados_ficheiro(t_viatura v[],int pos)
{
    FILE *fptr;
    int i=0;
    fptr=fopen("viaturas.bin","wb");

    if (fptr!=NULL)
    {
        for(i=0; i<pos; i++)
        {
            fwrite(&v[i].numero_ident,sizeof(t_viatura),1,fptr);
            fwrite(&pos,sizeof(int),1,fptr);
        }
    }
    fclose(fptr);


}

void ler_dados_ficheiro(t_viatura v[],int pos)
{

    int i=0;
    FILE *fptr;
    fptr=fopen("viaturas.bin","rb");
    if (fptr!=NULL)
    {
        for(i=0; i<pos; i++)
        {
            fread(&v[i].numero_ident,sizeof(t_viatura),1,fptr);
            fread(&pos,sizeof(int),1,fptr);
        }
    }
    fclose(fptr);



}

char menu_informacoes(char escolha)
{
    do
    {
        system("cls");
        printf("INFORMACOES");
        printf("\n\n\n1-Estado e distancia total percorrida por uma viatura ,com a listagem de todas as requisiçoes registadas ");
        printf("\n\n\n2-Distancia media percorrida em cada emprestimo registado ");
        printf("\n\n\n3-Percentagem do custo de carregamento por cada veiculo");
        printf("\n\n\n4-Dados do(s) veiculo(s) com a menor distancia percorrida numa deslocacao");
        printf("\n\n\n5-Quantidade de veiculos e respetiva identificaçao, entregues apos uma determinada data");
        printf("\n\n\n6-Quantidade de veiculos e respetiva identificacao, que nunca foram requisitados");
        printf("\n\n\n7-Discrepancia no consumo teorico previsto e o consumo verificado pela pratica (kWh/km)");

        printf("\n\n\n\n\t\t\tSelecione a  opcao (1 a 7):");
        fflush(stdin);
        escolha=getche();
    }
    while(escolha<'1'||escolha>'7');


    return escolha;


}

void informacao_viatura(t_viatura v[],t_emprestimo e[],int pos,int pos2)
{
    system("cls");
    int i,viatura,validar=0;

    printf("\n\nViaturas:");
    for(i=0; i<pos; i++)
    {
        printf("\n\nNumero de identidade: %d",v[i].numero_ident);
        printf("\nDesignacao:%s",v[i].designacao);
    }


    do
    {
        printf("\n\n\nInsira o numero de identidade da viatura:");
        fflush(stdin);
        scanf("%d",&viatura);
        for(i=0; i<pos; i++)
        {
            if(viatura==v[i].numero_ident)
            {
                system("cls");
                printf("\nNumero de identidade %d ",v[i].numero_ident);
                printf("\nDistancia total percorrida pela viatura %d kms",v[i].dist_percorrida);
                printf("\nEstado:");
                estado(v[i].estado);
                validar=1;
            }

        }

    }
    while(validar==0);

    if (validar==1)
    {


        for(i=0; i<pos2; i++)
        {
            if(viatura==e[i].viatura.numero_ident)
            {
                validar=0;
                printf("\n\nEmprestimo:");
                printf("\nNome do Requisitante %s",e[i].nome);
                printf("\nDistancia prevista  %d kms",e[i].dist_prevista);
                printf("\nHora da requisicao: %d:%d",e[i].hora_req.horas,e[i].hora_req.minutos);
                printf("\nData de requisicao: %d/%d/%d",e[i].data_requisicao.dia,e[i].data_requisicao.mes,e[i].data_requisicao.ano);

                printf("\nDevolucao:");
                if(e[i].dist_real==0)
                    printf(" \t A viatura ainda nao foi devolvida!");
                else
                {
                    printf("\nDistancia real percorrida: %d kms",e[i].dist_real);
                    printf("\nHora de devolucao %d:%d h",e[i].hora_entrega.horas,e[i].hora_entrega.minutos);
                    printf("\nData de devolucao: %d/%d/%d",e[i].data_entrega.dia,e[i].data_entrega.mes,e[i].data_entrega.ano);
                }

            }

        }
        if (validar==1)
            printf("\nEsta viatura nunca teve emprestimos!");


    }
}

void dist_media(t_emprestimo e[],int pos)
{

    int i,soma,media=0;

    for(i=0; i<pos; i++)
        soma=+e[i].dist_real;

    media=soma/i;
    if (media!=0)
        printf("\n\n\nA distancia media percorrida em cada emprestimo registado e de %d kms por emprestimo!!!",media);
    else
        printf("ATENCAO!!Nao existem registo de devolucoes logo nao e possivel saber a distancia efetivamente percorrida em emprestimos");

}
void custo_carregamento(t_viatura v[],int pos)
{
    int i;
    float soma=0,custo;

    system("cls");

    printf("Custo de carregamento das viaturas:");
    for(i=0; i<pos; i++)
    {

        soma=soma+v[i].custo_carregamento;

    }
    for (i=0; i<pos; i++)
    {
        custo=(v[i].custo_carregamento/soma)*100;
        printf("\n\n\n\nNumero de identidade da viatura:%d",v[i].numero_ident);
        printf("\nDesignacao da viatura:%s",v[i].designacao);
        printf("\nCusto de carregamento:%f",v[i].custo_carregamento);
        printf("\nPercentagem do custo de carregamento: %.2f por cento",custo);
    }

}

void menor_dist(t_emprestimo e[],int pos)
{
    int i,validar=0,menor=300;

    system("cls");
    printf("Dados do(s) veiculo(s) com a menor distancia percorrida numa deslocacao");

    for(i=0; i<pos; i++)
    {
        if(e[i].dist_real!=0&&e[i].dist_real<=menor)
        {
            validar=1;
            menor=e[i].dist_real;

        }
    }


    if (validar==1)
    {
        printf("\nMenor distancia percorrida: %d kms ",menor);
        for(i=0; i<pos; i++) /** caso haja mais emprestimos com a mesma distancia percorrida mostra todos e nao so 1 */
        {
            if(e[i].dist_real==menor)
            {
                printf("\n\n\nNumero de identificacao: %d",e[i].viatura.numero_ident);  /** so pedia dados da viatura */
                printf("\nDesignacao: %s",e[i].viatura.designacao);
                printf("\nBateria atual da carga: %.2f por cento",e[i].viatura.carga_bateria);
                printf("\nEstado atual da viatura: ");
                estado(e[i].viatura.estado);
                printf("\nDistancia total percorrida pela viatura: %d kms",e[i].viatura.dist_percorrida);
                printf("\nData ultima requsicao: %d/%d/%d ",e[i].viatura.data_ult_req.dia,e[i].viatura.data_ult_req.mes,e[i].viatura.data_ult_req.ano);
                printf("\nCusto total dos carregamentos: %.2f euros",e[i].viatura.custo_carregamento);
                printf("\nNumero de vezes requsitada: %d ",e[i].viatura.vezes_requisitada);

            }
        }
    }


    if(validar==0)
        printf("\n\nNao existe registos de devolucao portanto nao e possivel saber a menor distancia percorrida!");
}


void data_entrega(t_emprestimo e[],int pos)
{
    int i,dia,mes,ano,contador=0,validar=0;
    system("cls");
    printf("Quantidade de veiculos e respetiva identificacao, entregues apos uma determinada data");
    printf("\n\n\nDatas de devolucoes:");
    for (i=0; i<pos; i++)
    {

        if(e[i].data_entrega.dia!=0)
        {
            printf("%d/%d/%d",e[i].data_entrega.dia,e[i].data_entrega.mes,e[i].data_entrega.ano);
            validar=1;
        }
    }

    if (validar==0)
        printf("\nAtencao!Nao existem devolucoes registadas!");


    else if (validar==1)
    {
        validar=0;

        do
        {
            printf("\n\nInsira a data(dd/mm/aa): ");
            fflush(stdin);
            scanf("%d/%d/%d",&dia,&mes,&ano);
        }
        while(validar_data(dia,mes,ano)==0);
        for (i=0; i<pos; i++)
        {



            if(comparar_data(dia,mes,ano,e[i].data_entrega.dia,e[i].data_entrega.mes,e[i].data_entrega.ano)==1)
            {
                validar=1;
                contador++;
            }

        }

        if (validar==1)
        {
            printf("\nQuantidade de veiculos entregues apos %d/%d/%d: %d ",dia,mes,ano,contador);



            for (i=0; i<pos; i++)
            {
                if(comparar_data(dia,mes,ano,e[i].data_entrega.dia,e[i].data_entrega.mes,e[i].data_entrega.ano)==1)
                {


                    printf("\nNumero de identidade: %d",e[i].viatura.numero_ident);
                    printf("\nDesignacao da viatura: %s",e[i].viatura.designacao);
                    printf("\nNome do Requisitante %s",e[i].nome);
                    printf("\nDistancia prevista a percorrer %d kms",e[i].dist_prevista);
                    printf("\nDistancia realmente percorrida: %d kms",e[i].dist_real);
                    printf("\nData de requisicao: %d/%d/%d",e[i].data_requisicao.dia,e[i].data_requisicao.mes,e[i].data_requisicao.ano);
                    printf("\nData de devolucao: %d/%d/%d",e[i].data_entrega.dia,e[i].data_entrega.mes,e[i].data_entrega.ano);

                }
            }
        }
    }
    else if(validar==0)
        printf("\n\n\n\nNao existem registos de devolucao a partir da data inserida %d/%d/%d",dia,mes,ano);




}
void nao_requisitados(t_viatura v[],int pos)
{
    int i,contador=0;
    system("cls");

    for(i=0; i<pos; i++)
    {
        if(v[pos].vezes_requisitada==0)
            contador++;
    }
    printf("Quantidade de veiculos que nunca foram requisitados:%d",contador);
    for(i=0; i<pos; i++)
    {

        if(v[pos].vezes_requisitada==0)
        {
            printf("\n\n\nNumero de idendidade:%d",v[i].numero_ident);
            printf("\nDesigncacao:%s",v[i].designacao);
        }
    }
}
void consumo(t_emprestimo e[],int pos)
{

    int i,validar=0;
    float descrepancia;


    for(i=0; i<pos; i++)
    {
        if(e[i].consumo_real!=0)
            validar=1;

    }

    if(validar==1)
    {

        system("cls");
        printf("Consumo teorico previsto :%f kWh/km",CONSUMO_TEORICO);
        for(i=0; i<pos; i++)
        {
            if(e[i].consumo_real!=0)
            {
                printf("\n\n\n\nNumero de identidade da viatura:%d ",e[i].viatura.numero_ident);
                printf("\nDistancia percorrida prevista:%d Km ",e[i].dist_prevista);
                printf("\nDistancia percorrida real: %dKm",e[i].dist_real);
                printf("\nConsumo verificado pela pratica:%f kWh/Km ",e[i].consumo_real);
                descrepancia=abs((e[i].consumo_real-CONSUMO_TEORICO)*100)/CONSUMO_TEORICO;
                printf("\nDescrepancia entre o consumo teorico e o pratico:%f por cento",descrepancia);

            }

        }

    }
    else
        printf("\nNao existem devolucoes portanto nao ha registos quanto aos consumos!! ");





}

void estado(int estado)
{
    switch(estado)
    {
    case 1:
        printf("disponivel");
        break;
    case 2:
        printf("requisitada");
        break;
    case 3:
        printf("por carregar");
        break;
    }
}

int validar_data(int dia,int mes,int ano)
{
    int validar=0;
    if(2000<=ano&&ano<=2020)
    {
        if(0<mes&&mes<13)
        {
            if((mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)&&(0<dia&&dia<=31))
                validar=1;
            else if((mes==4||mes==6||mes==9||mes==1)&&(0<dia&&dia<=30))
                validar=1;
            else if(ano%4==0&&mes==2&&(1<=dia&&dia<=29))
                validar=1;
            else if(ano%4!=0&&mes==2&&(1<=dia&&dia<=28))
                validar=1;
            if(validar==0)
                printf("\ndia invalido!");
        }
        else
            printf("\nMes invalido!");
    }
    else
        printf("\nData invalida!\nInsira uma data entre 2000 e 2020!");

    return validar;

}

int comparar_data(int dia,int mes,int ano,int dia2,int mes2,int ano2)
{
    int validar=0;

    if(ano<ano2)
        validar=1;
    else if(ano==ano2&&mes<mes2)
        validar=1;
    else if(ano==ano2&&mes==mes2&&dia<dia2)
        validar=1;
    else if(ano==ano2&&mes==mes2&&dia==dia2)
        validar=2;

    return validar;
}


int validar_hora(int hora,int min)
{
    int validar=0;
    if(hora<24&&hora>=0&&min<60&&min>=0)
        validar=1;
    else
        printf("\nHora inserida incorretamente!");
    return validar;

}

int comparar_hora(int hora,int min,int hora2,int min2)
{
    int validar=2;

    if(hora<hora2)
        validar=1;
    else if(hora==hora2&&min<min2)
        validar=1;

    return validar;
}






