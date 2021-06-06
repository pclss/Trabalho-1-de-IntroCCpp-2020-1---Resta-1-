#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <locale.h>
#define LIN 7
#define COL 7

//--------------------------------------------------------------------------------------- FUNÇÕES --------------------------------------------------------------------------------------------------------------

// ESTRUTURA PARA DEFINIR AS POSIÇÕES INVALIDAS
typedef struct {
	int x[16], y[16];	//A ESTRUTURA DEFINE UMA VARIÁVEL QUE POSSUI DOIS VETORES, UMA PARA RECEBER AS LINHAS ("COORDENADA" X), E A OUTRA AS COLUNAS ("COORDENADA" Y)
} COORDENADA_BLOQ;

//FUNÇÃO QUE APRESENTA O JOGO E MOSTRA AS INSTRUÇÕES
void inicio_de_jogo(){
	printf("\n\t\t-------<SEJA MUITO BEM VINDO!>-------\n");
	printf("\nEste é o jogo Resta 1! Caso não conheça o jogo, aqui estao as instruções:\n\n");
	printf("O objetivo do jogo RESTA UM é deixar apenas uma peça no tabuleiro.\n");
	printf("Escolha uma peça para começar, a peça escolhida deve saltar sobre outra peça,\n");
	printf("fazendo movimentos na horizontal ou na vertical, e deve chegar a um espaço\nvazio. ");
	printf("\nA peça que foi pulada sai do jogo. \nO jogo termina quando restar somente uma peça ou não for possível fazer\nmovimentos.\n");
	printf("\nCOMO JOGAR:\n");
	printf("Para mover um pino, é necessário que você indica a coordenada onde ele se\nencontra (X-Y),");
	printf("movendo-o para o lado que possa comer outro pino, utilizando\nassim, as teclas direcionais do teclado, as famosas 'setinhas'.\n\n");
	printf("Caso não seja possível realizar mais movimentos, digite a coordenada 0-0 e o\njogo terminará!\n\n");
}



// FUNCAO QUE IMPRIME UMA MATRIZ 7X7
void imprime_matriz(char matriz[LIN][COL]){
	int i, j;
	printf("\t\t\t"); //ESPAÇAMENTO PARA CENTRALIZAR O TABULEIRO
	printf("    1 2 3 4 5 6 7\n\n"); //COORDENADA DAS COLUNAS (APENAS PARA REFERÊNCIA DO JOGADOR)
	for(i=0 ; i < LIN ; i++){
		printf("\t\t\t"); //ESPAÇAMENTO PARA CENTRALIZAR O TABULEIRO
		printf("%d   ", i+1); //COORDENADA DAS LINHAS (APENAS PARA REFERÊNCIA DO JOGADOR)
		for(j=0 ; j < COL ; j++){
			printf("%c", matriz[i][j]); //IMPRESSÃO DA MATRIZ
			printf(" "); //UTILIZAÇÃO DO CARACTER ESPAÇO PARA MELHORA DA INTERFACE
		}
		printf("\n\n"); //DUAS QUEBRAS DE LINHA PARA MELHORA DA INTERFACE
	}
}


// FUNCAO QUE IMPRIME O RESULTADO FINAL
void resultado(char matriz[LIN][COL], int linha, int coluna){
	if((linha == 0) && (coluna==0)){ //CASO O JOGADOR NÃO CONSIGA FAZER MAIS JOGADAS OU DECIDA DESISTIR, ELE ENTRARÁ COM A COORDENADA 0-0
		system("cls");
		imprime_matriz(matriz);
		printf("\nVocê perdeu o jogo!! ;-;\nGAME OVER\n\n"); //CASO PERCA O JOGO, ESSA É A MENSAGEM EXIBIDA
	}else{
		system("cls");
		imprime_matriz(matriz);
		printf("\t\tParabéns!!! Você venceu o jogo!!!\n"); //CASO GANHE O JOGO, ESSA É A MENSAGEM EXIBIDA
	}
}


//---------------------------------------------------------------------------------- INÍCIO DO PROGRAMA -----------------------------------------------------------------------------------------------------
int main(){
	COORDENADA_BLOQ bloqueadas;
	int i, j, linha, coluna, direcao, pecas_comidas = 0, aux = 0;
	char matriz[LIN][COL];
	
	//FUNCAO QUE PERMITE A UTILIZAÇÃO DE CARACTERES ESPECIAIS
	setlocale(LC_ALL, "Portuguese");
	
	// APRESENTAÇÃO DO JOGO 
	inicio_de_jogo();
	
	// INICIA O JOGO	
	printf("Para iniciar o jogo, utilize a tecla ENTER\n\n");
	getch();													//PEGA UMA TECLA QUALQUER APENAS PARA INICIAR O JOGO E LIMPAR A TELA
	system("cls");												//LIMPA A TELA
	
	// DEFINE AS COORDENADAS QUE NAO FAZEM PARTE DO JOGO
	for(i=0; i<LIN ; i++){
		for(j=0; j<COL ; j++){
			if( ((i<2) || (i>4)) && ((j<2) || (j>4))){
				bloqueadas.x[aux] = i;	//RECEBE A LINHA
				bloqueadas.y[aux] = j;	//RECEBE A COLUNA
				aux++;	//ANDA NO VETOR DE VARIÁVEIS BLOQUEADAS
			}
		}
	}
	
	aux = 0; // REDEFINE A VARIÁVEL "aux" COM O VALOR 0 PARA REUTILIZÁ-LA
	
	
	// DEFINE A MATRIZ JOGÁVEL COMO UMA CRUZ DE CARACTERES "O" 
	for(i=0 ; i<LIN ; i++){
		for(j=0 ; j<COL ; j++){
			//DEFINE AS POSICOES BLOQUEADAS COMO UM CARACTER ESPACO!!!!!
			if((i == bloqueadas.x[aux]) && (j == bloqueadas.y[aux])){
				matriz[i][j] = ' ';
				aux++;	//ANDA NO VETOR DAS VARIÁVEIS BLOQUEADAS
			}
			//DEFINE A POSICAO CENTRAL COMO VAZIA, OU SEJA, NÃO POSSUI PEDRA. UTILIZAREMOS O CARACTER "." PARA DEFINIR UMA POSIÇÃO SEM PEDRAS!!!!!
			else if((i == 3) && (j == 3)){
				matriz[i][j] = '.';	
			}
			//DEFINE AS POSIÇÕES QUE CONTÉM PEDRAS!!!!!!
			else{
				matriz[i][j] = 'O';
			}
		}
	}
	
	
	imprime_matriz(matriz); // IMPRIME A MATRIZ INICIAL
	
	// ENTRADA DO USUARIO
	printf("\nDigite a coordenada do pino que deseja mover! Formato a se utilizar: X-Y\n");
	scanf("%d-%d", &linha, &coluna); //COORDENADA DA PEDRA QUE O USUÁRIO VAI MOVER
	
	while((pecas_comidas < 31) && ((linha != 0) || (coluna != 0))){ //ESTRUTURA DE REPETIÇÃO QUE DEFINE ATÉ QUANDO O JOGO VAI DURAR
	
		if(matriz[linha-1][coluna-1] == 'O'){ //AS COORDENADAS PASSADAS TEM SEU VALOR IGUALADO COM A COORDENADA CODIFICADA POIS DEFINIMOS A PRIMEIRA POSIÇÃO DA MATRIZ COMO 1-1 PARA O USUÁRIO
			
			printf("Digite uma tecla direcional (seta), dizendo para onde deseja jogar o pino:\n\n");
			direcao = getch(); //RECEBE A TECLA DIRECIONAL
			
			if(direcao == 224){ //UTILIZAMOS ESSA ESTRUTURA DE REPETIÇÃO POIS QUANDO RECEBEMOS A TECLA DIRECIONAL, SÃO PASSADOS DOIS VALORES, 224 E O VALOR DA TECLA DIRECIONAL
				direcao = getch();
			}
			else{
				system("cls");
				printf("DIREÇÃO INVÁLIDA, COMECE SUA JOGADA NOVAMENTE E SELECIONE UMA DIREÇÃO VÁLIDA\nCOM AS SETAS!\n\n");
			}
			switch (direcao) {
  				case 72:
  					//COME UMA PEDRA ACIMA DA SELECIONADA
  					if((matriz[linha-3][coluna-1] == '.') && (matriz[linha-2][coluna-1] == 'O')){	 
						//SE A POSIÇÃO QUE O JOGADOR DESEJA MOVER A PEDRA FOR VAZIA "."E A POSIÇÃO QUE ELE VAI COMER TIVER UMA PEÇA "O", A JOGADA PODE SER FEITA!
  						matriz[linha-1][coluna-1] = '.';	//POSIÇÃO SELECIONADA RECEBE "." POIS FICARÁ VAZIA DEPOIS DA JOGADA
  						matriz[linha-2][coluna-1] = '.';	//POSIÇÃO DA PEÇA COMIDA RECEBE "." POIS FICARÁ VAZIA
  						matriz[linha-3][coluna-1] = 'O';	//POSIÇÃO NOVA DA PEDRA SELECIONADA
  						system("cls");						//LIMPA A TELA
  						pecas_comidas++;					//INCREMENTA A CONDIÇÃO DE PARADA (NÚMERO DE PEÇAS COMIDAS)
					}
					else{
					//CASO NÃO ATENDA ÀS CONDIÇÕES, A JOGADA É CONSIDERADA INVÁLIDA
						system("cls");												//LIMPA A TELA
						printf("Jogada invalida! Comece a jogada novamente!\n\n");	//EXIBE A MENSAGEM DE QUE NÃO FOI POSSÍVEL REALIZAR A JOGADA
					}
					break;
					
				case 75:
					//COME UMA PEDRA A ESQUERDA DA SELECIONADA
					if((matriz[linha-1][coluna-3] == '.') && (matriz[linha-1][coluna-2] == 'O')){
						//SE A POSIÇÃO QUE O JOGADOR DESEJA MOVER A PEDRA FOR VAZIA "."E A POSIÇÃO QUE ELE VAI COMER TIVER UMA PEÇA "O", A JOGADA PODE SER FEITA!
  						matriz[linha-1][coluna-1] = '.';	//POSIÇÃO SELECIONADA RECEBE "." POIS FICARÁ VAZIA DEPOIS DA JOGADA
  						matriz[linha-1][coluna-2] = '.';	//POSIÇÃO DA PEÇA COMIDA RECEBE "." POIS FICARÁ VAZIA
  						matriz[linha-1][coluna-3] = 'O';	//POSIÇÃO NOVA DA PEDRA SELECIONADA
  						system("cls");						//LIMPA A TELA
  						pecas_comidas++;					//INCREMENTA A CONDIÇÃO DE PARADA (NÚMERO DE PEÇAS COMIDAS)
					}
					else{
						system("cls");												//LIMPA A TELA
						printf("Jogada invalida! Comece a jogada novamente!\n\n");	//EXIBE A MENSAGEM DE QUE NÃO FOI POSSÍVEL REALIZAR A JOGADA
					}
					break;
					
				case 77:
					//COME UMA PEDRA A DIREITA DA SELECIONADA
					if((matriz[linha-1][coluna+1] == '.') && (matriz[linha-1][coluna] == 'O')){
						//SE A POSIÇÃO QUE O JOGADOR DESEJA MOVER A PEDRA FOR VAZIA "."E A POSIÇÃO QUE ELE VAI COMER TIVER UMA PEÇA "O", A JOGADA PODE SER FEITA!
  						matriz[linha-1][coluna-1] = '.';	//POSIÇÃO SELECIONADA RECEBE "." POIS FICARÁ VAZIA DEPOIS DA JOGADA
  						matriz[linha-1][coluna] = '.';		//POSIÇÃO DA PEÇA COMIDA RECEBE "." POIS FICARÁ VAZIA
  						matriz[linha-1][coluna+1] = 'O';	//POSIÇÃO NOVA DA PEDRA SELECIONADA
  						system("cls");						//LIMPA A TELA
  						pecas_comidas++;					//INCREMENTA A CONDIÇÃO DE PARADA (NÚMERO DE PEÇAS COMIDAS)
					  }
					  else{
					  	system("cls");												//LIMPA A TELA
					  	printf("Jogada invalida! Comece a jogada novamente!\n\n");	//EXIBE A MENSAGEM DE QUE NÃO FOI POSSÍVEL REALIZAR A JOGADA
					  }
					break;
					
				case 80:
					//COME UMA PEDRA ABAIXO DA SELECIONADA
					if((matriz[linha+1][coluna-1] == '.') && (matriz[linha][coluna-1] == 'O')){
						//SE A POSIÇÃO QUE O JOGADOR DESEJA MOVER A PEDRA FOR VAZIA "."E A POSIÇÃO QUE ELE VAI COMER TIVER UMA PEÇA "O", A JOGADA PODE SER FEITA!
  						matriz[linha-1][coluna-1] = '.';	//POSIÇÃO SELECIONADA RECEBE "." POIS FICARÁ VAZIA DEPOIS DA JOGADA
  						matriz[linha][coluna-1] = '.';		//POSIÇÃO DA PEÇA COMIDA RECEBE "." POIS FICARÁ VAZIA
  						matriz[linha+1][coluna-1] = 'O';	//POSIÇÃO NOVA DA PEDRA SELECIONADA
  						system("cls");						//LIMPA A TELA
  						pecas_comidas++;					//INCREMENTA A CONDIÇÃO DE PARADA (NÚMERO DE PEÇAS COMIDAS)
					  }
					  else{
					  	system("cls");												//LIMPA A TELA
					  	printf("Jogada invalida! Comece a jogada novamente!\n\n");	//EXIBE A MENSAGEM DE QUE NÃO FOI POSSÍVEL REALIZAR A JOGADA
					  }
					break;
			}
		}
		else if(matriz[linha-1][coluna-1] == '.'){											//SE A POSIÇÃO ESCOLHIDA FOR "VAZIA", OU SEJA, IGUAL AO CARACTERE ".", A POSIÇÃO NÃO TEM PINO!
			system("cls");																	//LIMPA A TELA
			printf("Posicao sem pino! Por favor, Selecione uma posicao com um pino!\n");	
		}	//EXIBE A MENSAGEM PARA O JOGADOR DE QUE A POSIÇÃO ESCOLHIDA NÃO TEM UM PINO E DEPOIS DA MENSAGEM ESPERA UMA NOVA JOGADA PELO SCANF NO FINAL DA ESTRUTURA DE REPETIÇÃO WHILE
		
		else{																				//CASO A POSIÇÃO NÃO ESTEJA NOS PARÂMETROS AVALIADOS, A JOGADA É INVÁLIDA
			system("cls");																	//LIMPA A TELA
			printf("Posicao Invalida! Por favor, Selecione uma posicao valida!\n");
		}	//EXIBE A MENSAGEM PARA O JOGADOR DE QUE A POSIÇÃO ESCOLHIDA NÃO TEM UM PINO E DEPOIS DA MENSAGEM ESPERA UMA NOVA JOGADA PELO SCANF NO FINAL DA ESTRUTURA DE REPETIÇÃO WHILE
		
		if(pecas_comidas < 31){
			imprime_matriz(matriz);												//IMPRIME A MATRIZ
			printf("\nDigite a coordenada X-Y do pino que deseja mover!\n");	//ESPERA UMA NOVA ENTRADA DE COORDENADA DO USUÁRIO
			scanf("%d-%d", &linha, &coluna);	
		}	
	}	//FINAL DA ESTRUTURA DE REPETIÇÃO WHILE, LOGO, É PRECISO APRESENTAR O RESULTADO DO JOGO
	
	// FUNÇÃO QUE APRESENTA O RESULTADO DO JOGO
	resultado(matriz, linha, coluna);
	
	return 0; //FINAL DO PROGRAMA
}
