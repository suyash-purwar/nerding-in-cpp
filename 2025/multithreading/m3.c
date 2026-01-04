#include <stdio.h>
#include <pthread.h>

/**
 * Here, the loop is running 10_000_000 times and increments the counter. This happens twice. It is natural to
 * except the value of counter would be 20_000_000 but that is not the case. The output of this program is
 * Undeterministic. Every time you run the program, it might yield a different output.
 *
 * Here, `counter` is the shared variable across two threads which are incrementing it parallely.
 * This leads to issues and can be understood when looked at its assembly instructions.
 *
 * Variable `counter` is static and global. It would be stored in the .bss section. Let's assume the address of
 * `counter` variable is 0x8049a1c. Now, let's look at the assembly instructions for `counter++` at line 16. This
 * is where things go haywire.
 *
 * I1: MOV eax, 0x8049a1c
 * I2: ADD eax, 0x1
 * I3: MOV 0x8049a1c, eax
 *
 * Assume the value of counter (0x8049a1c) is 90. Now, suppose thread T1 has executed upto instruction I2 and scheduler
 * preempts the thread saving the state of the `eax` register in the Thread Control Block (TCB, same as PCB but for
 * threads). In TCB, the value of eax is 91 and counter is 90. Memory location 0x8049a1c (counter) has not yet started
 * pointing to the updated value of 91.
 *
 * After preemption of thread T1, thread T2 starts executing and reads the value of counter as 90 and completes all the
 * three instructions (I1, I2, and I3). Now, the value of eax and counter, under the context of thread T2, is 91 and 91
 * respectively. Thread T2 completes it's work and exits.
 *
 * Now, scheduler decides to continue the Thread T1's work. Thread T1's context gets restored through its Thread
 * Control Block. Here, the value of register `eax` and variable counter is 91 and 90 respectively and the Program
 * Counter is pointing to the instruction I3 since I2 was executed. Here, I3 saves the value of register eax in
 * the counter (0x8049a1c) which is 91.
 *
 * Voila! You can see that here we saved the value 91 twice in the counter variable. This is a classic example of *(Race
 * Condition**.
 *
 * This happened due to the lack of atomicity of instructions. If all three instructions could be executed as one
 * single instruction, this problem would get resolved. This is where we make use of locks.
 *
 * `counter++` is the Critical Section of this program.  A critical section is a piece of code that accesses a shared
 * variable or resource  and must not be concurrently executed by more than one thread. What we really want in this
 * code is **Mutual Exclusion**.
 */

static int counter = 0;

void* increment() {
  for (int i = 0; i < 1e7; i++) {
    counter++;
  }

  return NULL;
}

int main() {
  pthread_t thread1;
  pthread_t thread2;

  int status = pthread_create(&thread1, NULL, increment, NULL);

  if (status) {
    printf("Failed to create the thread");
  }

  status = pthread_create(&thread2, NULL, increment, NULL);
  if (status) {
    printf("Failed to create the thread");
  }

  status = pthread_join(thread1, NULL);
  if (status) {
    printf("Failed to join the thread");
  }

  status = pthread_join(thread2, NULL);
  if (status) {
    printf("Failed to join the thread");
  }

  printf("Count is: %d\n", counter);
}