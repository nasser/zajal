//////// CLJS VECTOR SYNTAX ////////

// copied from virtual-thunk.js
cljs.core.PersistentVector.prototype.type = "vector-thunk";

cljs.core.PersistentVector.prototype.fn = function() {
  return this.cljs$core$IIndexed$_nth$arity$3(null, 0);
}

cljs.core.PersistentVector.prototype.args = function() {
  return cljs.core.subvec.cljs$core$IFn$_invoke$arity$2(this, 1);
}

cljs.core.PersistentVector.prototype.evaluate = function() {
  if(!this._cache) {
    this._cache = cljs.core.apply(this.fn(), this.args());
  }
  
  return this._cache;
}

cljs.core.PersistentVector.prototype.render = function() {
  return this.evaluate().render();
}

function vectorSame(a, b) {
  if(cljs.core.count(a) !== cljs.core.count(b))
    return false;
  
  var same = true;
  var i = cljs.core.count(a);
  
  while(same && i--) {
    same = a.cljs$core$IIndexed$_nth$arity$3(null, i) === b.cljs$core$IIndexed$_nth$arity$3(null, i)
  }
  
  return same;
}

cljs.core.PersistentVector.prototype.reconcile = function(other) {
  if(this === other)
    return;
  
  if(this.type !== other.type)
    throw "Cannot reconcile " + this.type + " and " + other.type;
  
  // fn changed, rerun
  if(this.fn() !== other.fn()) {
    this._cache.reconcile(other.evaluate());
    
  // args changed, rerun
  } else if(!vectorSame(this.args(), other.args())) {
    this._cache.reconcile(other.evaluate());
    
  }
  
  // propagate the cache
  other._cache = this._cache;
}