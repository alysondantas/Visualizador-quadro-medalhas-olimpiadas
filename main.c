/*******************************************************************************

Autor: Alyson Felipe Oliveira Dantas

Componente Curricular: MI - Algoritmos - P04

Concluido em: 03/09/2015

Declaro que este código foi elaborado por mim de forma individual e não contém nenhum

trecho de código de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código

de outra autoria que não a minha está destacado com uma citação para o autor e a fonte

do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.

******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>



int arquivodeentrada(int, int);//prototipo da função que ler e cria o quadro inicial
int ordenar_quadro(int,int,int quadroinicial[][5]);//prototipo da função que ordena o quadro inicial e grava no arquivo de saida
int editar_quadro(int,int,int quadroinicial[][5]);//prototipo da função que edita o quadro inicial
int sair_gerar_arquivo_final(int,int quadroinicial[][5]);//prototipo da função que sai do programa e finaliza o arquivo

int main(int paises, int modalidades, int quadroinicial) {
	int opcao_menu=0;//varivel para as opções do menu
	int l, c; //l=linha, c=coluna.
	
	system("cls");//limpa a tela
	printf("============MENU QUADRO DE MEDALHAS - OLIMPIADAS RIO 2016============");
	printf("\n Você deseja:\n	1-Ler arquivo e ordenar altomaticamente:\n	2-Editar quadro de medalhas:\n	3-Sair e gerar arquivo final de texto.\n");//menu criado pra navegar entre as opções que estão nas funçoes
	scanf("%i",&opcao_menu);
	switch(opcao_menu){
		case 1:
			arquivodeentrada(paises,modalidades);
			break;
		case 2:
			
			editar_quadro(paises,modalidades,quadroinicial);
			break;
		case 3:
			sair_gerar_arquivo_final(paises,quadroinicial);
			break;
		default:
			
			printf("Opção invalida.");
			break;
	}
	
		
	return 0;
}

//essa função ler o arquivo de entrada
int arquivodeentrada(int paises, int modalidades){
	int l=0,c=0;
	float percentual_provas_dispotadas;//variavel para calcular o percentual de provas disputadas
	
	FILE *entrada; //ponteiro para o arquivo txt entrada
	entrada = fopen("entrada.txt", "r");
	
	if(entrada == NULL){ //avisa caso o o arquivo não seja encontrado
		printf("Arquivo entrada.txt não encontrado");
		system ("pause");
		return 0;
	}
	
	fscanf(entrada,"%i", &paises); //ler primeiro caractere referente aos paises
	fscanf(entrada,"%i",&modalidades); // ler segundo caractere referente as modalidades
	
	int quadromedalhas[paises][modalidades*3];
	int quadroinicial[paises][5];
	
	printf("Sao %i paises.\n",paises);
	printf("Sao %i modalidades.\n",modalidades);
	printf("Sao %i medalhas por pais.\n",modalidades*3);
	

	for(l=0; l<paises; l++){
		for(c=0; c<5; c++){
			quadroinicial[l][c]=0;}}//Zera a matriz do primeiro quadro.
	
	for(l=0; l<paises; l++){
		for(c=0; c<(modalidades*3); c++){
			fscanf(entrada, "%i", &quadromedalhas [l][c]);
		}
	}
		printf("O arquivo lido é:\n");
		for(l=0; l<paises; l++){
			for(c=0; c<modalidades*3; c++){
				printf(" %i",quadromedalhas [l][c]);			
		}
		printf("\n");
		}
	
	fclose(entrada);
	
	float provasdisp=0;//variavel para contar quantas provas disputadas
	for(l=0; l<paises; l++){
	for(c=0; c<(modalidades*3); c+=3){//numera os paises
		quadroinicial[l][0] = l+1; }}
	for(l=0; l<paises; l++){
		for(c=0; c<(modalidades*3); c+=3){//aqui guarda ouro
			quadroinicial[l][1] = quadromedalhas[l][c]+quadroinicial[l][1];}
			provasdisp=provasdisp+quadroinicial[l][1];}//faz a soma das medalhas de ouro para saber quantas provas foram disputadas
	for(l=0; l<paises; l++){
		for(c=1; c<(modalidades*3); c+=3){//aqui guarda prata	
			quadroinicial[l][2] = quadromedalhas[l][c]+quadroinicial[l][2];}}
	for(l=0; l<paises; l++){
		for(c=2; c<(modalidades*3); c+=3){//aqui guarda bronze
			quadroinicial[l][3] = quadromedalhas[l][c]+quadroinicial[l][3];}}
		for(l=0; l<paises; l++){
		for(c=1; c<4; c++){//aqui guarda o total de medalhas por país
			quadroinicial[l][4] = quadroinicial[l][c]+quadroinicial[l][4];}
	printf("\n");}

	//exibe o quadro inicial sem ordenação
	printf(" Quadro de Medalhas Inicial\n    Ouro | Prata | Bronze\n");
	for(l=0; l<paises; l++){
		printf(" P");
		for(c=0; c<4; c++){
			if(c==0){
			printf("%i",quadroinicial[l][c]);}else{
			printf(" %6i",quadroinicial[l][c]);	
			}
		}
		printf("\n");
	}
	//mostro a quantidades de provas disputadas e o percentual
	printf("\n Quantidade inicial de provas disputadas: %3.0f\n",provasdisp);
	percentual_provas_dispotadas = (provasdisp*100)/306;
	printf("\n Percentual de provas dispotadas: %3.2f\n",percentual_provas_dispotadas);
	
	// O arquivo de texto de saida é criado e grava nele os dois primeiros quadros
	FILE *saida; //ponteiro para o arquivo txt de saida relatorio.txt
	saida = fopen("relatorio.txt", "w");
	// Gravo no arquivo de texto o primeiro quadro
	fprintf(saida," Quadro de Medalhas Inicial\n    Ouro | Prata | Bronze\n\n");
	for(l=0; l<paises; l++){
		fprintf(saida,"P");
		for(c=0; c<4; c++){
				if(c==0){
			fprintf(saida,"%i",quadroinicial[l][c]);}else{
			fprintf(saida," %6i",quadroinicial[l][c]);	
			}
		}
		fprintf(saida,"\n");
	}
	fprintf(saida,"\n\n Quantidade inicial de provas disputadas: %3.0f\n",provasdisp); 
	fprintf(saida," Percentual de provas dispotadas: %3.2f \n\n",percentual_provas_dispotadas);
	
	fclose(saida);
	
//diretamente chamo a função de ordenar os quadros de medalha
ordenar_quadro(paises,modalidades,quadroinicial);
	

}

//função para ordenar os quadros.
int ordenar_quadro(int paises, int modalidades, int quadroinicial[][5]){
	int c,l,p,opcao_menu;	
	int vetorauxiliar[5]; //vetor usado para ordenar a matriz entre desempenho e quantidade total de medalhas
	//ordenação por rankin
	FILE *saida; //ponteiro para o arquivo txt de saida relatorio.txt
	saida = fopen("relatorio.txt", "a");
	//zera o vetor auxilizar
	for(c=0;c<5;c++){
		vetorauxiliar[c]=0;
	}
	//ordenação por toal de ouro
	for(l=paises-1;l>=0;l--){
		for(p=1;p<=l;p++){
			if(quadroinicial[p-1][1] < quadroinicial[p][1]){//se ouro for maior ordena por ouro
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
				
				else if(quadroinicial[p-1][1] == quadroinicial[p][1] && quadroinicial[p-1][2] < quadroinicial[p][2]){//caso ouro seja empate ordena por prata
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
				
				else if(quadroinicial[p-1][1] == quadroinicial[p][1] && quadroinicial[p-1][2] == quadroinicial[p][2] && quadroinicial[p-1][3] == quadroinicial[p][3]){//caso prata tambem empate ordena por bronze
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
					
					}}
					
	printf("\n Ranking com Desempenho Inicial dos paises\n    Ouro | Prata | Bronze | Total\n");
	for(l=0; l<paises; l++){
		printf(" P");
		for(c=0; c<5; c++){
			if(c==0){
				printf("%i",quadroinicial[l][c]);}else{
				printf(" %6i",quadroinicial[l][c]);	
			}
		}
		printf("\n");
	}
	//grava no arquivo de saida o ranking inicial
	fprintf(saida,"\n Rancking com Desempenho Inicial dos paises\n    Ouro | Prata | Bronze | Total\n");
	for(l=0; l<paises; l++){
		fprintf(saida,"P");
		for(c=0; c<5; c++){
			if(c==0){
				fprintf(saida,"%i",quadroinicial[l][c]);}else{
				fprintf(saida," %6i",quadroinicial[l][c]);	
			}
		}
		fprintf(saida,"\n");
	}
	
	
	//fim da ordenação por total de ouro
	//ordenação por total inicio
		for(l=paises-1;l>=0;l--){
		for(p=1;p<=l;p++){
			if(quadroinicial[p-1][4] < quadroinicial[p][4]){
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}}}



		printf("\n Quadro ordenado pela quantidade Total de medalhas recebidas\n    Total | Ouro | Prata | Bronze\n");
	for(l=0; l<paises; l++){
		printf("P");
		for(c=0; c<4; c++){
			if(c==1){
			printf("%5i",quadroinicial[l][4]);}
			if(c==0){
				printf("%i",quadroinicial[l][c]);}else{
				printf(" %6i",quadroinicial[l][c]);	
			}
		}
		printf("\n");
	}
	//ordenação por total fim
	
	//grava no arquivo txt saida o quadro ordenado pela quantidade total de medalhas
	fprintf(saida,"\n\n Quadro ordenado pela quantidade Total de medalhas recebidas\n    Total| Ouro | Prata | Bronze\n");
	for(l=0; l<paises; l++){
		fprintf(saida," P");
		for(c=0; c<4; c++){
			if(c==1){
				fprintf(saida,"%5i",quadroinicial[l][4]);}
			if(c==0){
				fprintf(saida,"%i",quadroinicial[l][c]);}else{
				fprintf(saida," %6i",quadroinicial[l][c]);	
			}
		}
		fprintf(saida,"\n");
	}
	
	fclose(saida);
	//um switch case para o usuario escolher o que deseja fazer apos finalizar a leitura e ordenação do arquivo
	printf("\n\n Agora que o quadro foi ordenado, você deseja voltar ao menu ou editar o quadro de medalhas?\n 1-voltar ao menu. 2-editar o quadro de medalhas.\n");
	scanf("%i",&opcao_menu);
	switch(opcao_menu){
		case 1:
			main(paises,modalidades,quadroinicial);
		break;
		case 2:	
			editar_quadro(paises,modalidades,quadroinicial);
		break;
		default:
			printf("\nOpção invalida, você foi redirecionado ao menu principal.\n");
			main(paises,modalidades,quadroinicial);
		break;
	}

}

int editar_quadro (int paises,int modalidades, int quadroinicial[][5]){
	int l=0,c=0,p=0,menu=0,medalha=0;//l = linha, c = coluna,p=auxiliar de coluna, menu é para o controle do menu de edição de medalhas, medalhas são a quantidade de medalhas que vão ser adicionadas
	int pais=0,tipo_medalha;
	int vetorauxiliar[5];
	//zera o vetor auxliar
	for(c=0;c<5;c++){
		vetorauxiliar[c]=0;
	}
	
	
	//ordena a matriz novamente por pais para melhorar a edição da mesma
	for(l=paises-1;l>=0;l--){
		for(p=1;p<=l;p++){
			if(quadroinicial[p-1][0] > quadroinicial[p][0]){
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}}}
	
	
		
	//entra em um laço de repetição para que a edição do quadro de medalhas seja continua, e so sai
	for(;;){//laço infinito para editar as medalhas
	system("cls");//limpa a tela
	printf(" Quadro de Medalhas\n   Ouro | Prata | Bronze\n");
	for(l=0; l<paises; l++){
		printf("P");
		for(c=0; c<4; c++){
			printf("%i    ",quadroinicial[l][c]);
		}
		printf("\n");
	}
	printf(" De qual país voce deseja adicionar ou remover uma medalha? ou '0' para sair\nP");
	scanf("%i",&pais);
	if(pais>paises || pais<0){//Caso o usuario digite um pais que não esteja no quadro a variavel recebe -1 e o switch case impede o programa de continuar
		menu = -1;
	} else if(pais==0){
		menu=0;}
	else{
		menu=1;
	}

	switch(menu){
		case 0:
		main(paises,modalidades,quadroinicial);
		break;
		
		case -1:
		printf("\nPaís invalido!\n");
		break;
		
		case 1:
	
		printf("\n Qual medalha deseja adicionar? 1-ouro/2-prata/3-bronze? ou 0-sair.\n");
		scanf("%i",&tipo_medalha);
		printf(" Quantas Medalhas deseja adicionar ou remover? (Exemplo: 2 ou -3)");
		scanf("%i",&medalha);
		
		switch(tipo_medalha){
			
			case 0:
				main(paises,modalidades,quadroinicial);
				break;
			
			case 1:
				quadroinicial[pais-1][1]=quadroinicial[pais-1][1]+medalha;
				printf(" Adicionada uma medalha de ouro em P%i",pais);
				break;
			case 2:
				quadroinicial[pais-1][2]=quadroinicial[pais-1][2]+medalha;
				printf(" Adicionada uma medalha de prata em P%i",pais);
				break;
			case 3:
				quadroinicial[pais-1][3]=quadroinicial[pais-1][3]+medalha;
				printf(" Adicionada uma medalha de bronze em P%i",pais);
				break;
			
			default:
				printf(" Opcao invalida.");
				break;
}	break;	
	default://por garantia se ouver algum erro ele chama a main novamente
		printf("Erro!");
		main(paises,modalidades,quadroinicial);
		break;	
}
	}
main(paises,modalidades,quadroinicial);
}

int sair_gerar_arquivo_final(int paises,int quadroinicial[][5]){
	
	int l,p,c;
	int vetorauxiliar[5];
	float percentual_provas_dispotadas,provasdisputadas;
	
	
	for(l=0; l<paises; l++){
		provasdisputadas=provasdisputadas+quadroinicial[l][1];}//faz a soma das medalhas de ouro para saber quantas provas foram disputadas
	
	
	FILE *saida; //ponteiro para o arquivo txt de saida relatorio.txt
	saida = fopen("relatorio.txt", "a");
	//Ordena novamente por relação de medalhas
	for(l=paises-1;l>=0;l--){
		for(p=1;p<=l;p++){
			if(quadroinicial[p-1][1] < quadroinicial[p][1]){//ordena por ouro maior
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
				
				else if(quadroinicial[p-1][1] == quadroinicial[p][1] && quadroinicial[p-1][2] < quadroinicial[p][2]){//caso ouro esteja empatado desempata por prata
					
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
				
				else if(quadroinicial[p-1][1] == quadroinicial[p][1] && quadroinicial[p-1][2] == quadroinicial[p][2] && quadroinicial[p-1][3] == quadroinicial[p][3]){ //caso prata tambem esteja empatado desempata por bronze
					
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}
					
					}}
	//grava no arquivo de saida o ranking inicial
	fprintf(saida,"\n Rancking com Desempenho dos paises ao encerrar o programa\n    Ouro | Prata | Bronze | Total\n");
	for(l=0; l<paises; l++){
		fprintf(saida,"P");
		for(c=0; c<5; c++){
			if(c==0){
				fprintf(saida,"%i",quadroinicial[l][c]);}else{
				fprintf(saida," %6i",quadroinicial[l][c]);	
			}
		}
			fprintf(saida,"\n");
		}
		//ordena por total de medalhas novamente
		for(l=paises-1;l>=0;l--){
		for(p=1;p<=l;p++){
			if(quadroinicial[p-1][4] < quadroinicial[p][4]){
				for(c=0;c<5;c++){
					vetorauxiliar[c]=quadroinicial[p-1][c];
					quadroinicial[p-1][c]=quadroinicial[p][c];
					quadroinicial[p][c]=vetorauxiliar[c];}}}}
	

	fprintf(saida,"\n Quadro ordenado pela quantidade Total de medalhas recebidas ao encerrar o programa\n    Total | Ouro | Prata | Bronze\n");
	for(l=0; l<paises; l++){
	fprintf(saida,"P");
		for(c=0; c<4; c++){
			if(c==1){
				fprintf(saida,"%5i",quadroinicial[l][4]);}
			if(c==0){
				fprintf(saida,"%i",quadroinicial[l][c]);}else{
				fprintf(saida," %6i",quadroinicial[l][c]);	
			}
		}
		fprintf(saida,"\n");
	}
	
	fprintf(saida,"\n Quantidade de provas disputadas ao encerrar o programa: %3.0f\n",provasdisputadas);
	percentual_provas_dispotadas = (provasdisputadas*100)/306;
	fprintf(saida," Percentual de provas dispotadas: %3.2f",percentual_provas_dispotadas);
	
	fclose(saida);
	
	
	printf(" Até mais!\n");
	
	system ("pause");
	return 0;
}
