// Compiled by ClojureScript 1.8.51 {}
goog.provide('reagent.dom');
goog.require('cljs.core');
goog.require('cljsjs.react.dom');
goog.require('reagent.impl.util');
goog.require('reagent.impl.template');
goog.require('reagent.ratom');
goog.require('reagent.debug');
goog.require('reagent.interop');
if(typeof reagent.dom.imported !== 'undefined'){
} else {
reagent.dom.imported = null;
}
reagent.dom.module = (function reagent$dom$module(){
if(cljs.core.some_QMARK_.call(null,reagent.dom.imported)){
return reagent.dom.imported;
} else {
if(typeof ReactDOM !== 'undefined'){
return reagent.dom.imported = ReactDOM;
} else {
if(typeof require !== 'undefined'){
var or__6210__auto__ = reagent.dom.imported = require("react-dom");
if(cljs.core.truth_(or__6210__auto__)){
return or__6210__auto__;
} else {
throw (new Error("require('react-dom') failed"));
}
} else {
throw (new Error("js/ReactDOM is missing"));

}
}
}
});
if(typeof reagent.dom.roots !== 'undefined'){
} else {
reagent.dom.roots = cljs.core.atom.call(null,cljs.core.PersistentArrayMap.EMPTY);
}
reagent.dom.unmount_comp = (function reagent$dom$unmount_comp(container){
cljs.core.swap_BANG_.call(null,reagent.dom.roots,cljs.core.dissoc,container);

return (reagent.dom.module.call(null)["unmountComponentAtNode"])(container);
});
reagent.dom.render_comp = (function reagent$dom$render_comp(comp,container,callback){
var _STAR_always_update_STAR_7867 = reagent.impl.util._STAR_always_update_STAR_;
reagent.impl.util._STAR_always_update_STAR_ = true;

try{return (reagent.dom.module.call(null)["render"])(comp.call(null),container,((function (_STAR_always_update_STAR_7867){
return (function (){
var _STAR_always_update_STAR_7868 = reagent.impl.util._STAR_always_update_STAR_;
reagent.impl.util._STAR_always_update_STAR_ = false;

try{cljs.core.swap_BANG_.call(null,reagent.dom.roots,cljs.core.assoc,container,new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [comp,container], null));

if(cljs.core.some_QMARK_.call(null,callback)){
return callback.call(null);
} else {
return null;
}
}finally {reagent.impl.util._STAR_always_update_STAR_ = _STAR_always_update_STAR_7868;
}});})(_STAR_always_update_STAR_7867))
);
}finally {reagent.impl.util._STAR_always_update_STAR_ = _STAR_always_update_STAR_7867;
}});
reagent.dom.re_render_component = (function reagent$dom$re_render_component(comp,container){
return reagent.dom.render_comp.call(null,comp,container,null);
});
/**
 * Render a Reagent component into the DOM. The first argument may be
 *   either a vector (using Reagent's Hiccup syntax), or a React element. The second argument should be a DOM node.
 * 
 *   Optionally takes a callback that is called when the component is in place.
 * 
 *   Returns the mounted component instance.
 */
reagent.dom.render = (function reagent$dom$render(var_args){
var args7869 = [];
var len__7280__auto___7872 = arguments.length;
var i__7281__auto___7873 = (0);
while(true){
if((i__7281__auto___7873 < len__7280__auto___7872)){
args7869.push((arguments[i__7281__auto___7873]));

var G__7874 = (i__7281__auto___7873 + (1));
i__7281__auto___7873 = G__7874;
continue;
} else {
}
break;
}

var G__7871 = args7869.length;
switch (G__7871) {
case 2:
return reagent.dom.render.cljs$core$IFn$_invoke$arity$2((arguments[(0)]),(arguments[(1)]));

break;
case 3:
return reagent.dom.render.cljs$core$IFn$_invoke$arity$3((arguments[(0)]),(arguments[(1)]),(arguments[(2)]));

break;
default:
throw (new Error([cljs.core.str("Invalid arity: "),cljs.core.str(args7869.length)].join('')));

}
});

reagent.dom.render.cljs$core$IFn$_invoke$arity$2 = (function (comp,container){
return reagent.dom.render.call(null,comp,container,null);
});

reagent.dom.render.cljs$core$IFn$_invoke$arity$3 = (function (comp,container,callback){
reagent.ratom.flush_BANG_.call(null);

var f = (function (){
return reagent.impl.template.as_element.call(null,((cljs.core.fn_QMARK_.call(null,comp))?comp.call(null):comp));
});
return reagent.dom.render_comp.call(null,f,container,callback);
});

reagent.dom.render.cljs$lang$maxFixedArity = 3;
reagent.dom.unmount_component_at_node = (function reagent$dom$unmount_component_at_node(container){
return reagent.dom.unmount_comp.call(null,container);
});
/**
 * Returns the root DOM node of a mounted component.
 */
reagent.dom.dom_node = (function reagent$dom$dom_node(this$){
return (reagent.dom.module.call(null)["findDOMNode"])(this$);
});
reagent.impl.template.find_dom_node = reagent.dom.dom_node;
/**
 * Force re-rendering of all mounted Reagent components. This is
 *   probably only useful in a development environment, when you want to
 *   update components in response to some dynamic changes to code.
 * 
 *   Note that force-update-all may not update root components. This
 *   happens if a component 'foo' is mounted with `(render [foo])` (since
 *   functions are passed by value, and not by reference, in
 *   ClojureScript). To get around this you'll have to introduce a layer
 *   of indirection, for example by using `(render [#'foo])` instead.
 */
reagent.dom.force_update_all = (function reagent$dom$force_update_all(){
reagent.ratom.flush_BANG_.call(null);

var seq__7880_7884 = cljs.core.seq.call(null,cljs.core.vals.call(null,cljs.core.deref.call(null,reagent.dom.roots)));
var chunk__7881_7885 = null;
var count__7882_7886 = (0);
var i__7883_7887 = (0);
while(true){
if((i__7883_7887 < count__7882_7886)){
var v_7888 = cljs.core._nth.call(null,chunk__7881_7885,i__7883_7887);
cljs.core.apply.call(null,reagent.dom.re_render_component,v_7888);

var G__7889 = seq__7880_7884;
var G__7890 = chunk__7881_7885;
var G__7891 = count__7882_7886;
var G__7892 = (i__7883_7887 + (1));
seq__7880_7884 = G__7889;
chunk__7881_7885 = G__7890;
count__7882_7886 = G__7891;
i__7883_7887 = G__7892;
continue;
} else {
var temp__4657__auto___7893 = cljs.core.seq.call(null,seq__7880_7884);
if(temp__4657__auto___7893){
var seq__7880_7894__$1 = temp__4657__auto___7893;
if(cljs.core.chunked_seq_QMARK_.call(null,seq__7880_7894__$1)){
var c__7021__auto___7895 = cljs.core.chunk_first.call(null,seq__7880_7894__$1);
var G__7896 = cljs.core.chunk_rest.call(null,seq__7880_7894__$1);
var G__7897 = c__7021__auto___7895;
var G__7898 = cljs.core.count.call(null,c__7021__auto___7895);
var G__7899 = (0);
seq__7880_7884 = G__7896;
chunk__7881_7885 = G__7897;
count__7882_7886 = G__7898;
i__7883_7887 = G__7899;
continue;
} else {
var v_7900 = cljs.core.first.call(null,seq__7880_7894__$1);
cljs.core.apply.call(null,reagent.dom.re_render_component,v_7900);

var G__7901 = cljs.core.next.call(null,seq__7880_7894__$1);
var G__7902 = null;
var G__7903 = (0);
var G__7904 = (0);
seq__7880_7884 = G__7901;
chunk__7881_7885 = G__7902;
count__7882_7886 = G__7903;
i__7883_7887 = G__7904;
continue;
}
} else {
}
}
break;
}

return "Updated";
});

//# sourceMappingURL=dom.js.map?rel=1476490289994