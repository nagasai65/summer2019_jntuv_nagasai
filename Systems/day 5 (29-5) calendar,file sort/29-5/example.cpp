#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
struct person
{
	char name[6];
	int marks;
	int nooffriends;
};
void storeStructure(FILE *fp)
{
	struct person p;
	p.marks = 120;
	sprintf(p.name, "sai");
	p.nooffriends = 1;
	fwrite(&p, sizeof(struct person), 1, fp);
	fclose(fp);
}
void getStructure()
{
	FILE *fp = fopen("sam.txt", "r");
	struct person ex;
	fread(&ex, sizeof(struct person), 1, fp);
	printf("%d", ex.marks);
	fclose(fp);
}
void storemagicnums()
{
	int a[] = { 1920409673,
		543519849, 543449442, 
		1701080931, 1767990304,
		3045740 };
	FILE *fp = fopen("sam.txt", "w");
	fwrite(&a, sizeof(int), 6, fp);
	fclose(fp);
}
void innerstructstorage();
int t_main()
{
	FILE *fp;
	fp = fopen("sam.txt", "wb");
	//storeStructure(fp);
	//getStructure();
	//fprinfex(fp);
	//storemagicnums();
	innerstructstorage();
	return 0;
}