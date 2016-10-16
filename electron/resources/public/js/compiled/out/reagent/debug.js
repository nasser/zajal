// Compiled by ClojureScript 1.8.51 {}
goog.provide('reagent.debug');
goog.require('cljs.core');
reagent.debug.has_console = typeof console !== 'undefined';
reagent.debug.tracking = false;
if(typeof reagent.debug.warnings !== 'undefined'){
} else {
reagent.debug.warnings = cljs.core.atom.call(null,null);
}
if(typeof reagent.debug.track_console !== 'undefined'){
} else {
reagent.debug.track_console = (function (){var o = {};
o.warn = ((function (o){
return (function() { 
var G__7392__delegate = function (args){
return cljs.core.swap_BANG_.call(null,reagent.debug.warnings,cljs.core.update_in,new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"warn","warn",-436710552)], null),cljs.core.conj,cljs.core.apply.call(null,cljs.core.str,args));
};
var G__7392 = function (var_args){
var args = null;
if (arguments.length > 0) {
var G__7393__i = 0, G__7393__a = new Array(arguments.length -  0);
while (G__7393__i < G__7393__a.length) {G__7393__a[G__7393__i] = arguments[G__7393__i + 0]; ++G__7393__i;}
  args = new cljs.core.IndexedSeq(G__7393__a,0);
} 
return G__7392__delegate.call(this,args);};
G__7392.cljs$lang$maxFixedArity = 0;
G__7392.cljs$lang$applyTo = (function (arglist__7394){
var args = cljs.core.seq(arglist__7394);
return G__7392__delegate(args);
});
G__7392.cljs$core$IFn$_invoke$arity$variadic = G__7392__delegate;
return G__7392;
})()
;})(o))
;

o.error = ((function (o){
return (function() { 
var G__7395__delegate = function (args){
return cljs.core.swap_BANG_.call(null,reagent.debug.warnings,cljs.core.update_in,new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"error","error",-978969032)], null),cljs.core.conj,cljs.core.apply.call(null,cljs.core.str,args));
};
var G__7395 = function (var_args){
var args = null;
if (arguments.length > 0) {
var G__7396__i = 0, G__7396__a = new Array(arguments.length -  0);
while (G__7396__i < G__7396__a.length) {G__7396__a[G__7396__i] = arguments[G__7396__i + 0]; ++G__7396__i;}
  args = new cljs.core.IndexedSeq(G__7396__a,0);
} 
return G__7395__delegate.call(this,args);};
G__7395.cljs$lang$maxFixedArity = 0;
G__7395.cljs$lang$applyTo = (function (arglist__7397){
var args = cljs.core.seq(arglist__7397);
return G__7395__delegate(args);
});
G__7395.cljs$core$IFn$_invoke$arity$variadic = G__7395__delegate;
return G__7395;
})()
;})(o))
;

return o;
})();
}
reagent.debug.track_warnings = (function reagent$debug$track_warnings(f){
reagent.debug.tracking = true;

cljs.core.reset_BANG_.call(null,reagent.debug.warnings,null);

f.call(null);

var warns = cljs.core.deref.call(null,reagent.debug.warnings);
cljs.core.reset_BANG_.call(null,reagent.debug.warnings,null);

reagent.debug.tracking = false;

return warns;
});

//# sourceMappingURL=debug.js.map?rel=1476490288757