const crypto = require('crypto-js');
var hash = crypto.createHash('sha256');
var code = 'bacon';
console.log(code);
code = hash.update(code);
console.log(code);
code = hash.digest(code);
console.log(code);
//import sha256 from 'crypto-js/sha256';