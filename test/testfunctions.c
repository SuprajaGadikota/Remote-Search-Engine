#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <CUnit/CUnit.h> // CU_ASSERT

#include <utility.h>

// UT
void DIR_test1(void)
{
	// positive testcase
	char path[] = "/home/supraja/Documents/";
	DIR *dir = opendir(path);
	CU_ASSERT(dir != NULL)
	printf("\nPath: %s, opened successfull\n", path);
}

void DIR_test2(void)
{
	// negative test pass
	char path[] = "/home/supaj/";
	DIR *dir = opendir(path);
	CU_ASSERT(dir == NULL)
	printf("\nPath Cannot open %s,test case passed", path);
}

void DIR_test3(void)
{
	// positive testcase
	char path[] = "/home/supraja/Desktop/RSE/";
	DIR *dir = opendir(path);
	CU_ASSERT(dir == NULL)
	printf("\nPath: %s, opened successfull\n", path);
}

void FILE_test1(void)
{
	// positive testcase
	char file_name[] = "/home/supraja/Documents/LSI.py";
	FILE *fp = fopen(file_name, "r");
	CU_ASSERT(fp != NULL)
	printf("\nFile %s, opened successfully\n", file_name);
}

void FILE_test2(void)
{
	// negative testcase
	char file_name[] = "/home/supraja/Documents/abc.py";
	FILE *fp = fopen(file_name, "r");
	CU_ASSERT(fp == NULL)
	printf("\nFile %s, cannot open \n", file_name);
}

void FILE_test3(void)
{
	// negative testcase
	char file_name[] = "/home/supraja/Desktop/RSE/server.c";
	FILE *fp = fopen(file_name, "r");
	CU_ASSERT(fp == NULL)
	printf("\nFile %s, cannot open \n", file_name);
}

// IT
// Test cases for serch_word_in_file()
void IT2_test1(void)
{
	char filename[] = "/home/supraja/Documents/LSI.py";
	char search[] = "print";
	CU_ASSERT(SUCCESS == search_word_in_file(filename, search))
	printf("\nWord found! Test Case Passed\n");
}

void IT2_test2(void)
{
	char filename[] = "/home/supraja/Documents/LSI.py";
	char search[] = "minimum";
	CU_ASSERT(SUCCESS == search_word_in_file(filename, search))
	printf("\nWord found! Test Case Passed\n");
}

void IT2_test3(void)
{
	char filename[] = "/home/supraja/Documents/LSI.py";
	char search[] = "Boink";
	CU_ASSERT(FAILURE == search_word_in_file(filename, search))
	printf("\nWord o file Not found! Test Case Passed\n");
}

void IT2_test4(void)
{
	char filename[] = "/home/supraja/Documents/sample.txt";
	char search[] = "members";
	CU_ASSERT(FAILURE == search_word_in_file(filename, search))
	printf("\nWord or file not found! Test Case Passed\n");
}

void IT2_test5(void)
{
	char filename[] = "/home/supraja/Documents/RSE/src/client.c";
	char search[] = "garbage";
	CU_ASSERT(FAILURE == search_word_in_file(filename, search))
	printf("\nWord or file not found! Test Case Passed\n");
}
// End of Test cases for serch_word_in_file()

////Test cases for findSize()
void IT3_test1(void)
{
	// positive testcase
	char path[] = "/home/supraja/Documents/sample.txt";
	CU_ASSERT(findSize(path) == 51)
	printf("\ntest case passed\n");
}

void IT3_test2(void)
{
	// negative test pass
	char path[] = "/home/supraja/Documents/LSI.py";
	CU_ASSERT(findSize(path) != 1060)
	printf("\nTest case passed\n");
}

void IT3_test3(void)
{
	// positive testcase
	char path[] = "/home/supraja/Documents/sample.txt";
	CU_ASSERT(findSize(path) == 51)
	printf("\ntest case passed\n");
}

void IT3_test4(void)
{
	// positive test pass
	char path[] = "/home/supraja/Documents/RSE/src/server_functions.c";
	CU_ASSERT(findSize(path) == 4134)
	printf("\ntest case passed\n");
}

void IT3_test5(void)
{
	// positive test pass
	char path[] = "/home/supraja/Documents/RSE/src/client_functions.c";
	CU_ASSERT(findSize(path) != 1092)
	printf("\ntest case passed\n");
}
// end of Test cases for findSize()

// Test cases for read_contents()
void IT4_test1(void)
{
	// positive testcase
	char path[] = "/home/supraja/Documents/sample.txt";
	char buf[MAX];
	CU_ASSERT(sizeof(read_contents(path, buf)) > 0)
	printf("\ntest case passed\n");
}

void IT4_test2(void)
{
	// negative test pass
	char path[] = "/home/supraja/Documents/LSI.py";
	char buf[MAX];
	CU_ASSERT(sizeof(read_contents(path, buf)) > 0)
	printf("\nTest case passed\n");
}

void IT4_test3(void)
{
	// positive testcase
	char path[] = "/home/supraja/Documents/sample.txt";
	char buf[MAX];
	CU_ASSERT(sizeof(read_contents(path, buf)) > 0)
	printf("\ntest case passed\n");
}
// end of test cases for read_contents()

//Test case for list_file_recursively()
void IT5_test1(void){
	int fd = open("files.txt",O_CREAT|O_RDWR);
	char dir_path[]="/home/supraja/Documents/";
	char string[]="Hello";
	CU_ASSERT(SUCCESS==list_files_recursively(fd,dir_path,string))
	printf("\n Function passed\n");
}

void IT5_test2(void){
	int fd = open("files.txt",O_CREAT|O_RDWR);
	char dir_path[]="/home/supraja/Documents/";
	char string[]="print";
	CU_ASSERT(SUCCESS==list_files_recursively(fd,dir_path,string))
	printf("\n Function passed\n");
}

void IT5_test3(void){
	int fd = open("files.txt",O_CREAT|O_RDWR);
	char dir_path[]="/home/supraja/Desktop/";
	char string[]="hi";
	CU_ASSERT(FAILURE!=list_files_recursively(fd,dir_path,string))
	printf("\n Function passed\n");
}
//end of test cases for list_file_recursively()