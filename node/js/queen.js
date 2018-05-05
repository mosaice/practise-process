//借助debugger能够非常清晰地看到跳转的过程！

var n = 8;
var arr = [];
var str = "";
function queen(index) {
  if (index === n) {
    str += arr;//每次完成一种情况，输出数组；
    str += "  "//空格隔离
  } else {
    for (var i = 0; i < n; ++i) {
      arr[index] = i;//为第一行的皇后寻找位置，从0开始，直到7
      var flag = true;//这里主要是为判定可攻击性提供一个开关，如果在攻击范围内
      // 则不进入下一列，继续向下寻找，如果找到了合适的位置，则进入下一行
      for (var j = 0; j < index; ++j) {
        //这里是为了判定攻击范围，把所有已经放置的皇后与当前放置的皇后做位置计算，如果在攻击范围内，flag为false，不在所有已经放置的皇后的攻击范围内，则不改变flag的属性：true
        if (arr[index] === arr[j]
          || arr[index] - arr[j] === j - index) {

          flag = false;
          break;
        };
      };
      if (flag) {//这里是根据flag的属性判定是否进入下一行的循环；
        queen(index + 1);
      }
    }
  }
};
queen(0);//从第0行进行试探
console.log(str)//输出拼接字符串所有情况
        //queen(0)===》思路：是从第一行开始放棋子， 每放一个就检查是否处于被攻击的范围，处于被攻击范围则向后移动一个，如果所在位置并不会被攻击到则进入到下一行，

//代码中已经标注了debugger的位置；