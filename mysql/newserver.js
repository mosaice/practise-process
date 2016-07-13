var express = require('express');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var path = require('path');
var Sequelize = require('sequelize');

var app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(session({secret: 'my secret'}));
app.use(express.static(__dirname + '/public'));
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.set('view options', {layout: false});

app.get('/', function (req, res, next) {
  Projects.findAll().then(function (projects) {
    res.render('todo-index', { projects: projects });
  }).catch(next);
});

app.delete('/project/:id', function (req, res, next) {
  Projects.findById(Number(req.params.id)).then(function (proj) {
    proj.destroy().then(function () {
      res.send(200);
    }).catch(next);
  }).catch(next);
});

app.post('/projects', function (req, res, next) {
  Projects.build(req.body).save().then(function (obj) {
    res.render('todo-projects', { project: obj });
  });
});

app.get('/project/:id/tasks', function (req, res, next) {
  Projects.findById(Number(req.params.id)).then(function (project) {
    project.getTasks().then(function (tasks) {
      res.render('todo-tasks', {project: project, tasks: tasks});
    }).catch(next);
  });
});

app.post('/project/:id/tasks', function (req, res, next) {
  req.body.ProjectId = req.params.id;
  Task.build(req.body).save().then(function (obj) {
    res.send(obj);
  }).catch(next);
});

app.delete('/task/:id', function (req, res, next) {
  Task.findById(Number(req.params.id)).then(function (proj) {
    proj.destroy().then(function () {
      res.sendStatus(200);
    }).catch(next);
  }).catch(next);
});

app.listen(3000, function () {
  console.log('listen on http://localhost:3000');
});

var sequelize = new Sequelize('todo_example', 'dev', '123', {
  host: 'localhost'
});

var Projects = sequelize.define('Project', {
  title: {
    type: Sequelize.STRING,
    defaultValue: 'No title'
  },
  description: Sequelize.TEXT,
  created: Sequelize.DATE
});

var Task = sequelize.define('Task', {
  title: {type: Sequelize.STRING, isUppercase: true}
});

Task.belongsTo(Projects);
Projects.hasMany(Task);
sequelize.sync();
