'use strict';

// let StringHelper = require('./StringHelper')
import StringHelper from './StringHelper.mjs';

let code = (str, shift) => StringHelper.sentenceShift(str, shift);
let decode = (str, shift) => StringHelper.sentenceShift(str, -shift);

let CODE = (str, shift) => code(str, shift).toUpperCase();
let DECODE = (str, shift) => decode(str, shift).toUpperCase();

let rot13 = str => code(str, 13);

const CaesarCode = {
    code: code,
    decode: decode,
    CODE: CODE,
    DECODE: DECODE,
    rot13: rot13
}
export default CaesarCode;