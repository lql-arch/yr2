//import java.util.concurrent.locks.Lock;
//import java.util.concurrent.locks.ReentrantLock;
//
//public class ThreadDemo {
//    int count = 0; // 记录方法的命中次数
//    public synchronized void threadMethod(int j) {
//         count++ ;
//         int i = 1;
//         j = j + i;
//    }
//
//    public static void main(String... args)
//    {
//
//    }
//
//    private Lock lock = new ReentrantLock();
//    // ReentrantLock是Lock的子类
//    private void method(Thread thread){
//        lock.lock(); // 获取锁对象
//        try {
//            System.out.println("线程名："+thread.getName() + "获得了锁");
//            Thread.sleep(2000);
//        }catch(Exception e){
//            e.printStackTrace();
//        } finally {
//            System.out.println("线程名："+thread.getName() + "释放了锁");
//            lock.unlock(); // 释放锁对象
//        }
//    }
//
////    private void method(Thread thread){
////        lock.lock(); // 获取锁对象
////        if (lock.tryLock()) {
////            try {
////                System.out.println("线程名："+thread.getName() + "获得了锁");
////                Thread.sleep(2000);
////            }catch(Exception e){
////                e.printStackTrace();
////            } finally {
////                System.out.println("线程名："+thread.getName() + "释放了锁");
////                lock.unlock(); // 释放锁对象
////            }
////        }
////    }
//
//    public static <LockTest> void main(String[] args) {
//        LockTest lockTest = new LockTest();
//        // 线程1
//             Thread t1 = new Thread(new Runnable() {
//                 @Override
//             public void run() {
//                 Thread.currentThread();  //返回当前线程的引用
//                 lockTest.method(Thread.currentThread());
//                }
//                },
//                    "t1");
//         //线程2
//         Thread t2 = new Thread(new Runnable() {
//             @Override
//             public void run() {
//             lockTest.method(Thread.currentThread());
//             }
//         },
//             "t2");
//             t1.start();
//             t2.start();
//         }
//    }
//}
