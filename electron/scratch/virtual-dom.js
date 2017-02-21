//////// TEXT NODE ////////


var DomTextNode = function(text) {
  this.type = "text"
  this.text = text;
  this._cache = undefined;
}

DomTextNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = document.createTextNode(this.text);
  } 
  
  return this._cache;
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
  
  if(other.text !== this.text) {
    this._cache.textContent = other.text;
  }
  
  other._cache = this._cache;
}



//////// DOM NODE ////////


var DomNode = function(tag, props, children) {
  this.type = "dom";
  this.tag = tag;
  this.props = props;
  this.children = children;
  this._cache = undefined;
}

DomNode.prototype.render = function() {
  if(!this._cache) {
    this._cache = document.createElement(this.tag);
    var c = this.children;
    for (var i = 0; i < c.length; i++) {
      this._cache.appendChild(c[i].render());
    }
    
    var thisProps = this.props;
    for (var thisKey in thisProps) {
      this._cache.setAttribute(thisKey, thisProps[thisKey]);
    }
  }
  
  return this._cache;
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
  // assumes this._cache
  if(other.tag !== this.tag) {
    var newRoot = other.render();
    this._cache.parentElement.replaceChild(newRoot, this._cache);
    return;
  }
  
  // other is a different dom node w/same tag
  this.reconcileProps(other);
  this.reconcileChildren(other);
  
  // propagate cache
  other._cache = this._cache;
};

DomNode.prototype.reconcileProps = function(other) {
  var _cache = this._cache
  var thisProps = this.props;
  var otherProps = other.props;
  
  // check for changed/removed props
  for (var thisKey in thisProps) {
    // key missing, remove attribute it
    if (!(thisKey in otherProps)) {
      _cache.removeAttribute(thisKey);
    }
    
    var thisValue = thisProps[thisKey];
    var otherValue = otherProps[thisKey];
    
    // same value, move on
    if(thisValue === otherValue)
      continue;
    
    // TODO deep prop diff?
    // changed value, update attribute
    _cache.setAttribute(thisKey, otherValue);
  }
  
  // check for new props
  for (var otherKey in otherProps) {
    if (!(otherKey in thisProps)) {
      _cache.setAttribute(otherKey, otherProps[otherValue]);
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
      this._cache.appendChild(otherChildren[i].render());
    };
  
  // fewer elements
  } else if(thisChildren.length > otherChildren.length) {
    for (var i = minLength; i < thisChildren.length; i++) {
      this._cache.removeChild(thisChildren[i]._cache);
    };
  }
};

function createDomNode(tag) {
  return function(props, children) {
    return new DomNode(tag, props, children)
  }
}


//////// API ////////

goog.provide('zajal.dom');

zajal.dom.p = createDomNode("p");
zajal.dom.h1 = createDomNode("h1");
zajal.dom.h2 = createDomNode("h2");
zajal.dom.h3 = createDomNode("h3");
zajal.dom.h4 = createDomNode("h4");
zajal.dom.h5 = createDomNode("h5");
zajal.dom.strong = createDomNode("strong");
zajal.dom.em = createDomNode("em");
zajal.dom.div = createDomNode("div");
zajal.dom.span = createDomNode("span");
zajal.dom.text = function(t) { return new DomTextNode(t.toString()) };


//////// TEST ////////


// var domTest = div(
//   {class:"pismo"},
//   [h1({}, [text("Here we go")]),
//   p({}, [
//     text("lorem impsum "),
//     span({}, [text("the jake")]),
//     text(" another one")])])

// var domTest2 = div(
//   {class:"pismo"},
//   [h1({}, [text("Here we go")]),
//   p({}, [
//     text("lorem impsum "),
//     em({}, [text("the jake")]),
//     text(" another one")])])

// var domClock = function(t) {
//   return div(
//     {class:"the-clock"},
//     [h1({}, [text("The time")]),
//     p({}, [
//       text("seems to be "),
//       t.getSeconds() % 2 == 1 ?
//         em({}, [text(t.getMilliseconds())]) :
//         span({}, [text(t.getMilliseconds())]),
//       text(" o'clock")])])
// }
