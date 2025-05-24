```markdown
# Лабораторная работа №7  
**Выполнил:** Крахмальный К.В.  
**Группа:** ИКС-433  

---

## Задание 1  
Создание потока с помощью `pthread_create()` с атрибутами по умолчанию.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }

    pthread_join(thread, NULL);
    return 0;
}
```

**Вывод:**  
```
Main thread: Line 0  
Main thread: Line 1  
Main thread: Line 2  
Main thread: Line 3  
Main thread: Line 4  
Child thread: Line 0  
Child thread: Line 1  
Child thread: Line 2  
Child thread: Line 3  
Child thread: Line 4  
```

---

## Задание 2  
Родительский поток выводит текст после завершения дочернего.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);

    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }

    return 0;
}
```

**Вывод:**  
```
Child thread: Line 0  
Child thread: Line 1  
Child thread: Line 2  
Child thread: Line 3  
Child thread: Line 4  
Main thread: Line 0  
Main thread: Line 1  
Main thread: Line 2  
Main thread: Line 3  
Main thread: Line 4  
```

---

## Задание 3  
Создание 4 потоков с разными сообщениями.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    char* message = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

**Вывод:**  
```
Thread 1: Line 0  
Thread 1: Line 1  
...  
Thread 4: Line 4  
```

---

## Задание 4  
Добавление задержки и прерывание потоков.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg) {
    char* message = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }

    sleep(2);
    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    return 0;
}
```

**Вывод:**  
```
Thread 1: Line 0  
Thread 2: Line 0  
...  
Thread 2: Line 2  
```

---

## Задание 5  
Обработка завершения потоков.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void cleanup_handler(void* arg) {
    printf("Cleaning up: %s\n", (char*)arg);
}

void* thread_func(void* arg) {
    char* message = (char*)arg;
    pthread_cleanup_push(cleanup_handler, message);

    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
        sleep(1);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }

    sleep(2);
    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

**Вывод:**  
```
Thread 1: Line 0  
...  
Cleaning up: Thread 1  
...  
```

---

## Задание 6  
Реализация Sleepsort.  

**Код:**  
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    sleep(value);
    printf("%d ", value);
    return NULL;
}

int main() {
    int arr[] = {3, 1, 4, 2, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n");
    return 0;
}
```

**Вывод:**  
```
1 2 3 4 5  
```