//////// THUNK NODE ////////


function ThunkNode(fn, args) {
  this.type = "thunk"
  this.fn = fn;
  this.args = args;
  this._cache = undefined;
}

ThunkNode.prototype.evaluate = function() {
  if(!this._cache) {
    this._cache = this.fn.apply(null, this.args);
  }
  
  return this._cache;
}

ThunkNode.prototype.render = function() {
  return this.evaluate().render();
}

function arraySame(a, b) {
  if(a.length !== b.length)
    return false;
  
  var same = true;
  var i = a.length;
  
  while(same && i--) {
    same = a[i] === b[i]
  }
  
  return same;
}

ThunkNode.prototype.reconcile = function(other) {
  if(this === other)
    return;
  
  if(this.type !== other.type)
    throw "Cannot reconcile " + this.type + " and " + other.type;
  
  // fn changed, rerun
  if(this.fn !== other.fn) {
    this._cache.reconcile(other.evaluate());
    
  // args changed, rerun
  } else if(!arraySame(this.args, other.args)) {
    this._cache.reconcile(other.evaluate());
    
  }
  
  // propagate the cache
  other._cache = this._cache;
}


//////// API ////////

var thunk = function(fn, args) { return new ThunkNode(fn, args); }



//////// TEST ////////


function testInner(t, a) {
  return mesh({
    rotation: {x: 0, y: 0, z:+t * 0.001},
    position: new THREE.Vector3(a, 0, 0),
    geometry:boxGeo,
    material:meshMat})
}

function thunkTest(t) {
    return new ThreeRendererNode(
    {},
    new ThreePerspectiveCameraNode({fov:60, aspect: 1, near:1, far:1000}),
    new ThreeSceneNode({},
      [thunk(testInner, [1, 0]),
       thunk(testInner, [1, 1]),
       thunk(testInner, [1*2, 2]),
       thunk(testInner, [1*3, 3]),
       thunk(testInner, [t*4, 4]),
      ]));
}