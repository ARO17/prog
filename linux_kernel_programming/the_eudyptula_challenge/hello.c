/*
 * hello.c -- Hello world Linux kernel module
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Fri Jun  6 17:38:31 2014 Harold André
 * Last update Fri Jun  6 18:18:01 2014 Harold André
 * 
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Hello world Linux kernel module");
MODULE_AUTHOR("Harold André <harold.andre@gmx.fr>");
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
    printk(KERN_DEBUG "Hello, world!!!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_DEBUG "Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);
