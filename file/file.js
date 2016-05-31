#! /usr/local/bin/node

var fs = require('fs');
var path = require('path');
var stdout = process.stdout;
var stdin = process.stdin;

var nodeRead = {
  files: [],
  stat: {},
  index: 0,
  path: __dirname,
  inited: false,
  readdir: function () {
    this.files = [];
    this.stat = {};
    this.index = 0;
    fs.readdir(this.path, function (err, files) {
      if (err) return console.log('        路径错误');
      if (!files.length) return console.log('\033[31m 没有文件！\033[39m\n');
      console.log('当前目录' + this.path);
      console.log('选择你想要查看的文件\n');
      this.files = files;
      this.read();
    }.bind(this));
  },
  read: function () {
    var file = this.files[this.index];
    if (!file) {
      this.stdin();
    } else {
      this.readStat(file);
    }
  },
  readStat: function (file) {
    fs.stat(this.path + '/' + file, function (err, stat) {
      if (err) console.log(err);
      if (stat.isDirectory()) {
        this.stat[this.index] = file;
        console.log('     ' + this.index + '       \033[36m' + file + '\033[39m');
      } else {
        console.log('     ' + this.index + '       \033[90m' + file + '\033[39m');
      }
      this.index++;
      this.read();
    }.bind(this));
  },
  stdin: function () {
    console.log('     \033[37m输入编号查看文件，输入"../"返回上级，输入"go"+目录进行跳转\033[39m');
    stdout.write('     \033[33m输入你的选择\033[39m');
    stdin.resume();
    stdin.setEncoding('utf8');
    if (this.inited) return;
    stdin.on('data', function (data) {
      if (!this.files[Number(data)]) {
        var pathReg = /^go\s\/\w*/;
        if (data.trim() === '../') {
          stdin.pause();
          this.path = path.normalize(this.path + '/..');
          return this.readdir();
        }

        if (pathReg.test(data.trim())) {
          stdin.pause();
          this.path = data.replace('go', '').trim();
          return this.readdir();
        }
        stdout.write('     \033[33m输入你的选择\033[39m');
      } else {
        stdin.pause();
        if (this.stat[Number(data)]) {
          this.path = this.path + '/' + this.stat[Number(data)];
          this.readdir();
        } else {
          this.readfile(this.files[Number(data)]);
        }
      }
    }.bind(this));
    this.inited = true;
  },
  readfile: function (file) {
    fs.readFile(this.path + '/' + file, 'utf8', function (err, data) {
      if (err) console.log(err);
      console.log('\033[90m' + data.replace(/(.*)/g, '       $1') + '\033[39m');
    });
  }
};

nodeRead.readdir();
