#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
setoutput(char **outputvalue, char *token, long tokenlen)
{
	*outputvalue = realloc(*outputvalue, tokenlen+1);

	strncpy(*outputvalue, token, tokenlen);
}

int
main()
{
	char *line = NULL;
	size_t len = 0;

	char *delim = "\t\n";

	printf("[");

	int isfirst = 1;
	while ((getline(&line, &len, stdin)) != -1)
	{
		char *token = strtok(line, delim);

		char itemtype = 0;
		char *displaystring = NULL;
		char *selector = NULL;
		char *host = NULL;
		char *portstring = NULL;
		int port = 0;

		int display = 0;

		int mapitem = 0;
		while (token != NULL)
		{
			if (token[0] == '\n') 
				break;

			long tokenlen = strlen(token);

			display = 1;
			switch (mapitem)
			{
			case 0:
				itemtype = token[0];

				displaystring = realloc(displaystring, tokenlen+1);

				strncpy(displaystring, token + 1, tokenlen - 1);
				displaystring[tokenlen-1] = '\0';
				break;

			case 1:
				setoutput(&selector, token, tokenlen);
				break;

			case 2:
				setoutput(&host, token, tokenlen);
				break;

			case 3:
				setoutput(&portstring, token, tokenlen);

				if (portstring != NULL)
					port = atoi(portstring);
				else
					port = 0;
				break;
			}

			token = strtok(NULL, delim);
			mapitem++;
		}

		if (display)
		{
			if (!isfirst)
				printf(",");
			isfirst = 0;

			printf("{itemType: \"%c\"", itemtype);

			if (displaystring != NULL)
				printf(",displayString: \"%s\"", displaystring);
			if (selector != NULL)
				printf(",selector: \"%s\"", selector);
			if (host != NULL)
				printf(",host: \"%s\"", host);
			if (port != 0)
				printf(",port: \"%d\"", port);

			printf("}");

			itemtype = 0;
			free(portstring);
			free(host);
			free(selector);
			free(displaystring);
		}
	}

	printf("]");

	free(line);

	return 0;
}
