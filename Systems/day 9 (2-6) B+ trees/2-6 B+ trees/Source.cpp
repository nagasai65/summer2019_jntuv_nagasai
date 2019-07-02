#define _CRT_SECURE_NO_WARNINGS
#define PAGESIZE 32
#include<stdio.h>
#include<stdlib.h>
struct NonLeafPage
{
	char pagetype;
	char unused[3];
	int children[4];
	int value[3];
};
struct LeafPage
{
	char pagetype;
	char unused[6];
	int sid[3];
	char name[3][5];
};
struct pageInfo
{
	char pagebuffer[PAGESIZE];
	bool used;
	time_t lastused;
	int pageid;
};
void Error(char *s)
{
	printf("%s", s);
	exit(0);
}
void readPage(FILE *fp, void *buff, int pagenum)
{
	if (!fread(buff, pagenum * PAGESIZE, 1, fp))
	{
		Error("Cant Reading Page\n");
	}
}
void writePage(FILE *fp, void *buff, int pagenum)
{
	if (!fwrite(buff, pagenum*PAGESIZE, 1, fp))
	{
		Error("Error Writing Page");
	}
}
void writeNamesToLeafPage()
{

	FILE *fp = fopen("store.txt", "wb");
	struct LeafPage *lp = (struct LeafPage*)malloc(sizeof(struct LeafPage));;
	struct NonLeafPage *nlp = (struct NonLeafPage*)malloc(sizeof(struct NonLeafPage));
	nlp->pagetype = 2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%d %s", &lp->sid[j], lp->name[j]);
		}
		if (i)
		{
			nlp->value[i - 1] = lp->sid[0];
			nlp->unused[i - 1] = 0;
		}
		nlp->children[i] = i;
		fwrite(lp, PAGESIZE, 1, fp);
	}
	fwrite(nlp, PAGESIZE, 1, fp);
	free(nlp);
	free(lp);
	fclose(fp);
}
int isNonLeafPage(void *buff)
{
	char *which;
	which = (char*)buff;
	if (*which == 2)
		return 1;
	return 0;
}
int searchInLP(int pgno, int search_id)
{

}
int searchInNLP(struct NonLeafPage *nlp, int search_id)
{
	int i,stats=0;
	for (i = 0; i < 3; i++)
	{
		if (nlp->value[i] < search_id)
		{
			stats=searchInLP(nlp->children[i],search_id);
			if (stats)
				return 1;
		}
	}
	return searchInLP(nlp->children[i], search_id);
}
int isPoolHaveNLP(struct pageInfo *pgpool)
{
	for (int i = 0; i < 3; i++)
	{
		if (pgpool->pagebuffer[0]==2)
			return 
	}
}
void getStdName(int id,char *res,struct pageInfo *pgpool)
{
	if (isPoolHaveNLP(pgpool))
}
void init(struct pageInfo *pginfo, int len)
{
	for (int i = 0; i < len; i++)
	{
		pginfo->used = 0;
	}
}
int main()
{
	struct pageInfo pgpool[3];
	init(pgpool, 3);
	char *res = (char*)malloc(50);
	int i = 1;
	while (i)
	{
		scanf("%d", &i);
		if (i == -1)
			break;
		getStdName(i,res,pgpool);
	}
	free(res);
	return 0;
}