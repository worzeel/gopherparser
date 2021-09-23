#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	char *line = NULL;
	size_t len = 0;

	char *delim = "\t";

	while ((getline(&line, &len, stdin)) != -1)
	{
		char *token = strtok(line, delim);

		char itemtype;
		char *displaystring = NULL;
		char *selector = NULL;
		char *host = NULL;
		int port = 0;

		int display = 1;

		int mapitem = 0;
		while (token != NULL)
		{
			if (token[0] == '\n') 
			{
				display = 0;
			}
			long tokenlen = strlen(token);

			switch (mapitem)
			{
			case 0:
				itemtype = token[0];
				displaystring = realloc(displaystring, tokenlen);

				strncpy(displaystring, token + 1, tokenlen - 1);
				displaystring[tokenlen-1] = '\0';
				break;

			case 1:
				// selector
				break;

			case 2:
				// host
				break;

			case 3:
				// port
				break;
			}

			token = strtok(NULL, delim);
			mapitem++;
		}

		if (display)
		{
			printf("itemtype: %c\n", itemtype);
			printf("displaystring: %s\n", displaystring);
		}
	}

	/*
	 * 2) Parse the line into the following format:
	 *      => ABBB\tCCC\tDDD\tEEE
	 *  A   - Item type (single character)
	 *  BBB - Display string
	 *  CCC - Selector
	 *  DDD - host
	 *  EEE - port
	 */

	/*
	 * 3) Create data using this information obtained from steps above
	 */

	free(line);

	return 0;
}
