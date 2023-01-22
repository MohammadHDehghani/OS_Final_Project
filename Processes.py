from multiprocessing import Process, Value, Array, Queue, Semaphore
from time import sleep

def add(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.wait(0)
        print('add')
        num.value += value
        tmp = num.value
        sleep(1)
        if tmp != num.value:
            print("Process conflict")
        semaphore.signal()


def sub(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.wait(1)
        print('sub')
        num.value += value
        tmp = num.value
        sleep(1.5)
        if tmp != num.value:
            print("Process conflict")
        semaphore.signal()

def mul(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.wait(2)
        print('mul')
        num.value *= value
        tmp = num.value
        sleep(2)
        if tmp != num.value:
            print("Process conflict")
        semaphore.signal()

def div(semaphore, num, value):
    tmp = 0
    while True:
        semaphore.wait(3)
        print('div')
        num.value /= value
        tmp = num.value
        sleep(3)
        if tmp != num.value:
            print("Process conflict")
        semaphore.signal()

def Show(semaphore, num):
    while True:
        semaphore.wait(4)
        sleep(0.5)
        print(num.value)
        semaphore.signal()