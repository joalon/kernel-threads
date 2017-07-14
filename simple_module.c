#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/sched.h>

int myint = 3;
module_param(myint, int, 0);
MODULE_PARM_DESC(myint, "My own int");

static char * mystring = "Aha!";
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "Just a string");

struct task_struct *task;
int myfunction(void *data){
    int input = (int)data;
    printk(KERN_DEBUG "Kernel thread started, got: %d\n", input);
    
    while(!kthread_should_stop()){
        msleep(3000);
        printk(KERN_DEBUG "Thread still alive \n");
    }

    printk(KERN_DEBUG "Thread exiting");
    return input;
}

static int __init hello_init(void)
{
    printk(KERN_DEBUG "%s\n", mystring);
	printk(KERN_DEBUG "Hello, world! I got: %d\n", myint);

    task = kthread_run(&myfunction, (void *)myint, mystring);

	return 0;
}

static void __exit hello_cleanup(void)
{
    int ret = kthread_stop(task);
    printk(KERN_DEBUG "thread returned: %d\n", ret);
	printk(KERN_DEBUG "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joakim Lönnegren");
