#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void import( char *imp_type, char *imp_pattern )
{
	char filename[76];

	int isp = 0;
	int isn = 0;

	while( isn != 76 ) //zero out filename
	{
		filename[isn] = '\0';
		isn++;
	}

	filename[0] = 'g'; //fill in first characters in filename
	filename[1] = 'e';
	filename[2] = 'n';
	filename[3] = '/';
	
	isn = 4;
	while( isn != 72 && imp_pattern[isp] != '\0' ) //add the import pattern to filename
	{
		filename[isn] = imp_pattern[isp];
		isp++;
		isn++;
	}
	
	isp = 0;
	while( isn != 75 && imp_type[isp] != '\0' ) //add extention/type to filename
	{
		filename[isn] = imp_type[isp];
		isp++;
		isn++;
	}

	FILE *isfp;
	isfp = fopen(filename, "r"); //open file with filename for reading

	if( isfp != NULL ) //check if file could be opened
	{
		char isch;
		isch = fgetc(isfp);

		while( isch != EOF ) //print links from file char by char
		{
			printf("%c", isch );
			isch = fgetc(isfp);
		}
	}
	//put error in else here if file couldn't be opened
}	

int main( int argc, char *argv[] )
{
	int running = 0;;
	if(argc == 2) //check if it's one argument and open if so
	{
		running = 1;
	}
	else if( argc > 2 ) //abort if more than one argument
	{
		printf("ERROR: Too many filenames.\n");
		return 1;
	}
	else //abort if there is no argument
	{
		printf("ERROR: Missing argument - No filename.\n");
		return 1;
	}

	//make a file pointer and open the file for reading
	FILE *fp;
	fp = fopen(argv[1], "r");

	if( fp==NULL ) //check if the file opened properly
	{
		printf("ERROR: File couldn't be opened");
		return 1;
	}

	//get the first char from the file
	char ch = '\n';
	
	//setup chars to find imports
	int n;
	int newline = 0;
	char cs[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	char tag[8] = {'i', 'm', 'p', 't', 'a', 'g', '\0', '\0'};
	char sub[8] = {'i', 'm', 'p', 's', 'u', 'b', '\0', '\0'};
	char blog[8] = {'i', 'm', 'p', 'b', 'l', 'o', 'g', '\0'};
	char start[8] = {'s', 't', 'a', 'r', 't', '\0', '\0', '\0'};
	char title[8] = {'t', 'i', 't', 'l', 'e', '\0', '\0', '\0'};
	char pattern[63];
	
	char dottag[8] = {'.', 't', 'a', 'g', '\0', '\0', '\0', '\0'};
	char dotsub[8] = {'.', 's', 'u', 'b', '\0', '\0', '\0', '\0'};

	int p;
	p = 0;
	while( p != 63 )
	{
		pattern[p] = '\0';
		p++;
	}

//	printf("debug variables declared");

	while( ch!=EOF && running == 1 )
	{
		if( ch == '\n' )
		{
			ch = fgetc(fp); //get the first char of the file
			//printf("first char read");

			if( ch == '!' )
			{
				n = 0;
	
				ch = fgetc(fp);
				while( ch != ':' && ch != '\n' && ch != EOF && n <= 8 )
				{
					cs[n] = ch;
					ch = fgetc(fp);
					n++;
				}
				
				ch = fgetc(fp); //ignore colon
				
				if( strcmp( cs, start ) == 0 )
				{
				       	running = 2;
					//printf("start reading file");
				}
		
				//implement search engine stuff, header modification and such here
		
				while( n >= 0 )
				{
					cs[n] = '\0';
					n--;
				}
			}
			
			else //char after new line wasn't!
			{
				//printf("\n%c", ch); //print lost newline and current char
				ch = fgetc(fp);
			}
		}
		else //no new line so print char and move on
		{
			//printf("%c", ch);
			ch = fgetc(fp);
		}
	}

	//run through the entire file char by char
	while( ch!=EOF )
	{
		if( ch == '\n' )
		{
			printf("\n");
			ch = fgetc(fp);

			while( ch == '\n' )
			{
				printf("\n");
				ch = fgetc(fp);
			}
		
			if( ch == '!' )
			{
				ch = fgetc(fp);
				n = 0;
				while( ch != ':' && ch != '\n' && ch != EOF && n <= 8 )
				{
					cs[n] = ch;
					ch = fgetc(fp);
					n++;
				}
			
				if( ch != ':' )
				{
					break;
				}
				
				ch = fgetc(fp); //ignore : and read pattern
				
				p = 0; //set p to 0 before we get the pattern
				while( ch != '\n' && ch != EOF && p != 63 )
				{
					pattern[p] = ch;
					ch = fgetc(fp);
					p++;
				}

				//printf("\npattern gotten %s\n", cs);

				if( strcmp( cs, tag ) == 0 )
				{
					import( dottag, pattern );
				//	printf("\npattern written\n");
				}
				else if( strcmp( cs, sub ) == 0 )
				{
					import( dotsub, pattern );
				}
				//if( strcmp( cs, blog ) == 0 ){ impblog(pattern); }
		
				p = 63;
				while( p >= 0 )
				{
					pattern[p] = '\0';
					p--;
				}
				n = 7;
				while( n >= 0 )
				{
					cs[n] = '\0';
					n--;
				}
			}
			else if( ch == EOF )
			{
				break;
			}
			else
			{
				printf("%c", ch); // print lost newline and char
				ch = fgetc(fp);
			}
		}
		else
		{
			printf("%c", ch);
			ch = fgetc(fp);
		}
	}
	
	//printf("Det finns inget mer i %s\n", argv[1]);
	fclose(fp);

	return 0;
}

