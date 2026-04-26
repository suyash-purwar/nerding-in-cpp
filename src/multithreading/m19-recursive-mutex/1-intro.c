#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * With normal mutex, if a thread tries to lock the mutex which is already locked by it, the thread get self-deadlocked.
 * Recursive Mutex fixes this problem. It's a mutex on which a thread can repeatedly take logs without getting blocked.
 *
 * Why is it needed? There are a bunch of use cases
 * - It is useful when several public methods of a class need to acquire the same lock, but they also call each other.
 *   Example: If MethodA locks the mutex and then calls MethodB, which also attempts to lock the same mutex, a recursive
 *   mutex allows this sequence to continue safely
 * - It enables writing recursive function that takes a lock. Without recursive mutex, such thread would get deadlocked.
 * - It simplifies writing a thread safe function.
 *
 * In the following examples:
 * - `fail_student` is complete in itself and does the job it is supposed to with complete safety
 * - Now, let's say you want to build another function on top of it access the student's state.
 * - For example, fail all students which have score < 40. To check for this state we would need to take lock on that
 *   student. So far so good.
 * - To write this function, you will need to take the lock to check the state and duplicate the logic for marking the
 *   student as failed. You can't unlock the mutex and then call the `fail_student` function. If you do this, there is
 *   a possibility of another thread changing the marks between two lock-unlock operations.
 * - Without recursive mutex we would need to write a new function and duplicate the logic already present in the
 *  `fail_student` function.
 */

#define STUDENT_COUNT 5

typedef struct {
    char name[20];
    unsigned short marks;
    bool passed;
    pthread_mutex_t lock;
    pthread_mutexattr_t lock_attributes;
} student_t;

student_t create_student(const char* name, const unsigned short marks) {
    student_t student;

    memcpy(student.name, name, 20);
    student.marks = marks;
    student.passed = true;

    pthread_mutexattr_init(&student.lock_attributes);
    pthread_mutexattr_settype(&student.lock_attributes, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&student.lock, &student.lock_attributes);

    return student;
}

student_t* create_students() {
    student_t* students = malloc(sizeof(student_t) * STUDENT_COUNT);

    if (students == NULL) {
        perror("Failed to allocate memory for student");
        exit(-1);
    }

    students[0] = create_student("Suyash", 20);
    students[1] = create_student("Shubham", 100);
    students[2] = create_student("Adeeba", 80);
    students[3] = create_student("Khushboo", 60);
    students[4] = create_student("Rashi", 40);

    return students;
}

void free_students(student_t* students) {
    for (int i = 0; i < STUDENT_COUNT; i++) {
        pthread_mutexattr_destroy(&students[i].lock_attributes);
        pthread_mutex_destroy(&students[i].lock);
    }

    free(students);
    students = NULL;
}

void fail_student(student_t* student) {
    pthread_mutex_lock(&student->lock);

    student->passed = false;

    pthread_mutex_unlock(&student->lock);
}

void evaluate_students(student_t* students) {
    for (int i = 0; i < STUDENT_COUNT; i++) {
        student_t* student = &students[i];

        pthread_mutex_lock(&student->lock);
        if (students[i].marks < 40) {
            fail_student(student);
        }
        pthread_mutex_unlock(&student->lock);
    }
}

void* process_students_worker(void* arg) {
    student_t* students = arg;

    evaluate_students(students);

    for (int i = 0; i < STUDENT_COUNT; i++) {
        if (students[i].passed == false)
            printf("%s has failed\n", students[i].name);
    }

    return NULL;
}

int main() {
    pthread_t process_students_thread;

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr,  PTHREAD_CREATE_JOINABLE);

    student_t* students = create_students();

    if (pthread_create(&process_students_thread, &thread_attr, process_students_worker, students)) {
        printf("Failed to create student processing thread\n");
        free_students(students);
        exit(-1);
    }

    if (pthread_join(process_students_thread, NULL)) {
        printf("Failed to join student processing thread\n");
        free_students(students);
        exit(-1);
    }

    pthread_attr_destroy(&thread_attr);
    free_students(students);

    return 0;
}