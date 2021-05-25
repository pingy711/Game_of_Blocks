console.time("executionTime");
var crypto = require('crypto');
const { EOF } = require('dns');
const { exit } = require('process');
var code = process.argv[2];
var i = 3;
while(process.argv[i]!=null){
    code = code + ' ';
    code = code.concat(process.argv[i]);++i;}
console.log(code);
var x = 2;
{
    const hash_0 = crypto.createHash('sha256').update(code).digest('hex');
    if(hash_0 <='0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF')
        {
            console.log(code);
            console.log('Nothing to be appended');
            return ;
        }
}
code = code.concat(String(1));
while(true)
{
    //const hash = crypto.createHash('sha256');                         //initially written,does not give 'hash' as hexadecimal but returns as an object
    //var code_hashed = hash.update(code);                              //initially written,does not give 'hash' as hexadecimal but returns as an object
    //code_hashed = hash.digest(code_hashed);                           //initially written,does not give 'hash' as hexadecimal but returns as an object
    const hash = crypto.createHash('sha256').update(code).digest('hex');
    var temp = String(hash).slice(0,-59);
    if(temp=='00000')
        {                                                                       
            console.log(hash);
            console.log(x-1);
            console.timeEnd("executionTime");
            return ;
        }
   // console.log(Math.floor(Math.log10(x-1))+1);               //used while debugging
    code = code.slice(0,-(Math.floor(Math.log10(x-1))+1));                //removes the concatenated x-1 from 'code'
    //console.log(code);                                    //used while debugging
    code = code.concat(String(x));                                        //appends x to 'code'
    //console.log(code);                        //used while debugging
    //console.log(x);                          //used while debugging
    //console.log(hash);                       //used while debugging
    //console.log('\n');                       //used while debugging
    x++;                   
}
//const end_time = window.performance.now();
//console.log(end_time-start_time);