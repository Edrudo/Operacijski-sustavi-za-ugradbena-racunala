#ifdef DISK

#include <arch/device.h>
#include <kernel/memory.h>
#include <kernel/errno.h>
#include <lib/string.h>

#define BLOCK_SIZE	512
#define BLOCKS		4096

static int init(uint flags, void *params, device_t *dev);
static int destroy(uint flags, void *params, device_t *dev);
static int send(void *data, size_t size, uint flags, device_t *dev);
static int recv(void *data, size_t size, uint flags, device_t *dev);

device_t disk = (device_t)
{
	.dev_name =	"DISK",
	.irq_num = 	-1,
	.irq_handler =	NULL,

	.init =		init,
	.destroy =	destroy,
	.send =		send,
	.recv =		recv,
	.status =	NULL,

	.flags = 	0,
	.params = 	NULL
};


static int init(uint flags, void *params, device_t *dev)
{
	ASSERT_AND_RETURN_ERRNO(dev->params == NULL, -EINVAL);

	dev->params = kmalloc(BLOCK_SIZE * BLOCKS);

	ASSERT_AND_RETURN_ERRNO(dev->params != NULL, -ENOMEM);

	memset(dev->params, 0, BLOCK_SIZE * BLOCKS);

	return 0;
}

static int destroy(uint flags, void *params, device_t *dev)
{
	ASSERT_AND_RETURN_ERRNO(dev->params != NULL, -EINVAL);

	kfree(dev->params);

	return 0;
}

/* size: 16+16 bitova = prvi blok | broj blokova */
static int send(void *data, size_t size, uint flags, device_t *dev)
{
	size_t start = size >> 16;
	size_t count = size & 0xffff;

	ASSERT_AND_RETURN_ERRNO(dev->params != NULL, -EINVAL);
	ASSERT_AND_RETURN_ERRNO(size > 0, -EINVAL);
	ASSERT_AND_RETURN_ERRNO(start + count < BLOCKS, -EINVAL);

	memcpy(dev->params + start * BLOCK_SIZE, data, count * BLOCK_SIZE);

	return count * BLOCK_SIZE;
}

/* size: 16+16 bitova = prvi blok | broj blokova */
static int recv(void *data, size_t size, uint flags, device_t *dev)
{
	size_t start = size >> 16;
	size_t count = size & 0xffff;

	ASSERT_AND_RETURN_ERRNO(dev->params != NULL, -EINVAL);
	ASSERT_AND_RETURN_ERRNO(size > 0, -EINVAL);
	ASSERT_AND_RETURN_ERRNO(start + count < BLOCKS, -EINVAL);

	memcpy(data, dev->params + start * BLOCK_SIZE, count * BLOCK_SIZE);

	return count * BLOCK_SIZE;
}

#endif /* DISK */
