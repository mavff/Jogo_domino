#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    unsigned char parte1,parte2;
    unsigned char emJogo;
}Peca;
typedef struct{
    Peca* pecas;
    char num_pecas;
}Jogador;
///////////////////////////////////
Peca *inicializaPecasDomino();
Peca *pecasIndividuo(Peca *);
Peca *jogada(char, char, Peca**, char*, Peca**, char*);
void mostraPecas(Jogador*);
void mostraMesa(Peca*,char*);
void ganhador(Peca*,char,Peca*,char);
//////////////////////////////////
int main(){
       
    Jogador player1,player2;
    Peca* domino=NULL;
    Peca *naMesa=NULL;
    int jogoacaba=0;
    char pecaescolhida=0,extremidade,tammesa=0,vez;
    char conferir,conferir2;
    player1.pecas=NULL;
    player2.pecas=NULL;
    domino=inicializaPecasDomino();
    player1.pecas= pecasIndividuo(domino);
    player2.pecas= pecasIndividuo(domino);
    player1.num_pecas=7;
    player2.num_pecas=7;
    printf("Quem ira iniciar o jogo?jogador1(1)|jogador(2)");
    scanf(" %c",&vez);
    
    while(!jogoacaba){
        
        if(vez=='1'){
            mostraMesa(naMesa,&tammesa);
            mostraPecas(&player1);
            printf("Qual peca voce quer jogar jogador 1?(0 a seu total de pecas)\n");
            scanf(" %c",&pecaescolhida);
            printf("Peca escolhida= [%u:%u] \n",player1.pecas[pecaescolhida-'0'].parte1,player1.pecas[pecaescolhida-'0'].parte2);
            printf("Qual extremidade voce deseja jogar? 0|1 \n");
            scanf(" %c",&extremidade);
            conferir=player1.num_pecas;
            player1.pecas=jogada(pecaescolhida,extremidade,&player1.pecas,
                                    &player1.num_pecas,&naMesa,&tammesa);
            if(conferir==player1.num_pecas){
                printf("Jogada invalida!Vez do proximo jogador.\n");
            }
            else{
                printf("Jogada feita com sucesso, vez do proximo jogador.\n");
            }
            printf(" Vamos continuar?(Y|N)Y=Tenho como jogar|||N=Nao tenho como jogar\n");
            scanf(" %c",&conferir);
            if(conferir=='y'||conferir=='Y'){
                system("clear");            
                if(conferir2!='n'&&conferir2!='N'){
                    vez='2';
                }
            }
            else if(conferir=='n'||conferir=='N'){
                vez='2';               
                system("clear");               
            }
        }
       
        if(vez=='2'){          
            mostraMesa(naMesa,&tammesa);
            mostraPecas(&player2);
            printf("Qual peca voce quer jogar jogador 2?(0 a seu total de pecas)\n");
            scanf(" %c",&pecaescolhida);
            printf("Peca escolhida= [%u:%u] \n",player2.pecas[pecaescolhida-'0'].parte1,player2.pecas[pecaescolhida-'0'].parte2);
            printf("Qual extremidade voce deseja jogar? 0|1 \n");
            scanf(" %c",&extremidade);
            conferir2=player2.num_pecas;
            player2.pecas=jogada(pecaescolhida,extremidade,&player2.pecas,
                                    &player2.num_pecas,&naMesa,&tammesa);
            if(conferir2==player2.num_pecas){
                printf("Jogada invalida!Vez do proximo jogador.\n");
            }
            else{
                printf("Jogada feita com sucesso, vez do proximo jogador.\n");
            }
            printf(" Vamos continuar?(Y|N)Y=Tenho pecas sobrando|||N=Nao tenho como jogar\n");
            scanf(" %c",&conferir2);
            if(conferir2=='y'||conferir2=='Y'){
                system("clear");
                if(conferir!='n'&&conferir!='N'){
                    vez='1';
                }
            }
            else if(conferir2=='n'||conferir2=='N'){
                system("clear");
                vez='1';               
            }
        }  
        if(player1.num_pecas==0){
            printf("PARABENS JOGADOR 1, VOCE GANHOU\nFIM DE JOGO\n");
            jogoacaba=1;
        }
        else if(player2.num_pecas==0){
            printf("PARABENS JOGADOR 2, VOCE GANHOU\nFIM DE JOGO\n");
            jogoacaba=1;
        }
        else if((conferir=='n'||conferir=='N')&&(conferir2=='n'||conferir2=='N')){
            ganhador(player1.pecas,player1.num_pecas,player2.pecas,player2.num_pecas);
            jogoacaba=1;
        }
    }
    return 0;
}
Peca *inicializaPecasDomino(){
    Peca *aux=NULL;
    unsigned int pos=0,i,j;
    aux=(Peca*)malloc(sizeof(Peca)*28);
    if(aux==NULL)exit(1);
    for ( i = 0; i <= 6; i++) {
        for ( j = i; j <= 6; j++) {
            aux[pos].parte1 = (char)i;
            aux[pos].parte2 = (char)j;
            aux[pos].emJogo='0';
            pos++;
        }
    } 
    return aux;
}
Peca *pecasIndividuo(Peca *todasPecas){
    srand(time(NULL));
    Peca* mao=NULL;
    int contador=0;
    char x;
    mao=(Peca*)malloc(sizeof(Peca)*7);
    if(mao==NULL) exit(1);
    while(contador<7){
        x=rand()%28;
        if(todasPecas[x].emJogo=='0'){
           mao[contador].parte1=todasPecas[x].parte1;
           mao[contador].parte2=todasPecas[x].parte2;
           mao[contador].emJogo='1';
           todasPecas[x].emJogo='1';
           contador++;
        }
    }
    return mao;
}
void mostraPecas(Jogador* pecasJogador){
    printf("Pecas do jogador:\n");
    for(int i=0;i<pecasJogador->num_pecas;i++){
        unsigned char p1,p2;
        p1=pecasJogador->pecas[i].parte1;
        p2=pecasJogador->pecas[i].parte2;
        printf("[%u:%u]",p1,p2);
    }
    printf("\n");
}
Peca *jogada(char pecaEscolhida,char Extremidade,Peca **pecasJogador,char*tamPecasJog,Peca **Mesa,char *tamMesa){
    
     if((*tamMesa)==0&&(Extremidade=='0'||Extremidade=='1')){//primeira jogada, pois o tamMesa comeca com 0;
        (*tamMesa)++;
        (*Mesa)=(Peca*)realloc(*Mesa,sizeof(Peca*)*(*tamMesa));
        if(Mesa==NULL)exit(1);
        (*Mesa)[0]=(*pecasJogador)[pecaEscolhida-'0'];
        (*tamPecasJog)--;
        for(char i=(pecaEscolhida-'0');i<(*tamPecasJog);i++){
            (*pecasJogador)[i]=(*pecasJogador)[i+1];
        }
        (*pecasJogador)=(Peca*)realloc((*pecasJogador),sizeof(Peca*)*(*tamPecasJog));
        if(pecasJogador==NULL)exit(1);
        
     }
     else if(Extremidade=='0'){
        if((*Mesa)[0].parte1==(*pecasJogador)[pecaEscolhida-'0'].parte1||(*Mesa)[0].parte1==(*pecasJogador)[pecaEscolhida-'0'].parte2)
        {
            (*tamMesa)++;
            (*Mesa)=(Peca*)realloc((*Mesa),sizeof(Peca*)*(*tamMesa));
            if(Mesa==NULL)exit(1);
            for(char i=(*tamMesa)-1;i>=1;i--){
               
                (*Mesa)[i]=(*Mesa)[i-1];
                
            }
            if((*Mesa)[0].parte1==(*pecasJogador)[pecaEscolhida-'0'].parte1){
                (*Mesa)[0].parte2=(*pecasJogador)[pecaEscolhida-'0'].parte1;
                (*Mesa)[0].parte1=(*pecasJogador)[pecaEscolhida-'0'].parte2;
            }
            else if((*Mesa)[0].parte1==(*pecasJogador)[pecaEscolhida-'0'].parte2){
                (*Mesa)[0]=(*pecasJogador)[pecaEscolhida-'0'];
            }
            (*tamPecasJog)--;
            for(char i=(pecaEscolhida-'0');i<(*tamPecasJog);i++){
                (*pecasJogador)[i]=(*pecasJogador)[i+1];
            }
            (*pecasJogador)=(Peca*)realloc(*pecasJogador,sizeof(Peca*)*(*tamPecasJog));
            if(pecasJogador==NULL)exit(1);
        }
     }
     else if(Extremidade=='1'){
        if((*Mesa)[(*tamMesa)-1].parte2==(*pecasJogador)[pecaEscolhida-'0'].parte1||(*Mesa)[(*tamMesa)-1].parte2==(*pecasJogador)[pecaEscolhida-'0'].parte2){
            (*tamMesa)++;
            (*Mesa)=(Peca*)realloc((*Mesa),sizeof(Peca*)*(*tamMesa));
            if(Mesa==NULL)exit(1);
            if((*Mesa)[(*tamMesa)-2].parte2==(*pecasJogador)[pecaEscolhida-'0'].parte2){
                (*Mesa)[(*tamMesa)-1].parte1=(*pecasJogador)[pecaEscolhida-'0'].parte2;
                (*Mesa)[(*tamMesa)-1].parte2=(*pecasJogador)[pecaEscolhida-'0'].parte1;
            }
            else if((*Mesa)[(*tamMesa)-2].parte2==(*pecasJogador)[pecaEscolhida-'0'].parte1){
                (*Mesa)[(*tamMesa)-1]=(*pecasJogador)[pecaEscolhida-'0'];   
            }
            (*tamPecasJog)--;
            for(char i=(pecaEscolhida-'0');i<(*tamPecasJog);i++){
                (*pecasJogador)[i]=(*pecasJogador)[i+1];
            }
            (*pecasJogador)=(Peca*)realloc((*pecasJogador),sizeof(Peca*)*(*tamPecasJog));
            if(pecasJogador==NULL)exit(1);
        }
     }
    return (*pecasJogador);
}
void mostraMesa(Peca* Mesa,char* tamMesa){
    int i;
    printf("\t MESA DE DOMINO\t\n");
    for(i=0;i<7;i++){
        printf("_ _ _ _");
    }
    printf("\n\n");
    printf("  ");
    for(i=0;i<(*tamMesa);i++){
        printf("[%u:%u]",Mesa[i].parte1,Mesa[i].parte2);
    }
    printf("\n\n");
    for(i=0;i<7;i++){
        printf("_ _ _ _");
    }
    printf("\n");
    if(*tamMesa>1){
        printf("Peca da extremidade 0:[%u:%u]\nPeca da extremidade 1:[%u:%u]\n",
            Mesa[0].parte1,Mesa[0].parte2,Mesa[*tamMesa-1].parte1,Mesa[*tamMesa-1].parte2);
    }
}
void ganhador(Peca* mao1,char num_pecas1,Peca* mao2,char num_pecas2){
    int total_pontos1=0,total_pontos2=0;
    for(int i=0;i<num_pecas1;i++){
        total_pontos1+=(int)mao1[i].parte1 + (int)mao1[i].parte2;
    }
    for(int i=0;i<num_pecas2;i++){
        total_pontos2+=(int)mao2[i].parte1 + (int)mao2[i].parte2;
    }
    if(total_pontos1>total_pontos2){
        printf("\nVITORIA  DO JOGADOR 2\n");
        printf("Pontuacao do jogador 1: %d\n",total_pontos1);
        printf("Pontuacao do jogador 2: %d\n",total_pontos2);
    }
    else{
        printf("\nVITORIA  DO JOGADOR 1\n");
        printf("Pontuacao do jogador 1: %d\n",total_pontos1);
        printf("Pontuacao do jogador 2: %d\n",total_pontos2);
    }
}