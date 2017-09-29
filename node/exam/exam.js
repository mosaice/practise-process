var fs = require('fs');
var stdin = process.stdin
var stdout = process.stdout
var exam = 0;
var answer;
var start = false;
var count = 0;
var error = [];
console.log('选择考试，1计算机，2数学');

stdin.resume();
stdin.setEncoding('utf8');

stdin.on('data', function (data) {
  var _data = data.trim();
  if (!start) {
    if (Number(_data) === 1) {
      exam = 1;
      stdin.pause();
      return startExam();
    }
    if (Number(_data) === 2) {
      exam = 2;
      stdin.pause();
      return startExam();
    }
  } else {
    if (count < answer.length) {
      // console.log(_data === answer[count]);
      if (_data !== answer[count]) {
        error.push({
          index: count,
          value: _data
        });
      }
      count++;
      stdout.write('第' + (count + 1) + '题');
    } else {
      console.log('一共' + answer.length + '题，错误' + error.length + '题');
      error.forEach(function (item) {
        console.log('第' + (item.index + 1) + '题，正确答案' + answer[item.index] + '，我的答案' + item.value);
      });
      process.exit(1);
    }
  }

});

function startExam() {
  fs.readFile(exam + '.txt', 'utf8', function (err, data) {
    if (err) console.log(err);
    var _answer = data.replace(/,/g, '').replace(/\n/g, ',').split(',');
    answer = _answer.filter(function (item) {
      return !!item;
    });
    start = true;
    console.log('开始输入答案回车确认');
    stdout.write('第' + (count + 1) + '题');
    stdin.resume();
  });
}
