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
  store->Save("LoadTestKeyname", "Alice");
  ASSERT_EQ(store->Load("LoadTestKeyname"),
            "Alice"); // 断言能够加载"name"这个key
}

TEST_F(StoreTest, LoadByKeyTest) {
  // 使用ASSERT_EQ或ASSERT_NE来断言两个值是否相等或不等
  store->AddLabel("name", "LoadByKeyTest");
  ASSERT_EQ(store->LoadByLabel("LoadByKeyTest").size(),
            1); // 断言"name"这个key没有任何label
}

TEST_F(StoreTest, DelLabelTest) {
  // 使用ASSERT_TRUE或ASSERT_FALSE来断言一个条件是否为真或假
  store->Save("DelLabelTestname", "Alice");
  store->AddLabel("DelLabelTestname", "label1");
  ASSERT_TRUE(store->DelLabel("DelLabelTestname",
                              "label1")); // 断言能够删除"age"这个key的一个label
  ASSERT_EQ(store->LoadByLabel("DelLabelTestname").size(),
            0); // 断言"name"这个key没有任何label
  ASSERT_TRUE(store->DelLabel(
      "gender", "male")); // 断言不能删除"gender"这个key不存在的label
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}