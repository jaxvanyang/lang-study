# Java 学习笔记

## Java 命令行备忘
1. 启用断言：`-enableassertions`，简写 `-ea`  

## 数据类型

### 基本数据类型

### 抽象数据类型（ADT）

1. 背包（Bag）
    API：  
    ```java
    public class Bag<Item> implements Iterable<Item>
                Bag()                        创建一个空背包
        void   add(Item item)               添加一个元素
    boolean   isEmpty()                    背包是否为空
        int   size()                       背包中的元素数量
    ```

2. 队列（Queue）  
    实现队列的最好方式是链表  

3. 栈（Stack）  
    实现栈的最好方式是也链表  
    1. 通过删除表头实现 `pop()`  
    2. 通过插入表头实现 `push()`

## Java 特性

### 泛型
泛型类的定义例如：  
```java
public class Bag<Item> {
    // Defination
}
```

需要注意的是：Java 不允许创建泛型数组，即：  
```java
a = new Item[cap];      // 错误
```
需要使用类型转换：  
```java
a = (Item[]) new Object[cap];
```

### 迭代
如果集合是可迭代的，那么就可以使用 `for each` 语句。  

任何一个可迭代的集合类型都需要满足以下两点：  
1. 实现 `iterator()` 方法并返回一个 `Iterator` 对象  
2. `Iterator` 类必须包含两个方法：`hasNext()` 和 `next()`  

实现一个可迭代类型的步骤：  
1. 在声明中加入 `implements Iterable<Item>`  
2. 定义 `iterator()` 方法  
3. 定义 `Iterator<item>` 类，推荐使用嵌套类实现  
4. 在开头加入 `import java.util.Iterator`  

### 自动装箱 & 自动拆箱
例如：  
```java
Stack<Integer> stack = new Stack<Integer>();
stack.push(17);       // 自动装箱（int -> Integer）
int i = stack.pop();  // 自动拆箱（Integer -> int）
```

### 嵌套类
嵌套类可以访问包含它的类的实例变量
## 程序设计

### 契约式设计
1. 异常（Exception）：用于处理不受我们控制的不可预见的错误  
    最简单的异常 `RuntimeException`：
    ```java
    throw new RuntimeException("Error message here.");
    ```


2. 断言（Assertion）：验证我们在代码中做出的一些假设  
    断言默认是关闭的，需要在命令行下启用 `-enableassertions`，简写为 `-ea`  
    例如：  
    ```java
    // 冒号后是可选的错误信息
    assert index >= 0 : "Negative index in method X";
    ```

### 数据抽象的步骤
1. 定义 API  
2. 根据特定的应用场景开发用例代码  
3. 描述一种数据结构（一组值的表示），并在 API 所对应的抽象数据类型的实现中根据它定义类的实例变量  
4. 描述算法（实现一组操作的方式），并根据它实现类中的实例方法  
5. 分析算法的性能特点  

## 问题
1. 类型转换如何检查，例如：  
    ```java
    // 会报错："Type safety: Unchecked cast from Object[] to Item[]"
    Item[] arr = (Item[]) Object[cap];
    ```

## 算法分析
1. 获取程序运行时间可使用：  
    ```java
    System.currentTimeMillis(); // 返回
    ```

## 设计算法的基本步骤
1. 完整而详细地定义问题，找出解决问题所必需的基本抽象操作并定义一份 API。  

2. 简洁地实现一种初级算法，给出一个精心组织的开发用例并使用实际数据作为输入。  

3. 当`实现`所能解决的问题的最大规模达不到期望时决定改进还是放弃。  

4. 逐步改进`实现`，通过经验性分析或（和）数学分析验证改进后的效果。  

5. 用更高层次的抽象表示数据结构或算法来设计更高级的改进版本。  

6. 如果可能，尽量为最坏情况下的性能提供保证，但在处理普通数据时也要有良好的性能。  

7. 在适当的时候将更细致的深入研究留给有经验的研究者并继续解决下一个问题。  