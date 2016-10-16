// Compiled by ClojureScript 1.8.51 {}
goog.provide('zajal.core');
goog.require('cljs.core');
goog.require('reagent.core');
cljs.core.enable_console_print_BANG_.call(null);
if(typeof zajal.core.start_time !== 'undefined'){
} else {
zajal.core.start_time = Date.now();
}
if(typeof zajal.core.mouse_state !== 'undefined'){
} else {
zajal.core.mouse_state = cljs.core.atom.call(null,new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"x","x",2099068185),(0),new cljs.core.Keyword(null,"y","y",-1757859776),(0),new cljs.core.Keyword(null,"pressed","pressed",1100937946),false], null));
}
document.onmousemove = (function (p1__7989_SHARP_){
return cljs.core.swap_BANG_.call(null,zajal.core.mouse_state,cljs.core.assoc,new cljs.core.Keyword(null,"x","x",2099068185),p1__7989_SHARP_.pageX,new cljs.core.Keyword(null,"y","y",-1757859776),p1__7989_SHARP_.pageY);
});
document.onmousedown = (function (){
return cljs.core.swap_BANG_.call(null,zajal.core.mouse_state,cljs.core.assoc,new cljs.core.Keyword(null,"pressed?","pressed?",-473083504),true);
});
document.onmouseup = (function (){
return cljs.core.swap_BANG_.call(null,zajal.core.mouse_state,cljs.core.assoc,new cljs.core.Keyword(null,"pressed?","pressed?",-473083504),false);
});
zajal.core.input = (function zajal$core$input(){
var t = Date.now();
return new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"time","time",1385887882),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"elapsed","elapsed",-1293489698),(t - zajal.core.start_time)], null),new cljs.core.Keyword(null,"mouse","mouse",478628972),cljs.core.deref.call(null,zajal.core.mouse_state)], null);
});
zajal.core.sketch = (function zajal$core$sketch(start,step,draw){
step.call(null,cljs.core.PersistentArrayMap.EMPTY,zajal.core.input.call(null));

var state = reagent.core.atom.call(null,start);
var component = ((function (state){
return (function zajal$core$sketch_$_component(){
return new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [draw,cljs.core.deref.call(null,state)], null);
});})(state))
;
var render_loop = ((function (state){
return (function zajal$core$sketch_$_render_loop(t){
stats.begin();

cljs.core.swap_BANG_.call(null,state,step,zajal.core.input.call(null));

stats.end();

return window.requestAnimationFrame(zajal$core$sketch_$_render_loop);
});})(state))
;
reagent.core.render_component.call(null,new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [component], null),document.getElementById("app"));

return render_loop.call(null,(0));
});

//# sourceMappingURL=core.js.map?rel=1476490290162