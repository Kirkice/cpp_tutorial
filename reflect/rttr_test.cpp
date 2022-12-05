//
// Created by Administrator on 2022/12/5.
//
#include <iostream>
#include<rttr/type>
#include <rttr/registration>
using namespace rttr;

class MyStruct
{

public:
    MyStruct()
    {

    };

    void func(double a)
    {
        printf("a = %f\n", a);
    };

    int data;
RTTR_ENABLE()
};

class TestA : public MyStruct
{

public:
    TestA()
    {

    }

RTTR_ENABLE(MyStruct)
};

class TestB : public TestA
{

public:
    TestB()
    {

    }

RTTR_ENABLE(TestA)
};

//手动注册属性方法和构造函数
RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
            .constructor<>()
            .property("adata", &MyStruct::data)
                    (
                            metadata("TOOL_TIP", "1121`Set the name of node."),
                            metadata("TOOL_TIP1", "1121`Set the name of node.")
                    )
            .method("func", &MyStruct::func);

    registration::class_<TestA>("TestA")
            .constructor<>();

    registration::class_<TestB>("TestB")
            .constructor<>();
}

int main() {

    //遍历类的成员
    type t = type::get<MyStruct>();
    for (auto& prop : t.get_properties())
        std::cout << "name: " << prop.get_name() << std::endl;

    for (auto& meth : t.get_methods())
        std::cout << "name: " << meth.get_name() << std::endl;

    //创建类型的实例
    type t2 = type::get_by_name("MyStruct");
    variant var = t2.create();    // 方式1

    constructor ctor = t2.get_constructor();  // 方式2
    var = ctor.invoke();
    std::cout << "112= " << var.get_type().get_name() << std::endl;  // 打印类型名称

    //设置/获取属性
    MyStruct obj;

    property prop = type::get(obj).get_property("adata");
    prop.set_value(obj, 23);

    variant var_prop = prop.get_value(obj);

    std::cout << "metadata= " << prop.get_metadata("TOOL_TIP").to_string() << std::endl; // prints '23'
    std::cout << "1srfwe44= "<< prop.get_type().get_name() << std::endl; // prints '23'

    //调用方法
    MyStruct obj2;

    method meth = type::get(obj2).get_method("func");
    meth.invoke(obj2, 42.0);

    type a = type::get(obj2);
    variant var2 = a.create();
    meth.invoke(var2, 42.0);

    type b = type::get<TestB>();
    std::cout<<"b name is" << b.get_name()<<std::endl;
    array_range<type> baseClasses = b.get_base_classes();

    if (t.is_base_of(a))
    {
        printf("1111111111111111\n");
    }

    for (auto &baseclass : baseClasses)
    {
        std::cout<<"base class name is" << baseclass.get_name()<<std::endl;
    }

    auto ss = &MyStruct::data;

    std::cout << "fsdd11111= " << typeid(a).name() << std::endl; // prints '23'
    MyStruct aassdd;
    type cc = type::get(aassdd);
    std::cout << "aassdd= " << cc.get_name() << std::endl; // prints '23'
    system("pause");
    return 0;
}