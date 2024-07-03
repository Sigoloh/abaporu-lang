import fs from 'fs';
import path from 'path';
export function generateImage(tokens, outputPath){
  try {
    const head = `
      <html>
        <head>
          <title>Awesome Art!</title>
        </head>
        <body>
    `

    let body = '';

    const tail = `</body></html>`

    const artSize = Math.round(parseInt(Math.sqrt(tokens.length)))

    const canvaMatrix = [[]];

    const templateDiv = `
      <div style="height: 10px; width: 10px; background-color: {{color}}"></div>
    `
    let lineIndex = 0;
    let count = 0;
    for(let i = 0; i < tokens.length; i++){
      canvaMatrix[lineIndex].push(tokens[i]);
      if(i % artSize === 0 && i !== 1 && i !== 0){
        canvaMatrix.push([])
        lineIndex++;
      }
    }

    for(let i = 0; i < artSize; i++){
      body += '<div style="display: flex; flex-direction: row">'
      for(let k = 0; k < artSize; k++){
        if(canvaMatrix[i]){
          if(canvaMatrix[i][k]){
            body += templateDiv.replace("{{color}}", canvaMatrix[i][k])
          }
        }else{
          body += `<div style="height: 10px; width: 10px">-</div>`
        }
      }
      body += '</div>'
    }
    const document = head + body + tail;
    fs.writeFileSync(
      outputPath.endsWith('.html') ? outputPath : outputPath + '.html'
      , document)
    const savedIn = path.resolve(outputPath.endsWith('.html') ? outputPath : outputPath + '.html');
    console.log('Your art is ready. Click in the link bellow to see it!')
    console.log('file://'+savedIn);
  } catch (error) {
    console.log(error);
  }
}
