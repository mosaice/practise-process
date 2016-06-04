var net = require('net');
var count = 0;
var users = {};

var server = net.createServer(function (conn) {
  var nickName;
  conn.setEncoding('utf8');
  conn.write('欢迎来到聊天室\n');
  conn.write('共有' + count + '位其他用户在线\n');
  conn.write('请输入你的用户名,回车确认:');
  count++;

  conn.on('close', function () {
    count--;
    delete users[nickName];
    broadcast(nickName + '离开了聊天室\n');
  });

  conn.on('data', function (data) {
    data = data.replace('\r\n', '');
    if (!nickName) {
      nickName = data;
      users[nickName] = conn;
      broadcast(nickName + '加入聊天室\n');
      return;
    }
    broadcast(nickName + '说:' + data + '\n', true);
  });

  function broadcast(msg, includeSelf) {
    Object.keys(users).forEach(function (name) {
      if (includeSelf || name !== nickName) users[name].write(msg);
    });
  }
});

server.listen(3000, function () {
  console.log('server listen on :3000');
});
