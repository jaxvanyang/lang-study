'use strict';

// let CaesarCode = require('./CaesarCode.mjs');
import CaesarCode from './CaesarCode.mjs';

const getInput = prompt => window.prompt(prompt)
const output = (prompt, msg) => window.alert(prompt + msg)


function code() {
    const msg = getInput('请输入要加密的原文：');
    const shift = getInput('请输入加密位移：');
    const code = CaesarCode.code(msg, shift);
    output('加密后的密文是：', code);
}

function decode() {
    const code = getInput('请输入要解密的密文：');
    const shift = getInput('请输入加密位移（注意是加密时使用的）：');
    const msg = CaesarCode.decode(code, shift);
    output('解密后的原文是', msg);
}

function tryDecode() {
    const code = getInput('请输入要解密的密文：');
    let shift = 0;
    while (true) {
        let msg = CaesarCode.decode(code, shift);
        const input = getInput(`当前猜测的原文是：${msg}\n加密位移是：${shift}\n猜对了吗？\n正确输入：Y；错误输入：N`);
        if (input === 'Y') {
            output(`加密位移是：${shift}\n解密的原文是：`, msg);
            break;
        }
        shift = (shift + 1) % 26;
    }
}

function launchMenu() {
    let selection = 1;
    while (true) {
        selection = getInput('请输入数字选择：\n1：加密原文；2：解密密文；3：尝试解密密文');
        if (selection === '1') {
            code();
        } else if (selection === '2') {
            decode();
        } else {
            tryDecode();
        }
        let wantQuit = getInput('现在退出🏇？\nY：EXIT；N：再玩亿次')
        if (wantQuit === 'Y') break;
    }
}

const CaesarCodeApp = {
    getInput: getInput,
    output: output,
    code: code,
    decode: decode,
    tryDecode: tryDecode,
    launchMenu: launchMenu,
}
export default CaesarCodeApp;