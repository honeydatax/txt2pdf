#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int arg,char  *argv[]){
	FILE *f;
	FILE *ff;
	char envi[1080];
	char *c;
	int lines=800;
	if (arg>2){
		sprintf(envi,"%s.ps",argv[2]);
		ff=fopen(envi,"w");
		f=fopen(argv[1],"r");
		if (ff!=NULL && f!=NULL){
			fprintf (ff,"%!PS\n%%Pages: 1\n/Free-Mono findfont\n12 scalefont\nsetfont\nnewpath\n");
			while(feof(f)!=1){
				strcpy(envi," ");
				fgets(envi,1070,f);
				fprintf(ff,"\n20 %d moveto\n( %s ) show\n",lines,envi);
				lines=lines-13;
				if (lines < 28) goto exits;
			}
			exits:
			fprintf(ff,"\n%%EOF\n");
			fclose(ff);
			fclose(f);
			sprintf(envi,"ps2pdf %s.ps %s",argv[2],argv[2]);
			system(envi);
		}	
	}
	return 0;
}
