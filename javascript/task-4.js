/** 变量
 * 1. JS 是动态语言，变量可以改变类型；也是弱类型语言，变量可以自动改变类型
 * 2. 基本类型有：String，Number，Boolean，null，undefined
 *    封装类型有：Array，Object
 * 3. JS 基本类型按值传递，对象按共享传递
 * 4. 时间类型用 `new Date()` 构造，不加 `new` 只会返回字符串
 */

const dateStr = Date();
let date = new Date();
console.log(dateStr, date);
console.clear();

// // 用时间戳初始化一个日期
// date = new Date(24 * 3600 * 1000);
// console.log(date);

// date = new Date('2020-10-24 12:00:00.123');
// console.log(date);

// date = new Date(2020, 11, 30);  // 月份从 0 开始
// console.log(date);

// console.log(Date.now());    // 返回自 UTC 至今经过的毫秒数
// console.log(Date.parse('2014-10')); // 也是返回毫秒数
// console.log(Date.UTC(2014, 12, 9)); // 同上

// console.log(date)
// // 都是根据本地时间来的
// console.log(date.getDate()) // 返回月份中的天数
// console.log(date.getDay())  // 返回星期中的天数
// console.log(date.getFullYear())
// console.log(date.getTime()) // 返回自 UTC 以来的毫秒数
// console.log(date.getTimezoneOffset())   // 返回当前时区的时区偏移
// // 根据世界时
// console.log(date.getUTCDate())

// // Conversion getter
// console.log(date.toDateString())
// console.log(date.toISOString())
// console.log(typeof date.toJSON())   // 同上
// console.log(date.toUTCString())
// console.log(date.toGMTString())  // 同上

// const options = {weekday: 'long', year: 'numeric', month: 'numeric'}
// console.log(date.toLocaleDateString(undefined, options))
// console.log(new Intl.DateTimeFormat('zh-CN', options).format(date))

// const re = /[Hh]ello/g
// const hello = 'Hellohello'
// console.log(re.test('HHHhello'));
// console.log(re.exec(hello))
// console.log(hello.match(re))
// console.log(hello.replace('l', 'L'))
// console.log(hello.replace(/l/gi, 'L'))

// const p = 'The dog dog dog '
// const regex = /dog/gi;
// console.log(p.replace(regex, 'Jax'))

// const msg = 'Hello Steve, Hello Alex,Hello, Minecraft'
// const words = msg.split(/, | |,/g)  // 正则表达式作为分隔符会忽略 g flag
// const items = msg.split(/Hello[ ,]| |,/)
// console.log(words)
// console.log(items)
// const msg = 'Hello Steve, Hello Alex,Hello, Minecraft'
// const words = msg.split(/, | |,/g)  // 正则表达式作为分隔符会忽略 g flag
// const items = msg.split(/Hello[ ,]| |,/)
// console.log(words)
// console.log(items)

/** 容器对象
 * 1. 种类：Array，Object
 * 2. 遍历：for of XXX
 * 3. 数组是浅复制，对象是深复制（大概）
 * 4. 序列化使用 JSON.stringify()；反序列化使用 JSON.parse()
 * 5. reverse(), pop(), shift()...
 */

// const arr = [1, 2, 3, 4, 5, {isCool: true, hasMoney: false}]
// for (each of arr) {
//     console.log(each)
// }
// const copy = arr
// const flags = arr[arr.length - 1]
// arr[arr.length - 1] = null
// console.log(flags)
// arr.pop()
// console.log(copy)
// arr.pop()
// console.log(copy);
// console.log(flags)

// class Bag {
//     constructor() {
//         this.items = ['Sword', 'Axel']
//         this.weight = 2
//     }
// }
// class Player {
//     constructor(id = '000000', bag = new Bag(), level = 0) {
//         this.id = id
//         this.bag = bag
//         this.level = level
//     }
// }

// const steve = new Player()
// console.log(steve)

// const steveJSON = JSON.stringify(steve)
// console.log(steveJSON)
// const steveParse = JSON.parse(steveJSON)
// console.log(steveParse.bag.items)

/** 抽象
 * 1. 函数使用 function 定义，也可以用箭头函数
 * 2. 有默认参数；计划在 ES7 中加入运算符重载；默认没有函数重载，但可以使用剩余参数
 * 3. 可面向对象
 * 4. 接口，不需要提前声明
 * 5. 设计模式待学
 */

// function square(number) {
//     return number * number;
// }

// s1 = number => number * number;
// console.log(s1(2))
// console.log(number => number * number * number)

// function sum(...nums) {
//     return nums.reduce((cureent, previous) => cureent + previous)
// }

// console.log(sum(1, 2, 3, 4))

// function sum(a, b) {
//     return a + b
// }

/** 函数式编程
 * 高阶函数，箭头函数
 * 支持链式语法，模块由闭包实现
 */