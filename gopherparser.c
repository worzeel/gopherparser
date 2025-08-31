#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_json_string(const char *str)
{
	if (str == NULL) return;
	
	putchar('"');
	while (*str) {
		switch (*str) {
		case '"':
			printf("\\\"");
			break;
		case '\\':
			printf("\\\\");
			break;
		case '\n':
			printf("\\n");
			break;
		case '\r':
			printf("\\r");
			break;
		case '\t':
			printf("\\t");
			break;
		default:
			putchar(*str);
			break;
		}
		str++;
	}
	putchar('"');
}

int
setoutput(char **outputvalue, const char *token, size_t tokenlen)
{
	char *new_ptr = realloc(*outputvalue, tokenlen + 1);
	if (new_ptr == NULL) {
		return -1;
	}
	*outputvalue = new_ptr;
	strncpy(*outputvalue, token, tokenlen);
	(*outputvalue)[tokenlen] = '\0';
	return 0;
}

int
main()
{
	char *line = NULL;
	size_t len = 0;
	const char *delim = "\t\n";

	printf("[");

	int isfirst = 1;
	ssize_t read_result;
	
	while ((read_result = getline(&line, &len, stdin)) != -1)
	{
		char *token = strtok(line, delim);

		char itemtype = '\0';
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

			size_t tokenlen = strlen(token);

			display = 1;
			switch (mapitem)
			{
			case 0:
				itemtype = token[0];
				if (tokenlen > 1) {
					if (setoutput(&displaystring, token + 1, tokenlen - 1) != 0) {
						fprintf(stderr, "Memory allocation failed\n");
						goto cleanup;
					}
				}
				break;

			case 1:
				if (setoutput(&selector, token, tokenlen) != 0) {
					fprintf(stderr, "Memory allocation failed\n");
					goto cleanup;
				}
				break;

			case 2:
				if (setoutput(&host, token, tokenlen) != 0) {
					fprintf(stderr, "Memory allocation failed\n");
					goto cleanup;
				}
				break;

			case 3:
				if (setoutput(&portstring, token, tokenlen) != 0) {
					fprintf(stderr, "Memory allocation failed\n");
					goto cleanup;
				}
				port = atoi(portstring);
				break;
			}

			token = strtok(NULL, delim);
			mapitem++;
		}

		if (display)
		{
			if (!isfirst)
				printf(",\n  ");
			else
				printf("\n  ");
			isfirst = 0;

			printf("{\"itemType\":\"%c\"", itemtype);

			if (displaystring != NULL && displaystring[0] != '\0') {
				printf(",\"displayString\":");
				print_json_string(displaystring);
			}
			if (selector != NULL && selector[0] != '\0') {
				printf(",\"selector\":");
				print_json_string(selector);
			}
			if (host != NULL && host[0] != '\0') {
				printf(",\"host\":");
				print_json_string(host);
			}
			if (port != 0)
				printf(",\"port\":%d", port);

			printf("}");
		}

cleanup:
		free(portstring);
		portstring = NULL;
		free(host);
		host = NULL;
		free(selector);
		selector = NULL;
		free(displaystring);
		displaystring = NULL;
	}

	printf("\n]\n");

	free(line);
	return 0;
}
