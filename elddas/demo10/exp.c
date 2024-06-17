#include<linux/module.h>

int my_var=10;
void my_function(void)
{
	printk(KERN_INFO "%s : my_function():function is called\n",THIS_MODULE->name);
	printk(KERN_INFO "%s : my_function() : my_var =%d\n",THIS_MODULE->name,my_var);
}

static __init int export_init(void)
{
	printk(KERN_INFO"%s :export_init() : init is started\n",THIS_MODULE->name);
	my_function();
	printk(KERN_INFO"%s :export_init() : init is completed\n",THIS_MODULE->name);
	return 0;
}

static __exit void export_exit(void)
{
	printk(KERN_INFO "%s :export_exit() :exit is started\n",THIS_MODULE->name);
	my_function();
	printk(KERN_INFO "%s :export_exit() :exit is completed\n",THIS_MODULE->name);
}
EXPORT_SYMBOL(my_var);
EXPORT_SYMBOL_GPL(my_function);

module_init(export_init);
module_exit(export_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DESD@ SUNBEAM");
MODULE_DESCRIPTION("This is dependency modulse");












