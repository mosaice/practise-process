function streamCar (s) {
  return s[0];
}

function streamCdr (s) {
  return s[1]();
}

function streamNull(s) {
  return s.length === 0;
}

function consStream(a, b) {
  return [a, () => b];
}

function streamRef (s, n) {
  return n === 0 ? streamCar(s) : streamRef(streamCdr(s), --n);
}

function streamMap(proc, s) {
  return streamNull(s) ? [] : consStream(proc(streamCar(s)), streamMap(proc, streamCdr(s)))
}

function streamForEach(proc, s) {
  return streamNull(s) ? null : consStream(proc(streamCar(s)), streamForEach(proc, streamCdr(s)))  
}

function streamEnumerateInterval(low, high) {
  if (low > high) return [];
  return consStream(low, streamEnumerateInterval(low + 1, high))
}

streamForEach(console.log, streamEnumerateInterval(1, 1000));