// Compiled by ClojureScript 1.8.51 {}
goog.provide('gamma.emit.statement');
goog.require('cljs.core');
goog.require('gamma.emit.emit');
goog.require('gamma.ast');
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"break","break",126570225),(function (db,x){
return "break";
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"continue","continue",-207346553),(function (db,x){
return "continue";
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"discard","discard",-1939593545),(function (db,x){
return "discard";
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"block","block",664686210),(function (db,x){
return new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"group","group",582596132),cljs.core.interpose.call(null,new cljs.core.Keyword(null,"break","break",126570225),cljs.core.map.call(null,(function (y){
return new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"group","group",582596132),gamma.emit.emit.emit.call(null,db,db.call(null,y)),(cljs.core.truth_(new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"block","block",664686210),null,new cljs.core.Keyword(null,"if","if",-458814265),null], null), null).call(null,gamma.ast.head.call(null,db.call(null,y))))?"":";")], null);
}),gamma.ast.body.call(null,x)))], null);
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"set","set",304602554),(function (db,x){
return new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"group","group",582596132),gamma.emit.emit.emit.call(null,db,db.call(null,cljs.core.first.call(null,gamma.ast.body.call(null,x)))),"=",gamma.emit.emit.emit.call(null,db,db.call(null,cljs.core.second.call(null,gamma.ast.body.call(null,x))))], null);
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"if","if",-458814265),(function (db,x){
var vec__8356 = gamma.ast.body.call(null,x);
var test = cljs.core.nth.call(null,vec__8356,(0),null);
var then = cljs.core.nth.call(null,vec__8356,(1),null);
var else$ = cljs.core.nth.call(null,vec__8356,(2),null);
return new cljs.core.PersistentVector(null, 10, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"group","group",582596132),"if(",gamma.emit.emit.emit.call(null,db,db.call(null,test)),")","{",new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"nest","nest",-314993663),(2),new cljs.core.Keyword(null,"break","break",126570225),gamma.emit.emit.emit.call(null,db,db.call(null,then))], null),"}",new cljs.core.Keyword(null,"break","break",126570225),new cljs.core.PersistentVector(null, 5, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"nest","nest",-314993663),(2),"else {",new cljs.core.Keyword(null,"break","break",126570225),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"nest","nest",-314993663),(2),gamma.emit.emit.emit.call(null,db,db.call(null,else$))], null)], null),"}"], null);
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"for","for",-1323786319),(function (x){
var vec__8357 = gamma.ast.body.call(null,x);
var init = cljs.core.nth.call(null,vec__8357,(0),null);
var condition = cljs.core.nth.call(null,vec__8357,(1),null);
var increment = cljs.core.nth.call(null,vec__8357,(2),null);
var bod = cljs.core.nth.call(null,vec__8357,(3),null);
return [cljs.core.str("for("),cljs.core.str(gamma.emit.emit.emit.call(null,init)),cljs.core.str(";"),cljs.core.str(gamma.emit.emit.emit.call(null,condition)),cljs.core.str(";"),cljs.core.str(gamma.emit.emit.emit.call(null,increment)),cljs.core.str(";){"),cljs.core.str(gamma.emit.emit.emit.call(null,bod)),cljs.core.str("}")].join('');
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"if-else","if-else",979367526),(function (x){
var vec__8358 = gamma.ast.body.call(null,x);
var test = cljs.core.nth.call(null,vec__8358,(0),null);
var then = cljs.core.nth.call(null,vec__8358,(1),null);
var else$ = cljs.core.nth.call(null,vec__8358,(2),null);
new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"group","group",582596132),"if","(",cljs.core.List.EMPTY], null);

return [cljs.core.str("if("),cljs.core.str(gamma.emit.emit.emit.call(null,test)),cljs.core.str(")"),cljs.core.str("{"),cljs.core.str(gamma.emit.emit.emit.call(null,then)),cljs.core.str("}"),cljs.core.str("else"),cljs.core.str("{"),cljs.core.str(gamma.emit.emit.emit.call(null,else$)),cljs.core.str("}")].join('');
}));

//# sourceMappingURL=statement.js.map?rel=1476490290959