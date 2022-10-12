//Hello how are you this beautiful day?

#include "scanner.h"
#include <stdio.h>

int get_token(Token *token) {
	int c = fgetc(stream);
	if (c == EOF) {
		token->type = T_EOF;
		return 0;
	}
	return 0;
}
