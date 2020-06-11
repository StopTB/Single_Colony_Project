#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int cells, mutations, i, j, k, p, r, a, b, c, sample_cell[1001];
	int cell1[110000000] = {0}, cell2[110000000] = {0};   /*Record the mutation number of each cell*/
	float expected_number;							      /*The expected cell number in each generation*/
	float decimal;										  /*The actual cell number is the round expected cell number*/
	float exponential_parameter;						  /*The parameter of the exponential growth*/
	float expected_generations;							  /*The expected total generations of cell growth*/
	int stochastic = 10000, mu_rate = 8;				  /*The total mutation rate is mu_rate/stochastic=0.0008*/
	int up_cells = 100000000;							  /*The total cell number*/
	int samples = 50;									  /*The number of sampling cells*/
	float SNVs = 3;										  /*The expected mean mutation number per cell when sampling*/
	FILE *fp;
	srand((unsigned)time(NULL));

	/*The growth of TB*/
	cells = 1;
	expected_number = 1.0;
	mutations = 0;
	expected_generations = SNVs / 0.0008;
	exponential_parameter = log((float)up_cells) / expected_generations;
    fp = fopen("cell number.txt","w+");
	fprintf(fp, "generations\tcell_number\tmutation_number\n");
	for(i = 1; i <= expected_generations; i++)
	{
		k = cells;
		expected_number = expected_number * exp((float)exponential_parameter);
		decimal = expected_number - (int)expected_number;
		if(decimal < 0.5)
			cells = expected_number;
		else
			cells = expected_number + 1;
		for(j = 1; j <= cells; j++)
		{
			while(1)
			{
				r = k / 1000000 + 1;
				a = rand() % (r + 1);
				r = k / 1000 + 1;
				b = rand() % (r + 1);
				c = rand() % 1000 + 1;
				r = a * 1000000 + b * 1000 + c;
				if(r <= k)
					break;
			}
			p = rand() % stochastic;
			if(p < mu_rate)
			{
				mutations++;
				cell2[j] = cell1[r] + 1;
			}
			else
				cell2[j] = cell1[r];
		}
		fprintf(fp, "%d\t%d\t%d\n", i, cells, mutations);
		if(cells > up_cells)
			break;
		for(j = 1; j <= cells; j++)
			cell1[j] = cell2[j];
	}
	fclose(fp);




	/*Random Sampling*/
	fp = fopen("random sampling.txt", "w+");
	fprintf(fp, "numbers\tcell_label\tmutation_number\n");
	for(i = 1; i <= samples; i++)
	{
		while(1)
		{
			r = cells / 1000000 + 1;
			a = rand() % (r + 1);
			r = cells / 1000 + 1;
			b = rand() % (r + 1);
			c = rand() % 1000 + 1;
			r = a * 1000000 + b * 1000 + c;
			if(r <= cells)
				break;
		}
		sample_cell[i] = r;
		fprintf(fp, "%d\t%d\t%d\n", i, r, cell2[r]);
	}
	fclose(fp);

	return 0;
	
}