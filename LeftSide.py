from multiprocessing import Process, Queue, Value,Array, Semaphore
from time import sleep
from Car import Car



def producer(sem, queue, id,):
    print('Producer: Running', flush=True)
    while True:
        sem.wait(0)
        value = Car(id.value)
        id.value += 1
        sleep(1)
        queue.put(value)
        sem.signal()


def consumer(sem, queue, street):
    print('Consumer: Running', flush=True)
    while True:
        sem.wait(0)
        item = queue.get()     
        street.value = item.id
        print('car id: ', item.id, 'sleep: ', item.time)
        temp = street.value
        sleep(item.time)
        if temp != street.value:
            print('Process conflict!')
        sem.signal()
