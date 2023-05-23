#include <gtest/gtest.h>
#include <threadpool.hpp>



static std::mutex strlock;
void func(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
void func2(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 2 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
void func3(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 3 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));

}
int func4(const int& time, const std::string& str ) {
    std::scoped_lock lock(strlock);
    std::cout << "Executing this thread 3 " << str << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(time));
    return 100;
}


TEST(TestThreadpool, TestSpeed) {
    Threadpool tp(5);
    std::string str("Nam ");
    int num = 1;

    for (int i = 0; i<10; i++) {
        tp.submitWork(func, std::move(num), std::move(str));
    }
    
    auto obj = tp.submitWork(func4, std::move(num-3), std::move(str));
    
    obj.wait();
    auto val = obj.get();
    std::cout << "The value retuned is "<< val << "\n";
    ASSERT_EQ(val,100);
}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
