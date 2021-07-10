#include <linux/module.h>
#include <linux/kernel.h>

static int init_my_module(void) {
    printk("%s\n", "Example module was loaded into the kernel!");
    printk("%s %s\n", THIS_MODULE->name, THIS_MODULE->version);

    return 0;
}

static void exit_my_module(void) {
    printk("%s\n", "Example module was removed from the kernel");
}

module_init(init_my_module);
module_exit(exit_my_module);

MODULE_VERSION("0.1.0");
MODULE_LICENSE("GPLv2");


