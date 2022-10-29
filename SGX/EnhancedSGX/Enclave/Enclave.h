#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#include <stdlib.h>
#include <assert.h>

#if defined(__cplusplus)
extern "C" {
#endif
	typedef struct IntArrayNode{
	int d;
	int dimensions[5];
	int index[5];
	int location;
	int oriLocation;
	int *data;
	int sz=0;
	int paramLoc;
}*INODE,IntArrayNode;
typedef struct DoubleArrayNode{
	int d;
	int dimensions[5];
	int index[5];
	int location;
	int oriLocation;
	double *data;
	int sz=0;
	int paramLoc;
}*DNODE,DoubleArrayNode;
typedef struct CharArrayNode{
	int d;
	int dimensions[5];
	int index[5];
	int location;
	int oriLocation;
	char *data;
	int sz=0;
	int paramLoc;
}*CNODE,CharArrayNode;


void encall_switch_type_update2(void* data,void* rei,int* int_array,int int_tail,double* double_array,int double_tail,float* float_array,int float_tail,char* char_array,int char_tail,long* long_array, int long_tail,char* byte_array, int byte_tail,char* uuid,char* cuuid) ;
int print_int(long line,int* int_array,char* uuid,char* cuuid);
int print_int2(long line,int* int_array,char* uuid,char* cuuid);
double print_double(long line,double* double_array,int* int_array,char* uuid,char* cuuid);
float print_float(long line,float* float_array,char* uuid);
int print_char(long line,char* char_array,char* uuid);
long print_long(long line,long* long_array,int* int_array,char* uuid,char* cuuid);
int print_byte(long line,char* byte_array,int* int_array,char* uuid);

int print_array_i(long line,int* int_array,int int_tail,char* uuid,char* cuuid); 
int print_array_d(long line,double* double_array,int double_tail,char* uuid,char* cuuid); 
int print_array_c(long line,char* char_array,int char_tail,char* uuid,char* cuuid); 
int encall_table_load();
//int encall_invoketable_load();
int encall_hash_readin(char* buf,long line);
int encall_read_line(char* in_buf,int buf_len,long line,int isIndex);
int calIntArrayIndex(INODE node);

//void encall_varible(int* v_array,char* uuid);
//int encall_deleteValue(char* uuid);
/*int encall_switch_type_i(long Line,int* int_array,
			double* double_array,
			float* float_array,
			char* char_array,
			long* long_array,
			char* byte_array,
			char* uuid);
*/
/*double encall_switch_type_d(long Line, int* int_array, int lenint, [user_check]void* data, [user_check]void* rei,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
float encall_switch_type_f(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
char encall_switch_type_c(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
long encall_switch_type_l(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
char encall_switch_type_c(long Line, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong,
			char* byte_array, int lenbyte);
*/
#if defined(__cplusplus)
}
#endif

#endif /* !_ENCLAVE_H_ */
