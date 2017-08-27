//////// PIXI ////////

function applyProps(obj, props) {
  for (var propKey in props) {
    obj[propKey] = props[propKey];
  }
}

function reconcile(self, other) {
  if(self.type != other.type) {
    var index = self._cache.parent.getChildIndex(self._cache);
    self._cache.parent.removeChildAt(index)
    self._cache.parent.addChildAt(other.render(), index);
  } else {
    applyProps(self._cache, other.props)
    other._cache = self._cache;
  }
}

function reconcileChildren(self, other) {
  var selfChildCount = (self.children && self.children.length || 0);
  var otherChildCount = (other.children && other.children.length || 0);
  var minLength = Math.min(selfChildCount, otherChildCount);
  for (var i = 0; i < minLength; i++) {
    self.children[i].reconcile(other.children[i]);
  }
  if(otherChildCount > selfChildCount) {
    // more elements
    for(var i = minLength; i< otherChildCount; i++) {
      self._cache.addChild(other.children[i].render());
    }
  } else {
    // fewer elements
    for(var i = minLength; i < selfChildCount; i++) {
      self._cache.removeChild(self.children[i].render());
    }
  }
}

function ApplicationNode(props, children) {
  this.type = "pixi-application"
  this.props = props;
  this.children = children;
  this._cache = undefined;
}

ApplicationNode.prototype.render = function() {
  if(!this._cache) {
    // create and cache node
    this._cache = new PIXI.Application(this.props.width || 800, this.props.height || 600, this.props);
    
    // normalize interface
    this._cache.removeChild = function(c) { return this._cache.stage.removeChild(c); }
    this._cache.addChild = function(c) { return this._cache.stage.addChild(c); }
  
    // render and add children
    var childCount = this.children.length;
    for (var i = 0; i < childCount; i++) {
      this._cache.stage.addChild(this.children[i].render());
    }
  }
    
  return this._cache;
}

ApplicationNode.prototype.reconcile = function(other) {
  if(this.type != other.type)
    throw "Different types not supported " + this.type + " vs " + other.type;
  reconcile(this, other);
  reconcileChildren(this, other);
}

function DisplayObjectNode(ctor, props, children) {
  this.type = "pixi-displayobject"
  this.ctor = ctor;
  this.props = props;
  this.children = children;
  this._cache = undefined;
}

DisplayObjectNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = Object.create(this.ctor.prototype);
    this.ctor.call(this._cache);
    applyProps(this._cache, this.props)
    if(this.children) {
      var childCount = this.children.length;
      for (var i = 0; i < childCount; i++) {
        this._cache.addChild(this.children[i].render());
      }
    }
    
  }
  return this._cache;
}

DisplayObjectNode.prototype.reconcile = function(other) {
  if(this === other) return; // ???
  reconcile(this, other);
  reconcileChildren(this, other);
};

function SpriteNode(props, children) {
  this.type = "pixi-sprite"
  this.props = props;
  this.children = children;
  this._cache = undefined;
}

SpriteNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = PIXI.Sprite.fromImage(this.props.image);
    applyProps(this._cache, this.props)
    if(this.children) {
      var childCount = this.children.length;
      for (var i = 0; i < childCount; i++) {
        this._cache.addChild(this.children[i].render());
      }
    }
    
  }
  return this._cache;
}

SpriteNode.prototype.reconcile = function(other) {
  if(this === other) return; // ???
  reconcile(this, other);
  reconcileChildren(this, other);
};

function TextNode(props, children) {
  this.type = "pixi-text"
  this.props = props;
  this.children = children;
  this._cache = undefined;
}

TextNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = new PIXI.Text();
    applyProps(this._cache, this.props);
    applyProps(this._cache.style, this.props);
    if(this.children) {
      var childCount = this.children.length;
      for (var i = 0; i < childCount; i++) {
        this._cache.addChild(this.children[i].render());
      }
    }
    
  }
  return this._cache;
}

TextNode.prototype.reconcile = function(other) {
  if(this === other) return; // ???
  reconcile(this, other);
  applyProps(this._cache.style, this.props);
  reconcileChildren(this, other);
};



goog.provide('zajal.alt.draw.pixi');

zajal.alt.draw.pixi.renderer = function(props, children) { return new ApplicationNode(props, children); }
zajal.alt.draw.pixi.object = function(ctor, props, children) { return new DisplayObjectNode(ctor, props, children); }
zajal.alt.draw.pixi.container = function(props, children) { return zajal.alt.draw.pixi.object(PIXI.Container, props, children); }
zajal.alt.draw.pixi.sprite = function(props, children) { return new SpriteNode(props, children); }
zajal.alt.draw.pixi.text = function(props, children) { return new TextNode(props, children); }
