import fs from 'fs';
export function tokenize(content){
  let result = content.replace(/(\*.+)|(\|[\s\w#!@#$%¨&*()_\-+=]+\|)/gm, '')
    .replace(/\s+/gm, '').toUpperCase();
  result = result.match(/\#\w{6}/gm);
  fs.writeFileSync('./tests/teste.tx', result.join('\n'))
  return result;
}
