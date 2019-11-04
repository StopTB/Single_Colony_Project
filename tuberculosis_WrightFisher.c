#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
	int mutation_label;
	int mutation_numbers;
}CELL;

typedef struct
{
	int label;
	int number;
	float rate;
}MUTATION;

int main()
{
	CELL cell1[110000000] = {0}, cell2[110000000] = {0};
	//MUTATION mutation[6000000] = {0};
	int cells, mutations, i, j, k, p, q, r, m, n, a, b, c, sample_cell[1001], mutation_number[21] = {0};
	float theory;
	float s, t;
	float generations;
	int stochastic = 10000;
	int mu_rate = 8;
	int up_cells = 100000000;
	int samples = 1000;
	float SNVs = 1.19;    /*Input the expected SNVs*/
	FILE *fp;
	srand((unsigned)time(NULL));

	/*cell growth*/
	cells = 1;
	theory = 1.0;
	mutations = 0;
	generations = SNVs / 0.0008;
	t = log((float)up_cells);
	s = t / generations;
	fp = fopen("cell number.txt","w+");
	for(i = 1; i <= generations; i++)
	{
		k = cells;
		theory = theory * exp((float)s);
		t = theory - (int) theory;
		if(t < 0.5)
			cells = theory;
		else
			cells = theory + 1;
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
				//mutation[mutations].label = cell1[r].mutation_label;
				//cell2[j].mutation_label = mutations;
				cell2[j].mutation_numbers = cell1[r].mutation_numbers + 1;
			}
			else
			{
				//cell2[j].mutation_label = cell1[r].mutation_label;
				cell2[j].mutation_numbers = cell1[r].mutation_numbers;
			}
		}
		fprintf(fp, "%d\t%d\t%d\n", i, cells, mutations);
		if(cells > up_cells)
			break;
		for(j = 1; j <= cells; j++)
		{
			//cell1[j].mutation_label = cell2[j].mutation_label;
			cell1[j].mutation_numbers = cell2[j].mutation_numbers;
		}
	}



	/*random sampling*/
	fp = fopen("random choose.txt", "w+");
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
		fprintf(fp, "%d\t%d\t%d\n", i, r, cell2[r].mutation_numbers);
	}



	fclose(fp);
}