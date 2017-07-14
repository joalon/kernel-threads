# kernel-threads

A small experiment getting kernel threads to run. Prints to the kernel log every three seconds when loaded. Gracefully exits on removal.

Had some problems when calling kthread_stop(task); on the thread when it had already returned, got my first "Oops".
