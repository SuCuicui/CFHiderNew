#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_encall_switch_type_i_t {
	int ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_i_t;

typedef struct ms_encall_switch_type_d_t {
	double ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_d_t;

typedef struct ms_encall_switch_type_f_t {
	float ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_f_t;

typedef struct ms_encall_switch_type_c_t {
	char ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_c_t;

typedef struct ms_encall_switch_type_l_t {
	long int ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_l_t;

typedef struct ms_encall_switch_type_b_t {
	char ms_retval;
	long int ms_Line;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
	char* ms_byte_array;
	int ms_lenbyte;
} ms_encall_switch_type_b_t;

typedef struct ms_print_int_t {
	int ms_retval;
	long int ms_line;
	int* ms_int_array;
} ms_print_int_t;

typedef struct ms_print_double_t {
	double ms_retval;
	long int ms_line;
	double* ms_double_array;
} ms_print_double_t;

typedef struct ms_print_float_t {
	float ms_retval;
	long int ms_line;
	float* ms_float_array;
} ms_print_float_t;

typedef struct ms_print_char_t {
	char ms_retval;
	long int ms_line;
	char* ms_char_array;
} ms_print_char_t;

typedef struct ms_print_long_t {
	long int ms_retval;
	long int ms_line;
	long int* ms_long_array;
} ms_print_long_t;

typedef struct ms_print_byte_t {
	char ms_retval;
	long int ms_line;
	char* ms_byte_array;
} ms_print_byte_t;

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
} ms_encall_read_line_t;

typedef struct ms_encall_varible_t {
	int* ms_v_array;
	int ms_size;
} ms_encall_varible_t;

typedef struct ms_encall_deleteValue_t {
	int ms_retval;
} ms_encall_deleteValue_t;

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

static sgx_status_t SGX_CDECL Enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_print_int(void* pms)
{
	ms_ocall_print_int_t* ms = SGX_CAST(ms_ocall_print_int_t*, pms);
	ocall_print_int(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_print_long(void* pms)
{
	ms_ocall_print_long_t* ms = SGX_CAST(ms_ocall_print_long_t*, pms);
	ocall_print_long(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_write(void* pms)
{
	ms_ocall_file_write_t* ms = SGX_CAST(ms_ocall_file_write_t*, pms);
	ocall_file_write(ms->ms_file, ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_add(void* pms)
{
	ms_ocall_file_add_t* ms = SGX_CAST(ms_ocall_file_add_t*, pms);
	ocall_file_add(ms->ms_file, ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_read(void* pms)
{
	ms_ocall_file_read_t* ms = SGX_CAST(ms_ocall_file_read_t*, pms);
	ocall_file_read(ms->ms_file, ms->ms_buf, ms->ms_start);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_getline(void* pms)
{
	ms_ocall_file_getline_t* ms = SGX_CAST(ms_ocall_file_getline_t*, pms);
	ocall_file_getline(ms->ms_file, ms->ms_buf, ms->ms_line_num);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_open(void* pms)
{
	ms_ocall_open_t* ms = SGX_CAST(ms_ocall_open_t*, pms);
	ms->ms_retval = ocall_open((const char*)ms->ms_filename, ms->ms_flags, ms->ms_mode);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fallocate(void* pms)
{
	ms_ocall_fallocate_t* ms = SGX_CAST(ms_ocall_fallocate_t*, pms);
	ms->ms_retval = ocall_fallocate(ms->ms_fd, ms->ms_mode, ms->ms_offset, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fcntl_flock(void* pms)
{
	ms_ocall_fcntl_flock_t* ms = SGX_CAST(ms_ocall_fcntl_flock_t*, pms);
	ms->ms_retval = ocall_fcntl_flock(ms->ms_fd, ms->ms_cmd, ms->ms_p);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fcntl_int(void* pms)
{
	ms_ocall_fcntl_int_t* ms = SGX_CAST(ms_ocall_fcntl_int_t*, pms);
	ms->ms_retval = ocall_fcntl_int(ms->ms_fd, ms->ms_cmd, ms->ms_pa);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fcntl_void(void* pms)
{
	ms_ocall_fcntl_void_t* ms = SGX_CAST(ms_ocall_fcntl_void_t*, pms);
	ms->ms_retval = ocall_fcntl_void(ms->ms_fd, ms->ms_cmd);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_getenv(void* pms)
{
	ms_ocall_getenv_t* ms = SGX_CAST(ms_ocall_getenv_t*, pms);
	ms->ms_retval = ocall_getenv((const char*)ms->ms_name);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_stat(void* pms)
{
	ms_ocall_stat_t* ms = SGX_CAST(ms_ocall_stat_t*, pms);
	ms->ms_retval = ocall_stat((const char*)ms->ms_pathname, ms->ms_buf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fstat(void* pms)
{
	ms_ocall_fstat_t* ms = SGX_CAST(ms_ocall_fstat_t*, pms);
	ms->ms_retval = ocall_fstat(ms->ms_fd, ms->ms_buf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fchmod(void* pms)
{
	ms_ocall_fchmod_t* ms = SGX_CAST(ms_ocall_fchmod_t*, pms);
	ms->ms_retval = ocall_fchmod(ms->ms_fd, ms->ms_mode);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mkdir(void* pms)
{
	ms_ocall_mkdir_t* ms = SGX_CAST(ms_ocall_mkdir_t*, pms);
	ms->ms_retval = ocall_mkdir((const char*)ms->ms_pathname, ms->ms_mode);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_time(void* pms)
{
	ms_ocall_time_t* ms = SGX_CAST(ms_ocall_time_t*, pms);
	ms->ms_retval = ocall_time(ms->ms_t);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_utimes(void* pms)
{
	ms_ocall_utimes_t* ms = SGX_CAST(ms_ocall_utimes_t*, pms);
	ms->ms_retval = ocall_utimes((const char*)ms->ms_filename, (const struct timeval*)ms->ms_times);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_gettimeofday(void* pms)
{
	ms_ocall_gettimeofday_t* ms = SGX_CAST(ms_ocall_gettimeofday_t*, pms);
	ms->ms_retval = ocall_gettimeofday(ms->ms_tv);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_read(void* pms)
{
	ms_ocall_read_t* ms = SGX_CAST(ms_ocall_read_t*, pms);
	ms->ms_retval = ocall_read(ms->ms_file, ms->ms_buf, ms->ms_count);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_write(void* pms)
{
	ms_ocall_write_t* ms = SGX_CAST(ms_ocall_write_t*, pms);
	ms->ms_retval = ocall_write(ms->ms_file, (const void*)ms->ms_buf, ms->ms_count);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_close(void* pms)
{
	ms_ocall_close_t* ms = SGX_CAST(ms_ocall_close_t*, pms);
	ms->ms_retval = ocall_close(ms->ms_fd);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fchown(void* pms)
{
	ms_ocall_fchown_t* ms = SGX_CAST(ms_ocall_fchown_t*, pms);
	ms->ms_retval = ocall_fchown(ms->ms_fd, ms->ms_owner, ms->ms_group);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_getcwd(void* pms)
{
	ms_ocall_getcwd_t* ms = SGX_CAST(ms_ocall_getcwd_t*, pms);
	ms->ms_retval = ocall_getcwd(ms->ms_buf, ms->ms_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_truncate(void* pms)
{
	ms_ocall_truncate_t* ms = SGX_CAST(ms_ocall_truncate_t*, pms);
	ms->ms_retval = ocall_truncate((const char*)ms->ms_path, ms->ms_length);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_ftruncate(void* pms)
{
	ms_ocall_ftruncate_t* ms = SGX_CAST(ms_ocall_ftruncate_t*, pms);
	ms->ms_retval = ocall_ftruncate(ms->ms_fd, ms->ms_length);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pread(void* pms)
{
	ms_ocall_pread_t* ms = SGX_CAST(ms_ocall_pread_t*, pms);
	ms->ms_retval = ocall_pread(ms->ms_fd, ms->ms_buf, ms->ms_count, ms->ms_offset);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pwrite(void* pms)
{
	ms_ocall_pwrite_t* ms = SGX_CAST(ms_ocall_pwrite_t*, pms);
	ms->ms_retval = ocall_pwrite(ms->ms_fd, (const void*)ms->ms_buf, ms->ms_count, ms->ms_offset);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_access(void* pms)
{
	ms_ocall_access_t* ms = SGX_CAST(ms_ocall_access_t*, pms);
	ms->ms_retval = ocall_access((const char*)ms->ms_pathname, ms->ms_mode);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_unlink(void* pms)
{
	ms_ocall_unlink_t* ms = SGX_CAST(ms_ocall_unlink_t*, pms);
	ms->ms_retval = ocall_unlink((const char*)ms->ms_pathname);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_rmdir(void* pms)
{
	ms_ocall_rmdir_t* ms = SGX_CAST(ms_ocall_rmdir_t*, pms);
	ms->ms_retval = ocall_rmdir((const char*)ms->ms_pathname);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_geteuid(void* pms)
{
	ms_ocall_geteuid_t* ms = SGX_CAST(ms_ocall_geteuid_t*, pms);
	ms->ms_retval = ocall_geteuid();

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_lseek(void* pms)
{
	ms_ocall_lseek_t* ms = SGX_CAST(ms_ocall_lseek_t*, pms);
	ms->ms_retval = ocall_lseek(ms->ms_fd, ms->ms_offset, ms->ms_whence);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fsync(void* pms)
{
	ms_ocall_fsync_t* ms = SGX_CAST(ms_ocall_fsync_t*, pms);
	ms->ms_retval = ocall_fsync(ms->ms_fd);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_getpid(void* pms)
{
	ms_ocall_getpid_t* ms = SGX_CAST(ms_ocall_getpid_t*, pms);
	ms->ms_retval = ocall_getpid();

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_sleep(void* pms)
{
	ms_ocall_sleep_t* ms = SGX_CAST(ms_ocall_sleep_t*, pms);
	ms->ms_retval = ocall_sleep(ms->ms_seconds);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[37];
} ocall_table_Enclave = {
	37,
	{
		(void*)Enclave_ocall_print_string,
		(void*)Enclave_ocall_print_int,
		(void*)Enclave_ocall_print_long,
		(void*)Enclave_ocall_file_write,
		(void*)Enclave_ocall_file_add,
		(void*)Enclave_ocall_file_read,
		(void*)Enclave_ocall_file_getline,
		(void*)Enclave_ocall_open,
		(void*)Enclave_ocall_fallocate,
		(void*)Enclave_ocall_fcntl_flock,
		(void*)Enclave_ocall_fcntl_int,
		(void*)Enclave_ocall_fcntl_void,
		(void*)Enclave_ocall_getenv,
		(void*)Enclave_ocall_stat,
		(void*)Enclave_ocall_fstat,
		(void*)Enclave_ocall_fchmod,
		(void*)Enclave_ocall_mkdir,
		(void*)Enclave_ocall_time,
		(void*)Enclave_ocall_utimes,
		(void*)Enclave_ocall_gettimeofday,
		(void*)Enclave_ocall_read,
		(void*)Enclave_ocall_write,
		(void*)Enclave_ocall_close,
		(void*)Enclave_ocall_fchown,
		(void*)Enclave_ocall_getcwd,
		(void*)Enclave_ocall_truncate,
		(void*)Enclave_ocall_ftruncate,
		(void*)Enclave_ocall_pread,
		(void*)Enclave_ocall_pwrite,
		(void*)Enclave_ocall_access,
		(void*)Enclave_ocall_unlink,
		(void*)Enclave_ocall_rmdir,
		(void*)Enclave_ocall_geteuid,
		(void*)Enclave_ocall_lseek,
		(void*)Enclave_ocall_fsync,
		(void*)Enclave_ocall_getpid,
		(void*)Enclave_ocall_sleep,
	}
};
sgx_status_t encall_switch_type_i(sgx_enclave_id_t eid, int* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_i_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type_d(sgx_enclave_id_t eid, double* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_d_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type_f(sgx_enclave_id_t eid, float* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_f_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type_c(sgx_enclave_id_t eid, char* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_c_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 3, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type_l(sgx_enclave_id_t eid, long int* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_l_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 4, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type_b(sgx_enclave_id_t eid, char* retval, long int Line, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong, char* byte_array, int lenbyte)
{
	sgx_status_t status;
	ms_encall_switch_type_b_t ms;
	ms.ms_Line = Line;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	ms.ms_byte_array = byte_array;
	ms.ms_lenbyte = lenbyte;
	status = sgx_ecall(eid, 5, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_int(sgx_enclave_id_t eid, int* retval, long int line, int* int_array)
{
	sgx_status_t status;
	ms_print_int_t ms;
	ms.ms_line = line;
	ms.ms_int_array = int_array;
	status = sgx_ecall(eid, 6, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_double(sgx_enclave_id_t eid, double* retval, long int line, double* double_array)
{
	sgx_status_t status;
	ms_print_double_t ms;
	ms.ms_line = line;
	ms.ms_double_array = double_array;
	status = sgx_ecall(eid, 7, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_float(sgx_enclave_id_t eid, float* retval, long int line, float* float_array)
{
	sgx_status_t status;
	ms_print_float_t ms;
	ms.ms_line = line;
	ms.ms_float_array = float_array;
	status = sgx_ecall(eid, 8, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_char(sgx_enclave_id_t eid, char* retval, long int line, char* char_array)
{
	sgx_status_t status;
	ms_print_char_t ms;
	ms.ms_line = line;
	ms.ms_char_array = char_array;
	status = sgx_ecall(eid, 9, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_long(sgx_enclave_id_t eid, long int* retval, long int line, long int* long_array)
{
	sgx_status_t status;
	ms_print_long_t ms;
	ms.ms_line = line;
	ms.ms_long_array = long_array;
	status = sgx_ecall(eid, 10, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t print_byte(sgx_enclave_id_t eid, char* retval, long int line, char* byte_array)
{
	sgx_status_t status;
	ms_print_byte_t ms;
	ms.ms_line = line;
	ms.ms_byte_array = byte_array;
	status = sgx_ecall(eid, 11, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_table_load(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_encall_table_load_t ms;
	status = sgx_ecall(eid, 12, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_hash_readin(sgx_enclave_id_t eid, int* retval, char* buf, long int line)
{
	sgx_status_t status;
	ms_encall_hash_readin_t ms;
	ms.ms_buf = buf;
	ms.ms_line = line;
	status = sgx_ecall(eid, 13, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_read_line(sgx_enclave_id_t eid, int* retval, char* in_buf, int buf_len, long int line)
{
	sgx_status_t status;
	ms_encall_read_line_t ms;
	ms.ms_in_buf = in_buf;
	ms.ms_buf_len = buf_len;
	ms.ms_line = line;
	status = sgx_ecall(eid, 14, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_varible(sgx_enclave_id_t eid, int* v_array, int size)
{
	sgx_status_t status;
	ms_encall_varible_t ms;
	ms.ms_v_array = v_array;
	ms.ms_size = size;
	status = sgx_ecall(eid, 15, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t encall_deleteValue(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_encall_deleteValue_t ms;
	status = sgx_ecall(eid, 16, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

