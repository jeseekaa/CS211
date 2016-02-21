/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 #define true 1
 #define false 0


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *c; //input string
	char *ptr;	//iterator 

};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	if(strlen(ts)==0){
		return NULL;
	} //empty

    TokenizerT *copy = (TokenizerT *) malloc( sizeof(TokenizerT) );

	if(!copy){
	return NULL;
	} //copy was successfully created

	copy->c = malloc(strlen(ts)+1);
	strcpy(copy->c, ts);

	copy->ptr =copy->c;

  	return copy;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	tk->ptr = NULL;
	free(tk->c);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

//use ptr to get tokens without changing the original
	char *ptr = tk->ptr;
	int length = 0;


	while (*ptr != '\0'){ //while not end of char array

		// if . follow a digit
		/*if(isdigit(*ptr) && *(++ptr) == '.'){1
			char *token = (char*)malloc(length+1);
			strncpy(token, tk->ptr, length);
			token[length] = '\0';

			tk->ptr = ptr;

			while(isWhite(*tk->ptr)){ //skip whitepace
			*tk->ptr++;
			}	

			return token;

		}*/
		// if e or E follows a digit
		// if x or X follows a 0 break token before 0
		//...I...I will figure it out someday lel
		
		// if white space

		if(isWhite(*ptr)){
			//Copy char up to white space
			char *token =(char *)malloc(length+1);
			strncpy(token, tk->ptr, length);
			token[length]='\0';
		
			tk ->ptr = ptr;

			while(isWhite(*tk->ptr)){ //skip whitepace
			*tk->ptr++;
		}
		return token;
	}//end ifWhite

	else{ //iterate
		*ptr++;
		length++;
	}
}// end of while loop, end of char array

char *token = (char *)malloc(length +1);
strncpy(token, tk->ptr, length);
token[length] ='\0';
tk->ptr =ptr;

return token;
}


//Check if char is white space
int isWhite (char *c){
	//In command line the only white space that can be inputed as argument is a space
	if(isspace(c)){
		return true;
	}else{
		return false;
	}
}

//Check if char is decimal
int isDec (char *c){
	char *ptr = c;

	while ( *ptr != '\0'){
		if(!isdigit(*ptr++)){ //check if digit
			return false;
		}
	} return true;
}

//Check if char is octal : first 0 followed by 0-7
int isOctal (char *c){
	char *ptr = c;

	if(*ptr !='0'){ //first char is not 0
		return false;
	}

	*ptr++;
	//check if followed by 0-7
	while (isdigit(*ptr) && *ptr !='8' && *ptr !='9'){
		*ptr++; //iterate through
		if(*ptr == '\0'){
			return true;
		}
	} //not digit, 8 or 9
	return false; 

}

//Check if char is hexadecimal: 0x or 0X followed by 0-9, a-f, A-F
int isHex(char *c){
	char *ptr = c;
	if(*ptr++ = '0' && (*ptr =='x' || *ptr =='X')){ //has to start with 0x or 0X
		while(*(++ptr) != '\0'){
			if (!isxdigit(*ptr)){ //check if hex
				return false;
			}
		} 
		return true;
	} 
	return false;
}
//OMG why

//Check if char is float: digits and  can contain e, E, and . and -/+
int isFloat(char *c){ //without changing the string
 char *ptr = NULL;
 long p = strtol(c, &ptr, 0 ); //convert to long

 if(!*ptr){
 	return false;
 }

 if(*ptr =='.' || *ptr == 'e' || *ptr=='E'){ //check for float symbols
 	return true;
 }
 	return false;

}

//Print tokens
//Notes to self: octal has to go before decimal 
void printToken(char* token){

	if(isOctal(token)){
		printf("octal: %s\n", token);
	}

	else if(isFloat(token)){
		printf("float: %s\n", token);
	}

	else if(isDec(token)){
		printf("decimal: %s\n", token);
	}

	else if(isHex(token)){
		printf("hexadecimal: %s\n", token);
	}

	else{
		printf("[0x%02x]\n", token);
	}

	free(token);

}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	
 TokenizerT *tokenizer; //TKCreate("0x8AA5C 0x09 G 0XH520 1.528 201.7e-14 0743 0934 X583");

if(argc <2){
 	return 1;
 }// no input

 else{
 	int i =1;
 	while(i<argc){
 		if(*argv[i] != NULL){
 			tokenizer = TKCreate(argv[i]);
 			break;
 		}
 		i++;
 	}
 }

 if(tokenizer ==NULL){
 	return 1;
 }

 char *token = TKGetNextToken(tokenizer);
 while(*token != '\0'){
 	printToken(token);
 	token=TKGetNextToken(tokenizer);
 }

 TKDestroy(tokenizer);
 return 0;

}
