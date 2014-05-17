clementine.RpcChannel = function(sendCallback) {
  this.sendCallback = sendCallback;

  this.nextId_ = 1;
  this.pending_ = {};
};

clementine.RpcChannel.prototype.start = function(method, arguments, callback) {
  var id = this.nextId_ ++;
  
  this.sendCallback({
    'method': method,
    'arguments': arguments,
  });
};
