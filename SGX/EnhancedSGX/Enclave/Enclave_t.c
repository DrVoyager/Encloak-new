#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


typedef struct ms_encall_switch_type_get_i_t {
	void* ms_data;
	void* ms_rei;
	int* ms_int_array;
	int ms_intTail;
	double* ms_double_array;
	int ms_doubleTail;
	float* ms_float_array;
	int ms_floatTail;
	char* ms_char_array;
	int ms_charTail;
	long int* ms_long_array;
	int ms_longTail;
	char* ms_byte_array;
	int ms_byteTail;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_encall_switch_type_get_i_t;

typedef struct ms_encall_switch_type_branch_t {
	void* ms_data;
	void* ms_rei;
	int* ms_int_array;
	int ms_intTail;
	double* ms_double_array;
	int ms_doubleTail;
	float* ms_float_array;
	int ms_floatTail;
	char* ms_char_array;
	int ms_charTail;
	long int* ms_long_array;
	int ms_longTail;
	char* ms_byte_array;
	int ms_byteTail;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_encall_switch_type_branch_t;

typedef struct ms_encall_switch_type_update_t {
	void* ms_data;
	void* ms_rei;
	int* ms_int_array;
	int ms_intTail;
	double* ms_double_array;
	int ms_doubleTail;
	float* ms_float_array;
	int ms_floatTail;
	char* ms_char_array;
	int ms_charTail;
	long int* ms_long_array;
	int ms_longTail;
	char* ms_byte_array;
	int ms_byteTail;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_encall_switch_type_update_t;

typedef struct ms_print_int_t {
	int ms_retval;
	long int ms_line;
	int* ms_int_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_int_t;

typedef struct ms_print_long_t {
	long int ms_retval;
	long int ms_line;
	long int* ms_long_array;
	int* ms_int_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_long_t;

typedef struct ms_print_double_t {
	double ms_retval;
	long int ms_line;
	double* ms_double_array;
	int* ms_int_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_double_t;

typedef struct ms_print_float_t {
	float ms_retval;
	long int ms_line;
	float* ms_float_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_float_t;

typedef struct ms_print_char_t {
	int ms_retval;
	long int ms_line;
	char* ms_char_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_char_t;

typedef struct ms_print_byte_t {
	int ms_retval;
	long int ms_line;
	char* ms_byte_array;
	int* ms_int_array;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_byte_t;

typedef struct ms_print_array_i_t {
	int ms_retval;
	long int ms_line;
	int* ms_int_array;
	int ms_int_tail;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_array_i_t;

typedef struct ms_print_array_d_t {
	int ms_retval;
	long int ms_line;
	double* ms_double_array;
	int ms_double_tail;
	char* ms_uuid;
	char* ms_ouuid;
	char* ms_cuuid;
} ms_print_array_d_t;

typedef struct ms_encall_table_load_t {
	int ms_retval;
} ms_encall_table_load_t;

typedef struct ms_encall_hash_readin_t {
	int ms_retval;
	char* ms_buf;
	long int ms_line;
} ms_encall_hash_readin_t;

typedef struct ms_encall_read_line_t {
	int ms_retval;
	char* ms_in_buf;
	int ms_buf_len;
	long int ms_line;
	int ms_isIndex;
} ms_encall_read_line_t;

typedef struct ms_encall_varible_t {
	void* ms_data;
	char* ms_uuid;
	char* ms_calluuid;
} ms_encall_varible_t;

typedef struct ms_encall_deleteValue_t {
	void* ms_data;
	char* ms_uuid;
	char* ms_cuuid;
} ms_encall_deleteValue_t;

typedef struct ms_encall_initArray_t {
	char* ms_uuid;
	int ms_index;
	int ms_size;
	int ms_isSens;
} ms_encall_initArray_t;

typedef struct ms_encall_initNode_t {
	char* ms_uuid;
	int ms_type;
	int ms_size;
} ms_encall_initNode_t;

typedef struct ms_encall_getArraySize_t {
	int ms_retval;
	long int ms_line;
	char* ms_uuid;
} ms_encall_getArraySize_t;

typedef struct ms_EcallStartResponder_t {
	HotCall* ms_fastEcall;
} ms_EcallStartResponder_t;

typedef struct ms_EcallStartResponder3_t {
	HotCall* ms_fastEcall;
} ms_EcallStartResponder3_t;

typedef struct ms_ocall_print_string_t {
	char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_print_int_t {
	int ms_str;
} ms_ocall_print_int_t;

typedef struct ms_ocall_print_long_t {
	long int ms_str;
} ms_ocall_print_long_t;

typedef struct ms_ocall_file_write_t {
	char* ms_file;
	char* ms_buf;
	int ms_len;
} ms_ocall_file_write_t;

typedef struct ms_ocall_file_add_t {
	char* ms_file;
	char* ms_buf;
	int ms_len;
} ms_ocall_file_add_t;

typedef struct ms_ocall_file_read_t {
	char* ms_file;
	int* ms_buf;
	long int* ms_start;
} ms_ocall_file_read_t;

typedef struct ms_ocall_file_getline_t {
	char* ms_file;
	char* ms_buf;
	long int* ms_line_num;
} ms_ocall_file_getline_t;

typedef struct ms_ocall_open_t {
	int ms_retval;
	char* ms_filename;
	int ms_flags;
	mode_t ms_mode;
} ms_ocall_open_t;

typedef struct ms_ocall_fallocate_t {
	int ms_retval;
	int ms_fd;
	int ms_mode;
	off_t ms_offset;
	off_t ms_len;
} ms_ocall_fallocate_t;

typedef struct ms_ocall_fcntl_flock_t {
	int ms_retval;
	int ms_fd;
	int ms_cmd;
	struct flock* ms_p;
} ms_ocall_fcntl_flock_t;

typedef struct ms_ocall_fcntl_int_t {
	int ms_retval;
	int ms_fd;
	int ms_cmd;
	int ms_pa;
} ms_ocall_fcntl_int_t;

typedef struct ms_ocall_fcntl_void_t {
	int ms_retval;
	int ms_fd;
	int ms_cmd;
} ms_ocall_fcntl_void_t;

typedef struct ms_ocall_getenv_t {
	char* ms_retval;
	char* ms_name;
} ms_ocall_getenv_t;

typedef struct ms_ocall_stat_t {
	int ms_retval;
	char* ms_pathname;
	struct stat* ms_buf;
} ms_ocall_stat_t;

typedef struct ms_ocall_fstat_t {
	int ms_retval;
	int ms_fd;
	struct stat* ms_buf;
} ms_ocall_fstat_t;

typedef struct ms_ocall_fchmod_t {
	int ms_retval;
	int ms_fd;
	unsigned int ms_mode;
} ms_ocall_fchmod_t;

typedef struct ms_ocall_mkdir_t {
	int ms_retval;
	char* ms_pathname;
	mode_t ms_mode;
} ms_ocall_mkdir_t;

typedef struct ms_ocall_time_t {
	time_t ms_retval;
	time_t* ms_t;
} ms_ocall_time_t;

typedef struct ms_ocall_utimes_t {
	int ms_retval;
	char* ms_filename;
	struct timeval* ms_times;
} ms_ocall_utimes_t;

typedef struct ms_ocall_gettimeofday_t {
	int ms_retval;
	struct timeval* ms_tv;
} ms_ocall_gettimeofday_t;

typedef struct ms_ocall_read_t {
	ssize_t ms_retval;
	int ms_file;
	void* ms_buf;
	size_t ms_count;
} ms_ocall_read_t;

typedef struct ms_ocall_write_t {
	ssize_t ms_retval;
	int ms_file;
	void* ms_buf;
	size_t ms_count;
} ms_ocall_write_t;

typedef struct ms_ocall_close_t {
	int ms_retval;
	int ms_fd;
} ms_ocall_close_t;

typedef struct ms_ocall_fchown_t {
	int ms_retval;
	int ms_fd;
	uid_t ms_owner;
	gid_t ms_group;
} ms_ocall_fchown_t;

typedef struct ms_ocall_getcwd_t {
	char* ms_retval;
	char* ms_buf;
	size_t ms_size;
} ms_ocall_getcwd_t;

typedef struct ms_ocall_truncate_t {
	int ms_retval;
	char* ms_path;
	off_t ms_length;
} ms_ocall_truncate_t;

typedef struct ms_ocall_ftruncate_t {
	int ms_retval;
	int ms_fd;
	off_t ms_length;
} ms_ocall_ftruncate_t;

typedef struct ms_ocall_pread_t {
	ssize_t ms_retval;
	int ms_fd;
	void* ms_buf;
	size_t ms_count;
	off_t ms_offset;
} ms_ocall_pread_t;

typedef struct ms_ocall_pwrite_t {
	ssize_t ms_retval;
	int ms_fd;
	void* ms_buf;
	size_t ms_count;
	off_t ms_offset;
} ms_ocall_pwrite_t;

typedef struct ms_ocall_access_t {
	int ms_retval;
	char* ms_pathname;
	int ms_mode;
} ms_ocall_access_t;

typedef struct ms_ocall_unlink_t {
	int ms_retval;
	char* ms_pathname;
} ms_ocall_unlink_t;

typedef struct ms_ocall_rmdir_t {
	int ms_retval;
	char* ms_pathname;
} ms_ocall_rmdir_t;

typedef struct ms_ocall_geteuid_t {
	uid_t ms_retval;
} ms_ocall_geteuid_t;

typedef struct ms_ocall_lseek_t {
	off_t ms_retval;
	int ms_fd;
	off_t ms_offset;
	int ms_whence;
} ms_ocall_lseek_t;

typedef struct ms_ocall_fsync_t {
	int ms_retval;
	int ms_fd;
} ms_ocall_fsync_t;

typedef struct ms_ocall_getpid_t {
	pid_t ms_retval;
} ms_ocall_getpid_t;

typedef struct ms_ocall_sleep_t {
	unsigned int ms_retval;
	unsigned int ms_seconds;
} ms_ocall_sleep_t;

static sgx_status_t SGX_CDECL sgx_encall_switch_type_get_i(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_switch_type_get_i_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_switch_type_get_i_t* ms = SGX_CAST(ms_encall_switch_type_get_i_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_data = ms->ms_data;
	void* _tmp_rei = ms->ms_rei;
	int* _tmp_int_array = ms->ms_int_array;
	double* _tmp_double_array = ms->ms_double_array;
	float* _tmp_float_array = ms->ms_float_array;
	char* _tmp_char_array = ms->ms_char_array;
	long int* _tmp_long_array = ms->ms_long_array;
	char* _tmp_byte_array = ms->ms_byte_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	encall_switch_type_get_i(_tmp_data, _tmp_rei, _tmp_int_array, ms->ms_intTail, _tmp_double_array, ms->ms_doubleTail, _tmp_float_array, ms->ms_floatTail, _tmp_char_array, ms->ms_charTail, _tmp_long_array, ms->ms_longTail, _tmp_byte_array, ms->ms_byteTail, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_switch_type_branch(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_switch_type_branch_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_switch_type_branch_t* ms = SGX_CAST(ms_encall_switch_type_branch_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_data = ms->ms_data;
	void* _tmp_rei = ms->ms_rei;
	int* _tmp_int_array = ms->ms_int_array;
	double* _tmp_double_array = ms->ms_double_array;
	float* _tmp_float_array = ms->ms_float_array;
	char* _tmp_char_array = ms->ms_char_array;
	long int* _tmp_long_array = ms->ms_long_array;
	char* _tmp_byte_array = ms->ms_byte_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	encall_switch_type_branch(_tmp_data, _tmp_rei, _tmp_int_array, ms->ms_intTail, _tmp_double_array, ms->ms_doubleTail, _tmp_float_array, ms->ms_floatTail, _tmp_char_array, ms->ms_charTail, _tmp_long_array, ms->ms_longTail, _tmp_byte_array, ms->ms_byteTail, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_switch_type_update(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_switch_type_update_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_switch_type_update_t* ms = SGX_CAST(ms_encall_switch_type_update_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_data = ms->ms_data;
	void* _tmp_rei = ms->ms_rei;
	int* _tmp_int_array = ms->ms_int_array;
	double* _tmp_double_array = ms->ms_double_array;
	float* _tmp_float_array = ms->ms_float_array;
	char* _tmp_char_array = ms->ms_char_array;
	long int* _tmp_long_array = ms->ms_long_array;
	char* _tmp_byte_array = ms->ms_byte_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	encall_switch_type_update(_tmp_data, _tmp_rei, _tmp_int_array, ms->ms_intTail, _tmp_double_array, ms->ms_doubleTail, _tmp_float_array, ms->ms_floatTail, _tmp_char_array, ms->ms_charTail, _tmp_long_array, ms->ms_longTail, _tmp_byte_array, ms->ms_byteTail, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_int(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_int_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_int_t* ms = SGX_CAST(ms_print_int_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_int_array = ms->ms_int_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_int(ms->ms_line, _tmp_int_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_long(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_long_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_long_t* ms = SGX_CAST(ms_print_long_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	long int* _tmp_long_array = ms->ms_long_array;
	int* _tmp_int_array = ms->ms_int_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_long(ms->ms_line, _tmp_long_array, _tmp_int_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_double(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_double_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_double_t* ms = SGX_CAST(ms_print_double_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	double* _tmp_double_array = ms->ms_double_array;
	int* _tmp_int_array = ms->ms_int_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_double(ms->ms_line, _tmp_double_array, _tmp_int_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_float(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_float_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_float_t* ms = SGX_CAST(ms_print_float_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	float* _tmp_float_array = ms->ms_float_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_float(ms->ms_line, _tmp_float_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_char(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_char_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_char_t* ms = SGX_CAST(ms_print_char_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_char_array = ms->ms_char_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_char(ms->ms_line, _tmp_char_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_byte(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_byte_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_byte_t* ms = SGX_CAST(ms_print_byte_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_byte_array = ms->ms_byte_array;
	int* _tmp_int_array = ms->ms_int_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_byte(ms->ms_line, _tmp_byte_array, _tmp_int_array, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_array_i(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_array_i_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_array_i_t* ms = SGX_CAST(ms_print_array_i_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_int_array = ms->ms_int_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_array_i(ms->ms_line, _tmp_int_array, ms->ms_int_tail, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_print_array_d(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_print_array_d_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_print_array_d_t* ms = SGX_CAST(ms_print_array_d_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	double* _tmp_double_array = ms->ms_double_array;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_ouuid = ms->ms_ouuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	ms->ms_retval = print_array_d(ms->ms_line, _tmp_double_array, ms->ms_double_tail, _tmp_uuid, _tmp_ouuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_table_load(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_table_load_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_table_load_t* ms = SGX_CAST(ms_encall_table_load_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ms->ms_retval = encall_table_load();


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_hash_readin(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_hash_readin_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_hash_readin_t* ms = SGX_CAST(ms_encall_hash_readin_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_buf = ms->ms_buf;
	size_t _len_buf = 400;
	char* _in_buf = NULL;

	CHECK_UNIQUE_POINTER(_tmp_buf, _len_buf);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_buf != NULL && _len_buf != 0) {
		_in_buf = (char*)malloc(_len_buf);
		if (_in_buf == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_buf, _tmp_buf, _len_buf);
	}

	ms->ms_retval = encall_hash_readin(_in_buf, ms->ms_line);
err:
	if (_in_buf) free(_in_buf);

	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_read_line(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_read_line_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_read_line_t* ms = SGX_CAST(ms_encall_read_line_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_in_buf = ms->ms_in_buf;
	size_t _len_in_buf = 50;
	char* _in_in_buf = NULL;

	CHECK_UNIQUE_POINTER(_tmp_in_buf, _len_in_buf);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_in_buf != NULL && _len_in_buf != 0) {
		_in_in_buf = (char*)malloc(_len_in_buf);
		if (_in_in_buf == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_in_buf, _tmp_in_buf, _len_in_buf);
	}

	ms->ms_retval = encall_read_line(_in_in_buf, ms->ms_buf_len, ms->ms_line, ms->ms_isIndex);
err:
	if (_in_in_buf) free(_in_in_buf);

	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_varible(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_varible_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_varible_t* ms = SGX_CAST(ms_encall_varible_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_data = ms->ms_data;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_calluuid = ms->ms_calluuid;



	encall_varible(_tmp_data, _tmp_uuid, _tmp_calluuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_deleteValue(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_deleteValue_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_deleteValue_t* ms = SGX_CAST(ms_encall_deleteValue_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_data = ms->ms_data;
	char* _tmp_uuid = ms->ms_uuid;
	char* _tmp_cuuid = ms->ms_cuuid;



	encall_deleteValue(_tmp_data, _tmp_uuid, _tmp_cuuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_initArray(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_initArray_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_initArray_t* ms = SGX_CAST(ms_encall_initArray_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_uuid = ms->ms_uuid;



	encall_initArray(_tmp_uuid, ms->ms_index, ms->ms_size, ms->ms_isSens);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_initNode(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_initNode_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_initNode_t* ms = SGX_CAST(ms_encall_initNode_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_uuid = ms->ms_uuid;



	encall_initNode(_tmp_uuid, ms->ms_type, ms->ms_size);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_getArraySize(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_encall_getArraySize_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_encall_getArraySize_t* ms = SGX_CAST(ms_encall_getArraySize_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_uuid = ms->ms_uuid;



	ms->ms_retval = encall_getArraySize(ms->ms_line, _tmp_uuid);


	return status;
}

static sgx_status_t SGX_CDECL sgx_EcallStartResponder(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EcallStartResponder_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EcallStartResponder_t* ms = SGX_CAST(ms_EcallStartResponder_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	HotCall* _tmp_fastEcall = ms->ms_fastEcall;



	EcallStartResponder(_tmp_fastEcall);


	return status;
}

static sgx_status_t SGX_CDECL sgx_EcallStartResponder3(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EcallStartResponder3_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EcallStartResponder3_t* ms = SGX_CAST(ms_EcallStartResponder3_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	HotCall* _tmp_fastEcall = ms->ms_fastEcall;



	EcallStartResponder3(_tmp_fastEcall);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[21];
} g_ecall_table = {
	21,
	{
		{(void*)(uintptr_t)sgx_encall_switch_type_get_i, 0},
		{(void*)(uintptr_t)sgx_encall_switch_type_branch, 0},
		{(void*)(uintptr_t)sgx_encall_switch_type_update, 0},
		{(void*)(uintptr_t)sgx_print_int, 0},
		{(void*)(uintptr_t)sgx_print_long, 0},
		{(void*)(uintptr_t)sgx_print_double, 0},
		{(void*)(uintptr_t)sgx_print_float, 0},
		{(void*)(uintptr_t)sgx_print_char, 0},
		{(void*)(uintptr_t)sgx_print_byte, 0},
		{(void*)(uintptr_t)sgx_print_array_i, 0},
		{(void*)(uintptr_t)sgx_print_array_d, 0},
		{(void*)(uintptr_t)sgx_encall_table_load, 0},
		{(void*)(uintptr_t)sgx_encall_hash_readin, 0},
		{(void*)(uintptr_t)sgx_encall_read_line, 0},
		{(void*)(uintptr_t)sgx_encall_varible, 0},
		{(void*)(uintptr_t)sgx_encall_deleteValue, 0},
		{(void*)(uintptr_t)sgx_encall_initArray, 0},
		{(void*)(uintptr_t)sgx_encall_initNode, 0},
		{(void*)(uintptr_t)sgx_encall_getArraySize, 0},
		{(void*)(uintptr_t)sgx_EcallStartResponder, 0},
		{(void*)(uintptr_t)sgx_EcallStartResponder3, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[37][21];
} g_dyn_entry_table = {
	37,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		memcpy(__tmp, str, _len_str);
		__tmp = (void *)((size_t)__tmp + _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_print_int(int str)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_print_int_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_int_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_int_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_int_t));

	ms->ms_str = str;
	status = sgx_ocall(1, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_print_long(long int str)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_print_long_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_long_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_long_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_long_t));

	ms->ms_str = str;
	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_write(char* file, char* buf, int len)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_write_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_write_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_write_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_write_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_len = len;
	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_add(char* file, char* buf, int len)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_add_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_add_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_add_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_add_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_len = len;
	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_read(char* file, int* buf, long int* start)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_file = file ? strlen(file) + 1 : 0;
	size_t _len_buf = 400;
	size_t _len_start = 8;

	ms_ocall_file_read_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_read_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	void *__tmp_start = NULL;
	ocalloc_size += (file != NULL && sgx_is_within_enclave(file, _len_file)) ? _len_file : 0;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;
	ocalloc_size += (start != NULL && sgx_is_within_enclave(start, _len_start)) ? _len_start : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_read_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_read_t));

	if (file != NULL && sgx_is_within_enclave(file, _len_file)) {
		ms->ms_file = (char*)__tmp;
		memcpy(__tmp, file, _len_file);
		__tmp = (void *)((size_t)__tmp + _len_file);
	} else if (file == NULL) {
		ms->ms_file = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (int*)__tmp;
		__tmp_buf = __tmp;
		memcpy(__tmp_buf, buf, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (start != NULL && sgx_is_within_enclave(start, _len_start)) {
		ms->ms_start = (long int*)__tmp;
		__tmp_start = __tmp;
		memcpy(__tmp_start, start, _len_start);
		__tmp = (void *)((size_t)__tmp + _len_start);
	} else if (start == NULL) {
		ms->ms_start = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(5, ms);

	if (status == SGX_SUCCESS) {
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
		if (start) memcpy((void*)start, __tmp_start, _len_start);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_getline(char* file, char* buf, long int* line_num)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_getline_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_getline_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_getline_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_getline_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_line_num = SGX_CAST(long int*, line_num);
	status = sgx_ocall(6, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_open(int* retval, const char* filename, int flags, mode_t mode)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;

	ms_ocall_open_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_open_t);
	void *__tmp = NULL;

	ocalloc_size += (filename != NULL && sgx_is_within_enclave(filename, _len_filename)) ? _len_filename : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_open_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_open_t));

	if (filename != NULL && sgx_is_within_enclave(filename, _len_filename)) {
		ms->ms_filename = (char*)__tmp;
		memcpy(__tmp, filename, _len_filename);
		__tmp = (void *)((size_t)__tmp + _len_filename);
	} else if (filename == NULL) {
		ms->ms_filename = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_flags = flags;
	ms->ms_mode = mode;
	status = sgx_ocall(7, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fallocate(int* retval, int fd, int mode, off_t offset, off_t len)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fallocate_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fallocate_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fallocate_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fallocate_t));

	ms->ms_fd = fd;
	ms->ms_mode = mode;
	ms->ms_offset = offset;
	ms->ms_len = len;
	status = sgx_ocall(8, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fcntl_flock(int* retval, int fd, int cmd, struct flock* p)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_p = sizeof(struct flock);

	ms_ocall_fcntl_flock_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fcntl_flock_t);
	void *__tmp = NULL;

	ocalloc_size += (p != NULL && sgx_is_within_enclave(p, _len_p)) ? _len_p : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fcntl_flock_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fcntl_flock_t));

	ms->ms_fd = fd;
	ms->ms_cmd = cmd;
	if (p != NULL && sgx_is_within_enclave(p, _len_p)) {
		ms->ms_p = (struct flock*)__tmp;
		memcpy(__tmp, p, _len_p);
		__tmp = (void *)((size_t)__tmp + _len_p);
	} else if (p == NULL) {
		ms->ms_p = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(9, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fcntl_int(int* retval, int fd, int cmd, int pa)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fcntl_int_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fcntl_int_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fcntl_int_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fcntl_int_t));

	ms->ms_fd = fd;
	ms->ms_cmd = cmd;
	ms->ms_pa = pa;
	status = sgx_ocall(10, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fcntl_void(int* retval, int fd, int cmd)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fcntl_void_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fcntl_void_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fcntl_void_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fcntl_void_t));

	ms->ms_fd = fd;
	ms->ms_cmd = cmd;
	status = sgx_ocall(11, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_getenv(char** retval, const char* name)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_name = name ? strlen(name) + 1 : 0;

	ms_ocall_getenv_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_getenv_t);
	void *__tmp = NULL;

	ocalloc_size += (name != NULL && sgx_is_within_enclave(name, _len_name)) ? _len_name : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_getenv_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_getenv_t));

	if (name != NULL && sgx_is_within_enclave(name, _len_name)) {
		ms->ms_name = (char*)__tmp;
		memcpy(__tmp, name, _len_name);
		__tmp = (void *)((size_t)__tmp + _len_name);
	} else if (name == NULL) {
		ms->ms_name = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(12, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_stat(int* retval, const char* pathname, struct stat* buf)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pathname = pathname ? strlen(pathname) + 1 : 0;
	size_t _len_buf = sizeof(struct stat);

	ms_ocall_stat_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_stat_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	ocalloc_size += (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) ? _len_pathname : 0;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_stat_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_stat_t));

	if (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) {
		ms->ms_pathname = (char*)__tmp;
		memcpy(__tmp, pathname, _len_pathname);
		__tmp = (void *)((size_t)__tmp + _len_pathname);
	} else if (pathname == NULL) {
		ms->ms_pathname = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (struct stat*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(13, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fstat(int* retval, int fd, struct stat* buf)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = sizeof(struct stat);

	ms_ocall_fstat_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fstat_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fstat_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fstat_t));

	ms->ms_fd = fd;
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (struct stat*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(14, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fchmod(int* retval, int fd, unsigned int mode)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fchmod_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fchmod_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fchmod_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fchmod_t));

	ms->ms_fd = fd;
	ms->ms_mode = mode;
	status = sgx_ocall(15, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mkdir(int* retval, const char* pathname, mode_t mode)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pathname = pathname ? strlen(pathname) + 1 : 0;

	ms_ocall_mkdir_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mkdir_t);
	void *__tmp = NULL;

	ocalloc_size += (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) ? _len_pathname : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mkdir_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mkdir_t));

	if (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) {
		ms->ms_pathname = (char*)__tmp;
		memcpy(__tmp, pathname, _len_pathname);
		__tmp = (void *)((size_t)__tmp + _len_pathname);
	} else if (pathname == NULL) {
		ms->ms_pathname = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_mode = mode;
	status = sgx_ocall(16, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_time(time_t* retval, time_t* t)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_t = sizeof(time_t);

	ms_ocall_time_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_time_t);
	void *__tmp = NULL;

	ocalloc_size += (t != NULL && sgx_is_within_enclave(t, _len_t)) ? _len_t : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_time_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_time_t));

	if (t != NULL && sgx_is_within_enclave(t, _len_t)) {
		ms->ms_t = (time_t*)__tmp;
		memcpy(__tmp, t, _len_t);
		__tmp = (void *)((size_t)__tmp + _len_t);
	} else if (t == NULL) {
		ms->ms_t = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(17, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_utimes(int* retval, const char* filename, const struct timeval* times)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;
	size_t _len_times = 2 * sizeof(struct timeval);

	ms_ocall_utimes_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_utimes_t);
	void *__tmp = NULL;

	ocalloc_size += (filename != NULL && sgx_is_within_enclave(filename, _len_filename)) ? _len_filename : 0;
	ocalloc_size += (times != NULL && sgx_is_within_enclave(times, _len_times)) ? _len_times : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_utimes_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_utimes_t));

	if (filename != NULL && sgx_is_within_enclave(filename, _len_filename)) {
		ms->ms_filename = (char*)__tmp;
		memcpy(__tmp, filename, _len_filename);
		__tmp = (void *)((size_t)__tmp + _len_filename);
	} else if (filename == NULL) {
		ms->ms_filename = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (times != NULL && sgx_is_within_enclave(times, _len_times)) {
		ms->ms_times = (struct timeval*)__tmp;
		memcpy(__tmp, times, _len_times);
		__tmp = (void *)((size_t)__tmp + _len_times);
	} else if (times == NULL) {
		ms->ms_times = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(18, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_gettimeofday(int* retval, struct timeval* tv)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_tv = sizeof(struct timeval);

	ms_ocall_gettimeofday_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_gettimeofday_t);
	void *__tmp = NULL;

	void *__tmp_tv = NULL;
	ocalloc_size += (tv != NULL && sgx_is_within_enclave(tv, _len_tv)) ? _len_tv : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_gettimeofday_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_gettimeofday_t));

	if (tv != NULL && sgx_is_within_enclave(tv, _len_tv)) {
		ms->ms_tv = (struct timeval*)__tmp;
		__tmp_tv = __tmp;
		memset(__tmp_tv, 0, _len_tv);
		__tmp = (void *)((size_t)__tmp + _len_tv);
	} else if (tv == NULL) {
		ms->ms_tv = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(19, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (tv) memcpy((void*)tv, __tmp_tv, _len_tv);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_read(ssize_t* retval, int file, void* buf, size_t count)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = count;

	ms_ocall_read_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_read_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_read_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_read_t));

	ms->ms_file = file;
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (void*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_count = count;
	status = sgx_ocall(20, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_write(ssize_t* retval, int file, const void* buf, size_t count)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = count;

	ms_ocall_write_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_write_t);
	void *__tmp = NULL;

	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_write_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_write_t));

	ms->ms_file = file;
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (void*)__tmp;
		memcpy(__tmp, buf, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_count = count;
	status = sgx_ocall(21, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_close(int* retval, int fd)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_close_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_close_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_close_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_close_t));

	ms->ms_fd = fd;
	status = sgx_ocall(22, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fchown(int* retval, int fd, uid_t owner, gid_t group)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fchown_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fchown_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fchown_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fchown_t));

	ms->ms_fd = fd;
	ms->ms_owner = owner;
	ms->ms_group = group;
	status = sgx_ocall(23, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_getcwd(char** retval, char* buf, size_t size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = size * sizeof(char);

	ms_ocall_getcwd_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_getcwd_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_getcwd_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_getcwd_t));

	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (char*)__tmp;
		__tmp_buf = __tmp;
		memcpy(__tmp_buf, buf, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_size = size;
	status = sgx_ocall(24, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_truncate(int* retval, const char* path, off_t length)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_path = path ? strlen(path) + 1 : 0;

	ms_ocall_truncate_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_truncate_t);
	void *__tmp = NULL;

	ocalloc_size += (path != NULL && sgx_is_within_enclave(path, _len_path)) ? _len_path : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_truncate_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_truncate_t));

	if (path != NULL && sgx_is_within_enclave(path, _len_path)) {
		ms->ms_path = (char*)__tmp;
		memcpy(__tmp, path, _len_path);
		__tmp = (void *)((size_t)__tmp + _len_path);
	} else if (path == NULL) {
		ms->ms_path = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_length = length;
	status = sgx_ocall(25, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_ftruncate(int* retval, int fd, off_t length)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_ftruncate_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_ftruncate_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_ftruncate_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_ftruncate_t));

	ms->ms_fd = fd;
	ms->ms_length = length;
	status = sgx_ocall(26, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pread(ssize_t* retval, int fd, void* buf, size_t count, off_t offset)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = count;

	ms_ocall_pread_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pread_t);
	void *__tmp = NULL;

	void *__tmp_buf = NULL;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pread_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pread_t));

	ms->ms_fd = fd;
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (void*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_count = count;
	ms->ms_offset = offset;
	status = sgx_ocall(27, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pwrite(ssize_t* retval, int fd, const void* buf, size_t count, off_t offset)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buf = count;

	ms_ocall_pwrite_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pwrite_t);
	void *__tmp = NULL;

	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pwrite_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pwrite_t));

	ms->ms_fd = fd;
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (void*)__tmp;
		memcpy(__tmp, buf, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_count = count;
	ms->ms_offset = offset;
	status = sgx_ocall(28, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_access(int* retval, const char* pathname, int mode)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pathname = pathname ? strlen(pathname) + 1 : 0;

	ms_ocall_access_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_access_t);
	void *__tmp = NULL;

	ocalloc_size += (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) ? _len_pathname : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_access_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_access_t));

	if (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) {
		ms->ms_pathname = (char*)__tmp;
		memcpy(__tmp, pathname, _len_pathname);
		__tmp = (void *)((size_t)__tmp + _len_pathname);
	} else if (pathname == NULL) {
		ms->ms_pathname = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_mode = mode;
	status = sgx_ocall(29, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_unlink(int* retval, const char* pathname)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pathname = pathname ? strlen(pathname) + 1 : 0;

	ms_ocall_unlink_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_unlink_t);
	void *__tmp = NULL;

	ocalloc_size += (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) ? _len_pathname : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_unlink_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_unlink_t));

	if (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) {
		ms->ms_pathname = (char*)__tmp;
		memcpy(__tmp, pathname, _len_pathname);
		__tmp = (void *)((size_t)__tmp + _len_pathname);
	} else if (pathname == NULL) {
		ms->ms_pathname = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(30, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_rmdir(int* retval, const char* pathname)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pathname = pathname ? strlen(pathname) + 1 : 0;

	ms_ocall_rmdir_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_rmdir_t);
	void *__tmp = NULL;

	ocalloc_size += (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) ? _len_pathname : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_rmdir_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_rmdir_t));

	if (pathname != NULL && sgx_is_within_enclave(pathname, _len_pathname)) {
		ms->ms_pathname = (char*)__tmp;
		memcpy(__tmp, pathname, _len_pathname);
		__tmp = (void *)((size_t)__tmp + _len_pathname);
	} else if (pathname == NULL) {
		ms->ms_pathname = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(31, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_geteuid(uid_t* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_geteuid_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_geteuid_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_geteuid_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_geteuid_t));

	status = sgx_ocall(32, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_lseek(off_t* retval, int fd, off_t offset, int whence)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_lseek_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_lseek_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_lseek_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_lseek_t));

	ms->ms_fd = fd;
	ms->ms_offset = offset;
	ms->ms_whence = whence;
	status = sgx_ocall(33, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fsync(int* retval, int fd)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fsync_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fsync_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fsync_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fsync_t));

	ms->ms_fd = fd;
	status = sgx_ocall(34, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_getpid(pid_t* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_getpid_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_getpid_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_getpid_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_getpid_t));

	status = sgx_ocall(35, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_sleep(unsigned int* retval, unsigned int seconds)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_sleep_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_sleep_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_sleep_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_sleep_t));

	ms->ms_seconds = seconds;
	status = sgx_ocall(36, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

