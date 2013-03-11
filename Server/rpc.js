// socket.io 
//var io = require('socket.io').listen(httpServ);
var io = require('socket.io').listen(3001);
var rpc = require('jsonrpc-ws');

/*
var RpcFunctions = {
  add: function(a, b) {
    var r = a + b;
    //throw {code: 101, info: "failed"};
    return [r, r];  
  },

  sub: function(a, b) {
    return a - b;
  }
};

rpc.exposeModule('rpc', RpcFunctions);
rpc.exposeModule('abc', RpcFunctions);
*/
var control = require('./statControl.js');

rpc.exposeModule('rpc', control.rpc);
rpc.listen(io.sockets);

module.exports = rpc;