/*
 * Ian Winter
 * New Beginnings
 * Problem 3
 *
 * Asks for residency status, status as a graduate/undergraduate student
 * and number of credits being taken. Calculates cost of tuition. 
 * Terminates on entering 999999 as ID# and returns number of graduates
 * and undergraduates.
 */

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define MAXCREDITS 36
#define MINCREDITS 1
#define EXIT_NUMBER 999999

/** function declarations **/
int question_num(char question[], int lower_bound, int upper_bound);
int question_yes_no(char question[]);
int tuition_cost(int credits,int is_grad,int is_resident);
void clear_buffer(void);

/** function implementations **/
/* Asks a yes/no question. Return 1 for yes and 0 for no. */
int question_yes_no(char question[])
{
    int valid_answer = FALSE;
    char response = 0; 
    int result;

    printf("%s", question);
    while (valid_answer == FALSE) {
        scanf("%c", &response);
        if (response == 'y') {
            result = TRUE; 
            valid_answer = TRUE;
        } else if (response == 'n') {
            result = FALSE;
            valid_answer = TRUE;
        } else 
            printf("Invalid option. Please enter 'y' or 'n': ");
        clear_buffer();
    }
    return result;
}

/* Asks a question expecting a number as a response. Returns number. */
int question_num(char question[], int lower_bound, int upper_bound)
{
    int valid_answer = FALSE;
    int response = 0;
    int result;

    printf("%s", question);
    while (valid_answer == FALSE) {
        scanf("%d", &response);
        clear_buffer();
        if ((lower_bound <= response) && (response <= upper_bound)) {
            valid_answer = TRUE;
            result = response;
        } else 
            printf("Invalid response. Try again: ");
    }
    return result;
}

/* Calculates tuition from number of credits, graduate status and residency */
int tuition_cost(int is_resident, int is_grad, int credits)
{
    int tuition;

    if (is_resident == TRUE && is_grad == TRUE) {
        if (credits < 13)
            tuition = 368 * credits;
        else
            tuition = 4416 + (credits - 12) * 234;
    } else if (is_resident == TRUE && is_grad == FALSE) {
        tuition = 156 * credits;
    } else if (is_resident == FALSE && is_grad == TRUE) {
        if (credits < 13)
            tuition = 576 * credits;
        else
            tuition = 6912 + (credits - 12) * 547;
    } else if (is_resident == FALSE && is_grad == FALSE)
            tuition = 523 * credits;
    return tuition;
}

/* so scanf will behave */
void clear_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    int id, grad, resident, num_credits, final_tuition;
    int num_grads, num_undergrads;
    num_grads = num_undergrads = 0;

    while (TRUE) {
        id = question_num("Enter your 6-digit ID number: ", 100000, 999999);
        if (id == EXIT_NUMBER)
            break;
        resident = question_yes_no("Are you a resident? (y/n) ");
        grad = question_yes_no("Are you a graduate student? (y/n) ");
        if (grad == TRUE)
            ++num_grads;
        else
            ++num_undergrads;
        num_credits = question_num("How many credits are you taking? ",
                                    MINCREDITS, MAXCREDITS);
        final_tuition = tuition_cost(resident, grad, num_credits);
        printf("Tuition: %d\n", final_tuition);
    }
    printf("Number of undergrad students: %d\n", num_undergrads);
    printf("Number of grad students: %d\n", num_grads);
    return 0;
}
