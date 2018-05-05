function* steam(iter, initValue, endValue, endIndex) {
  let index = 0;
  let value = initValue || index;
  if (!endValue && !endIndex) throw 'need a board';
  
  const endCondition = () => endValue ? endValue !== value : endIndex !== index;
  while (endCondition()) {
    yield value;
    value = iter(value, index++);
  }
}


function steamMap(steam, func) {
  let index = 0;
  for(let v of steam) {
    func(v, index++);
  }
}

const s = steam((p, i) => i, 0, undefined, 1000000000);

steamMap(s, console.log);


