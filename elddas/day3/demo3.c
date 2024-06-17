#include<linux/module.h>
static __init int desd_init(void)
{
	printk(KERN_INFO "%s : desd_init(): state =%d\n",THIS_MODULE->name,THIS_MODULE->state);
	printk(KERN_INFO "%s : desd_init:intialization is successful\n",THIS_MODULE->name);

	return 0;
}

static __exit void desd_exit(void)
{
	printk(KERN_INFO "%s :desd_exit():state =%d\n",THIS_MODULE->name,THIS_MODULE->state);
	printk(KERN_INFO"%s:desd_exit() :intialization is successful\n",THIS_MODULE->name);
}
	module_init(desd_init);
	module_exit(desd_exit);
	MODULE_LICENSE("GPL");
	MODULE_AUTHOR("BHARATH");
	MODULE_DESCRIPTION("DEMO 3");
