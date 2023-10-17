#include <gtest/gtest.h>

#include "jsonstore.h" // 包含你的store类的头文件

using namespace command;

// 定义一个测试夹具类，继承自::testing::Test
class StoreTest : public ::testing::Test {
protected:
  // 在每个测试之前执行
  void SetUp() override {
    // 创建一个store对象
    store = new Store("./store.json");
    // 设置一些初始的key和value
    store->Save("name", "Alice");
    store->Save("age", "25");
    store->Save("gender", "female");
  }

  // 在每个测试之后执行
  void TearDown() override {
    // 删除store对象
    delete store;
  }

  // 定义一个store指针
  Store *store;
};

// 使用TEST_F宏来定义一个测试用例，第一个参数是测试夹具类的名字，第二个参数是测试用例的名字
TEST_F(StoreTest, LoadTest) {
  // 使用ASSERT_TRUE或ASSERT_FALSE来断言一个条件是否为真或假
  ASSERT_EQ(store->Load("name"), "Alice");   // 断言能够加载"name"这个key
  ASSERT_EQ(store->Load("email"), ""); // 断言不能加载"email"这个key
}

TEST_F(StoreTest, LoadByKeyTest) {
  // 使用ASSERT_EQ或ASSERT_NE来断言两个值是否相等或不等
  ASSERT_EQ(store->LoadByKey("name").size(),
            0); // 断言"name"这个key没有任何label
  ASSERT_NE(store->LoadByKey("age").size(),
            1); // 断言"age"这个key有至少一个label
}

TEST_F(StoreTest, SaveTest) {
  // 使用ASSERT_TRUE或ASSERT_FALSE来断言一个条件是否为真或假
  ASSERT_TRUE(store->Save(
      "email", "alice@gmail.com")); // 断言能够保存"email"这个key和对应的value
  ASSERT_FALSE(store->Save("", "")); // 断言不能保存空的key和value
}

TEST_F(StoreTest, AddLabelTest) {
  // 使用ASSERT_TRUE或ASSERT_FALSE来断言一个条件是否为真或假
  ASSERT_TRUE(store->AddLabel(
      "name", "student")); // 断言能够给"name"这个key添加一个label
  ASSERT_FALSE(store->AddLabel(
      "email", "student")); // 断言不能给不存在的key添加一个label
}

TEST_F(StoreTest, DelLabelTest) {
  // 使用ASSERT_TRUE或ASSERT_FALSE来断言一个条件是否为真或假
  ASSERT_TRUE(
      store->DelLabel("age", "adult")); // 断言能够删除"age"这个key的一个label
  ASSERT_FALSE(store->DelLabel(
      "gender", "male")); // 断言不能删除"gender"这个key不存在的label
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}