export function processArgs(args){
  if(args.length === 0){
    console.log('Welcome to abaporu-lang');
    console.log('The goal with this language is to produce cools scripts using colors');
    console.log('To run your program you need to call the interpreter with some args:');
    console.log('-p <path-to-the-file>')
    console.log('-o <path-to-the-output-file>')
    console.log('--help to see this text again')
    throw new Error('Remember: you need to call the interpreter with input and output files set')
  }

  if(args.includes('--help')){
    console.log('Welcome to abaporu-lang');
    console.log('The goal with this language is to produce cools scripts using colors');
    console.log('To run your program you need to call the interpreter with some args:');
    console.log('-p <path-to-the-file>')
    console.log('-o <path-to-the-output-file>')
    console.log('--help to see this text again')
  }


  if(!args.includes('-o') || !args.includes('-p')){
    console.log('Welcome to abaporu-lang');
    console.log('The goal with this language is to produce cools scripts using colors');
    console.log('To run your program you need to call the interpreter with some args:');
    console.log('-p <path-to-the-file>')
    console.log('-o <path-to-the-output-file>')
    console.log('--help to see this text again')
    throw new Error('Remember: you need to call the interpreter with input and output files set')
  }

  

  const organizedArgs = {
    outputPath: '',
    inputFile: '',
  }

  const inputFilePathIndex = args.indexOf('-p') + 1;
   
  const outputPathIndex = args.indexOf('-o') + 1;

  organizedArgs.inputFile = args[inputFilePathIndex];

  organizedArgs.outputPath = args[outputPathIndex]

  return organizedArgs;
}
