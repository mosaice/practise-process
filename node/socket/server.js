var express = require('express');
var http = require('http');
var sio = require('socket.io');
var path = require('path');
var superagent = require('superagent');
var api = 'http://s.music.163.com/search/get/?type=1&s=';
var song = {};
var dj;

var app = express();

app.use(express.static(path.join(__dirname, 'public')));

var server = http.createServer(app).listen(3000, '0.0.0.0');
var io = sio(server);

function elect(socket) {
  dj = socket;
  io.sockets.emit('notification', dj.name + ' is the new dj');
  io.sockets.emit('elected', '当前dj ' + socket.name);
  socket.dj = true;
  socket.on('disconnect', function () {
    dj = null;
    song = {};
    io.sockets.emit('notification', 'the dj left');
    io.sockets.emit('elected', '目前没有dj');
  });
}

io.on('connection', function (socket) {
  socket.on('join', function (name) {
    socket.name = name;
    io.sockets.emit('notification', name + ' join the chat');
    if (!dj) {
      elect(socket);
    } else {
      socket.emit('elected', '当前dj ' + dj.name);
      if (song.url) {
        socket.emit('song', song);
      }
    }
  });

  socket.on('text', function (msg) {
    socket.broadcast.emit('text', socket.name, msg);
  });

  socket.on('song', function (s, n) {
    if (socket.dj) {
      song.url = s;
      song.name = n;
      io.sockets.emit('song', song);
    }
  });
  socket.on('search', function (q, fn) {
    superagent.get(api + encodeURIComponent(q))
    .end(function (err, res) {
      if (err) console.log(err);
      fn(JSON.parse(res.text));
    });
  });
});
