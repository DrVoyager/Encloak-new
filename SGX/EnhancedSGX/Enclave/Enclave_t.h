#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "user_types.h"
#include "hot_calls.h"
#include "common.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void encall_switch_type_get_i(void* data, void* rei, int* int_array, int intTail, double* double_array, int doubleTail, float* float_array, int floatTail, char* char_array, int charTail, long int* long_array, int longTail, char* byte_array, int byteTail, char* uuid, char* ouuid, char* cuuid);
void encall_switch_type_branch(void* data, void* rei, int* int_array, int intTail, double* double_array, int doubleTail, float* float_array, int floatTail, char* char_array, int charTail, long int* long_array, int longTail, char* byte_array, int byteTail, char* uuid, char* ouuid, char* cuuid);
void encall_switch_type_update(void* data, void* rei, int* int_array, int intTail, double* double_array, int doubleTail, float* float_array, int floatTail, char* char_array, int charTail, long int* long_array, int longTail, char* byte_array, int byteTail, char* uuid, char* ouuid, char* cuuid);
int print_int(long int line, int* int_array, char* uuid, char* ouuid, char* cuuid);
long int print_long(long int line, long int* long_array, int* int_array, char* uuid, char* ouuid, char* cuuid);
double print_double(long int line, double* double_array, int* int_array, char* uuid, char* ouuid, char* cuuid);
float print_float(long int line, float* float_array, char* uuid, char* ouuid, char* cuuid);
int print_char(long int line, char* char_array, char* uuid, char* ouuid, char* cuuid);
int print_byte(long int line, char* byte_array, int* int_array, char* uuid, char* ouuid, char* cuuid);
int print_array_i(long int line, int* int_array, int int_tail, char* uuid, char* ouuid, char* cuuid);
int print_array_d(long int line, double* double_array, int double_tail, char* uuid, char* ouuid, char* cuuid);
int encall_table_load();
int encall_hash_readin(char* buf, long int line);
int encall_read_line(char* in_buf, int buf_len, long int line, int isIndex);
void encall_varible(void* data, char* uuid, char* calluuid);
void encall_deleteValue(void* data, char* uuid, char* cuuid);
void encall_initArray(char* uuid, int index, int size, int isSens);
void encall_initNode(char* uuid, int type, int size);
int encall_getArraySize(long int line, char* uuid);
void EcallStartResponder(HotCall* fastEcall);
void EcallStartResponder3(HotCall* fastEcall);

sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_print_int(int str);
sgx_status_t SGX_CDECL ocall_print_long(long int str);
sgx_status_t SGX_CDECL ocall_file_write(char* file, char* buf, int len);
sgx_status_t SGX_CDECL ocall_file_add(char* file, char* buf, int len);
sgx_status_t SGX_CDECL ocall_file_read(char* file, int* buf, long int* start);
sgx_status_t SGX_CDECL ocall_file_getline(char* file, char* buf, long int* line_num);
sgx_status_t SGX_CDECL ocall_open(int* retval, const char* filename, int flags, mode_t mode);
sgx_status_t SGX_CDECL ocall_fallocate(int* retval, int fd, int mode, off_t offset, off_t len);
sgx_status_t SGX_CDECL ocall_fcntl_flock(int* retval, int fd, int cmd, struct flock* p);
sgx_status_t SGX_CDECL ocall_fcntl_int(int* retval, int fd, int cmd, int pa);
sgx_status_t SGX_CDECL ocall_fcntl_void(int* retval, int fd, int cmd);
sgx_status_t SGX_CDECL ocall_getenv(char** retval, const char* name);
sgx_status_t SGX_CDECL ocall_stat(int* retval, const char* pathname, struct stat* buf);
sgx_status_t SGX_CDECL ocall_fstat(int* retval, int fd, struct stat* buf);
sgx_status_t SGX_CDECL ocall_fchmod(int* retval, int fd, unsigned int mode);
sgx_status_t SGX_CDECL ocall_mkdir(int* retval, const char* pathname, mode_t mode);
sgx_status_t SGX_CDECL ocall_time(time_t* retval, time_t* t);
sgx_status_t SGX_CDECL ocall_utimes(int* retval, const char* filename, const struct timeval* times);
sgx_status_t SGX_CDECL ocall_gettimeofday(int* retval, struct timeval* tv);
sgx_status_t SGX_CDECL ocall_read(ssize_t* retval, int file, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write(ssize_t* retval, int file, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_close(int* retval, int fd);
sgx_status_t SGX_CDECL ocall_fchown(int* retval, int fd, uid_t owner, gid_t group);
sgx_status_t SGX_CDECL ocall_getcwd(char** retval, char* buf, size_t size);
sgx_status_t SGX_CDECL ocall_truncate(int* retval, const char* path, off_t length);
sgx_status_t SGX_CDECL ocall_ftruncate(int* retval, int fd, off_t length);
sgx_status_t SGX_CDECL ocall_pread(ssize_t* retval, int fd, void* buf, size_t count, off_t offset);
sgx_status_t SGX_CDECL ocall_pwrite(ssize_t* retval, int fd, const void* buf, size_t count, off_t offset);
sgx_status_t SGX_CDECL ocall_access(int* retval, const char* pathname, int mode);
sgx_status_t SGX_CDECL ocall_unlink(int* retval, const char* pathname);
sgx_status_t SGX_CDECL ocall_rmdir(int* retval, const char* pathname);
sgx_status_t SGX_CDECL ocall_geteuid(uid_t* retval);
sgx_status_t SGX_CDECL ocall_lseek(off_t* retval, int fd, off_t offset, int whence);
sgx_status_t SGX_CDECL ocall_fsync(int* retval, int fd);
sgx_status_t SGX_CDECL ocall_getpid(pid_t* retval);
sgx_status_t SGX_CDECL ocall_sleep(unsigned int* retval, unsigned int seconds);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
