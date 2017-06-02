"use strict";
/// <reference path="./pixi.js.d.ts" />
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
exports.__esModule = true;
var pixi = require("pixi.js");
var Zajal;
(function (Zajal) {
    function applyProperties(obj, props) {
        for (var k in props) {
            obj[k] = props[k];
        }
    }
    var Virtual = (function () {
        function Virtual(props, children) {
            this.type = "";
            this.props = props || {};
            this.children = children || [];
        }
        Virtual.prototype.render = function () { return this.pointer; };
        Virtual.prototype.reconcile = function (other) {
            if (this.type != other.type) {
                // replace child
            }
            else {
                // same type, apply props
                applyProperties(this.render(), other.props);
            }
        };
        return Virtual;
    }());
    Zajal.Virtual = Virtual;
    var Applicaiton = (function (_super) {
        __extends(Applicaiton, _super);
        // seems faster
        function Applicaiton(props, children) {
            var _this = _super.call(this, props, children) || this;
            _this.stage = new Container();
            _this.type = "application";
            return _this;
        }
        Applicaiton.prototype.render = function () {
            if (!this.pointer) {
                this.pointer = new pixi.Application(this.props);
                for (var i = 0; i < this.children.length; ++i) {
                    this.pointer.stage.addChild(this.children[i].render());
                    this.children[i].parent = this.stage;
                }
            }
            return this.pointer;
        };
        return Applicaiton;
    }(Virtual));
    Zajal.Applicaiton = Applicaiton;
    var Container = (function (_super) {
        __extends(Container, _super);
        function Container() {
            return _super !== null && _super.apply(this, arguments) || this;
        }
        Container.prototype.render = function () {
            if (!this.pointer) {
                this.pointer = new pixi.Container();
                applyProperties(this.pointer, this.props);
                for (var i = 0; i < this.children.length; ++i) {
                    this.pointer.addChild(this.children[i].render());
                    this.children[i].parent = this;
                }
            }
            return this.pointer;
        };
        return Container;
    }(Virtual));
    Zajal.Container = Container;
    var Sprite = (function (_super) {
        __extends(Sprite, _super);
        function Sprite() {
            return _super !== null && _super.apply(this, arguments) || this;
        }
        Sprite.prototype.render = function () {
            if (!this.pointer) {
                this.pointer = pixi.Sprite.fromImage(this.props.image);
                applyProperties(this.pointer, this.props);
                for (var i = 0; i < this.children.length; ++i) {
                    this.pointer.addChild(this.children[i].render());
                    this.children[i].parent = this;
                }
            }
            return this.pointer;
        };
        return Sprite;
    }(Container));
    Zajal.Sprite = Sprite;
})(Zajal || (Zajal = {}));
