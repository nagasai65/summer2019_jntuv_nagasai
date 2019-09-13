#include "includeheaders.h"
#include "execute.h"
#include "compile.h"
#include "strfuns.h"

int main()
{
	char line[50],str1[30],str2[30];
	printf("Assembly Code Compiler + Interpreter\n");
	printf("NOTE:\nWant to Compile --> 'compile filename.ext'\n");
	printf("Want to Execute --> 'execute filename.nag' (your extension will be changed to .nag)\n");
	printf("Want to EXIT --> 'exit'\n");
	while (1){

		printf("\n>");
		gets(line);
		splitString(line, str1, str2, ' ');
		if (check(str1, "exit"))
			break;
		if (check(str1, "compile"))
		{
			rtrim(str2);
			compile(str2);
			continue;
		}
		if (check(str1, "execute"))
		{
			rtrim(str2);
			execute(str2);
			continue;
		}
	}
}