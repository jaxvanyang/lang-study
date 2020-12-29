'use strict';

var msg = 'Hello';

function greet(name) {
    console.log(`${msg}，${name}`)
}

module.exports = {
    msg: msg,       // 暴露变量
    greet: greet,   // 暴露函数
}