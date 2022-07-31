/******************************************************************************
 * File Name:test.c
 * Purpose: Main function to call the CUNIT Framework
 *******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include <utility.h>
#include <testfunctions.h>

/******************************************************************************
 Function     : init_rse
 Description  : Initializes the suite
 Input        : Nothing
 Output       : int
***************************************************************************/
int init_rse(void)
{
    return 0;
}

/******************************************************************************
 Function     : clean_rse
 Description  : clean the suite after successful run
 Input        : Nothing
 Output       : int
***************************************************************************/
int clean_rse(void)
{
    return 0;
}

/*************************************************************************************
 Function     : main
 Description  :This is the main function to test backend server_functions.c
 Input        : None
 Output       : Int
************************************************************************************/
int main(int argc, char *argv[])
{
    CU_pSuite pSuite = NULL;

    /* Register  */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add init and cleanup handlers */
    pSuite = CU_add_suite("RSE DIR SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add test case */
    if (NULL == CU_add_test(pSuite, "RSE_DIR_TEST_1", DIR_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_DIR_TEST_2", DIR_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_DIR_TEST_2", DIR_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("RSE FILE SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FILE_TEST_1", FILE_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FILE_TEST_2", FILE_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FILE_TEST_2", FILE_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("RSE WORD SEARCH SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "RSE_WORD_SEARCH_TEST_1", IT2_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_WORD_SEARCH_TEST_2", IT2_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_WORD_SEARCH_TEST_3", IT2_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_WORD_SEARCH_TEST_4", IT2_test4))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_WORD_SEARCH_TEST_5", IT2_test5))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("RSE FIND SIZE SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "RSE_FIND_SIZE_TEST_1", IT3_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FIND_SIZE_TEST_2", IT3_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FIND_SIZE_TEST_3", IT3_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FIND_SIZE_TEST_4", IT3_test4))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_FIND_SIZE_TEST_5", IT3_test5))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("RSE READ CONTENTS SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "RSE_READ_CONTENTS_TEST_1", IT4_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_READ_CONTENTS_TEST_2", IT4_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_READ_CONTENTS_TEST_3", IT4_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("RSE LIST RECCURSIVE SUITE", init_rse, clean_rse);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "RSE_LIST_RECURSIVE_TEST_1", IT5_test1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_LIST_RECURSIVE_TEST_2", IT5_test2))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "RSE_LIST_RECURSIVE_TEST_3", IT5_test3))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Set the mode and  invoke test(s) */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* unregister and do cleanup */
    CU_cleanup_registry();

    return CU_get_error();
}
