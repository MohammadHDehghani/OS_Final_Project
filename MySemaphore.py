from multiprocessing import Value, Array, Queue

class Semaphore:
    def __init__(self, n : int) -> None:
        self.semaphore = Value('i', 1)
        self.flag_arr  = Array('i', range(5))
        self.queue     = Queue(n)
        for i in range(5):
            self.flag_arr[i] = 0
    
    def wait(self, pid : int):
        self.semaphore.value -= 1
        if self.semaphore.value < 0:
            self.flag_arr[pid] = 0
            self.queue.put(pid)
            while self.flag_arr[pid] == 0:
                continue

    def signal(self):
        self.semaphore.value += 1
        if self.semaphore.value <= 0:
            pid = self.queue.get()
            for i in range(5):
                if pid == i:
                    self.flag_arr[i] = 1
                    break