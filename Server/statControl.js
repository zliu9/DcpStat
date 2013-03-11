var port = 3002;
var io = require('socket.io').listen(port);
var stat = require('../DcpStat.node/build/Debug/dcp_stat_addon.node');
var cons = [];
var logger = require('nlogger').logger(module);

io.sockets.on('connection', function (socket) {
    logger.info('1 peer connected');
    cons.push(socket);
});

function sendStat() {
    var idx;
    for(idx in cons) {	    
	    cons[idx].emit("dcpStat", stat.dump());
	}
};

var timer;

function startStat(timeout) {
    logger.info('startStat is called');
	
	if(timer) {
	    logger.info('kill old timer');
	    clearInterval(timer);
	}
	
    timer = setInterval(sendStat, timeout);
}

function stopStat() {
    logger.info('stopStat is called');
    clearInterval(timer);
}

module.exports = {
    'io' : io,
	'port' : port,
	'rpc' : {
	    'startStat' : startStat,
	    'stopStat'  : stopStat,   
	}
}
