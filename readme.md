# Practice with <semaphore.h>

This exercise is an opportunity to see how semaphores applied in a C program. `queue.h` and `queue.c` are provided in their entirety. Your goal is to complete the code in `template.c`. `answer.c` is the answer key with one possible implementation, but you are encouraged not to look at the solution until you've made an attempt on your own. `template.c` contains comments to guide you and a file header with helpful documentation pages you may want to look at.

The program is an interesting contrived scenario in which you want to cap the number of threads running by splitting the data they need to operate on and guarding it with a semaphore. For more information, see the file header in `template.c`.

**Bonus conceptual question:** The usual way to limit the number of active threads is with a thread pool, which contains some number of threads that may be woken to perform a task. Critically, they are not destroyed and recreated in between tasks; they are simply put back to sleep and woken up as needed to eliminate the overhead of creating and destroying threads. How might a semaphore be applied to implement a thread pool?

<details>
  <summary>View possible answer</summary>
  
  We could implement a thread pool with a similar strategy to that used in this program. Instead of calling `pthread_create()` whenever the semaphore value is greater than 0, we could send a signal to an already-created thread that is in the `TASK_INTERRUPTIBLE` state. When it finishes its task, we would increment the semaphore and then return the thread to the `TASK_INTERRUPTIBLE` state.
</details>
