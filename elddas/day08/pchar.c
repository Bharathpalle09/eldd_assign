#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kfifo.h>
#include<linux/slab.h>


static int pchar_open(struct inode*, struct file *);
static int pchar_close(struct indoe *,struct file *);
static ssize_t pchar_read(struct file *,char *,size_t , loff_t *);
static ssize_t pchar_write(struct file *,const char *,size_t, loff_t);

#define MAX 32

struct pchar_device {
	struct kfifo buf;
	dev_t devno;
	struct cdev cdev;
};

static int major;
static struct class *pclass;
static int devcnt=3;
struct pchar_device *devices;


static struct file_operations pchar_fops= {
	.owner = THIS_MODULE,
	.open = pchar_open,

