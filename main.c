//
//  main.c
//  7.8 prog 2 tic tac win
//
//  Created by Ryan Roderick on 8/29/20.
//  Copyright © 2020 Ryan Roderick. All rights reserved.
//

/*
 * From Hanley and Koffman's "Problem Solving
 * and Program Design in C", 7th Ed.
 * Chapter 7, section 9, Programming question #2:
 *
 * Write a function that determines who has won
 * a game of tic-tac-toe. The function should first
 * check all rows to see whether one player occupies
 * all the cells in one row, next check all columns,
 * and then check the two diagonals.  The function
 * should return a value from the enumerated type
 * {no_winner, x_wins, o_wins}.
 */

/*
 * The hardest thing to figure
 * out was how to stop the inner 'for'
 * loop after it checked the first row.
 *
 * I added the curly braces
 * after the first 'for' loop, then
 * added the 'results' function after
 * the inner loop exited to check a
 * winner after tallying that row.
 */

#include <stdio.h>



typedef enum {no_winner, x_wins, o_wins}
    winner;



int check_boxes(char[][3], int *x, int *o);

void tally(char, int*, int*);
int results(int*, int*);
void announce(int);



int main(int argc, const char * argv[])
{
    int winner = 0, xes = 0, ohs = 0;
    
    char tictac[3][3] =
    {   {'x', 'x', 'o'},
        {'x', 'o', 'o'},
        {'o', 'x', 'x'} };

    winner =
    check_boxes(tictac, &xes, &ohs);
    /*
     * Sends back winner in
     * enumerated type
     */

    /*
     * The '&'s pull the address of the
     * variables that I declared in THIS
     * function, main.
     */

    announce(winner);
}



int check_boxes(char matrix[][3], int *x, int *o)
/*
 * 'x' and 'o' have the address of 'xes'
 * and 'ohs' because their place order
 * in the funciton call,
 * check_boxes(tictac, &xes, &ohs) above,
 * wworks the same way an assignment
 * operator does,'=', making them pointers
 * to the integers 'xes' and 'ohs'.
 *
 * The second job done in the function
 * call/assignment statement is that the
 * uniary indirection operator, '*',
 * causes the addresses in 'x' and 'o'
 * to point to the VALUES in the cells
 * for 'xes' and'ohs' in the main.
 */
{
    int row, col, winner = 0;
    
    char answer;
    
    /* check rows */
    for (row = 0; row < 3; ++row) {
        for (col = 0; col < 3; ++col) {
            answer = matrix[row][col];
            
            tally(answer, x, o);
            /* Here, we're sending the addresses
             * in the pointer variables 'x' and 'o'
             * to the function below, where the '*'
             * uniary indirection operator used
             * throughout the function causes those
             * addresses to point to and manipulate
             * the variables 'xes' and 'ohs' in the
             * main.
             */
            
        }
        printf("exit inner row loop\n");
        
        winner = results(x, o);
                                            
        if (winner == x_wins || winner == o_wins)
            return(winner);
        /*
         * The 'if' statement allows me to
         * stop the program if we have a
         * winner from that row.  If not
         * we go on to the next row.
         */
    }
                                                    
    /* check columns */
    for (col = 0; col < 3; ++col) {
        for (row = 0; row < 3; ++row) {
            answer = matrix[row][col];
            
            tally(answer, x, o);
        }
        printf("exit inner column loop\n");
        winner = results(x, o);
        /*
         * Trace statements like the 'printf'
         * one above help me know whether or not
         * I'm getting the results I'm expecting.
         * I use them throughout the program.
         */
        
        if (winner == x_wins || winner == o_wins)
            return(winner);
    }
    
    /* check diagonals */
    if (matrix[1][1] == 'x') {
        if (matrix[0][0] == 'x')
            if (matrix[2][2] == 'x') {
                winner = x_wins;
                printf("x right wins\n");
                return(winner);
            }
        if (matrix[0][2] == 'x')
            if (matrix[2][0] == 'x') {
                winner = x_wins;
                printf("x left wins\n");
                return(winner);
            }
    }
    printf("exit diagonal check for x\n");
    
    if (matrix[1][1] == 'o') {
        if (matrix[0][0] == 'o')
            if (matrix[2][2] == 'o') {
                winner = o_wins;
                printf("o right wins\n");
                return(winner);
            }
        if (matrix[0][2] == 'o')
            if (matrix[2][0] == 'o') {
                winner = o_wins;
                printf("o left wins\n");
                return(winner);
            }
    }
    printf("exit diagonal check for o\n");

    return(winner);
}



void tally(char answer, int *x, int *o)
{
    printf("answer = %c\n", answer);
    switch(answer) {
        case 'x':
            *x = *x + 1;
            printf("*x = %d\n", *x);
            break;
                    
        case 'o':
            *o = *o + 1;
            printf("*o = %d\n", *o);
            break;
            
        default:
            printf("Missed that one!\n");
            /*
             * If anything other than 'x' or 'o'
             * is in the matrix, the program skips
             * it here.
             */
    }
}
    


int results(int *x, int *o)
{
    int winner = 0;

    if (*x == 3) {
       winner = x_wins;
    }
    if (*o == 3) {
       winner = o_wins;
    }
    /* resets *x and *o to zero if
     * no one won in a row or column */
    if (*x + *o == 3) {
       *x = 0;
       *o = 0;
    } else
       winner = no_winner;
    
    return(winner);
}



void announce(int winner)
{
    if(winner == x_wins)
        printf("Xes win.\n\n");
    
    if(winner == o_wins)
        printf("Ohs win.\n\n");
    
    if(winner == no_winner)
        printf("There is no winner.\n\n");
 }
