var http = require('http');
var qs = require('querystring');

http.createServer(function (req, res) {
  var body = '';
  req.setEncoding('utf8');
  req.on('data', function (chunk) {
    body += chunk;
  });

  req.on('end', function () {
    res.writeHead(200);
    res.end('done');
    console.log('get  ' + qs.parse(body).name);
  });
}).listen(3000, function () {
  console.log('listen on: 3000');
});
