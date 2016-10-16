// Compiled by ClojureScript 1.8.51 {}
goog.provide('zajal.three');
goog.require('cljs.core');
goog.require('reagent.core');
zajal.three.renderer = reagent.core.adapt_react_class.call(null,ReactTHREE.Renderer);
zajal.three.camera = reagent.core.adapt_react_class.call(null,ReactTHREE.PerspectiveCamera);
zajal.three.scene = reagent.core.adapt_react_class.call(null,ReactTHREE.Scene);
zajal.three.obj3d = reagent.core.adapt_react_class.call(null,ReactTHREE.Object3D);
zajal.three.mesh = reagent.core.adapt_react_class.call(null,ReactTHREE.Mesh);
zajal.three.line = reagent.core.adapt_react_class.call(null,ReactTHREE.Line);
zajal.three.v3 = (function zajal$three$v3(x,y,z){
return (new THREE.Vector3(x,y,z));
});
zajal.three.euler = (function zajal$three$euler(x,y,z){
return (new THREE.Euler(x,y,z));
});
zajal.three.line_material = (function zajal$three$line_material(color){
return (new THREE.LineBasicMaterial({"color": color}));
});
zajal.three.basic_scene = (function zajal$three$basic_scene(var_args){
var args__7287__auto__ = [];
var len__7280__auto___7997 = arguments.length;
var i__7281__auto___7998 = (0);
while(true){
if((i__7281__auto___7998 < len__7280__auto___7997)){
args__7287__auto__.push((arguments[i__7281__auto___7998]));

var G__7999 = (i__7281__auto___7998 + (1));
i__7281__auto___7998 = G__7999;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((1) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((1)),(0),null)):null);
return zajal.three.basic_scene.cljs$core$IFn$_invoke$arity$variadic((arguments[(0)]),argseq__7288__auto__);
});

zajal.three.basic_scene.cljs$core$IFn$_invoke$arity$variadic = (function (p__7994,children){
var map__7995 = p__7994;
var map__7995__$1 = ((((!((map__7995 == null)))?((((map__7995.cljs$lang$protocol_mask$partition0$ & (64))) || (map__7995.cljs$core$ISeq$))?true:false):false))?cljs.core.apply.call(null,cljs.core.hash_map,map__7995):map__7995);
var width = cljs.core.get.call(null,map__7995__$1,new cljs.core.Keyword(null,"width","width",-384071477));
var height = cljs.core.get.call(null,map__7995__$1,new cljs.core.Keyword(null,"height","height",1025178622));
return new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.renderer,new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"width","width",-384071477),width,new cljs.core.Keyword(null,"height","height",1025178622),height,new cljs.core.Keyword(null,"antialias","antialias",-2073640634),false], null),cljs.core.into.call(null,new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.scene,new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"camera","camera",-1190348585),"cam",new cljs.core.Keyword(null,"width","width",-384071477),width,new cljs.core.Keyword(null,"height","height",1025178622),height], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.camera,new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"name","name",1843675177),"cam",new cljs.core.Keyword(null,"position","position",-2011731912),zajal.three.v3.call(null,(0),(0),(2)),new cljs.core.Keyword(null,"lookat","lookat",-746583196),zajal.three.v3.call(null,(0),(0),(0))], null)], null)], null),children)], null);
});

zajal.three.basic_scene.cljs$lang$maxFixedArity = (1);

zajal.three.basic_scene.cljs$lang$applyTo = (function (seq7992){
var G__7993 = cljs.core.first.call(null,seq7992);
var seq7992__$1 = cljs.core.next.call(null,seq7992);
return zajal.three.basic_scene.cljs$core$IFn$_invoke$arity$variadic(G__7993,seq7992__$1);
});

//# sourceMappingURL=three.js.map?rel=1476490290182