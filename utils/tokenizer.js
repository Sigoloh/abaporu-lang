export function tokenize(content){
  const result = content.match(/\#\w{6}/gm);
  return result;
}
