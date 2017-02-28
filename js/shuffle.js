var readline = require('readline');

var rl = readline.createInterface({input: process.stdin, output: process.stdout, terminal: false});

var start = 0;
var array = [];

rl.setPrompt('shuffle>');
rl.prompt();

const compose = (...funcs) => {
  if (funcs.length === 0) {
    return arg => arg
  }

  if (funcs.length === 1) {
    return funcs[0]
  }

  return funcs.reduce((a, b) => (...args) => a(b(...args)))
}

const shuffle = times => {
  if (!times)
    return array;
  const cards = times > 1
    ? shuffle(times - 1)
    : array;
  const left = cards.slice(0, cards.length / 2).reverse();
  const right = cards.slice(cards.length / 2).reverse();
  const result = [];

  left.forEach((item, index) => {
    result.push(right[index]);
    result.push(item);
  });
  result.reverse();
  console.log(`before ${times} shuffle, array is ${cards}`);
  console.log(`after ${times} shuffle, array is ${result}`);
  return result;
}

const composeShuffle = array => {
  const left = array.slice(0, array.length / 2).reverse();
  const right = array.slice(array.length / 2).reverse();
  const result = [];
  left.forEach((item, index) => {
    result.push(right[index]);
    result.push(item);
  });
  result.reverse();
  return result;
}

const reduceShuffle = time => Array(+ time).fill(composeShuffle);

const tryInput = () => {
  rl.question('input your numbers length must be even, split by space\n', answer => {
    if (!start) {
      array = answer.trim().split(' ');
      if (array.length % 2) {
        console.log('sorry length must be even, try it again');
        return tryInput();
      }
      start = 1;
      inputTimes();
    }
    //不加close，则不会结束
  });
};

const inputTimes = () => {
  rl.question('input your times: ', answer => {
    if (!start || answer < 0) {
      console.log('sorry error!');
      process.exit(0);
    }
    // const result = shuffle(answer);
    const result = compose(...reduceShuffle(answer))(array);
    console.log(reduceShuffle(answer));
    console.log(`last result ${result}`);
    process.exit(0);
  });
}


tryInput();
