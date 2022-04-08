#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"


/* TODO
 * printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("<student name #1>Colton Mosier\n");
    printf("<student name #2>N/A\n");
}

/* TODO
 * evaluatePostfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
 * If the postfix expression is invalid it returns "E" to denote an error has occurred.  Be sure to use the helpful functions in booleanEvaluation.
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *evaluatePostfix( char *str )
{
    /* Your variable Declarations: */
    int tokenCount,i;
    char** arrTokens = tokenizeString( str, &tokenCount );
    Stack *s = createStack();
    char *op1;
    char *op2;

    for(i=0;i<tokenCount;i++){
        char *operand = arrTokens[i];

        if(stringToBoolean(operand)==TRUE || stringToBoolean(operand)==FALSE)
        {
            push(s,arrTokens[i]);
        }
        else
        {
            if(s->capacity == 0)
            {
                return booleanToString( ERROR ); 
            }
            else
            {
                if(strcmp(operand,"NOT")==0) /* handle NOT operator */
                {
                    op1 = pop(s);
                    push(s,booleanToString(!(stringToBoolean(op1))));
                }
                else
                {
                    if(s->top < 1) 
                    {
                      return booleanToString( ERROR );
                    }
                    else
                    {
                        op2 = pop(s);
                        op1 = pop(s);


                        if(strcmp(operand,"AND")==0) /* handle AND operator */
                        {   
                            push(s,booleanToString(stringToBoolean(op1) && stringToBoolean(op2)));
                        }
                
                        else if(strcmp(operand,"OR")==0)/* handle OR operator */
                        {
                            push(s,booleanToString(stringToBoolean(op1) || stringToBoolean(op2)));
                        }

                        else if(strcmp(operand,"NAND")==0)/* handle NAND operator */
                        {
                            push(s,booleanToString(!(stringToBoolean(op1) && stringToBoolean(op2))));
                        }

                        else if(strcmp(operand,"NOR")==0)/* handle NOR operator */
                        {
                            push(s,booleanToString(!(stringToBoolean(op1) || stringToBoolean(op2))));
                        }

                        else if(strcmp(operand,"XOR")==0)/* handle XOR operator */
                        {
                            push(s,booleanToString(stringToBoolean(op1) != stringToBoolean(op2)));
                        }

                        else if(strcmp(operand,"COND")==0)/* handle COND operator */
                        {
                            push(s,booleanToString(!stringToBoolean(op1) || stringToBoolean(op2)));
                        }

                        else if(strcmp(operand,"BICOND")==0)/* handle BICOND operator */
                        {              
                            push(s,booleanToString(stringToBoolean(op1) == stringToBoolean(op2)));
                        }
                        free(op1);
                        free(op2);
                        free(operand);
                    }
                }
            }
        }
    }     
    
    if(s->top > 0)
    {
        free(arrTokens);
        freeStackElements(s);
        freeStack(s);
        return booleanToString( ERROR ); 
    }
    else
    {
        char *answer = pop(s);
        freeStackElements(s);
        freeStack(s);
        free(arrTokens);
        return answer;
    }
}

/* TODO
 * postfixToInfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *postfixToInfix( char *str )
{
    /* Your variable Declarations: */
    Stack *s = createStack();
    int tokenCount, i, comboLen;
    char *op1;
    char *op2;
    char** arrTokens = tokenizeString( str, &tokenCount );

    for ( i = 0; i < tokenCount; i++)
    {
        char *operand = arrTokens[i];
        char *combo = (char*) malloc (sizeof(char) * 500);

        if(stringToBoolean(operand)==TRUE || stringToBoolean(operand)==FALSE)
        {
            push(s,arrTokens[i]);
        }
        
        else if(strcmp(operand, "NOT") == 0)
        {
            op1 = pop(s);
            sprintf(combo, "( %s %s )", operand, op1);
            comboLen = strlen(combo);
            combo[comboLen+1] = "\0";
            push(s, combo);
        }

        else
        {
            op2 = pop(s);
            op1 = pop(s);
            sprintf(combo, "( %s %s %s )", op1, operand, op2);
            comboLen = strlen(combo);
            combo[comboLen+1] = "\0";
            push(s, combo);    
        }
        
        /*
        free(operand);
        free(combo);
        */
    }

    free(op1);
    free(op2);
    char *res = pop(s);
    freeStackElements(s);
    freeStack(s);
    free(arrTokens);
    return res; /* NEEDS TO BE A STRING */
}


/* You may want to create some helper functions down here! */
