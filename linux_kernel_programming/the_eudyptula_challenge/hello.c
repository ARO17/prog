/*
 * hello.c -- Hello world Linux kernel module
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 *
 * Started on  Fri Jun  6 17:38:31 2014 Harold André
 * Last update Sun Jul  6 09:46:17 2014 Harold André
 */

#define DEBUG 1

#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Hello world Linux kernel module");
MODULE_AUTHOR("Harold André <harold.andre@gmx.fr>");
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_debug("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);
