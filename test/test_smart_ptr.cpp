#include <gtest.h>
#include "smart_ptr.h"

TEST(SmartPointerTest, CreateAndDereference) {
    smart_ptr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
}

TEST(SmartPointerTest, CopyAndAccessValue) {
    smart_ptr<int> ptr1(new int(42));
    smart_ptr<int> ptr2 = ptr1;
    EXPECT_EQ(*ptr2, 42);
}

TEST(SmartPointerTest, CopyAndChangeValue) {
    smart_ptr<int> ptr1(new int(42));
    smart_ptr<int> ptr2 = ptr1;
    *ptr2 = 84;
    EXPECT_EQ(*ptr1, 84);
}

class MyClass {
public:
    int value;
    MyClass(int val) : value(val) {}
};

TEST(SmartPointerTest, AccessMemberFunction) {
    smart_ptr<MyClass> ptr(new MyClass(42));
    EXPECT_EQ(ptr->value, 42);
}

TEST(SmartPointerTest, AccessMemberFunctionWithCopiedPointer) {
    smart_ptr<MyClass> ptr1(new MyClass(42));
    smart_ptr<MyClass> ptr2 = ptr1;
    EXPECT_EQ(ptr2->value, 42);
}

TEST(SmartPointerTest, NullPointerDereferenceWarning) {
    smart_ptr<int> ptr;
    EXPECT_THROW(*ptr,std::logic_error);
}

TEST(SmartPointerTest, NullPointerMemberAccessWarning) {
    smart_ptr<MyClass> ptr;
    EXPECT_THROW(ptr->value,std::logic_error);
}