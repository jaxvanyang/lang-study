const A = 65, Z = 90, a = 97, z = 122;

let isChar = char => typeof char === 'string' && char.length == 1;

let isUpper = char => {
    let code = char.charCodeAt(0);
    return isChar(char) && A <= code && code <= Z;
}

let isLower = char => {
    let code = char.charCodeAt(0);
    return isChar(char) && a <= code && code <= z;
}

let isLetter = char => isUpper(char) || isLower(char);
let isNotLetter = char => !isLetter(char);

function charShift(char, shift = 0) {
    if (!isChar(char)) return ' ';
    return String.fromCharCode(char.charCodeAt(0) + shift)
}

let letterShift = (char, shift = 0) => {
    if (!isChar(char)) return ' ';
    // console.log(char)
    if (isNotLetter(char)) return char;
    shift = (shift % 26 + 26) % 26;
    let code = char.charCodeAt(0);
    if ((isUpper(char) && code + shift > Z) || (isLower(char) && code + shift > z)) {
        shift -= 26;
    }
    return charShift(char, shift);
}

let stringShift = (str, shift = 0) => str.split('').map(ch => charShift(ch, shift)).join('');
let sentenceShift = (str, shift = 0) => str.split('').map(ch => letterShift(ch, shift)).join('');

const StringHelper = {
    isChar: isChar,
    isUpper: isUpper,
    isLower: isLower,
    isLetter: isLetter,
    isNotLetter: isNotLetter,
    charShift: charShift,
    letterShift: letterShift,
    stringShift: stringShift,
    sentenceShift: sentenceShift,
}
export default StringHelper;