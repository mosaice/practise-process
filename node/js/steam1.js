/*
 * 本例子来自sicp中流例子的改写，原书采用scheme做为教材语言
 * 其中 cons 是一种 复合数据格式， 为了简化理解 可以认为 cons = [a, b]; 的存储结构
 * 对 cons 流化的思路是将 cons 的第二个值改写为函数
 * scheme 中没有循环体结构， 一切循环操作会转换成递归模式
 */

// 获取cons流的第一个元素
function streamCar(s) {
  return s[0];
}
// 获取cons流的第二个元素
function streamCdr(s) {
  return s[1]();
}

// 流判空
function streamNull(s) {
  return s.length === 0;
}

// 创建流
function consStream(a, b) {
  return [a, () => b];
}

function streamRef (s, n) {
  return n === 0 ? streamCar(s) : streamRef(streamCdr(s), --n);
}

// Map 联想Array.prototype.map
function streamMap(proc, s) {
  return streamNull(s)
    ? []
    : consStream(proc(streamCar(s)), streamMap(proc, streamCdr(s)));
}
// ForEach 联想Array.prototype.forEach
function streamForEach(proc, s) {
  if (streamNull(s)) return null;
  proc(streamCar(s));
  streamForEach(proc, streamCdr(s));
}
// 一个有序的流创建方法
function streamEnumerateInterval(low, high) {
  if (low > high) return [];
  return consStream(low, streamEnumerateInterval(low + 1, high));
}

streamForEach(
  console.log,
  streamMap(x => x + 1, streamEnumerateInterval(1, 100))
);
