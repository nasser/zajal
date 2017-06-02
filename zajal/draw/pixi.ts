/// <reference path="./pixi.js.d.ts" />

import pixi = require("pixi.js");

namespace Zajal {
  function applyProperties(obj, props) {
    for (var k in props) {
      obj[k] = props[k];
    }
  }
  
  interface IVirtual<T> {
    parent: IVirtual<T>;
    pointer: T;
    render(): T;
  }

  export class Virtual<T> implements IVirtual<T> {
    parent: IVirtual<T>;
    pointer: T;
    props;
    children: Container[];
    type = "";
    
    constructor (props?, children?) {
      this.props = props || {};
      this.children = children || [];
    }
    
    render() { return this.pointer; }
    reconcile<U>(other:Virtual<U>) {
      if(this.type != other.type) {
        // replace child
      } else {
        // same type, apply props
        applyProperties(this.render(), other.props);
        this.reconcileChildren(other);
      }
    }
    
    reconcileChildren<U>(other:Virtual<U>) {
      let minLength = Math.min(this.children.length, other.children.length);
      for (var i = 0; i < minLength; i++) {
        this.children[i].reconcile(other.children[i]);
      }
      if(other.children.length > this.children.length) {
        // more children
        for (var i = minLength; i < other.children.length; i++) {
          // this.pointer.a
        }
      }
    }
  }
  
  export class Applicaiton extends Virtual<pixi.Application> {
    stage = new Container();
    type = "application";
    
    // seems faster
    constructor (props?, children?) { super(props, children); }
    
    render() {
      if(!this.pointer) {
        this.pointer = new pixi.Application(this.props);
        for (var i = 0; i < this.children.length; ++i) {
          this.pointer.stage.addChild(this.children[i].render());
          this.children[i].parent = this.stage;
        }
      }
      
      return this.pointer;
    }
  }
  
  export class Container extends Virtual<pixi.Container> {
    render() {
      if(!this.pointer) {
        this.pointer = new pixi.Container();
        applyProperties(this.pointer, this.props);
        for (var i = 0; i < this.children.length; ++i) {
          this.pointer.addChild(this.children[i].render());
          this.children[i].parent = this;
        }
      }
      
      return this.pointer;
    }
  }
  
  export class Sprite extends Container {
    render() {
      if(!this.pointer) {
        this.pointer = pixi.Sprite.fromImage(this.props.image);
        applyProperties(this.pointer, this.props);
        for (var i = 0; i < this.children.length; ++i) {
          this.pointer.addChild(this.children[i].render());
          this.children[i].parent = this;
        }
      }
      
      return this.pointer;
    }
  }
}