#include "minunit.h"
#include "../minishell.h"
// THIS CODE WAS PULLED FROM: https://github.com/siu/minunit

/*
    --> mu_check(condition): will pass if the condition is evaluated to true,
            otherwise it will show the condition as the error message
            mu_check(i == 3);
    --> mu_fail(message): will fail and show the message
            mu_fail("this fails");
    --> mu_assert(condition, message): will pass if the condition is true,
            otherwise it will show the failed condition and the message
            mu_assert(i == 3, "i should be equal to three");
    --> mu_assert_int_eq(expected, result): it will pass if the two numbers are
            equal or show their values as the error message

    --> mu_assert_double_eq(expected, result): it will pass if the two values are
            almost equal or show their values as the error message. The value of MINUNIT_EPSILON
            sets the threshold to determine if the values are close enough.
    --> mu_assert_string_eq(str1, str2): compares two strings. 

    *!* A _fail TEST EXISTS FOR MOST TESTS. EX: mu_assert_int_eq_fail(expected, result);
*/

// USE GLOBAL VARIABLES FOR TESTING.
// EACH test_UNIT.c FILE SHOULD TEST ONE THING.
//char	*
extern char **environ;
char		*trim_line_one;
char		*trim_line_two;
char		*insert_line_one;
char		*insert_line_two;
char		*insert_line_three;
char		*expand_line_one;
char		*expand_line_two;
char		*expand_line_three;
char		*expand_line_four;
char		*expand_line_five;
char		*expand_line_six;


void    test_setup_base(void)
{
    // DEFINE VARIABLES.
	setenv("ARG", "an argument", 1);
	trim_line_one = ft_strdup("echo $BOGUS | grep stuff");
	trim_line_two = ft_strdup("echo $BOGUS | grep $ARG");
	insert_line_one = ft_strdup("echo $ARG");
	insert_line_two = ft_strdup("echo $ARG | grep stuff");
	insert_line_three = ft_strdup("echo $ARG $BOGUS | grep $HELLO stuff");
}

void    test_teardown_base(void)
{
    // FREE ALLOCATED MEMORY.
	unsetenv("ARG");
	free(trim_line_one);
	free(trim_line_two);
	free(insert_line_one);
	free(insert_line_two);
	free(insert_line_three);
}

void    test_setup_expand(void)
{
    // DEFINE VARIABLES.
	setenv("ARG", "an argument", 1);
	setenv("BLA", "BLARGUMENT", 1);
	setenv("I", "i==3", 1);
	setenv("PXE", "stuff", 1);
	setenv("XEP", "$PXE", 1);
	setenv("EXP", "$XEP", 1);
	setenv("VERYLONG", "looooooong", 1);
	setenv("IVERYLONG", "l222222ng", 1);
	expand_line_one = ft_strdup("echo $I | grep $BLA > $ARG");
	expand_line_two = ft_strdup("This is $ARG | echo $ARG | chmod $BLA");
	expand_line_three = ft_strdup("$I + $ARG == - !!! $BLA");
	expand_line_four = ft_strdup("echo $I| set $BLA | unset $ARG>>hello");
	expand_line_five = ft_strdup("echo $EXP | ls $PXE");
	expand_line_six = ft_strdup("echo $I | ls $IVERYLONG");
	
}

void    test_teardown_expand(void)
{
    // FREE ALLOCATED MEMORY.
	unsetenv("ARG");
	unsetenv("BLA");
	unsetenv("I");
	unsetenv("VERYLONG");
	unsetenv("PXE");
	unsetenv("XEP");
	unsetenv("EXP");
	// free(expand_line_one); // these get freed by the expand function.
	// free(expand_line_two);
	// free(expand_line_three);
}

MU_TEST(test_get_environ_variable)
{
    // CHANGE PLACEHOLDER NAME
    // ADD ASSERT CALLS.
	mu_assert(find_environment_variable("$BOGUS", environ) == NULL, "should've returned NULL.");
	mu_assert(find_environment_variable("$ARG", environ) != NULL, "should've returned NULL.");
}

MU_TEST(test_trim_var_from_string)
{
	mu_assert_string_eq("echo  | grep stuff", trim_var_from_string(trim_line_one, "$BOGUS"));
	mu_assert_string_eq("echo  | grep $ARG", trim_var_from_string(trim_line_two, "$BOGUS"));
}

MU_TEST(test_insert_into_new_string)
{
	mu_assert_string_eq("echo an argument", insert_into_new_string(insert_line_one, getenv("ARG"), "$ARG"));
	mu_assert_string_eq("echo an argument | grep stuff", insert_into_new_string(insert_line_two, getenv("ARG"), "$ARG"));
	mu_assert_string_eq("echo an argument $BOGUS | grep $HELLO stuff", insert_into_new_string(insert_line_three, getenv("ARG"), "$ARG"));
}

MU_TEST(test_expand_variable)
{
	mu_assert_string_eq("echo i==3 | grep $BLA > $ARG", expand_variable(expand_line_one, environ, 5));
	mu_assert_string_eq("This is an argument | echo $ARG | chmod $BLA", expand_variable(expand_line_two, environ, 8));
}

MU_TEST(test_expand)
{
	mu_assert_string_eq("echo i==3 | grep BLARGUMENT > an argument", expand(expand_line_one, environ));
	mu_assert_string_eq("This is an argument | echo an argument | chmod BLARGUMENT", expand(expand_line_two, environ));
	mu_assert_string_eq("i==3 + an argument == - !!! BLARGUMENT", expand(expand_line_three, environ));
	mu_assert_string_eq("echo i==3| set BLARGUMENT | unset an argument>>hello", expand(expand_line_four, environ));
	mu_assert_string_eq("echo stuff | ls stuff", expand(expand_line_five, environ));
	mu_assert_string_eq("echo i==3 | ls l222222ng", expand(expand_line_six, environ));
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup_base, &test_teardown_base);
    MU_RUN_TEST(test_get_environ_variable);
	MU_RUN_TEST(test_trim_var_from_string);
	MU_RUN_TEST(test_insert_into_new_string);
	MU_SUITE_CONFIGURE(&test_setup_expand, &test_teardown_expand);
	MU_RUN_TEST(test_expand_variable);
	MU_RUN_TEST(test_expand);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}