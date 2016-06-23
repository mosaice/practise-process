var express = require('express');
var mongodb = require('mongodb');
var path = require('path');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var objectid = require('objectid');

var app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(session({secret: 'my secret'}));
app.use(function (req, res, next) {
  if (req.session.loggedIn) {
    app.locals.auth = true;
    app.users.findOne({_id: objectid(req.session.loggedIn)}, function (err, doc) {
      if (err) return next(err);
      if (doc) app.locals.me = doc;
      next();
    });
  } else {
    app.locals.auth = false;
    next();
  }
});

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.set('view options', {layout: false});

app.get('/', function (req, res) {
  res.render('index');
});

app.get('/login/:email', function (req, res) {
  res.render('login', {email: req.params.email});
});

app.get('/login', function (req, res) {
  res.render('login');
});

app.post('/login', function (req, res, next) {
  app.users.findOne({email: req.body.user.email, password: req.body.user.password}, function (err, doc) {
    if (err) return next(err);
    if (!doc) return res.send('<p>User not found </p>');
    req.session.loggedIn = doc._id.toString();
    res.redirect('/');
  });
});

app.get('/signup', function (req, res) {
  res.render('signup');
});

app.get('/logout', function (req, res) {
  req.session.loggedIn = null;
  res.redirect('/');
});

app.post('/signup', function (req, res, next) {
  app.users.insert(req.body.user, function (err, doc) {
    if (err) next(err);
    console.log(doc);
    res.redirect('/login/' + doc.ops[0].email);
  });
});

app.listen(3000, function (err) {
  if (err) console.log(err);
  console.log('listen on http://localhost:3000');
});

var server = new mongodb.Server('127.0.0.1', 27017);
var db = new mongodb.Db('web', server);

db.open(function (err, client) {
  if (err) console.log(err);
  console.log('connect to mongodb');
  app.users = client.collection('users');
  client.ensureIndex('user', 'email', function (err) {
    if (err) console.log(err);
    client.ensureIndex('user', 'password', function (err) {
      if (err) console.log(err);
      console.log('ensured index');
    });
  });
});
