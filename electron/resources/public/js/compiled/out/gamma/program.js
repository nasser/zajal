// Compiled by ClojureScript 1.8.51 {}
goog.provide('gamma.program');
goog.require('cljs.core');
goog.require('gamma.emit.tag');
goog.require('gamma.emit.statement');
goog.require('gamma.emit.operator');
goog.require('fipp.engine');
goog.require('gamma.emit.emit');
goog.require('gamma.api');
goog.require('gamma.compiler.core');
goog.require('gamma.emit.construct');
goog.require('gamma.emit.fun');
gamma.program.ast = (function gamma$program$ast(inputs){
return cljs.core.apply.call(null,gamma.api.block,cljs.core.mapv.call(null,(function (p__8878){
var vec__8879 = p__8878;
var k = cljs.core.nth.call(null,vec__8879,(0),null);
var v = cljs.core.nth.call(null,vec__8879,(1),null);
return gamma.api.set.call(null,k,v);
}),inputs));
});
gamma.program.precision_defaults = (function gamma$program$precision_defaults(p){
var x = cljs.core.map.call(null,(function (p__8882){
var vec__8883 = p__8882;
var k = cljs.core.nth.call(null,vec__8883,(0),null);
var v = cljs.core.nth.call(null,vec__8883,(1),null);
return [cljs.core.str("precision "),cljs.core.str(cljs.core.name.call(null,v)),cljs.core.str(" "),cljs.core.str(cljs.core.name.call(null,k)),cljs.core.str(";\n")].join('');
}),p);
if(cljs.core.empty_QMARK_.call(null,x)){
return "";
} else {
return cljs.core.apply.call(null,cljs.core.str,x);
}
});
gamma.program.glsl = (function gamma$program$glsl(shader,precision){
var p = precision;
return [cljs.core.str(gamma.program.precision_defaults.call(null,p)),cljs.core.str((function (){var sb__7196__auto__ = (new goog.string.StringBuffer());
var _STAR_print_newline_STAR_8886_8888 = cljs.core._STAR_print_newline_STAR_;
var _STAR_print_fn_STAR_8887_8889 = cljs.core._STAR_print_fn_STAR_;
cljs.core._STAR_print_newline_STAR_ = true;

cljs.core._STAR_print_fn_STAR_ = ((function (_STAR_print_newline_STAR_8886_8888,_STAR_print_fn_STAR_8887_8889,sb__7196__auto__,p){
return (function (x__7197__auto__){
return sb__7196__auto__.append(x__7197__auto__);
});})(_STAR_print_newline_STAR_8886_8888,_STAR_print_fn_STAR_8887_8889,sb__7196__auto__,p))
;

try{fipp.engine.pprint_document.call(null,gamma.emit.emit.emit.call(null,new cljs.core.Keyword(null,"ir","ir",-1141752677).cljs$core$IFn$_invoke$arity$1(shader),shader),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"width","width",-384071477),(80)], null));
}finally {cljs.core._STAR_print_fn_STAR_ = _STAR_print_fn_STAR_8887_8889;

cljs.core._STAR_print_newline_STAR_ = _STAR_print_newline_STAR_8886_8888;
}
return [cljs.core.str(sb__7196__auto__)].join('');
})())].join('');
});
gamma.program.shader = (function gamma$program$shader(shader__$1,opts){
var ast = gamma.program.ast.call(null,shader__$1);
var ir = gamma.compiler.core.compile.call(null,ast);
var v = gamma.compiler.core.variables.call(null,ir);
var locals = cljs.core.filter.call(null,((function (ast,ir,v){
return (function (p1__8890_SHARP_){
return cljs.core.not.call(null,new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"attribute","attribute",-2074029119),null,new cljs.core.Keyword(null,"varying","varying",685535123),null,new cljs.core.Keyword(null,"uniform","uniform",496503348),null], null), null).call(null,new cljs.core.Keyword(null,"storage","storage",1867247511).cljs$core$IFn$_invoke$arity$1(p1__8890_SHARP_)));
});})(ast,ir,v))
,v);
var globals = cljs.core.filter.call(null,((function (ast,ir,v,locals){
return (function (p1__8891_SHARP_){
return new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"attribute","attribute",-2074029119),null,new cljs.core.Keyword(null,"varying","varying",685535123),null,new cljs.core.Keyword(null,"uniform","uniform",496503348),null], null), null).call(null,new cljs.core.Keyword(null,"storage","storage",1867247511).cljs$core$IFn$_invoke$arity$1(p1__8891_SHARP_));
});})(ast,ir,v,locals))
,v);
var outputs = cljs.core.keys.call(null,shader__$1);
var inputs = clojure.set.difference.call(null,cljs.core.into.call(null,cljs.core.PersistentHashSet.EMPTY,globals),cljs.core.into.call(null,cljs.core.PersistentHashSet.EMPTY,outputs));
var p = new cljs.core.PersistentArrayMap(null, 6, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"shader","shader",1492833021),new cljs.core.Keyword(null,"inputs","inputs",865803858),inputs,new cljs.core.Keyword(null,"outputs","outputs",-1896513034),outputs,new cljs.core.Keyword(null,"locals","locals",535295783),locals,new cljs.core.Keyword(null,"ir","ir",-1141752677),ir,new cljs.core.Keyword(null,"ast","ast",-860334068),ast], null);

return cljs.core.assoc.call(null,p,new cljs.core.Keyword(null,"glsl","glsl",547384260),gamma.program.glsl.call(null,p,opts));
});
gamma.program.program_inputs = (function gamma$program$program_inputs(vs,fs){
return cljs.core.into.call(null,new cljs.core.Keyword(null,"inputs","inputs",865803858).cljs$core$IFn$_invoke$arity$1(vs),cljs.core.filter.call(null,(function (p1__8892_SHARP_){
return cljs.core._EQ_.call(null,new cljs.core.Keyword(null,"uniform","uniform",496503348),new cljs.core.Keyword(null,"storage","storage",1867247511).cljs$core$IFn$_invoke$arity$1(p1__8892_SHARP_));
}),new cljs.core.Keyword(null,"inputs","inputs",865803858).cljs$core$IFn$_invoke$arity$1(fs)));
});
gamma.program.program = (function gamma$program$program(x){
var map__8895 = x;
var map__8895__$1 = ((((!((map__8895 == null)))?((((map__8895.cljs$lang$protocol_mask$partition0$ & (64))) || (map__8895.cljs$core$ISeq$))?true:false):false))?cljs.core.apply.call(null,cljs.core.hash_map,map__8895):map__8895);
var vertex_shader = cljs.core.get.call(null,map__8895__$1,new cljs.core.Keyword(null,"vertex-shader","vertex-shader",82674447));
var fragment_shader = cljs.core.get.call(null,map__8895__$1,new cljs.core.Keyword(null,"fragment-shader","fragment-shader",-2107324701));
var precision = cljs.core.get.call(null,map__8895__$1,new cljs.core.Keyword(null,"precision","precision",-1175707478));
var vs = gamma.program.shader.call(null,vertex_shader,precision);
var fs = gamma.program.shader.call(null,fragment_shader,precision);
return new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"program","program",781564284),new cljs.core.Keyword(null,"vertex-shader","vertex-shader",82674447),vs,new cljs.core.Keyword(null,"fragment-shader","fragment-shader",-2107324701),fs,new cljs.core.Keyword(null,"inputs","inputs",865803858),gamma.program.program_inputs.call(null,vs,fs)], null);
});

//# sourceMappingURL=program.js.map?rel=1476490292388