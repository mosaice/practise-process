var express = require('express');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var path = require('path');
var mysql = require('mysql');

var app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(session({secret: 'my secret'}));

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.set('view options', {layout: false});

app.get('/', function (req, res, next) {
  db.query('SELECT id, title, description FROM item', function (err, result) {
    if (err) next(err);
    res.render('index', {items: result});
  });
});

app.post('/create', function (req, res, next) {
  db.query('INSERT INTO item SET title = ?, description = ?', [req.body.title, req.body.description], function (err, info) {
    if (err) return next(err);
    console.log('item created with id ', info.insertId);
    console.log(info);
    res.redirect('/');
  });
});

app.get('/item/:id', function (req, res, next) {
  function getItem(fn) {
    db.query('SELECT id, title, description FROM item WHERE id = ? LIMIT 1', [req.params.id], function (err, result) {
      if (err) next(err);
      if (!result[0]) return res.send(404);
      fn(result[0]);
    });
  }

  function getReviews(item_id, fn) {
    db.query('SELECT text, stars FROM review WHERE item_id = ?', [item_id], function (err, result) {
      if (err) next(err);
      fn(result);
    });
  }
  getItem(function (item) {
    getReviews(item.id, function (reviews) {
      res.render('item', {item: item, reviews: reviews});
    });
  });
});

app.post('/item/:id/review', function (req, res, next) {
  db.query('INSERT INTO review SET item_id = ?, stars = ?, text = ?', [req.params.id, req.body.stars, req.body.text], function (err, info) {
    if (err) return next(err);
    console.log('review created with id', info.insertId);
    console.log(info);
    res.redirect('/item/' + req.params.id);
  });
});

app.listen(3000, function (err) {
  if (err) console.log(err);
  console.log('listen on http://localhost:3000');
});

var db = mysql.createConnection({
  host: 'localhost',
  user: 'dev',
  database: 'cart',
  password: '123'
});
db.connect();

db.query('CREATE DATABASE IF NOT EXISTS `cart`');
db.query('USE `cart`');
db.query('DROP TABLE IF EXISTS item');
db.query('CREATE TABLE item (id INT(11) AUTO_INCREMENT,title VARCHAR(255),description TEXT,created DATETIME, PRIMARY KEY (id))');
db.query('DROP TABLE IF EXISTS review');
db.query('CREATE TABLE review (id INT(11) AUTO_INCREMENT, item_id INT(11), text TEXT, stars INT(1), created DATETIME, PRIMARY KEY (id))');

// db.end(function () {
//   process.exit();
// });
