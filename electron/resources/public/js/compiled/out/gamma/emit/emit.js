// Compiled by ClojureScript 1.8.51 {}
goog.provide('gamma.emit.emit');
goog.require('cljs.core');
goog.require('gamma.ast');
gamma.emit.emit.function_QMARK_ = (function gamma$emit$emit$function_QMARK_(x){
return gamma.ast.functions.call(null,gamma.ast.head.call(null,x));
});
gamma.emit.emit.operator_class = (function gamma$emit$emit$operator_class(x){
var temp__4655__auto__ = gamma.ast.operators.call(null,gamma.ast.head.call(null,x));
if(cljs.core.truth_(temp__4655__auto__)){
var o = temp__4655__auto__;
return new cljs.core.Keyword(null,"class","class",-2030961996).cljs$core$IFn$_invoke$arity$1(o);
} else {
return null;
}
});
gamma.emit.emit.primitive_QMARK_ = (function gamma$emit$emit$primitive_QMARK_(x){
return (x === true) || (x === false) || (cljs.core.integer_QMARK_.call(null,x)) || (typeof x === 'number');
});
gamma.emit.emit.constructor_QMARK_ = (function gamma$emit$emit$constructor_QMARK_(x){
return new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 12, [new cljs.core.Keyword(null,"bvec3","bvec3",-635324058),null,new cljs.core.Keyword(null,"mat3","mat3",402087048),null,new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"ivec4","ivec4",-537108439),null,new cljs.core.Keyword(null,"mat2","mat2",238424363),null,new cljs.core.Keyword(null,"ivec2","ivec2",148465998),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null,new cljs.core.Keyword(null,"bvec2","bvec2",-148389679),null,new cljs.core.Keyword(null,"mat4","mat4",-237531594),null,new cljs.core.Keyword(null,"bvec4","bvec4",1798744632),null,new cljs.core.Keyword(null,"ivec3","ivec3",-104254851),null], null), null).call(null,new cljs.core.Keyword(null,"head","head",-771383919).cljs$core$IFn$_invoke$arity$1(x));
});
gamma.emit.emit.emit_dispatch = (function gamma$emit$emit$emit_dispatch(db,x){
if(cljs.core.truth_(gamma.emit.emit.primitive_QMARK_.call(null,x))){
return new cljs.core.Keyword(null,"primitive","primitive",1884541424);
} else {
if(cljs.core.truth_(new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"int","int",-1741416922),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"bool","bool",1444635321),null], null), null).call(null,x))){
return new cljs.core.Keyword(null,"primitive-type","primitive-type",-130245537);
} else {
if(cljs.core.truth_(gamma.emit.emit.constructor_QMARK_.call(null,x))){
return new cljs.core.Keyword(null,"constructor","constructor",-1953928811);
} else {
if(cljs.core.truth_(gamma.emit.emit.function_QMARK_.call(null,x))){
return new cljs.core.Keyword(null,"function","function",-2127255473);
} else {
var temp__4655__auto__ = gamma.emit.emit.operator_class.call(null,x);
if(cljs.core.truth_(temp__4655__auto__)){
var c = temp__4655__auto__;
return c;
} else {
var temp__4655__auto____$1 = gamma.ast.head.call(null,x);
if(cljs.core.truth_(temp__4655__auto____$1)){
var h = temp__4655__auto____$1;
return h;
} else {
return new cljs.core.Keyword(null,"tag","tag",-1290361223).cljs$core$IFn$_invoke$arity$1(x);
}
}
}
}
}
}
});
if(typeof gamma.emit.emit.emit !== 'undefined'){
} else {
gamma.emit.emit.emit = (function (){var method_table__7135__auto__ = cljs.core.atom.call(null,cljs.core.PersistentArrayMap.EMPTY);
var prefer_table__7136__auto__ = cljs.core.atom.call(null,cljs.core.PersistentArrayMap.EMPTY);
var method_cache__7137__auto__ = cljs.core.atom.call(null,cljs.core.PersistentArrayMap.EMPTY);
var cached_hierarchy__7138__auto__ = cljs.core.atom.call(null,cljs.core.PersistentArrayMap.EMPTY);
var hierarchy__7139__auto__ = cljs.core.get.call(null,cljs.core.PersistentArrayMap.EMPTY,new cljs.core.Keyword(null,"hierarchy","hierarchy",-1053470341),cljs.core.get_global_hierarchy.call(null));
return (new cljs.core.MultiFn(cljs.core.symbol.call(null,"gamma.emit.emit","emit"),gamma.emit.emit.emit_dispatch,new cljs.core.Keyword(null,"default","default",-1987822328),hierarchy__7139__auto__,method_table__7135__auto__,prefer_table__7136__auto__,method_cache__7137__auto__,cached_hierarchy__7138__auto__));
})();
}
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"primitive","primitive",1884541424),(function (db,x){
if(typeof x === 'number'){
var tmp = [cljs.core.str(x)].join('');
if((tmp.indexOf(".") > (0))){
return tmp;
} else {
return [cljs.core.str(tmp),cljs.core.str(".0")].join('');
}
} else {
return [cljs.core.str(x)].join('');
}
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"primitive-type","primitive-type",-130245537),(function (db,x){
return cljs.core.name.call(null,x);
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,new cljs.core.Keyword(null,"literal","literal",1664775605),(function (db,x){
return gamma.emit.emit.emit.call(null,db,new cljs.core.Keyword(null,"value","value",305978217).cljs$core$IFn$_invoke$arity$1(x));
}));
cljs.core._add_method.call(null,gamma.emit.emit.emit,null,(function (db,x){
return cljs.core.println.call(null,new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"nil","nil",99600501),x], null));
}));

//# sourceMappingURL=emit.js.map?rel=1476490290917