var http = require('http');
var qs = require('querystring');

function sendName(theName) {
  http.request({
    host: '127.0.0.1',
    port: 3000,
    method: 'POST'
  }, function (res) {
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
      console.log(chunk);
    });

    res.on('end', function () {
      console.log('request complete!');
      process.stdout.write('your name:');
    });
  }).end(qs.stringify({name: theName}));
}

process.stdout.write('your name:');
process.stdin.resume();
process.stdin.setEncoding('utf8');

process.stdin.on('data', function (name) {
  sendName(name.replace('\n', ''));
});
