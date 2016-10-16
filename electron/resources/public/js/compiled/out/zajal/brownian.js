// Compiled by ClojureScript 1.8.51 {}
goog.provide('zajal.brownian');
goog.require('cljs.core');
goog.require('zajal.three');
goog.require('zajal.core');
goog.require('gamma.api');
goog.require('gamma.program');
zajal.brownian.rrand = (function zajal$brownian$rrand(a,b){
return (cljs.core.rand.call(null,(a - b)) - a);
});
zajal.brownian.geometry = (function zajal$brownian$geometry(ps){
var geo = (new THREE.Geometry());
(geo["vertices"] = cljs.core.into_array.call(null,ps));

(geo["verticesNeedUpdate"] = true);

return geo;
});
zajal.brownian.v3_PLUS_ = (function zajal$brownian$v3_PLUS_(a,b){
return a.clone().add(b);
});
zajal.brownian.apply_angle_axis = (function zajal$brownian$apply_angle_axis(v,axis,angle){
return v.clone().applyAxisAngle(axis,angle);
});
zajal.brownian.rainbow = (function (){var position = gamma.api.attribute.call(null,"position",new cljs.core.Keyword(null,"vec3","vec3",1116680488));
var projectionMatrix = gamma.api.uniform.call(null,"projectionMatrix",new cljs.core.Keyword(null,"mat4","mat4",-237531594));
var viewMatrix = gamma.api.uniform.call(null,"viewMatrix",new cljs.core.Keyword(null,"mat4","mat4",-237531594));
var modelMatrix = gamma.api.uniform.call(null,"modelMatrix",new cljs.core.Keyword(null,"mat4","mat4",-237531594));
var varying = gamma.api.varying.call(null,"v_position",new cljs.core.Keyword(null,"vec3","vec3",1116680488),"highp");
return gamma.program.program.call(null,new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"vertex-shader","vertex-shader",82674447),cljs.core.PersistentArrayMap.fromArray([gamma.api.gl_position.call(null),cljs.core.reduce.call(null,gamma.api._STAR_,new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [projectionMatrix,viewMatrix,modelMatrix,gamma.api.vec4.call(null,position,(1))], null)),varying,position], true, false),new cljs.core.Keyword(null,"fragment-shader","fragment-shader",-2107324701),cljs.core.PersistentArrayMap.fromArray([gamma.api.gl_frag_color.call(null),gamma.api._STAR_.call(null,(16),gamma.api.vec4.call(null,varying,(1)))], true, false)], null));
})();
zajal.brownian.gamma_material = (new THREE.RawShaderMaterial({"vertexShader": new cljs.core.Keyword(null,"glsl","glsl",547384260).cljs$core$IFn$_invoke$arity$1(new cljs.core.Keyword(null,"vertex-shader","vertex-shader",82674447).cljs$core$IFn$_invoke$arity$1(zajal.brownian.rainbow)), "fragmentShader": new cljs.core.Keyword(null,"glsl","glsl",547384260).cljs$core$IFn$_invoke$arity$1(new cljs.core.Keyword(null,"fragment-shader","fragment-shader",-2107324701).cljs$core$IFn$_invoke$arity$1(zajal.brownian.rainbow))}));
zajal.brownian.shaded_line = (function zajal$brownian$shaded_line(ps){
return new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.line,new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"geometry","geometry",-405034994),zajal.brownian.geometry.call(null,ps),new cljs.core.Keyword(null,"material","material",460118677),zajal.brownian.gamma_material], null)], null);
});
zajal.brownian.line = (function zajal$brownian$line(p__8899,ps){
var map__8902 = p__8899;
var map__8902__$1 = ((((!((map__8902 == null)))?((((map__8902.cljs$lang$protocol_mask$partition0$ & (64))) || (map__8902.cljs$core$ISeq$))?true:false):false))?cljs.core.apply.call(null,cljs.core.hash_map,map__8902):map__8902);
var color = cljs.core.get.call(null,map__8902__$1,new cljs.core.Keyword(null,"color","color",1011675173),(16777215));
return new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.line,new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"geometry","geometry",-405034994),zajal.brownian.geometry.call(null,ps),new cljs.core.Keyword(null,"material","material",460118677),zajal.three.line_material.call(null,color)], null)], null);
});
zajal.brownian.rand_point = (function zajal$brownian$rand_point(v){
return zajal.three.v3.call(null,zajal.brownian.rrand.call(null,-0.5,0.5),zajal.brownian.rrand.call(null,-0.5,0.5),zajal.brownian.rrand.call(null,-0.5,0.5)).multiplyScalar(v);
});
zajal.brownian.step_size = 0.01;
zajal.brownian.start = new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"trail","trail",-272340561),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.v3.call(null,(0),(0),(0))], null)], null);
zajal.brownian.constrain = (function zajal$brownian$constrain(trail,length){
return cljs.core.vec.call(null,cljs.core.take_last.call(null,length,trail));
});
zajal.brownian.grow = (function zajal$brownian$grow(trail,p){
return cljs.core.conj.call(null,trail,p);
});
zajal.brownian.grow_random = (function zajal$brownian$grow_random(trail){
return zajal.brownian.grow.call(null,trail,zajal.brownian.v3_PLUS_.call(null,cljs.core.last.call(null,trail),zajal.brownian.rand_point.call(null,zajal.brownian.step_size)));
});
zajal.brownian.remap = (function zajal$brownian$remap(v,low1,high1,low2,high2){
return (low2 + (((v - low1) * (high2 - low2)) / (high1 - low1)));
});
zajal.brownian.grow_on_mouse = (function zajal$brownian$grow_on_mouse(trail,p__8904){
var map__8907 = p__8904;
var map__8907__$1 = ((((!((map__8907 == null)))?((((map__8907.cljs$lang$protocol_mask$partition0$ & (64))) || (map__8907.cljs$core$ISeq$))?true:false):false))?cljs.core.apply.call(null,cljs.core.hash_map,map__8907):map__8907);
var mouse = cljs.core.get.call(null,map__8907__$1,new cljs.core.Keyword(null,"mouse","mouse",478628972));
if(cljs.core.truth_(mouse.call(null,new cljs.core.Keyword(null,"pressed?","pressed?",-473083504)))){
return zajal.brownian.grow.call(null,trail,zajal.three.v3.call(null,zajal.brownian.remap.call(null,new cljs.core.Keyword(null,"x","x",2099068185).cljs$core$IFn$_invoke$arity$1(mouse),(0),(600),-0.5,0.5),zajal.brownian.remap.call(null,new cljs.core.Keyword(null,"y","y",-1757859776).cljs$core$IFn$_invoke$arity$1(mouse),(0),(600),0.5,-0.5),(0)));
} else {
return trail;
}
});
zajal.brownian.turn_trail = (function zajal$brownian$turn_trail(trail){
var axis = zajal.three.v3.call(null,(0),(1),(0));
return cljs.core.map.call(null,((function (axis){
return (function (p1__8909_SHARP_){
return zajal.brownian.apply_angle_axis.call(null,p1__8909_SHARP_,axis,0.01);
});})(axis))
,trail);
});
zajal.brownian.step = (function zajal$brownian$step(state,input){
return cljs.core.assoc.call(null,cljs.core.update.call(null,state,new cljs.core.Keyword(null,"trail","trail",-272340561),(function (p1__8910_SHARP_){
return zajal.brownian.turn_trail.call(null,zajal.brownian.grow_on_mouse.call(null,zajal.brownian.grow_random.call(null,p1__8910_SHARP_),input));
})),new cljs.core.Keyword(null,"angle","angle",1622094254),(new cljs.core.Keyword(null,"elapsed","elapsed",-1293489698).cljs$core$IFn$_invoke$arity$1(new cljs.core.Keyword(null,"time","time",1385887882).cljs$core$IFn$_invoke$arity$1(input)) / (4000)));
});
zajal.brownian.draw = (function zajal$brownian$draw(p__8911){
var map__8914 = p__8911;
var map__8914__$1 = ((((!((map__8914 == null)))?((((map__8914.cljs$lang$protocol_mask$partition0$ & (64))) || (map__8914.cljs$core$ISeq$))?true:false):false))?cljs.core.apply.call(null,cljs.core.hash_map,map__8914):map__8914);
var trail = cljs.core.get.call(null,map__8914__$1,new cljs.core.Keyword(null,"trail","trail",-272340561));
var angle = cljs.core.get.call(null,map__8914__$1,new cljs.core.Keyword(null,"angle","angle",1622094254));
return new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.basic_scene,new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"width","width",-384071477),(600),new cljs.core.Keyword(null,"height","height",1025178622),(600)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.mesh,new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"geometry","geometry",-405034994),zajal.brownian.geometry.call(null,trail),new cljs.core.Keyword(null,"material","material",460118677),zajal.brownian.gamma_material], null)], null),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.three.obj3d,new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"rotation","rotation",-1728051644),zajal.three.euler.call(null,(0),angle,(0))], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [zajal.brownian.shaded_line,trail], null)], null)], null);
});
if(typeof zajal.brownian.sketch !== 'undefined'){
} else {
zajal.brownian.sketch = zajal.core.sketch.call(null,zajal.brownian.start,new cljs.core.Var(function(){return zajal.brownian.step;},new cljs.core.Symbol("zajal.brownian","step","zajal.brownian/step",290622403,null),cljs.core.PersistentHashMap.fromArrays([new cljs.core.Keyword(null,"ns","ns",441598760),new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"file","file",-1269645878),new cljs.core.Keyword(null,"end-column","end-column",1425389514),new cljs.core.Keyword(null,"column","column",2078222095),new cljs.core.Keyword(null,"line","line",212345235),new cljs.core.Keyword(null,"end-line","end-line",1837326455),new cljs.core.Keyword(null,"arglists","arglists",1661989754),new cljs.core.Keyword(null,"doc","doc",1913296891),new cljs.core.Keyword(null,"test","test",577538877)],[new cljs.core.Symbol(null,"zajal.brownian","zajal.brownian",1091691552,null),new cljs.core.Symbol(null,"step","step",-1365547645,null),"src/zajal/brownian.cljs",11,1,95,95,cljs.core.list(new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Symbol(null,"state","state",-348086572,null),new cljs.core.Symbol(null,"input","input",-2097503808,null)], null)),null,(cljs.core.truth_(zajal.brownian.step)?zajal.brownian.step.cljs$lang$test:null)])),new cljs.core.Var(function(){return zajal.brownian.draw;},new cljs.core.Symbol("zajal.brownian","draw","zajal.brownian/draw",712537889,null),cljs.core.PersistentHashMap.fromArrays([new cljs.core.Keyword(null,"ns","ns",441598760),new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"file","file",-1269645878),new cljs.core.Keyword(null,"end-column","end-column",1425389514),new cljs.core.Keyword(null,"column","column",2078222095),new cljs.core.Keyword(null,"line","line",212345235),new cljs.core.Keyword(null,"end-line","end-line",1837326455),new cljs.core.Keyword(null,"arglists","arglists",1661989754),new cljs.core.Keyword(null,"doc","doc",1913296891),new cljs.core.Keyword(null,"test","test",577538877)],[new cljs.core.Symbol(null,"zajal.brownian","zajal.brownian",1091691552,null),new cljs.core.Symbol(null,"draw","draw",-1296104095,null),"src/zajal/brownian.cljs",11,1,104,104,cljs.core.list(new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"keys","keys",1068423698),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Symbol(null,"trail","trail",1368190966,null),new cljs.core.Symbol(null,"angle","angle",-1032341515,null)], null)], null)], null)),null,(cljs.core.truth_(zajal.brownian.draw)?zajal.brownian.draw.cljs$lang$test:null)])));
}

//# sourceMappingURL=brownian.js.map?rel=1476490292449