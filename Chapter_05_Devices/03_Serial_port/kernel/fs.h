/*! Simple file system */
#pragma once

int k_fs_init(char *disk_device, size_t bsize, size_t blocks);
int k_fs_is_file_open(descriptor_t *desc);
int k_fs_open_file(char *pathname, int flags, mode_t mode, descriptor_t *desc);
int k_fs_close_file(descriptor_t *desc);
int k_fs_read_write(descriptor_t *desc, void *buffer, size_t size, int op);
int k_fs_rename_file(char *old_file_name, char *new_file_name);

#ifdef _K_FS_C_

#include <types/time.h>

#define FS_TYPE		42 //any number will do :)
#define KTYPE_FILE	(1<<10)

#define MAXFILESONDISK	16
#define MAXFILENAMESIZE	16
#define MAXFILEBLOCKS	16

struct fs_node {
	char node_name[MAXFILENAMESIZE];
	size_t id;      // position in file table
	timespec_t tc;  // time of file creation
	timespec_t ta;  // time of last access
	timespec_t tm;  // time of last modification
	size_t size;    // total size in bytes
	size_t blocks;  // allocated blocks
	size_t block[MAXFILEBLOCKS]; // where are blocks on disk
} __attribute__((packed));

struct fs_table {
	int file_system_type;
	char partition_name[MAXFILENAMESIZE];
	size_t block_size;
	size_t blocks;
	size_t max_files;
	struct fs_node fd[MAXFILESONDISK];
	char free[1]; // bitmap would be better, but ...
} __attribute__((packed));

/* disk blocks:
   0-X: [file_table] => sizeof(struct file_table)
   X+1: free block or file content
*/

//open file descriptor
struct kfile_desc {
	id_t id;    // kernel object id
	struct fs_node *tfd; //pointer to descriptor in file table in memory
	int flags;
	size_t fp; //file pointer, offset from beginning
	list_h list;
};

#endif /* _K_FS_C_ */
