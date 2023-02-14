#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>         

int MatTabu[4][4];

typedef struct {
    int baralho[12];
    int n_da_maior_carta;
    int proximo_do_baralho;
    int carta_proxima;
} threes;

typedef struct {
    int MovC;
    int MovB;
    int MovD;
    int MovE;
} Moov;

typedef struct {
    char nome[10];
    float pontuacao;
} player;

void IniTab()
{
    int i, j;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            MatTabu[i][j] = 0;
        }
    }
}

void Tip_Opcoes()
{
    printf("\n");
    printf("[n] Novo Jogo\n");
    printf("[w] Cima\n");
    printf("[s] Baixo\n");
    printf("[a] Esquerda\n");
    printf("[d] Direita\n");
    printf("[q] Sair\n");
    printf("Digite a opcao: ");
}

void apresentacao()
{
    printf("\033[1;32m");
    printf("-------------------------\n");
    printf(" BEM VINDO AO JOGO THREES\n");
    printf("-------------------------\n");
    printf("\033[0m");
}

void centraliza(int i, int n)
{
   char s[30];
   sprintf(s, "%d", i);
   int l = strlen(s);

   if (n>l) {
     int e = (n-l)/2;
     int d = n-l-e;
     printf("%*s%*s", e, "", d, "");
   }
}

int Acha_Maior_Valor()
{
    int maior = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(MatTabu[i][j] > maior){
                maior = MatTabu[i][j];
            }  
        }
    }
    return maior;
}

int descobrirN(int Ns[])
{

    int maiorv = Acha_Maior_Valor();
    int aux = 0;
    
    for(int i = 0; i < 12;i++){
        aux = Ns[i];
        if((3*pow(2, aux) == maiorv)){
            return aux;
        }
    }
    return aux;
}

void limpa_tela()
{
    printf("\033[2J\033[H");
}

void Mostra_Prox_Carta(threes *jogo)
{
    printf("\nProxima carta = ");
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(jogo->carta_proxima == 1){
                printf("\033[44;1;37m");
                printf(" %d \033[0m\n", jogo->carta_proxima);
            }else if(jogo->carta_proxima == 2){
                printf("\033[41;1;37m");
                printf(" %d \033[0m\n", jogo->carta_proxima);
            }else if(jogo->carta_proxima == 3){
                printf("\033[42;1;37m");
                printf(" %d \033[0m\n", jogo->carta_proxima);
            }
            break;
        }
        break;
    }
}

int aleatorio_entre(int num_ini, int num_fin)
{
    int num_alea;
    
    num_alea = num_ini + ( rand() % num_fin ); 
    
    return num_alea;
    
}

void embaralha_vetor(int tam_vet, int *baralho)
{
    int control = 0;
    for(int i = 0; i < tam_vet; i++){
        while(control < 555){
            int r = rand() % tam_vet;
            int aux = baralho[i];
            baralho[i] = baralho[r];
            baralho[r] = aux;
            control++;
        }
    }
}    

int proxima_carta(threes *jogo)
{
    if (jogo->n_da_maior_carta >= 4 && aleatorio_entre(1, 21) == 21) {
        // carta bÃ´nus
        return 3*pow(2, aleatorio_entre(1, jogo->n_da_maior_carta-3));
    }
    // carta normal
    if (jogo->proximo_do_baralho == 0) {
        // no inicio do baralho -> embaralha
        embaralha_vetor(12, jogo->baralho);
    }
    int carta = jogo->baralho[jogo->proximo_do_baralho];
    jogo->proximo_do_baralho++;
    if (jogo->proximo_do_baralho >= 12) {
        jogo->proximo_do_baralho = 0;
    }
    return carta;
}

void Muda_Prox_Carta(threes *jogo, Moov *VeriMov)
{
    //se qualquer lado nao for possivel, a proxima carta nao muda  
    if((VeriMov->MovC == 0) || (VeriMov->MovB == 0) || (VeriMov->MovE == 0) || (VeriMov->MovD == 0)){
        jogo->carta_proxima = jogo->carta_proxima;
    }else{
        jogo->carta_proxima = proxima_carta(jogo);
    }
}

void Tabuleiro(threes *jogo, Moov *VeriMov)
{
    Muda_Prox_Carta(jogo, VeriMov);
    
    for (int i = 0; i < 4; i++){
        printf("\n| ");
        for (int j = 0; j < 4; j++){
            int valores = MatTabu[i][j];
            if(MatTabu[i][j] == 1){
                printf("\033[44;1;37m");
            }else if(MatTabu[i][j] == 2){
                printf("\033[41;1;37m");
            }else if(MatTabu[i][j] == 3){
                printf("\033[42;1;37m");
            }
            if (MatTabu[i][j] == 0){
                centraliza(valores, 2);
                printf("  ");
            }else{
                centraliza(valores, 2);
                printf("%d ", MatTabu[i][j]);
            }
            printf("\033[0m");
            if (j < 4) {
                printf(" | ");
            }
        }
        printf("\n");
    }
}

void Primeiro_Jogo(threes *jogo)
{
    
    int linhaAle, colunaAle;
    
    for(int i = 0; i < 9; i++){
        linhaAle = aleatorio_entre(0, 4);
        colunaAle = aleatorio_entre(0, 4);
        if(MatTabu[linhaAle][colunaAle] == 0){        
            MatTabu[linhaAle][colunaAle] = proxima_carta(jogo);
        }else if(MatTabu[linhaAle][colunaAle] != 0){
            i = i - 1;
        }
    }
}
void Verifica_Mov_C(Moov *VeriMov)
{
    VeriMov->MovC = 0;
    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if((MatTabu[i][j] == MatTabu[i-1][j]) && ((MatTabu[i][j] > 2 && MatTabu[i-1][j] > 2))){
                VeriMov->MovC = 1;

            }else if(MatTabu[i-1][j] == 0){
                VeriMov->MovC = 1;

            }
            if((MatTabu[i][j] == 2 && MatTabu[i-1][j] == 1) || (MatTabu[i][j] == 1 && MatTabu[i-1][j] == 2)){
                VeriMov->MovC = 1;
            }
        }
    }
}
void Cima(threes *jogo){

    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if((MatTabu[i][j] == MatTabu[i-1][j]) && ((MatTabu[i][j] > 2 && MatTabu[i-1][j] > 2))){
                MatTabu[i-1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
                
            }else if(MatTabu[i-1][j] == 0){
                MatTabu[i-1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i-1][j] == 1) || (MatTabu[i][j] == 1 && MatTabu[i-1][j] == 2)){
                MatTabu[i-1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
        }
    }
    //coloca a carta depois do movimento 
    int colunaAle;
    for(int i = 0; i < 100;i++){
        colunaAle = aleatorio_entre(0, 4);
        if(MatTabu[3][colunaAle] == 0){
            MatTabu[3][colunaAle] = jogo->carta_proxima;
            break;
        }
    }
}
void Verifica_Mov_B(Moov *VeriMov)
{
    VeriMov->MovB = 0;
    for(int i = 2; i >= 0 ; i--){
        for(int j = 3; j >= 0; j--){
            if((MatTabu[i][j] == MatTabu[i+1][j] && (MatTabu[i][j] > 2 && MatTabu[i+1][j] > 2))){
                VeriMov->MovB = 1;
            }else if(MatTabu[i+1][j] == 0){

                VeriMov->MovB = 1;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i+1][j] == 1) || (MatTabu[i][j] == 1 && MatTabu[i+1][j] == 2)){
                VeriMov->MovB = 1;

            }
        }
    }
}

void Baixo(threes *jogo){
    
    for(int i = 2; i >= 0 ; i--){
        for(int j = 3; j >= 0; j--){
            if((MatTabu[i][j] == MatTabu[i+1][j] && (MatTabu[i][j] > 2 && MatTabu[i+1][j] > 2))){
                MatTabu[i+1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }else if(MatTabu[i+1][j] == 0){
                MatTabu[i+1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i+1][j] == 1) || (MatTabu[i][j] == 1 && MatTabu[i+1][j] == 2)){
                MatTabu[i+1][j] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
        }
    }
    //coloca a carta depois do movimento 
    int colunaAle;
    for(int i = 0; i < 100;i++){
        colunaAle = aleatorio_entre(0, 4);
        if(MatTabu[0][colunaAle] == 0){
            MatTabu[0][colunaAle] = jogo->carta_proxima;
            break;
        }
    }
}

void Verifica_Mov_E(Moov *VeriMov)
{
    VeriMov->MovE = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){
            if((MatTabu[i][j] == MatTabu[i][j-1] && (MatTabu[i][j] > 2 && MatTabu[i][j-1] > 2))){
                VeriMov->MovE = 1;
            }else if( MatTabu[i][j-1] == 0){
                VeriMov->MovE = 1;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i][j-1] == 1) || (MatTabu[i][j] == 1 && MatTabu[i][j-1] == 2)){
                VeriMov->MovE = 1;

            }
        }
    }
}

void Esquerda(threes *jogo){
    

    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){
            if((MatTabu[i][j] == MatTabu[i][j-1] && (MatTabu[i][j] > 2 && MatTabu[i][j-1] > 2))){
                MatTabu[i][j-1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }else if( MatTabu[i][j-1] == 0){
                MatTabu[i][j-1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i][j-1] == 1) || (MatTabu[i][j] == 1 && MatTabu[i][j-1] == 2)){
                MatTabu[i][j-1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
        }
    }
    int linhaAle;
    //coloca a carta depois do movimento 
    for(int i = 0; i < 100;i++){
        linhaAle = aleatorio_entre(0, 4);
        if(MatTabu[linhaAle][3] == 0){
            MatTabu[linhaAle][3] = jogo->carta_proxima;
            break;
        }
    }
    
}

void Verifica_Mov_D(Moov *VeriMov)
{
    VeriMov->MovD = 0;
    
    for(int i = 0; i < 4; i++){
        for(int j = 2; j >= 0; j--){
            if((MatTabu[i][j] == MatTabu[i][j+1] && (MatTabu[i][j] > 2 && MatTabu[i][j+1] > 2))){
                VeriMov->MovD = 1;
            }else if(MatTabu[i][j+1] == 0){
                VeriMov->MovD = 1;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i][j+1] == 1) || (MatTabu[i][j] == 1 && MatTabu[i][j+1] == 2)){
                VeriMov->MovD = 1;
            }
            
        }
    }
}

void Direita(threes *jogo)
{
    
    for(int i = 0; i < 4; i++){
        for(int j = 2; j >= 0; j--){
            if((MatTabu[i][j] == MatTabu[i][j+1] && (MatTabu[i][j] > 2 && MatTabu[i][j+1] > 2))){
                MatTabu[i][j+1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }else if(MatTabu[i][j+1] == 0){
                MatTabu[i][j+1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
            if((MatTabu[i][j] == 2 && MatTabu[i][j+1] == 1) || (MatTabu[i][j] == 1 && MatTabu[i][j+1] == 2)){
                MatTabu[i][j+1] += MatTabu[i][j];
                MatTabu[i][j] = 0;
            }
            
        }
    }
    //coloca a carta depois do movimento 
    int linhaAle;
    for(int i = 0; i < 100;i++){
        linhaAle = aleatorio_entre(0, 4);
        if(MatTabu[linhaAle][0] == 0){
            MatTabu[linhaAle][0] = jogo->carta_proxima;
            break;
        }
    }
}

int VeriAca(Moov *VeriMov)
{
    //se tudo for igual a 0, significa que nao foi possivel fazer o movimento  
    if((VeriMov->MovC == 0) && (VeriMov->MovB == 0) && (VeriMov->MovE == 0) && (VeriMov->MovD == 0)){
        return 1;
    }else{
        return 0;
    }
}

void Repet_Verificacao(threes *jogo, Moov *VeriMov)
{
    Verifica_Mov_C(VeriMov);
    Verifica_Mov_B(VeriMov);
    Verifica_Mov_E(VeriMov);
    Verifica_Mov_D(VeriMov);
    
}

void RetornaMov(Moov *VeriMov)
{
    VeriMov->MovC = 1;
    VeriMov->MovB = 1;
    VeriMov->MovE = 1;
    VeriMov->MovD = 1;
    
}

void Organiza_Vetor(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++){
        for (int j = i; j < tamanho - 1; j++){
            if (vetor[i] < vetor[j]){
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

int pontuacao_final(int Ns[], threes *jogo)
{
    
    int PontF = 0;
    int AuxValores[16];
    int aux = 0;
    //guarda dos valores > 3 em um vetor e zera o resto
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            if(MatTabu[i][j] >= 3){
                AuxValores[aux] = MatTabu[i][j];
            }else{
                AuxValores[aux] = 0;
            }
            aux++;
        }
    }
    
    Organiza_Vetor(AuxValores, 16);
    //faz a conta de 3*2^n 
    for(int i = 0; i < 16; i++){
        for(int j = 0; j <= jogo->n_da_maior_carta; j++){    
            if((AuxValores[i] >= 3) && (3*pow(2, Ns[j]) == AuxValores[i])){
                PontF = PontF + 3*pow(2, Ns[j]);
                AuxValores[i] = 0;
            }
        }
    }
    return PontF;
}

void Repet_Jogada(threes *jogo, Moov *VeriMov)
{
    Tabuleiro(jogo, VeriMov);
    Mostra_Prox_Carta(jogo);
    Tip_Opcoes();
}

void limpa_linha(char v[10])
{
    
    int tam = strlen(v);
    for(int i = 0; i < tam; i++){
        if(v[i] == '\n'){
            v[i] = 0;
            break;
        }
    }
}

int lei_arq(player lista[])
{
    FILE *arquivo;
    
    char nome[] = "ranking";
    arquivo = fopen(nome, "r");
    if (arquivo == NULL) {
        printf("\nErro na leitura do arquivo.");
        return 0;
    }
    
    for(int i = 0; i < 10; i++){
        fscanf(arquivo, "%f ", &lista[i].pontuacao);
        
        fgets(lista[i].nome, 10, arquivo);
        
        limpa_linha(lista[i].nome);
        
        if (feof(arquivo)) {
            break;
        }
    }
    
    fclose(arquivo);
    
    return 1;
}

int comparar_jogador(int n, player lista[n], int score)
{
    int posicao = 0;
    for(int i = 0; i < n; i++){
        if(score > lista[i].pontuacao){
            posicao = i + 1;
            break;
        }
    }
    
    return posicao;
}

void colocar_no_ranking(player lista[], player *jogador)
{
    player jogadorcopia = *jogador;
    player aux;
    
    for(int i = 0; i < 10;i++){
        if(jogador->pontuacao > lista[i].pontuacao){
            aux = lista[i];
            lista[i] = jogadorcopia;
            jogadorcopia = aux;
        }
    }
}

int escreve_arquivo(player lista[])
{
    FILE *arquivo;
    
    char nome[] = "ranking";
    arquivo = fopen(nome, "w");
    if (arquivo == NULL) {
        printf("\nErro na leitura do arquivo.");
        return 0;
    }
    
    for(int i = 0; i < 10; i++){
        fprintf(arquivo, "%0.f %s\n", lista[i].pontuacao, lista[i].nome);
        
        if (feof(arquivo)) {
            printf("\nErro na leitura do arquivo.");
            break;
        }
    }
    
    fclose(arquivo);    
    return 1;

}

void pede_nome(player *jogador)
{
    printf("\nDigite as suas inicais jogador: ");
    scanf("%s", jogador->nome);
    printf("\n");
}

void parabenizar(int pos, player *jogador)
{
    printf("Parabens %s. Voce esta na posicao = %d\n", jogador->nome, pos);
}

void rankear_jogador(player *jogador)
{
    player lista[10];
    
    lei_arq(lista);
    
    int posicao = comparar_jogador(10, lista, jogador->pontuacao);
    if (posicao > 0){
        pede_nome(jogador);
        colocar_no_ranking(lista, jogador);
        parabenizar(posicao, jogador);
    }
    escreve_arquivo(lista);

}

int main()
{
    srand(time(0));
    //guarda as cartas dentro do baralho
    threes jogo = {1,1,1,1,2,2,2,2,3,3,3,3};
    player jogador = {0};
    //valores dos Ns
    int ValoresdeN[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    Moov VeriMov;
    
    apresentacao();
    
    //primeiro contato com o game
    jogo.carta_proxima = proxima_carta(&jogo);
    IniTab(); 
    Primeiro_Jogo(&jogo);
    Repet_Jogada(&jogo, &VeriMov);

    while(true) {
        
        char Escolha;
        scanf("%c", &Escolha);
        
        if (Escolha == 'n'){
            limpa_tela();
            IniTab(); 
            Primeiro_Jogo(&jogo);
            Repet_Jogada(&jogo, &VeriMov);
        }
    
        switch(Escolha){
            case 'w':
                limpa_tela();
                Cima(&jogo);
                Repet_Jogada(&jogo, &VeriMov);
                break;
    
            case 's':
                limpa_tela();
                Baixo(&jogo);
                Repet_Jogada(&jogo, &VeriMov);
                break;
    
            case 'a':
                limpa_tela();
                Esquerda(&jogo);
                Repet_Jogada(&jogo, &VeriMov);
                break;
    
            case 'd':
                limpa_tela();
                Direita(&jogo);
                Repet_Jogada(&jogo, &VeriMov);
                break;
        }
        
        Repet_Verificacao(&jogo, &VeriMov);
        if (Escolha == 'q'){
            break;
        }
        //precisa confirmar todas as direcoes para ter certeza de que nao ha movimentos
        if(VeriAca(&VeriMov) == 1){
            
            jogador.pontuacao = pontuacao_final(ValoresdeN, &jogo);
            printf("\nParabens, sua pontuacao foi = %0.f\n", jogador.pontuacao);
            rankear_jogador(&jogador);
            int Cont = 4;
            for(;;){
                printf("Deseja continuar [1]Sim [0]Nao: ");
                scanf("%d", &Cont);
                if(Cont == 1 || Cont == 0){
                    break;
                }
            }
                
            if(Cont == 0){
                break;
            }else if(Cont == 1){
                RetornaMov(&VeriMov);
                limpa_tela();
                IniTab(); 
                Primeiro_Jogo(&jogo);
                Repet_Jogada(&jogo, &VeriMov);
            }
        }
        jogo.n_da_maior_carta = descobrirN(ValoresdeN);
    }
    printf("Obrigado por jogar. Volte sempre!!");
    
    return 0;
}
