#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *f;
	char *location = "/etc/todo/todo.txt";
	char *config = "~/.todocconfig";
	char *mode = "r+";
	char buf[BUFSIZ];
	char out[BUFSIZ];
	int i = 0;
	if(argc > 1 && (strcmp("a", argv[1]) == 0)) mode = "a";

	if((f = fopen(location, mode)) == NULL)
	{
		puts("no todo.txt found");
		return 0;
	}
	
	if((f = fopen(config, "a")) == NULL)
	{
		puts("no config found");
		return 0;
	}
	
	if(argc > 1)
	{
		switch(argv[1][0])
		{
			case 'a':
			for(i; i < (argc - 2); i++)
			{
				strcat(buf, argv[i + 2]);
				if(i != (argc - 3)) strcat(buf, " ");
			}
			fprintf(f, "%s\n", buf);	
			break;

			case 'r':		
			while(fgets(buf, sizeof(buf), f) != NULL)
			{
				if(((i++) + 1) != atoi(argv[2])) strcat(out, buf);
			}
			fclose(f);
			fopen("/etc/todo/todo.txt", "w");
			fputs(out, f);	
			break;

			case 'c':
			fclose(f);
			fopen("/etc/todo/todo.txt", "w");
			break;

			case 'h':
			puts("a [string]. appends. ex. todo a make todo.c better.");
			puts("r [index]. removes. ex. todo r 5.");
			puts("c. clears.");
			puts("h. displays this menu.");
			puts("v. displays version info.");
			break;

			case 'v':
			puts("todo.c 1.0");
			break;

			default:
			puts("please use 'a, r, c, h, v'");
			break;
		}
	}
	else
	{
		while(fgets(buf, sizeof(buf), f) != NULL) 
			printf("%d: %s",((i++) + 1), buf);
	}
	fclose(f);
	return 0;
}
