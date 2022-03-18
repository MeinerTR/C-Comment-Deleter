#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SUCCESS 0x42
#define FAILURE 0x41

/*| D: Comment Deleter :D \*/
/*| D: Very Very Useful :D \*/

char *Concatenated(const char *STR1, const char *STR2) {
    const size_t Len1 = strlen(STR1);
    const size_t Len2 = strlen(STR2);
    char *Output = malloc(Len1 + Len2 + 1);
    memcpy(Output, STR1, Len1);
    memcpy(Output + Len1, STR2, Len2 + 1);
return Output;}

void Error(const char *ErrorMessage, const char *OF, const int Message) {
	if (Message) {
		printf("Explain: [%s]\nError: [%s!]\n", ErrorMessage, strerror(errno));
	} else {
		printf("%s[Input]: [%s]\n%s[Error]: [%s!]\n", OF, ErrorMessage, OF, strerror(errno));
	} 
exit(EXIT_FAILURE);}

const char *WithPath(char *String, const char *Path) {
	char *CWD; if ((CWD = (getcwd(NULL, 0))) == NULL) {
		Error("Unable to get CWD(Current-Work-Directory)!", NULL, 1);
	} else {
		String = Concatenated(String, CWD);
		strncat(String, "/", 2);
		String = Concatenated(String, Path);
	} 
return String;}

char *CopyTheCat(const char *Path) {
	char* Output = NULL; size_t len; FILE* File;
	if ((File = fopen(Path, "r")) == NULL) {
		Error(WithPath("", Path), "GetTheCat", 0);	}
	ssize_t Success = getdelim(&Output, &len, '\0', File);
	if (!Success) {Error(WithPath("", Path), "getdelim", 0);}
return Output;}

void MakeBossThe(const char *RealCat, const char *Company) {
	FILE *File = NULL; if ((File = fopen(Company, "w")) == NULL) {
		Error(WithPath("", Company), "MakeBossThe", 0);  }
	for (int Cord = 0; Cord < strlen(RealCat); Cord++)   {
		fputc(RealCat[Cord], File);		   }fclose(File);}

int main(int argc, char** argv) {
	if (argv[1] == NULL) {Error("Need some argv!", "main", 1);}
	for (int vgra = 1; vgra < argc; vgra++) {
		FILE *File = fopen(argv[1], "r");
		char *CopyCat = CopyTheCat(argv[1]);
		char CHR; int DEL = 0; int CURR = 0;
		while (CHR != EOF) {
			CHR = fgetc(File);
			if (CHR == '/' & DEL == 0) {DEL = 1;}
			else if (DEL == 1) {
				if (CHR == '/') {
					CopyCat[CURR - 1] = ' ';
					CopyCat[CURR] = ' '; DEL = 2;}
				else if (CHR == '*') {
					CopyCat[CURR - 1] = ' '; 
					CopyCat[CURR] = ' '; DEL = 3;}
				else {DEL = 0;} }
			if (DEL == 2) {
				if (CHR == '\n') {DEL = 0;} else {
					CopyCat[CURR] = ' ';
				}
			} else if (DEL == 3) {
				if (CHR == '*') {DEL = 4;} else {
					CopyCat[CURR] = ' ';
				}
			} else if (DEL == 4) {
				if (CHR == '/') {
					CopyCat[CURR - 1] = ' ';
					CopyCat[CURR] = ' '; DEL = 0;} 
				else { CopyCat[CURR] = ' '; DEL = 3; } }
			CURR++;} fclose(File); MakeBossThe(CopyCat, argv[vgra]);}
return EXIT_SUCCESS;} // 0 4 2 = 1 5 3
