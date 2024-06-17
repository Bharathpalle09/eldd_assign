#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kfifo.h>

static int pchar_open(struct inode *,struct file *);
static int pchar_close(struct inode *,struct file *);
static ssize_t pchar_read(struct file*,char*,size_t,loff_t*);
static ssize_t pchar_write(struct file*,const char*,size_t,loff_t*);

#define MAX 32
static struct kfifo buf;
static dev_t devno;
static int major;
static struct class *pclass;
static struct cdev cdev;
static struct file_operations pchar_fops={
	.owner=THIS_MODULE,
	.open=pchar_open,
	.release=pchar_close,
	.write=pchar_write,
	.read=pchar_read
};

static __init int pchar_init(void)
{	
	int ret,minor;
	struct device *pdevice;
	printk(KERN_INFO "%s the init function is called \n",THIS_MODULE->name);
	ret=kfifo_alloc(&buf,MAX,GFP_KERNEL);
	if(ret!=0)
	{
		printk(KERN_ERR"%s the fif0_allocate is failed\n",THIS_MODULE->name);
	goto kfifo_alloc;
	}
	
	printk(KERN_INFO"%s the buffer is allocated ",THIS_MODULE->name);
	
	ret=alloc_chrdev_region(&devno,0,1,"pchar");
	if(ret!=0)
	{
		printk(KERN_INFO"%s the alloc_chrdev_region is failed",THIS_MODULE->name);
		goto alloc_chrdev_region;
	}
	major=MAJOR(devno);
	minor=MINOR(devno);
	printk(KERN_INFO"%s alloc_chrdev_region is successfully allocaed the devno is =%d/%d",THIS_MODULE->name,major,minor);
	pclass=class_create("pchar_class");

	if(IS_ERR(pclass))
	{
		printk(KERN_ERR "%s class_create is failed ",THIS_MODULE->name);
		goto class_create;
	}
	printk(KERN_INFO "%s class is successfully created ",THIS_MODULE->name);
	pdevice=device_create(pclass,NULL,devno,NULL,"pchar%d",0);
	if(IS_ERR(pdevice))
	{
		printk(KERN_ERR "%s the device_create is failed\n",THIS_MODULE->name);
		goto device_called_failed;
	}
	printk(KERN_INFO "%s device_create is succesfull\n",THIS_MODULE->name);

	cdev_init(&cdev,&pchar_fops);
	ret=cdev_add(&cdev,devno,1);
	if(ret !=0)
	{
		printk(KERN_INFO"%s cdev is added in kernel db",THIS_MODULE->name);
		goto cdev_failed;
	}
	printk(KERN_INFO "%s the cdev is allocated device in  kernel  db\n",THIS_MODULE->name);

	return 0;
cdev_failed:
	device_destroy(pclass,devno);
device_called_failed:
	class_destroy(pclass);
class_create:
	unregister_chrdev_region(devno,1);
alloc_chrdev_region:
	kfifo_free(&buf);
kfifo_alloc:
	return ret;

}

static __exit void pchar_exit(void)
{
	printk(KERN_INFO "%s the exit function is called\n",THIS_MODULE->name);
	cdev_del(&cdev);
	printk(KERN_INFO "%s the cdev is delloacted \n",THIS_MODULE->name);
	device_destroy(pclass,devno);
	printk(KERN_INFO" %s the device created is destroyed\n",THIS_MODULE->name);
	class_destroy(pclass);
	printk(KERN_INFO"%s the class_destroyed() ",THIS_MODULE->name);

	unregister_chrdev_region(devno,1);
	printk(KERN_INFO"%s the devno is deallocated ",THIS_MODULE->name);
	kfifo_free(&buf);
	printk(KERN_INFO"%s the buffer is freed\n ",THIS_MODULE->name);



}


static int pchar_open(struct inode *pinode,struct file *pfile)
{
printk(KERN_INFO "%s the open file called \n",THIS_MODULE->name);
return 0;
}

static int pchar_close(struct inode *pinode,struct file *pfile)
{
	printk(KERN_INFO "%s pchar_close() is called\n",THIS_MODULE->name);
	return 0;
}
static ssize_t pchar_read(struct file *pfile,char *ubuf ,size_t size,loff_t *poffset)
{
int nbytes,ret;
printk(KERN_INFO "%s :pchar_read() called \n",THIS_MODULE->name);
ret=kfifo_to_user(&buf,ubuf,size,&nbytes);
if(ret<0)
{
	printk(KERN_ERR "%s :pchar_read() copied failed \n",THIS_MODULE->name);
	return ret;

}
printk(KERN_INFO "%s :pchar_read() copied %d bytes to user space \n",THIS_MODULE->name,nbytes);
return nbytes;
}


static ssize_t pchar_write(struct file *pfile,const char *ubuf,size_t size,loff_t *poffset)
{
int nbytes,ret;
printk(KERN_INFO "%s the write() is called \n",THIS_MODULE->name);
ret=kfifo_from_user(&buf,ubuf,size,&nbytes);
if(ret<0)
{
	printk(KERN_ERR "%s the write() is failed\n",THIS_MODULE->name);
	return ret;
}
printk(KERN_INFO "%s :pchar_write() copied %d bytes from user space\n",THIS_MODULE->name,nbytes);
return nbytes;
}

module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUNBEAM DESD");
MODULE_DESCRIPTION("This is new dd program");

