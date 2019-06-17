import threading
import sys
import time
count=0
curr_thread=threading.current_thread()
def update():
    global count
    while 1:
        count += 1
        # time.sleep(1)


def worker1():
    update()


def worker2():
    update()


def watcher():
    global count
    while 1:
        print("counter :",count)
        time.sleep(1)

def main():
    thread1=threading.Thread(target=worker1)
    thread2=threading.Thread(target=worker2)
    thread3=threading.Thread(target=watcher)
    thread1.start()
    thread2.start()
    thread3.start()

if __name__ == "__main__":
    main()