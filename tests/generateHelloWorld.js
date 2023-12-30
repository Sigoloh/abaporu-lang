import fs from 'fs';
let out = '';

// H
for(let i = 0; i < 72; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// e
for(let i = 0; i < 102; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// ll
for(let i = 0; i < 109; i++){
  out += '#FF0000';
}

out += '#FFFFFF#FFFFFF#00FF00'

// o
for(let i = 0; i < 112; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'


// <space>
for(let i = 0; i < 33; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// W
for(let i = 0; i < 88; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// o
for(let i = 0; i < 112; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// r
for(let i = 0; i < 115; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// l
for(let i = 0; i < 109; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// d
for(let i = 0; i < 101; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

// !
for(let i = 0; i < 34; i++){
  out += '#FF0000';
}

out += '#FFFFFF#00FF00'

fs.writeFileSync('./tests/HelloWorld.abapl', out);
