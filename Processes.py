from multiprocessing import Process, Value, Array, Queue, Semaphore
from time import sleep

def add(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.acquire()
        print('add')
        num.value += value
        tmp = num.value
        sleep(1)
        if tmp != num.value:
            print("Process conflict")
        semaphore.release()


def sub(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.acquire()
        print('sub')
        num.value += value
        tmp = num.value
        sleep(1.5)
        if tmp != num.value:
            print("Process conflict")
        semaphore.release()

def mul(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.acquire()
        print('mul')
        num.value *= value
        tmp = num.value
        sleep(2)
        if tmp != num.value:
            print("Process conflict")
        semaphore.release()

def div(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.acquire()
        print('div')
        num.value /= value
        tmp = num.value
        sleep(3)
        if tmp != num.value:
            print("Process conflict")
        semaphore.release()

def Show(semaphore, num):
    while True:
        semaphore.acquire()
        sleep(0.5)
        print(num.value)
        semaphore.release()