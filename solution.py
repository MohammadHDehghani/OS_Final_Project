from multiprocessing import Process, Value, Array, Queue, Semaphore
from time import sleep
from Processes import *

if __name__ == '__main__':
    semaphore = Semaphore(1)
    num = Value('d', 0.0)
    arr = Array('i', range(2))
    q = Queue()
    p1 = Process(target=add, args=(semaphore, num, 10))
    p2 = Process(target=sub, args=(semaphore, num, 5))
    p3 = Process(target=mul, args=(semaphore, num, 2))
    p4 = Process(target=div, args=(semaphore, num, 4))

    show = Process(target=Show, args=(semaphore, num,))
    show.start()
    sleep(1)
    
    p1.start()
    p2.start()
    p3.start()
    p4.start()

