#include<stdio.h>
#include <stdlib.h>
#include<locale.h>
//ALGORITMO SIMPLEX COM CONDIÇÃO MENOR IGUAL

//Alocação dinâmica
float **Alocar_matriz_real (int m, int n)
{
	float **v; /* ponteiro para a matriz */
	int i; /* variavel auxiliar */
	if (m < 1 || n < 1)   /* verifica parametros recebidos */
	{
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}
	/* aloca as linhas da matriz */
	v = (float **) calloc (m, sizeof(float *));
	if (v == NULL)
	{
		printf ("** Erro: Memoria Insuficiente **");
		return (NULL);
	}
	/* aloca as colunas da matriz */
	for ( i = 0; i < m; i++ )
	{
		v[i] = (float*) calloc (n, sizeof(float));
		if (v[i] == NULL)
		{
			printf ("** Erro: Memoria Insuficiente **");
			return (NULL);
		}
	}
	return (v); /* retorna o ponteiro para a matriz */
}
float **Liberar_matriz_real (int m, int n, float **v)
{
	int i; /* variavel auxiliar */
	if (v == NULL) return (NULL);
	if (m < 1 || n < 1)   /* verifica parametros recebidos */
	{
		return (v);
	}
	for (i = 0; i < m; i++) free (v[i]); /* libera as linhas da matriz */
	free (v); /* libera a matriz */
	return (NULL); /* retorna um ponteiro nulo */
}








int main()
{
	float **mat; /* matriz a ser alocada */
	float **base;
	int l, c; /* numero de linhas e colunas da matriz */
	int i, j, k, t;
	char converte[16];
	setlocale(LC_ALL, "Portuguese");
	printf("Digite o numero de restrições: ");
	scanf("%d", &l);
	l = l + 1;
	printf("\nDigite o numero de variáveis da forma não padrão: ");
	scanf("%d", &c);
	k = c;
	c = c + l;
	
	int pergunta;
	while(pergunta!=1 && pergunta!=2){
		printf("\nDigite 1-[Maximização] 2-[Minimização]: ");
		scanf("%d", &pergunta);
		}
	printf("\nDigite os valores da matriz já na forma tabular!\n\n");

	mat = Alocar_matriz_real (l, c);
	base = Alocar_matriz_real (1, l - 1);
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (!(i == l - 1 && j == c - 1)) // enquanto for diferente de 'z'
			{
				printf("\nDigite o cof %d:%d->> ", i + 1, j + 1);
				scanf("%f", &mat[i][j]);
			}
			if (i == l - 1 && pergunta == 1 && j != c - 1) //ultima linha, menos o 'z'
			{
				mat[i][j] = mat[i][j] * (-1); //Quando for problema de max, o progama já inverte o sinal de no tablo 'z' automaticamente
			}
		}
	}




	for (j = 0; j < l; j++) //primeiras variaveis que estao na base
	{
		k++;
		base[0][j] = k;
	}




	int iteracao = 1;
	mat[l - 1][c - 1] = 0; //onde fica o z
	
	while(1)
	{
		system("CLS");
		printf("-------------\n");
		printf("|%dª ITERAÇÃO|\n", iteracao);
		printf("-------------\n");
		printf("|   Base   |");
		for (j = 0; j < c - 1; j++)
		{
			printf("%3sx%d%-3s|", "", j + 1, ""); //printa os 'x' da forma padrao no tablo
		}
		printf("   b    |\n");
		t = k;
		for (i = 0; i < l; i++)
		{
			for (j = 0; j < c; j++)
			{
				if (j == 0 && i != l - 1) //primeira coluna / diferente da ultima l
				{
					printf("|%3s x%.f    |", "", base[0][i]); //printa o 'x' que esta na base
				}

				if (i == l - 1 && j == c - 1) // ultima coluna/ ultima linha
				{
					if (mat[l - 1][c - 1] >= 0)
						printf("Z + %.3f", mat[l - 1][c - 1]); //enquanto for diferente da ultima coluna
					else
						printf("Z %3.f", mat[l - 1][c - 1]);


				}
				else
				{
					if (j == 0 && i == l - 1) //elemento da primeira coluna ultima linha
					{
						printf("|          |");
						sprintf(converte, "%.3f", mat[i][j]);
						printf("%-8s|", converte);
					}
					else
					{
						sprintf(converte, "%.3f", mat[i][j]);
						printf("%-8s|", converte);
					}
				}
			}
			printf("\n");
		}
		int pos_col = -1;
		//achar a variavel que vai sair da base, escolhe um valor negativo
		for (j = 0; j < c; j++)
		{
			if (mat[l - 1][j] < 0)
			{
				pos_col = j; //recebe a posição da coluna que tem o valor negativo
				break;// quando achar o primeiro valor negativo, já para a procura!
			}
		}
		if (pos_col < 0) //fim da solução otima
		{
			int cont = 0;
			printf("\n*Solução Ótima*\n\n");
			for (j = 0; j < c - 1; j++)
			{
				for (i = 0; i < l - 1; i++)
				{
					if (j + 1 == base[0][i])
						cont++;
				}
				if (cont == 0 && mat[l - 1][j] == 0 || mat[l-1][j]==-0) // se os custos de alguma variavel não básica for igual a zero (na solução ótima) entao tem infinitas soluções
				{
					printf("\nSolução tem infinitas soluções!\n\n");
					break;
				}
				cont = 0;
			}
			printf("|Variáveis básicas|\n");
			for (i = 0; i < l - 1; i++)
			{
				printf("x%.f = %.4f\n", base[0][i], mat[i][c - 1]);
			}

			printf("\n\n|Variáveis não básicas|\n");
			cont = 0;
			float z;
			for (i = 0; i < c - 1; i++)
			{
				for (j = 0; j < l - 1; j++)
				{
					if (i + 1 == base[0][j])
					{
						cont++;
						break;
					}
				}
				if (cont == 0)
				{
					printf("x%d = 0\n", i + 1);
				}
				cont = 0;
			}


			if (pergunta==1)
				z = (-mat[l - 1][c - 1])*(-1);
			else
				z = -mat[l - 1][c - 1];
			if (z == -0)
				z = 0;
			printf("\n\nZ = %.4f\n\n", z);


			break;
		}





		int pos_lin;
		float min = -1;
		int verifica = 0;
		for (i = 0; i < l - 1; i++) //não precisa da ultima linha do tablo
		{
			if (mat[i][c - 1] >= 0 && mat[i][pos_col] > 0) //so pode fazer o minimo com valor maior q zero!
				if (verifica == 0) //pega o primeiro minimo
				{
					min = mat[i][c - 1] / mat[i][pos_col]; //teste da razao (valor minimo) primeiro minimov
					pos_lin = i;	//posição da linha em que a variavel sai da base
					verifica++;
				}
				else
				{
					if (min > mat[i][c - 1] / mat[i][pos_col])
					{
						pos_lin = i;
						min = mat[i][c - 1] / mat[i][pos_col]; //pega o minimo
					}
				}
		}
		if (min < 0) //se min for negativo entao solução é ilimitada!
		{
			printf("\nSolução ilimitada!\n\n");
			break;
		}


		printf("\n\no minimo do teste da razao é %f\n\n", min);
		printf("|Variáveis básicas|\n");
		for (i = 0; i < l - 1; i++)
		{
			printf("x%.f = %.4f\n", base[0][i], mat[i][c - 1]);
		}

		printf("\n\n|Variáveis não básicas|\n");
		int cont = 0;
		float z;
		for (i = 0; i < c - 1; i++)
		{
			for (j = 0; j < l - 1; j++)
			{
				if (i + 1 == base[0][j])
				{
					cont++;
					break;
				}
			}
			if (cont == 0)
			{
				printf("x%d = 0\n", i + 1);
			}
			cont = 0;
		}



		z = -mat[l - 1][c - 1];
		if (z == -0)
			z = 0;
		printf("\n\nZ = %.4f", z);

		float pivo;
		pivo = mat[pos_lin][pos_col]; //pivô
		for (j = 0; j < c; j++)
		{
			mat[pos_lin][j] = mat[pos_lin][j] / pivo; //colocando o pivo igual a 1 caso nao esteja
		}
		pivo = mat[pos_lin][pos_col]; //pivô atualizado


		//pivoteamento
		float coeficiente;
		for (i = pos_lin + 1; i < l; i++) //proximas linhas em relação ao pivo //zerar para baixo do pivo
		{
			coeficiente = mat[i][pos_col] / pivo;
			for (j = 0; j < c; j++)
			{
				mat[i][j] = mat[i][j] - coeficiente * mat[pos_lin][j];
			}
		}
		if (pos_lin - 1 >= 0)
		{
			for (i = pos_lin - 1; i >= 0; i--) //zerar acima do pivo
			{
				coeficiente = mat[i][pos_col] / pivo;
				for (j = 0; j < c; j++) //ultimo elemento da minha matriz é lixo pois é o "z"
				{
					mat[i][j] = mat[i][j] - coeficiente * mat[pos_lin][j];
				}
			}
		}

		base[0][pos_lin] = pos_col + 1;
		iteracao++;



		printf("\n\n");
		printf("Pressione qualquer tecla para ver a próxima iteração!\n");
		system("PAUSE>>null");
	}

	base = Liberar_matriz_real (1, l - 1, base);
	mat = Liberar_matriz_real (l, c, mat);
	printf("Pressione qualquer tecla para finalizar o progama!\n\n");
	system("PAUSE>>null");
	return 0;


}
