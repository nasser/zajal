function cachingFn(f) {
  var _gensym = cljs.core.gensym().toString();
  return function(a) {
    if(!a[_gensym])
      a[_gensym] = f(a);
    return a[_gensym];
  }
}

//////// THREE ////////

function mergeProps(obj, fromProps, toProps) {
  // check for changed/removed props
  for (var fromKey in fromProps) {
    // key missing, remove attribute it
    if (toProps[fromKey] === undefined) {
      delete obj[fromKey];
      
    } else {
      var fromValue = fromProps[fromKey];
      var toValue = toProps[fromKey];
      
      // same value, move on
      if(fromValue === toValue)
        continue;
      
      // TODO deep prop diff?
      // changed value, update attribute

      switch(fromKey) {
        case "rotation":
        obj.rotation.set(toValue.x, toValue.y, toValue.z);
        break;
        case "position":
        obj.position.set(toValue.x, toValue.y, toValue.z);
        break;
        default:
        obj[fromKey] = toValue;
      }
    }
  }
  
  // check for new props
  for (var toKey in toProps) {
    if (!(toKey in fromProps)) {
      obj[toKey] = toProps[toValue];
    }
  }
}

// TODO multiple cameras
function ThreeRendererNode(props, camera, scene) {
  this.type = "three-renderer"
  this.props = props;
  this.camera = camera;
  this.scene = scene;
  this._cache = undefined;
}

ThreeRendererNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = new THREE.WebGLRenderer(this.props);
    for(k in this.props) {
      this._cache[k] = this.props[k];
    }
    this.camera.render();
    this.scene.render();
  }
  
  return this._cache;
};

ThreeRendererNode.prototype.reconcile = function(other) {
  if(this === other)
    return;
  
  if(this.type !== other.type)
    throw "Cannot reconcile " + this.type + " and " + other.type;
  
  if(this.props !== other.props)
    mergeProps(this._cache, this.props, other.props);
  
  this.camera.reconcile(other.camera);
  this.scene.reconcile(other.scene);
  
  // propagate the cache
  other._cache = this._cache;
};


var ThreeNode = function(type, ctor) {
  var nodeCtor = function(props, children) {
    this.type = "three-" + type;
    this.props = props;
    this.children = children;
    this._cache = undefined;
  }
  
  nodeCtor.prototype.render = function() {
    if(!this._cache) {
      this._cache = Object.create(ctor.prototype);
      ctor.call(this._cache); // TODO ctor args?
      
      // if(parent)
      //   parent.add(this._cache);
      
      for(k in this.props) {
        switch(k) {
          case "rotation":
          this._cache.rotation.set(this.props[k].x, this.props[k].y, this.props[k].z);
          break;
          case "position":
          this._cache.position.set(this.props[k].x, this.props[k].y, this.props[k].z);
          break;
          default:
          this._cache[k] = this.props[k];
        }
      }
      
      if(this.children)
        for (var i = 0; i < this.children.length; i++) {
          this._cache.add(this.children[i].render());
        };
    }
    
    return this._cache;
  };
  
  nodeCtor.prototype.reconcile = function(other) {
    if(this === other)
      return;
    
    if(this.type !== other.type)
      throw "Cannot reconcile " + this.type + " and " + other.type;
    
    if(this.props !== other.props)
      mergeProps(this._cache, this.props, other.props)
    
    if(this.children && other.children)
      this.reconcileChildren(other);
    
    // propagate the cache
    other._cache = this._cache;
  };
  
  nodeCtor.prototype.reconcileChildren = function(other) {
    var thisChildren = this.children;
    var otherChildren = other.children;
    var minLength = Math.min(thisChildren.length, otherChildren.length);
    
    for (var i = 0; i < minLength; i++) {
      thisChildren[i].reconcile(otherChildren[i]);
    };
    
    // new elements
    if(otherChildren.length > thisChildren.length) {
      for (var i = minLength; i < otherChildren.length; i++) {
        this._cache.add(otherChildren[i].render());
      };
    
    // fewer elements
    } else if(thisChildren.length > otherChildren.length) {
      for (var i = minLength; i < thisChildren.length; i++) {
        this._cache.remove(thisChildren[i]._cache);
      };
    }
  };
  
  return nodeCtor;
}

var ThreeOrthographicCameraNode = ThreeNode("orthographic-camera", THREE.OrthographicCamera);
var ThreePerspectiveCameraNode = ThreeNode("perspective-camera", THREE.PerspectiveCamera);
var ThreeSceneNode = ThreeNode("scene", THREE.Scene);
var ThreeObject3DNode = ThreeNode("node", THREE.Object3D);
var ThreeMeshNode = ThreeNode("node", THREE.Mesh);
var ThreeLineNode = ThreeNode("node", THREE.Line);

//////// API ////////

goog.provide('zajal.three');

zajal.three.rednerer = function(props, camera, scene) { return new ThreeRendererNode(props, camera, scene); }
zajal.three.perspectiveCamera = function(props) { return new ThreePerspectiveCameraNode(props); }
zajal.three.scene = function(props, children) { return new ThreeSceneNode(props, children); }
zajal.three.mesh = function(props, children) { return new ThreeMeshNode(props, children); }
zajal.three.line = function(props, children) { return new ThreeLineNode(props, children); }

//////// TEST ////////


// var boxGeo = new THREE.BoxGeometry(1, 1, 1)
// var meshMat = new THREE.MeshBasicMaterial({wireframe:true})


// var box = function(t, children) {
//   if(!children)
//     return new ThreeMeshNode({
//       rotation: {x: 0, y: 0, z:+t/1000},
//       position: new THREE.Vector3(3, 0, 0),
//       geometry:boxGeo,
//       material:meshMat})
//   else
//     return new ThreeMeshNode({
//       rotation: {x: 0, y: 0, z:+t * 0.001},
//       position: new THREE.Vector3(1, 0, 0),
//       geometry:boxGeo,
//       material:meshMat},
//       children)
// }

// var boxes = function(t, i) {
//   if(i > 0)
//     return box(t * i * 0.001, [boxes(t, i - 1)]);
//   else
//     return box(t)
// }

// var threeTest = function(t) {
//   return new ThreeRendererNode(
//     {},
//     new ThreePerspectiveCameraNode({fov:60, aspect: 1, near:1, far:1000}),
//     new ThreeSceneNode({},
//       [boxes(0, 5),
//        boxes(t * 2, 5),
//        boxes(t * 4, 5),
//        boxes(t * 6, 5),
//        boxes(t * 8, 5),
//        boxes(t * 10, 5),
//        boxes(t * 20, 5),
//        boxes(t * 30, 5),
//        boxes(t * 40, 5),
//        boxes(t * 50, 5),
//        boxes(t * 60, 5),
//        boxes(t * 70, 5),
//        boxes(t * 80, 5),
//        boxes(t * 90, 5),
//        boxes(t * 100, 5),
//        boxes(t * 110, 5),
//        boxes(t * 120, 5),
//        boxes(t * 130, 5),
//        boxes(t * 140, 5),
//        boxes(t * 150, 5),
//        boxes(t * 2, 5),
//        boxes(t * 4, 5),
//        boxes(t * 6, 5),
//        boxes(t * 8, 5),
//        boxes(t * 10, 5),
//        boxes(t * 20, 5),
//        boxes(t * 30, 5),
//        boxes(t * 40, 5),
//        boxes(t * 50, 5),
//        boxes(t * 60, 5),
//        boxes(t * 70, 5),
//        boxes(t * 80, 5),
//        boxes(t * 90, 5),
//        boxes(t * 100, 5),
//        boxes(t * 110, 5),
//        boxes(t * 120, 5),
//        boxes(t * 130, 5),
//        boxes(t * 140, 5),
//        boxes(t * 150, 5),
//        boxes(t * 2, 5),
//        boxes(t * 4, 5),
//        boxes(t * 6, 5),
//        boxes(t * 8, 5),
//        boxes(t * 10, 5),
//        boxes(t * 20, 5),
//        boxes(t * 30, 5),
//        boxes(t * 40, 5),
//        boxes(t * 50, 5),
//        boxes(t * 60, 5),
//        boxes(t * 70, 5),
//        boxes(t * 80, 5),
//        boxes(t * 90, 5),
//        boxes(t * 100, 5),
//        boxes(t * 110, 5),
//        boxes(t * 120, 5),
//        boxes(t * 130, 5),
//        boxes(t * 140, 5),
//        boxes(t * 150, 5),
//        boxes(t * 2, 5),
//        boxes(t * 4, 5),
//        boxes(t * 6, 5),
//        boxes(t * 8, 5),
//        boxes(t * 10, 5),
//        boxes(t * 20, 5),
//        boxes(t * 30, 5),
//        boxes(t * 40, 5),
//        boxes(t * 50, 5),
//        boxes(t * 60, 5),
//        boxes(t * 70, 5),
//        boxes(t * 80, 5),
//        boxes(t * 90, 5),
//        boxes(t * 100, 5),
//        boxes(t * 110, 5),
//        boxes(t * 120, 5),
//        boxes(t * 130, 5),
//        boxes(t * 140, 5),
//        boxes(t * 150, 5),
//        ]));
// }