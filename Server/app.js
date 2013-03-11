
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path');

var servAddr = "127.0.0.1";

var app = express();

app.configure(function(){
  app.set('port', process.env.PORT || 3000);
  app.set('views', __dirname + '/views');
  app.set('view engine', 'ejs');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(app.router);
  app.use(express.static(path.join(__dirname, 'public')));
});

app.configure('development', function(){
  app.use(express.errorHandler());
});

//app.get('/', routes.index);
app.get('/', function(req, res){
  res.render('index', { 'servAddr': servAddr });
});

app.get('/users', user.list);

var httpServ = http.createServer(app);

httpServ.listen(app.get('port'), function(){
  console.log("Express server listening on port " + app.get('port'));
});

var rpc = require('./rpc.js');
