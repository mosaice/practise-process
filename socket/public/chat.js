window.onload = function () {
  var $ul = document.getElementById('message');
  var $input = document.getElementById('input');
  var $s = document.getElementById('s');
  var $form = document.getElementById('form');
  var $djform = document.getElementById('djform');
  var $result = document.getElementById('result');
  var $audio = document.getElementById('audio');
  var $dj = document.getElementById('dj');
  var $playing = document.getElementById('playing');

  var socket = io.connect();
  var name = prompt('输入名字');
  socket.emit('join', name);

  socket.on('notification', function (msg) {
    var li = document.createElement('li');
    li.className = 'notification';
    li.innerHTML = msg;
    $ul.appendChild(li);
    li = null;
  });

  socket.on('text', function (from, value) {
    addMsg(from, value);
  });

  $form.onsubmit = function (e) {
    addMsg('me', $input.value);
    socket.emit('text', $input.value);

    $input.value = '';
    $input.focus();
    return false;
  };

  function addMsg(from, value) {
    var li = document.createElement('li');
    li.innerHTML = 'from ' + from + ' :' + value;
    $ul.appendChild(li);
    li = null;
  }

  $djform.onsubmit = function (e) {
    var song = $s.value;
    $result.innerHTML = '';
    socket.emit('search', song, function (songs) {
      var _arr = songs.result.songs.map(function (item) {
        return '<li>' +
                  '<img src="' + item.album.picUrl + '" alt="" width=100 height=100/>' +
                  '<p>' + item.album.name + '--' + item.name + '</p>' +
                  '<a href="#" data-href="' + item.audio + '" class="play" data-name="' + item.name + '">播放</a>' +
                '<li>';
      });
      console.log(_arr.join());
      $result.innerHTML = _arr.join();
    });
    $s.value = '';
    console.log(e);
    return false;
  };

  function play(e) {
    e.preventDefault();
    if (e.target.className === 'play') {
      console.log(e.target.getAttribute('data-href'));
      socket.emit('song', e.target.getAttribute('data-href'), e.target.getAttribute('data-name'));
    }
    return false;
  }
  $result.addEventListener('click', play, false);

  socket.on('song', function (song) {
    $playing.innerHTML = song.name;
    $audio.src = song.url;
    $audio.play();
  });

  socket.on('elected', function (msg) {
    console.log(msg);
    $dj.innerHTML = msg;
  });
};
