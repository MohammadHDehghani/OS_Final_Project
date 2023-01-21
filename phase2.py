from multiprocessing import Process, Queue, Value, Semaphore
import  RightSide, LeftSide



def main():
    sem1 = Semaphore(1)
    sem2 = Semaphore(1)
    street = Value('d',0)
    id = Value('d',1)
    
    car_list1 = Queue(maxsize=10)
    car_list2 = Queue(maxsize=10)


    prod1 = Process(target=RightSide.producer, args=(sem1, car_list1, id))
    cons1 = Process(target=RightSide.consumer, args=(sem2, car_list1, street))
    prod1.start()
    cons1.start()


    prod2 = Process(target=LeftSide.producer, args=(sem1, car_list2, id))
    cons2 = Process(target=LeftSide.consumer, args=(sem2, car_list2, street))
    prod2.start()
    cons2.start()




if __name__ == '__main__':
    main()