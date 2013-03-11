var tt = require('./build/Debug/dcp_stat_addon');
var str = tt.dump();
console.log(str);

var t0 = eval('(' + str + ')');
console.log(JSON.stringify(t0));
