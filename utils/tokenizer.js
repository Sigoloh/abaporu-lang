export function tokenize(content){
  let result = content.replace(/(\*.+)|(\|[\s\w#!@#$%¨&*()_\-+=]+\|)/gm, '')
    .replace(/\s+/gm, '').toUpperCase();
  result = result.match(/\#\w{6}/gm);
  return result;
}
