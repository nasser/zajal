//////// TEXT NODE ////////


function DomTextNode(text) {
  this.type = "text"
  this.text = text;
  this._cachedRender = undefined;
}

DomTextNode.prototype.render = function() {
  if(!this._cachedRender) {
    this._cachedRender = document.createTextNode(this.text);
  } 
  
  return this._cachedRender;
}

DomTextNode.prototype.reconcile = function(other) {
  // TODO dont copy/paste
  // identical other, noop
  if(other === this)
    return;
  
  // different type, bail?
  if(other.type !== this.type) {
    throw "Cannot reconcile " + this.type + " and " + other.type;
  }
  
  // different tags, replace this node
  // assumes this._cachedRender
  if(other.tag !== this.tag) {
    var newRoot = other.render();
    this._cachedRender.parentElement.replaceChild(this._cachedRender, newRoot);
    return;
  }
  
  if(other.text !== this.text) {
    this._cachedRender.textContent = other.text;
    other._cachedRender = this._cachedRender;
  }
  
  other._cachedRender = this._cachedRender;
}



//////// DOM NODE ////////


function DomNode(tag, props, children) {
  this.type = "dom"
  this.tag = tag;
  this.props = props;
  this.children = children;
  this._cachedRender = undefined;
}

DomNode.prototype.render = function() {
  if(!this._cachedRender) {
    this._cachedRender = document.createElement(this.tag);
    var c = this.children;
    for (var i = 0; i < c.length; i++) {
      this._cachedRender.appendChild(c[i].render());
    }
    
    var thisProps = this.props;
    for (var thisKey in thisProps) {
      this._cachedRender.setAttribute(thisKey, thisProps[thisKey]);
    }
  }
  
  return this._cachedRender;
};

DomNode.prototype.reconcile = function(other) {
  // identical other, noop
  if(other === this)
    return;
  
  // different type, bail?
  if(other.type !== this.type) {
    throw "Cannot reconcile " + this.type + " and " + other.type;
  }
  
  // different tags, replace this node
  // assumes this._cachedRender
  if(other.tag !== this.tag) {
    var newRoot = other.render();
    this._cachedRender.parentElement.replaceChild(newRoot, this._cachedRender);
    return;
  }
  
  // other is a different dom node w/same tag
  this.reconcileProps(other);
  this.reconcileChildren(other);
  
  // propagate cache
  other._cachedRender = this._cachedRender;
};

DomNode.prototype.reconcileProps = function(other) {
  var _cachedRender = this._cachedRender
  var thisProps = this.props;
  var otherProps = other.props;
  
  // check for changed/removed props
  for (var thisKey in thisProps) {
    // key missing, remove attribute it
    if (!(thisKey in otherProps)) {
      _cachedRender.removeAttribute(thisKey);
    }
    
    var thisValue = thisProps[thisKey];
    var otherValue = otherProps[thisKey];
    
    // same value, move on
    if(thisValue === otherValue)
      continue;
    
    // TODO deep prop diff?
    // changed value, update attribute
    _cachedRender.setAttribute(thisKey, otherValue);
  }
  
  // check for new props
  for (var otherKey in otherProps) {
    if (!(otherKey in thisProps)) {
      _cachedRender.setAttribute(otherKey, otherProps[otherValue]);
    }
  }
};

// TODO keyed nodes?
DomNode.prototype.reconcileChildren = function(other) {
  var thisChildren = this.children;
  var otherChildren = other.children;
  var minLength = Math.min(thisChildren.length, otherChildren.length);
  
  for (var i = 0; i < minLength; i++) {
    thisChildren[i].reconcile(otherChildren[i]);
  };
  
  // new elements
  if(otherChildren.length > thisChildren.length) {
    for (var i = minLength; i < otherChildren.length; i++) {
      this._cachedRender.appendChild(otherChildren[i].render());
    };
  
  // fewer elements
  } else if(thisChildren.length > otherChildren.length) {
    for (var i = minLength; i < thisChildren.length; i++) {
      this._cachedRender.removeChild(thisChildren[i]._cachedRender);
    };
  }
};

function domNodeFunction(tag) {
  return function(props, children) {
    return new DomNode(tag, props, children)
  }
}



//////// API ////////

var p = domNodeFunction("p");
var h1 = domNodeFunction("h1");
var h2 = domNodeFunction("h2");
var h3 = domNodeFunction("h3");
var strong = domNodeFunction("strong");
var em = domNodeFunction("em");
var div = domNodeFunction("div");
var span = domNodeFunction("span");
var text = function(t) { return new DomTextNode(t.toString()) };


//////// TEST ////////


var domTest = div(
  {class:"pismo"},
  [h1({}, [text("Here we go")]),
  p({}, [
    text("lorem impsum "),
    span({}, [text("the jake")]),
    text(" another one")])])

var domTest2 = div(
  {class:"pismo"},
  [h1({}, [text("Here we go")]),
  p({}, [
    text("lorem impsum "),
    em({}, [text("the jake")]),
    text(" another one")])])

var domClock = function(t) {
  return div(
    {class:"the-clock"},
    [h1({}, [text("The time")]),
    p({}, [
      text("seems to be "),
      t.getSeconds() % 2 == 1 ?
        em({}, [text(t.getMilliseconds())]) :
        span({}, [text(t.getMilliseconds())]),
      text(" o'clock")])])
}
