const dgram = require('dgram');
const server = dgram.createSocket('udp4');

server.on('error', (err) => {
  console.log(`server error:\n${err.stack}`);
  server.close();
});

server.on('message', (msg, rinfo) => {
  let code = msg.toString(),
      result = cljs.core.pr_str(clojurescript.core.eval(code));
  server.send(`${clojurescript.core.eval("(str *ns*)")}=> ${code}${result}\n\n`, rinfo.port, rinfo.address);
});

server.on('listening', () => {
  var address = server.address();
  console.log(`server listening ${address.address}:${address.port}`);
});

server.bind(10011);