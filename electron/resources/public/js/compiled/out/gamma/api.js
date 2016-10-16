// Compiled by ClojureScript 1.8.51 {}
goog.provide('gamma.api');
goog.require('cljs.core');
goog.require('gamma.ast');
gamma.api.vector_type = (function gamma$api$vector_type(l){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"vector","vector",1902966158),new cljs.core.Keyword(null,"member-type","member-type",645139088),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"length","length",588987862),l], null);
});
gamma.api.array_type = (function gamma$api$array_type(type,length){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"array","array",-2080713842),new cljs.core.Keyword(null,"member-type","member-type",645139088),type,new cljs.core.Keyword(null,"length","length",588987862),length], null);
});
gamma.api.attribute = (function gamma$api$attribute(name,type){
return new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),name,new cljs.core.Keyword(null,"type","type",1174270348),type,new cljs.core.Keyword(null,"storage","storage",1867247511),new cljs.core.Keyword(null,"attribute","attribute",-2074029119)], null);
});
gamma.api.uniform = (function gamma$api$uniform(name,type){
return new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),name,new cljs.core.Keyword(null,"type","type",1174270348),type,new cljs.core.Keyword(null,"storage","storage",1867247511),new cljs.core.Keyword(null,"uniform","uniform",496503348)], null);
});
gamma.api.varying = (function gamma$api$varying(name,type,precision){
return new cljs.core.PersistentArrayMap(null, 5, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),name,new cljs.core.Keyword(null,"type","type",1174270348),type,new cljs.core.Keyword(null,"storage","storage",1867247511),new cljs.core.Keyword(null,"varying","varying",685535123),new cljs.core.Keyword(null,"precision","precision",-1175707478),precision], null);
});
gamma.api.variable = (function gamma$api$variable(var_args){
var args8048 = [];
var len__7280__auto___8051 = arguments.length;
var i__7281__auto___8052 = (0);
while(true){
if((i__7281__auto___8052 < len__7280__auto___8051)){
args8048.push((arguments[i__7281__auto___8052]));

var G__8053 = (i__7281__auto___8052 + (1));
i__7281__auto___8052 = G__8053;
continue;
} else {
}
break;
}

var G__8050 = args8048.length;
switch (G__8050) {
case 1:
return gamma.api.variable.cljs$core$IFn$_invoke$arity$1((arguments[(0)]));

break;
case 2:
return gamma.api.variable.cljs$core$IFn$_invoke$arity$2((arguments[(0)]),(arguments[(1)]));

break;
default:
throw (new Error([cljs.core.str("Invalid arity: "),cljs.core.str(args8048.length)].join('')));

}
});

gamma.api.variable.cljs$core$IFn$_invoke$arity$1 = (function (x){
return gamma.api.variable.call(null,x,null);
});

gamma.api.variable.cljs$core$IFn$_invoke$arity$2 = (function (x,t){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),x,new cljs.core.Keyword(null,"type","type",1174270348),t], null);
});

gamma.api.variable.cljs$lang$maxFixedArity = 2;
gamma.api.gl_position = (function gamma$api$gl_position(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_Position",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null);
});
gamma.api.gl_point_size = (function gamma$api$gl_point_size(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_PointSize",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"float","float",-1732389368)], null);
});
gamma.api.gl_frag_coord = (function gamma$api$gl_frag_coord(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_FragCoord",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null);
});
gamma.api.gl_front_facing = (function gamma$api$gl_front_facing(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_FrontFacing",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321)], null);
});
gamma.api.gl_point_coord = (function gamma$api$gl_point_coord(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_PointCoord",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec2","vec2",-762258640)], null);
});
gamma.api.gl_frag_color = (function gamma$api$gl_frag_color(){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),"gl_FragColor",new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null);
});
gamma.api.gl_frag_data = (function gamma$api$gl_frag_data(n){
return new cljs.core.PersistentArrayMap(null, 3, [new cljs.core.Keyword(null,"tag","tag",-1290361223),new cljs.core.Keyword(null,"variable","variable",-281346492),new cljs.core.Keyword(null,"name","name",1843675177),[cljs.core.str("gl_FragData"),cljs.core.str(n)].join(''),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null);
});
gamma.api.ensure_term = (function gamma$api$ensure_term(x){
if(cljs.core.truth_(gamma.ast.term_QMARK_.call(null,x))){
return x;
} else {
return gamma.ast.literal.call(null,x);
}
});
gamma.api.arithmetic_type = (function gamma$api$arithmetic_type(a,b){
var t = cljs.core.into.call(null,cljs.core.PersistentHashSet.EMPTY,cljs.core.map.call(null,new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [a,b], null)));
if(cljs.core._EQ_.call(null,(1),cljs.core.count.call(null,t))){
return new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 8, [new cljs.core.Keyword(null,"int","int",-1741416922),null,new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"ivec4","ivec4",-537108439),null,new cljs.core.Keyword(null,"ivec2","ivec2",148465998),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null,new cljs.core.Keyword(null,"ivec3","ivec3",-104254851),null], null), null).call(null,cljs.core.first.call(null,t));
} else {
return null;
}
});
gamma.api._PLUS_ = (function gamma$api$_PLUS_(a,b){
var a__$1 = gamma.api.ensure_term.call(null,a);
var b__$1 = gamma.api.ensure_term.call(null,b);
var t = gamma.api.arithmetic_type.call(null,a__$1,b__$1);
if(cljs.core.truth_(t)){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"+","+",1913524883),a__$1,b__$1),new cljs.core.Keyword(null,"type","type",1174270348),t);
} else {
throw (new Error([cljs.core.str("Arguments to + must have type :int or :float")].join('')));
}
});
gamma.api._ = (function gamma$api$_(a,b){
var a__$1 = gamma.api.ensure_term.call(null,a);
var b__$1 = gamma.api.ensure_term.call(null,b);
var t = gamma.api.arithmetic_type.call(null,a__$1,b__$1);
if(cljs.core.truth_(t)){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"-","-",-2112348439),a__$1,b__$1),new cljs.core.Keyword(null,"type","type",1174270348),t);
} else {
throw (new Error([cljs.core.str("Arguments to - must have type :int or :float")].join('')));
}
});
gamma.api._STAR_ = (function gamma$api$_STAR_(a,b){
var a__$1 = gamma.api.ensure_term.call(null,a);
var b__$1 = gamma.api.ensure_term.call(null,b);
var at = new cljs.core.Keyword(null,"type","type",1174270348).cljs$core$IFn$_invoke$arity$1(a__$1);
var bt = new cljs.core.Keyword(null,"type","type",1174270348).cljs$core$IFn$_invoke$arity$1(b__$1);
var temp__4655__auto__ = (function (){var or__6210__auto__ = cljs.core.PersistentHashMap.fromArrays([new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat3","mat3",402087048),new cljs.core.Keyword(null,"vec3","vec3",1116680488)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat3","mat3",402087048),new cljs.core.Keyword(null,"mat3","mat3",402087048)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"vec3","vec3",1116680488)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat4","mat4",-237531594),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat2","mat2",238424363),new cljs.core.Keyword(null,"vec2","vec2",-762258640)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat4","mat4",-237531594),new cljs.core.Keyword(null,"mat4","mat4",-237531594)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.Keyword(null,"vec2","vec2",-762258640)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"mat2","mat2",238424363),new cljs.core.Keyword(null,"mat2","mat2",238424363)], null)],[new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"mat3","mat3",402087048),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.Keyword(null,"mat4","mat4",-237531594),new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"mat2","mat2",238424363)]).call(null,new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [at,bt], null));
if(cljs.core.truth_(or__6210__auto__)){
return or__6210__auto__;
} else {
return cljs.core.PersistentArrayMap.fromArray([new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"mat2","mat2",238424363),null], null), null),new cljs.core.Keyword(null,"mat2","mat2",238424363),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"mat3","mat3",402087048),null,new cljs.core.Keyword(null,"float","float",-1732389368),null], null), null),new cljs.core.Keyword(null,"mat3","mat3",402087048),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"mat4","mat4",-237531594),null], null), null),new cljs.core.Keyword(null,"mat4","mat4",-237531594),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null),new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null], null), null),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 2, [new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null], null), null),new cljs.core.Keyword(null,"vec4","vec4",631182126)], true, false).call(null,cljs.core.PersistentHashSet.fromArray([bt,at], true));
}
})();
if(cljs.core.truth_(temp__4655__auto__)){
var t = temp__4655__auto__;
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"*","*",-1294732318),a__$1,b__$1),new cljs.core.Keyword(null,"type","type",1174270348),t);
} else {
throw (new Error([cljs.core.str("Arguments to * of incompatible type: "),cljs.core.str(at),cljs.core.str(","),cljs.core.str(bt)].join('')));
}
});
gamma.api.div = (function gamma$api$div(a,b){
var a__$1 = gamma.api.ensure_term.call(null,a);
var b__$1 = gamma.api.ensure_term.call(null,b);
var t = gamma.api.arithmetic_type.call(null,a__$1,b__$1);
if(cljs.core.truth_(t)){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"div","div",1057191632),a__$1,b__$1),new cljs.core.Keyword(null,"type","type",1174270348),t);
} else {
throw (new Error([cljs.core.str("Arguments to div must have type :int or :float")].join('')));
}
});
gamma.api._LT_ = (function gamma$api$_LT_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"<","<",-646864291),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api._GT_ = (function gamma$api$_GT_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,">",">",-555517146),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api._LT__EQ_ = (function gamma$api$_LT__EQ_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"<=","<=",-395636158),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api._GT__EQ_ = (function gamma$api$_GT__EQ_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,">=",">=",-623615505),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api._EQ__EQ_ = (function gamma$api$_EQ__EQ_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"==","==",-1874649676),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.not_EQ_ = (function gamma$api$not_EQ_(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"!=","!=",-1841737356),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.and = (function gamma$api$and(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"and","and",-971899817),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.or = (function gamma$api$or(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"or","or",235744169),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.xor = (function gamma$api$xor(a,b){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"xor","xor",-1119942254),gamma.api.ensure_term.call(null,a),gamma.api.ensure_term.call(null,b)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.not = (function gamma$api$not(a){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"not","not",-595976884),gamma.api.ensure_term.call(null,a)),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bool","bool",1444635321));
});
gamma.api.if$ = (function gamma$api$if(c,a,b){
var a__$1 = gamma.api.ensure_term.call(null,a);
var b__$1 = gamma.api.ensure_term.call(null,b);
var at = new cljs.core.Keyword(null,"type","type",1174270348).cljs$core$IFn$_invoke$arity$1(a__$1);
var bt = new cljs.core.Keyword(null,"type","type",1174270348).cljs$core$IFn$_invoke$arity$1(b__$1);
if(cljs.core._EQ_.call(null,at,bt)){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"if","if",-458814265),c,gamma.ast.term.call(null,new cljs.core.Keyword(null,"block","block",664686210),a__$1),gamma.ast.term.call(null,new cljs.core.Keyword(null,"block","block",664686210),b__$1)),new cljs.core.Keyword(null,"type","type",1174270348),at);
} else {
throw (new Error([cljs.core.str("Branches of if term are not of same type: "),cljs.core.str(at),cljs.core.str(", "),cljs.core.str(bt)].join('')));
}
});
gamma.api.infer_parameterized_type = (function gamma$api$infer_parameterized_type(rule,args){
var prule = new cljs.core.Keyword(null,"parameter","parameter",1978789597).cljs$core$IFn$_invoke$arity$1(rule);
var input_types = new cljs.core.Keyword(null,"input","input",556931961).cljs$core$IFn$_invoke$arity$1(rule);
if(cljs.core.not_EQ_.call(null,cljs.core.count.call(null,input_types),cljs.core.count.call(null,args))){
return new cljs.core.Keyword(null,"fail","fail",1706214930);
} else {
var input = args;
var expected = input_types;
var parameter = null;
while(true){
if((cljs.core.empty_QMARK_.call(null,expected)) || (cljs.core.empty_QMARK_.call(null,input))){
if((cljs.core.empty_QMARK_.call(null,expected)) && (cljs.core.empty_QMARK_.call(null,input))){
if(cljs.core.truth_(prule.call(null,new cljs.core.Keyword(null,"output","output",-1105869043).cljs$core$IFn$_invoke$arity$1(rule)))){
return parameter;
} else {
return new cljs.core.Keyword(null,"output","output",-1105869043).cljs$core$IFn$_invoke$arity$1(rule);
}
} else {
return new cljs.core.Keyword(null,"fail","fail",1706214930);
}
} else {
var i = cljs.core.first.call(null,input);
var e = cljs.core.first.call(null,expected);
var p = prule.call(null,e);
if(cljs.core.truth_(p)){
if(cljs.core.truth_(parameter)){
if(cljs.core._EQ_.call(null,parameter,i)){
var G__8055 = cljs.core.next.call(null,input);
var G__8056 = cljs.core.next.call(null,expected);
var G__8057 = parameter;
input = G__8055;
expected = G__8056;
parameter = G__8057;
continue;
} else {
return new cljs.core.Keyword(null,"fail","fail",1706214930);
}
} else {
if(cljs.core.truth_(p.call(null,i))){
var G__8058 = cljs.core.next.call(null,input);
var G__8059 = cljs.core.next.call(null,expected);
var G__8060 = p.call(null,i);
input = G__8058;
expected = G__8059;
parameter = G__8060;
continue;
} else {
return new cljs.core.Keyword(null,"fail","fail",1706214930);
}
}
} else {
if(cljs.core._EQ_.call(null,i,e)){
var G__8061 = cljs.core.next.call(null,input);
var G__8062 = cljs.core.next.call(null,expected);
var G__8063 = parameter;
input = G__8061;
expected = G__8062;
parameter = G__8063;
continue;
} else {
return new cljs.core.Keyword(null,"fail","fail",1706214930);
}
}
}
break;
}
}
});
gamma.api.build_standard_function_term = (function gamma$api$build_standard_function_term(name,specs,args){
var t = cljs.core.apply.call(null,gamma.ast.term,name,args);
var temp__4655__auto__ = cljs.core.first.call(null,cljs.core.filter.call(null,((function (t){
return (function (p1__8064_SHARP_){
return cljs.core.not_EQ_.call(null,new cljs.core.Keyword(null,"fail","fail",1706214930),p1__8064_SHARP_);
});})(t))
,cljs.core.map.call(null,((function (t){
return (function (p1__8065_SHARP_){
return gamma.api.infer_parameterized_type.call(null,p1__8065_SHARP_,cljs.core.map.call(null,new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"body","body",-2049205669).cljs$core$IFn$_invoke$arity$1(t)));
});})(t))
,specs)));
if(cljs.core.truth_(temp__4655__auto__)){
var result = temp__4655__auto__;
return cljs.core.assoc.call(null,t,new cljs.core.Keyword(null,"type","type",1174270348),result);
} else {
throw (new Error(cljs.core.apply.call(null,cljs.core.str,"Wrong argument types for term ",cljs.core.name.call(null,name),": ",cljs.core.interpose.call(null," ,",cljs.core.map.call(null,new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"body","body",-2049205669).cljs$core$IFn$_invoke$arity$1(t))))));
}
});
gamma.api.ceil = (function gamma$api$ceil(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8136 = arguments.length;
var i__7281__auto___8137 = (0);
while(true){
if((i__7281__auto___8137 < len__7280__auto___8136)){
args__7287__auto__.push((arguments[i__7281__auto___8137]));

var G__8138 = (i__7281__auto___8137 + (1));
i__7281__auto___8137 = G__8138;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.ceil.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.ceil.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"ceil","ceil",-1824929952),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"ceil","ceil",-1824929952),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.ceil.cljs$lang$maxFixedArity = (0);

gamma.api.ceil.cljs$lang$applyTo = (function (seq8066){
return gamma.api.ceil.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8066));
});

gamma.api.atan = (function gamma$api$atan(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8139 = arguments.length;
var i__7281__auto___8140 = (0);
while(true){
if((i__7281__auto___8140 < len__7280__auto___8139)){
args__7287__auto__.push((arguments[i__7281__auto___8140]));

var G__8141 = (i__7281__auto___8140 + (1));
i__7281__auto___8140 = G__8141;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.atan.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.atan.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"atan","atan",1627885634),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"atan","atan",1627885634),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"atan","atan",1627885634),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.atan.cljs$lang$maxFixedArity = (0);

gamma.api.atan.cljs$lang$applyTo = (function (seq8067){
return gamma.api.atan.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8067));
});

gamma.api.sign = (function gamma$api$sign(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8142 = arguments.length;
var i__7281__auto___8143 = (0);
while(true){
if((i__7281__auto___8143 < len__7280__auto___8142)){
args__7287__auto__.push((arguments[i__7281__auto___8143]));

var G__8144 = (i__7281__auto___8143 + (1));
i__7281__auto___8143 = G__8144;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.sign.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.sign.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"sign","sign",1261721667),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"sign","sign",1261721667),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.sign.cljs$lang$maxFixedArity = (0);

gamma.api.sign.cljs$lang$applyTo = (function (seq8068){
return gamma.api.sign.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8068));
});

gamma.api.cos = (function gamma$api$cos(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8145 = arguments.length;
var i__7281__auto___8146 = (0);
while(true){
if((i__7281__auto___8146 < len__7280__auto___8145)){
args__7287__auto__.push((arguments[i__7281__auto___8146]));

var G__8147 = (i__7281__auto___8146 + (1));
i__7281__auto___8146 = G__8147;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.cos.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.cos.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"cos","cos",1201758276),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"cos","cos",1201758276),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.cos.cljs$lang$maxFixedArity = (0);

gamma.api.cos.cljs$lang$applyTo = (function (seq8069){
return gamma.api.cos.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8069));
});

gamma.api.textureCubeLod = (function gamma$api$textureCubeLod(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8148 = arguments.length;
var i__7281__auto___8149 = (0);
while(true){
if((i__7281__auto___8149 < len__7280__auto___8148)){
args__7287__auto__.push((arguments[i__7281__auto___8149]));

var G__8150 = (i__7281__auto___8149 + (1));
i__7281__auto___8149 = G__8150;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.textureCubeLod.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.textureCubeLod.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"textureCubeLod","textureCubeLod",149096100),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"textureCubeLod","textureCubeLod",149096100),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.textureCubeLod.cljs$lang$maxFixedArity = (0);

gamma.api.textureCubeLod.cljs$lang$applyTo = (function (seq8070){
return gamma.api.textureCubeLod.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8070));
});

gamma.api.tan = (function gamma$api$tan(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8151 = arguments.length;
var i__7281__auto___8152 = (0);
while(true){
if((i__7281__auto___8152 < len__7280__auto___8151)){
args__7287__auto__.push((arguments[i__7281__auto___8152]));

var G__8153 = (i__7281__auto___8152 + (1));
i__7281__auto___8152 = G__8153;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.tan.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.tan.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"tan","tan",1273609893),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"tan","tan",1273609893),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.tan.cljs$lang$maxFixedArity = (0);

gamma.api.tan.cljs$lang$applyTo = (function (seq8071){
return gamma.api.tan.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8071));
});

gamma.api.sqrt = (function gamma$api$sqrt(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8154 = arguments.length;
var i__7281__auto___8155 = (0);
while(true){
if((i__7281__auto___8155 < len__7280__auto___8154)){
args__7287__auto__.push((arguments[i__7281__auto___8155]));

var G__8156 = (i__7281__auto___8155 + (1));
i__7281__auto___8155 = G__8156;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.sqrt.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.sqrt.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"sqrt","sqrt",-1270051929),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"sqrt","sqrt",-1270051929),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.sqrt.cljs$lang$maxFixedArity = (0);

gamma.api.sqrt.cljs$lang$applyTo = (function (seq8072){
return gamma.api.sqrt.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8072));
});

gamma.api.mod = (function gamma$api$mod(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8157 = arguments.length;
var i__7281__auto___8158 = (0);
while(true){
if((i__7281__auto___8158 < len__7280__auto___8157)){
args__7287__auto__.push((arguments[i__7281__auto___8158]));

var G__8159 = (i__7281__auto___8158 + (1));
i__7281__auto___8158 = G__8159;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.mod.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.mod.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"mod","mod",-130487320),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"mod","mod",-130487320),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.mod.cljs$lang$maxFixedArity = (0);

gamma.api.mod.cljs$lang$applyTo = (function (seq8073){
return gamma.api.mod.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8073));
});

gamma.api.exp = (function gamma$api$exp(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8160 = arguments.length;
var i__7281__auto___8161 = (0);
while(true){
if((i__7281__auto___8161 < len__7280__auto___8160)){
args__7287__auto__.push((arguments[i__7281__auto___8161]));

var G__8162 = (i__7281__auto___8161 + (1));
i__7281__auto___8161 = G__8162;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.exp.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.exp.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"exp","exp",-261706262),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"exp","exp",-261706262),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.exp.cljs$lang$maxFixedArity = (0);

gamma.api.exp.cljs$lang$applyTo = (function (seq8074){
return gamma.api.exp.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8074));
});

gamma.api.texture2DProjLod = (function gamma$api$texture2DProjLod(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8163 = arguments.length;
var i__7281__auto___8164 = (0);
while(true){
if((i__7281__auto___8164 < len__7280__auto___8163)){
args__7287__auto__.push((arguments[i__7281__auto___8164]));

var G__8165 = (i__7281__auto___8164 + (1));
i__7281__auto___8164 = G__8165;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.texture2DProjLod.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.texture2DProjLod.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"texture2DProjLod","texture2DProjLod",-1483280499),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProjLod","texture2DProjLod",-1483280499),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProjLod","texture2DProjLod",-1483280499),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.texture2DProjLod.cljs$lang$maxFixedArity = (0);

gamma.api.texture2DProjLod.cljs$lang$applyTo = (function (seq8075){
return gamma.api.texture2DProjLod.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8075));
});

gamma.api.log2 = (function gamma$api$log2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8166 = arguments.length;
var i__7281__auto___8167 = (0);
while(true){
if((i__7281__auto___8167 < len__7280__auto___8166)){
args__7287__auto__.push((arguments[i__7281__auto___8167]));

var G__8168 = (i__7281__auto___8167 + (1));
i__7281__auto___8167 = G__8168;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.log2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.log2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"log2","log2",803778830),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"log2","log2",803778830),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.log2.cljs$lang$maxFixedArity = (0);

gamma.api.log2.cljs$lang$applyTo = (function (seq8076){
return gamma.api.log2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8076));
});

gamma.api.texture2D = (function gamma$api$texture2D(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8169 = arguments.length;
var i__7281__auto___8170 = (0);
while(true){
if((i__7281__auto___8170 < len__7280__auto___8169)){
args__7287__auto__.push((arguments[i__7281__auto___8170]));

var G__8171 = (i__7281__auto___8170 + (1));
i__7281__auto___8170 = G__8171;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.texture2D.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.texture2D.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"texture2D","texture2D",-252500594),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2D","texture2D",-252500594),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2D","texture2D",-252500594),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec2","vec2",-762258640)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.texture2D.cljs$lang$maxFixedArity = (0);

gamma.api.texture2D.cljs$lang$applyTo = (function (seq8077){
return gamma.api.texture2D.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8077));
});

gamma.api.asin = (function gamma$api$asin(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8172 = arguments.length;
var i__7281__auto___8173 = (0);
while(true){
if((i__7281__auto___8173 < len__7280__auto___8172)){
args__7287__auto__.push((arguments[i__7281__auto___8173]));

var G__8174 = (i__7281__auto___8173 + (1));
i__7281__auto___8173 = G__8174;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.asin.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.asin.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"asin","asin",1750305199),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"asin","asin",1750305199),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.asin.cljs$lang$maxFixedArity = (0);

gamma.api.asin.cljs$lang$applyTo = (function (seq8078){
return gamma.api.asin.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8078));
});

gamma.api.textureCube = (function gamma$api$textureCube(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8175 = arguments.length;
var i__7281__auto___8176 = (0);
while(true){
if((i__7281__auto___8176 < len__7280__auto___8175)){
args__7287__auto__.push((arguments[i__7281__auto___8176]));

var G__8177 = (i__7281__auto___8176 + (1));
i__7281__auto___8176 = G__8177;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.textureCube.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.textureCube.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"textureCube","textureCube",-82179345),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"textureCube","textureCube",-82179345),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"samplerCube","samplerCube",-734605291),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"textureCube","textureCube",-82179345),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"samplerCube","samplerCube",-734605291),new cljs.core.Keyword(null,"vec3","vec3",1116680488)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.textureCube.cljs$lang$maxFixedArity = (0);

gamma.api.textureCube.cljs$lang$applyTo = (function (seq8079){
return gamma.api.textureCube.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8079));
});

gamma.api.power = (function gamma$api$power(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8178 = arguments.length;
var i__7281__auto___8179 = (0);
while(true){
if((i__7281__auto___8179 < len__7280__auto___8178)){
args__7287__auto__.push((arguments[i__7281__auto___8179]));

var G__8180 = (i__7281__auto___8179 + (1));
i__7281__auto___8179 = G__8180;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.power.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.power.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"power","power",-937852079),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"power","power",-937852079),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.power.cljs$lang$maxFixedArity = (0);

gamma.api.power.cljs$lang$applyTo = (function (seq8080){
return gamma.api.power.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8080));
});

gamma.api.refract = (function gamma$api$refract(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8181 = arguments.length;
var i__7281__auto___8182 = (0);
while(true){
if((i__7281__auto___8182 < len__7280__auto___8181)){
args__7287__auto__.push((arguments[i__7281__auto___8182]));

var G__8183 = (i__7281__auto___8182 + (1));
i__7281__auto___8182 = G__8183;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.refract.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.refract.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"refract","refract",-1502353966),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"refract","refract",-1502353966),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.refract.cljs$lang$maxFixedArity = (0);

gamma.api.refract.cljs$lang$applyTo = (function (seq8081){
return gamma.api.refract.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8081));
});

gamma.api.texture2DLod = (function gamma$api$texture2DLod(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8184 = arguments.length;
var i__7281__auto___8185 = (0);
while(true){
if((i__7281__auto___8185 < len__7280__auto___8184)){
args__7287__auto__.push((arguments[i__7281__auto___8185]));

var G__8186 = (i__7281__auto___8185 + (1));
i__7281__auto___8185 = G__8186;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.texture2DLod.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.texture2DLod.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"texture2DLod","texture2DLod",-1274741294),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DLod","texture2DLod",-1274741294),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec2","vec2",-762258640),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.texture2DLod.cljs$lang$maxFixedArity = (0);

gamma.api.texture2DLod.cljs$lang$applyTo = (function (seq8082){
return gamma.api.texture2DLod.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8082));
});

gamma.api.exp2 = (function gamma$api$exp2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8187 = arguments.length;
var i__7281__auto___8188 = (0);
while(true){
if((i__7281__auto___8188 < len__7280__auto___8187)){
args__7287__auto__.push((arguments[i__7281__auto___8188]));

var G__8189 = (i__7281__auto___8188 + (1));
i__7281__auto___8188 = G__8189;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.exp2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.exp2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"exp2","exp2",-1037021901),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"exp2","exp2",-1037021901),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.exp2.cljs$lang$maxFixedArity = (0);

gamma.api.exp2.cljs$lang$applyTo = (function (seq8083){
return gamma.api.exp2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8083));
});

gamma.api.smoothstep = (function gamma$api$smoothstep(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8190 = arguments.length;
var i__7281__auto___8191 = (0);
while(true){
if((i__7281__auto___8191 < len__7280__auto___8190)){
args__7287__auto__.push((arguments[i__7281__auto___8191]));

var G__8192 = (i__7281__auto___8191 + (1));
i__7281__auto___8191 = G__8192;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.smoothstep.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.smoothstep.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"smoothstep","smoothstep",968032787),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"smoothstep","smoothstep",968032787),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"smoothstep","smoothstep",968032787),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.smoothstep.cljs$lang$maxFixedArity = (0);

gamma.api.smoothstep.cljs$lang$applyTo = (function (seq8084){
return gamma.api.smoothstep.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8084));
});

gamma.api.abs = (function gamma$api$abs(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8193 = arguments.length;
var i__7281__auto___8194 = (0);
while(true){
if((i__7281__auto___8194 < len__7280__auto___8193)){
args__7287__auto__.push((arguments[i__7281__auto___8194]));

var G__8195 = (i__7281__auto___8194 + (1));
i__7281__auto___8194 = G__8195;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.abs.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.abs.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"abs","abs",-246026477),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"abs","abs",-246026477),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.abs.cljs$lang$maxFixedArity = (0);

gamma.api.abs.cljs$lang$applyTo = (function (seq8085){
return gamma.api.abs.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8085));
});

gamma.api.max = (function gamma$api$max(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8196 = arguments.length;
var i__7281__auto___8197 = (0);
while(true){
if((i__7281__auto___8197 < len__7280__auto___8196)){
args__7287__auto__.push((arguments[i__7281__auto___8197]));

var G__8198 = (i__7281__auto___8197 + (1));
i__7281__auto___8197 = G__8198;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.max.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.max.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"max","max",61366548),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"max","max",61366548),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.max.cljs$lang$maxFixedArity = (0);

gamma.api.max.cljs$lang$applyTo = (function (seq8086){
return gamma.api.max.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8086));
});

gamma.api.inversesqrt = (function gamma$api$inversesqrt(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8199 = arguments.length;
var i__7281__auto___8200 = (0);
while(true){
if((i__7281__auto___8200 < len__7280__auto___8199)){
args__7287__auto__.push((arguments[i__7281__auto___8200]));

var G__8201 = (i__7281__auto___8200 + (1));
i__7281__auto___8200 = G__8201;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.inversesqrt.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.inversesqrt.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"inversesqrt","inversesqrt",-1232448652),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"inversesqrt","inversesqrt",-1232448652),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.inversesqrt.cljs$lang$maxFixedArity = (0);

gamma.api.inversesqrt.cljs$lang$applyTo = (function (seq8087){
return gamma.api.inversesqrt.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8087));
});

gamma.api.length = (function gamma$api$length(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8202 = arguments.length;
var i__7281__auto___8203 = (0);
while(true){
if((i__7281__auto___8203 < len__7280__auto___8202)){
args__7287__auto__.push((arguments[i__7281__auto___8203]));

var G__8204 = (i__7281__auto___8203 + (1));
i__7281__auto___8203 = G__8204;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.length.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.length.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"length","length",588987862),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"length","length",588987862),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.length.cljs$lang$maxFixedArity = (0);

gamma.api.length.cljs$lang$applyTo = (function (seq8088){
return gamma.api.length.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8088));
});

gamma.api.sin = (function gamma$api$sin(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8205 = arguments.length;
var i__7281__auto___8206 = (0);
while(true){
if((i__7281__auto___8206 < len__7280__auto___8205)){
args__7287__auto__.push((arguments[i__7281__auto___8206]));

var G__8207 = (i__7281__auto___8206 + (1));
i__7281__auto___8206 = G__8207;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.sin.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.sin.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"sin","sin",80907862),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"sin","sin",80907862),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.sin.cljs$lang$maxFixedArity = (0);

gamma.api.sin.cljs$lang$applyTo = (function (seq8089){
return gamma.api.sin.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8089));
});

gamma.api.texture2DProj = (function gamma$api$texture2DProj(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8208 = arguments.length;
var i__7281__auto___8209 = (0);
while(true){
if((i__7281__auto___8209 < len__7280__auto___8208)){
args__7287__auto__.push((arguments[i__7281__auto___8209]));

var G__8210 = (i__7281__auto___8209 + (1));
i__7281__auto___8209 = G__8210;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.texture2DProj.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.texture2DProj.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"texture2DProj","texture2DProj",1965198007),new cljs.core.PersistentVector(null, 4, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProj","texture2DProj",1965198007),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProj","texture2DProj",1965198007),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProj","texture2DProj",1965198007),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"vec3","vec3",1116680488)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"texture2DProj","texture2DProj",1965198007),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"sampler2D","sampler2D",-2107312644),new cljs.core.Keyword(null,"coord","coord",-1453656639)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec4","vec4",631182126),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.texture2DProj.cljs$lang$maxFixedArity = (0);

gamma.api.texture2DProj.cljs$lang$applyTo = (function (seq8090){
return gamma.api.texture2DProj.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8090));
});

gamma.api.faceforward = (function gamma$api$faceforward(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8211 = arguments.length;
var i__7281__auto___8212 = (0);
while(true){
if((i__7281__auto___8212 < len__7280__auto___8211)){
args__7287__auto__.push((arguments[i__7281__auto___8212]));

var G__8213 = (i__7281__auto___8212 + (1));
i__7281__auto___8212 = G__8213;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.faceforward.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.faceforward.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"faceforward","faceforward",840660504),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"faceforward","faceforward",840660504),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.faceforward.cljs$lang$maxFixedArity = (0);

gamma.api.faceforward.cljs$lang$applyTo = (function (seq8091){
return gamma.api.faceforward.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8091));
});

gamma.api.dot = (function gamma$api$dot(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8214 = arguments.length;
var i__7281__auto___8215 = (0);
while(true){
if((i__7281__auto___8215 < len__7280__auto___8214)){
args__7287__auto__.push((arguments[i__7281__auto___8215]));

var G__8216 = (i__7281__auto___8215 + (1));
i__7281__auto___8215 = G__8216;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.dot.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.dot.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"dot","dot",1442709401),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"dot","dot",1442709401),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.dot.cljs$lang$maxFixedArity = (0);

gamma.api.dot.cljs$lang$applyTo = (function (seq8092){
return gamma.api.dot.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8092));
});

gamma.api.distance = (function gamma$api$distance(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8217 = arguments.length;
var i__7281__auto___8218 = (0);
while(true){
if((i__7281__auto___8218 < len__7280__auto___8217)){
args__7287__auto__.push((arguments[i__7281__auto___8218]));

var G__8219 = (i__7281__auto___8218 + (1));
i__7281__auto___8218 = G__8219;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.distance.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.distance.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"distance","distance",-1671893894),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"distance","distance",-1671893894),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.distance.cljs$lang$maxFixedArity = (0);

gamma.api.distance.cljs$lang$applyTo = (function (seq8093){
return gamma.api.distance.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8093));
});

gamma.api.fract = (function gamma$api$fract(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8220 = arguments.length;
var i__7281__auto___8221 = (0);
while(true){
if((i__7281__auto___8221 < len__7280__auto___8220)){
args__7287__auto__.push((arguments[i__7281__auto___8221]));

var G__8222 = (i__7281__auto___8221 + (1));
i__7281__auto___8221 = G__8222;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.fract.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.fract.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"fract","fract",-2061728070),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"fract","fract",-2061728070),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.fract.cljs$lang$maxFixedArity = (0);

gamma.api.fract.cljs$lang$applyTo = (function (seq8094){
return gamma.api.fract.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8094));
});

gamma.api.clamp = (function gamma$api$clamp(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8223 = arguments.length;
var i__7281__auto___8224 = (0);
while(true){
if((i__7281__auto___8224 < len__7280__auto___8223)){
args__7287__auto__.push((arguments[i__7281__auto___8224]));

var G__8225 = (i__7281__auto___8224 + (1));
i__7281__auto___8224 = G__8225;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.clamp.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.clamp.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"clamp","clamp",1803814940),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"clamp","clamp",1803814940),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"clamp","clamp",1803814940),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 3, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"float","float",-1732389368)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.clamp.cljs$lang$maxFixedArity = (0);

gamma.api.clamp.cljs$lang$applyTo = (function (seq8095){
return gamma.api.clamp.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8095));
});

gamma.api.radians = (function gamma$api$radians(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8226 = arguments.length;
var i__7281__auto___8227 = (0);
while(true){
if((i__7281__auto___8227 < len__7280__auto___8226)){
args__7287__auto__.push((arguments[i__7281__auto___8227]));

var G__8228 = (i__7281__auto___8227 + (1));
i__7281__auto___8227 = G__8228;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.radians.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.radians.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"radians","radians",1835725084),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"radians","radians",1835725084),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.radians.cljs$lang$maxFixedArity = (0);

gamma.api.radians.cljs$lang$applyTo = (function (seq8096){
return gamma.api.radians.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8096));
});

gamma.api.degrees = (function gamma$api$degrees(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8229 = arguments.length;
var i__7281__auto___8230 = (0);
while(true){
if((i__7281__auto___8230 < len__7280__auto___8229)){
args__7287__auto__.push((arguments[i__7281__auto___8230]));

var G__8231 = (i__7281__auto___8230 + (1));
i__7281__auto___8230 = G__8231;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.degrees.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.degrees.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"degrees","degrees",2015169884),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"degrees","degrees",2015169884),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.degrees.cljs$lang$maxFixedArity = (0);

gamma.api.degrees.cljs$lang$applyTo = (function (seq8097){
return gamma.api.degrees.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8097));
});

gamma.api.acos = (function gamma$api$acos(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8232 = arguments.length;
var i__7281__auto___8233 = (0);
while(true){
if((i__7281__auto___8233 < len__7280__auto___8232)){
args__7287__auto__.push((arguments[i__7281__auto___8233]));

var G__8234 = (i__7281__auto___8233 + (1));
i__7281__auto___8233 = G__8234;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.acos.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.acos.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"acos","acos",-1286789764),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"acos","acos",-1286789764),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.acos.cljs$lang$maxFixedArity = (0);

gamma.api.acos.cljs$lang$applyTo = (function (seq8099){
return gamma.api.acos.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8099));
});

gamma.api.step = (function gamma$api$step(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8235 = arguments.length;
var i__7281__auto___8236 = (0);
while(true){
if((i__7281__auto___8236 < len__7280__auto___8235)){
args__7287__auto__.push((arguments[i__7281__auto___8236]));

var G__8237 = (i__7281__auto___8236 + (1));
i__7281__auto___8236 = G__8237;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.step.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.step.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"step","step",1288888124),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"step","step",1288888124),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null),new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"step","step",1288888124),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"float","float",-1732389368),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.step.cljs$lang$maxFixedArity = (0);

gamma.api.step.cljs$lang$applyTo = (function (seq8100){
return gamma.api.step.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8100));
});

gamma.api.log = (function gamma$api$log(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8238 = arguments.length;
var i__7281__auto___8239 = (0);
while(true){
if((i__7281__auto___8239 < len__7280__auto___8238)){
args__7287__auto__.push((arguments[i__7281__auto___8239]));

var G__8240 = (i__7281__auto___8239 + (1));
i__7281__auto___8239 = G__8240;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.log.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.log.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"log","log",-1595516004),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"log","log",-1595516004),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.log.cljs$lang$maxFixedArity = (0);

gamma.api.log.cljs$lang$applyTo = (function (seq8101){
return gamma.api.log.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8101));
});

gamma.api.normalize = (function gamma$api$normalize(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8241 = arguments.length;
var i__7281__auto___8242 = (0);
while(true){
if((i__7281__auto___8242 < len__7280__auto___8241)){
args__7287__auto__.push((arguments[i__7281__auto___8242]));

var G__8243 = (i__7281__auto___8242 + (1));
i__7281__auto___8242 = G__8243;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.normalize.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.normalize.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"normalize","normalize",-1904390051),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"normalize","normalize",-1904390051),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.normalize.cljs$lang$maxFixedArity = (0);

gamma.api.normalize.cljs$lang$applyTo = (function (seq8102){
return gamma.api.normalize.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8102));
});

gamma.api.floor = (function gamma$api$floor(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8244 = arguments.length;
var i__7281__auto___8245 = (0);
while(true){
if((i__7281__auto___8245 < len__7280__auto___8244)){
args__7287__auto__.push((arguments[i__7281__auto___8245]));

var G__8246 = (i__7281__auto___8245 + (1));
i__7281__auto___8245 = G__8246;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.floor.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.floor.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"floor","floor",1882041021),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"floor","floor",1882041021),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.floor.cljs$lang$maxFixedArity = (0);

gamma.api.floor.cljs$lang$applyTo = (function (seq8103){
return gamma.api.floor.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8103));
});

gamma.api.cross = (function gamma$api$cross(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8247 = arguments.length;
var i__7281__auto___8248 = (0);
while(true){
if((i__7281__auto___8248 < len__7280__auto___8247)){
args__7287__auto__.push((arguments[i__7281__auto___8248]));

var G__8249 = (i__7281__auto___8248 + (1));
i__7281__auto___8248 = G__8249;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.cross.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.cross.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"cross","cross",194557789),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"cross","cross",194557789),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"vec3","vec3",1116680488)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"vec3","vec3",1116680488),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.cross.cljs$lang$maxFixedArity = (0);

gamma.api.cross.cljs$lang$applyTo = (function (seq8104){
return gamma.api.cross.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8104));
});

gamma.api.reflect = (function gamma$api$reflect(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8250 = arguments.length;
var i__7281__auto___8251 = (0);
while(true){
if((i__7281__auto___8251 < len__7280__auto___8250)){
args__7287__auto__.push((arguments[i__7281__auto___8251]));

var G__8252 = (i__7281__auto___8251 + (1));
i__7281__auto___8251 = G__8252;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.reflect.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.reflect.cljs$core$IFn$_invoke$arity$variadic = (function (body__8035__auto__){
return gamma.api.build_standard_function_term.call(null,new cljs.core.Keyword(null,"reflect","reflect",-2113821122),new cljs.core.PersistentVector(null, 1, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"name","name",1843675177),new cljs.core.Keyword(null,"reflect","reflect",-2113821122),new cljs.core.Keyword(null,"input","input",556931961),new cljs.core.PersistentVector(null, 2, 5, cljs.core.PersistentVector.EMPTY_NODE, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"T","T",175240877)], null),new cljs.core.Keyword(null,"output","output",-1105869043),new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.Keyword(null,"parameter","parameter",1978789597),new cljs.core.PersistentArrayMap(null, 1, [new cljs.core.Keyword(null,"T","T",175240877),new cljs.core.PersistentHashSet(null, new cljs.core.PersistentArrayMap(null, 4, [new cljs.core.Keyword(null,"vec3","vec3",1116680488),null,new cljs.core.Keyword(null,"float","float",-1732389368),null,new cljs.core.Keyword(null,"vec4","vec4",631182126),null,new cljs.core.Keyword(null,"vec2","vec2",-762258640),null], null), null)], null)], null)], null),body__8035__auto__);
});

gamma.api.reflect.cljs$lang$maxFixedArity = (0);

gamma.api.reflect.cljs$lang$applyTo = (function (seq8105){
return gamma.api.reflect.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8105));
});

gamma.api.selector = (function gamma$api$selector(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8253 = arguments.length;
var i__7281__auto___8254 = (0);
while(true){
if((i__7281__auto___8254 < len__7280__auto___8253)){
args__7287__auto__.push((arguments[i__7281__auto___8254]));

var G__8255 = (i__7281__auto___8254 + (1));
i__7281__auto___8254 = G__8255;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.selector.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.selector.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"selector","selector",762528866),body__8033__auto__);
});

gamma.api.selector.cljs$lang$maxFixedArity = (0);

gamma.api.selector.cljs$lang$applyTo = (function (seq8106){
return gamma.api.selector.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8106));
});

gamma.api.increment = (function gamma$api$increment(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8256 = arguments.length;
var i__7281__auto___8257 = (0);
while(true){
if((i__7281__auto___8257 < len__7280__auto___8256)){
args__7287__auto__.push((arguments[i__7281__auto___8257]));

var G__8258 = (i__7281__auto___8257 + (1));
i__7281__auto___8257 = G__8258;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.increment.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.increment.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"increment","increment",-1558831484),body__8033__auto__);
});

gamma.api.increment.cljs$lang$maxFixedArity = (0);

gamma.api.increment.cljs$lang$applyTo = (function (seq8107){
return gamma.api.increment.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8107));
});

gamma.api.pre_decrement = (function gamma$api$pre_decrement(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8259 = arguments.length;
var i__7281__auto___8260 = (0);
while(true){
if((i__7281__auto___8260 < len__7280__auto___8259)){
args__7287__auto__.push((arguments[i__7281__auto___8260]));

var G__8261 = (i__7281__auto___8260 + (1));
i__7281__auto___8260 = G__8261;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.pre_decrement.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.pre_decrement.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"pre-decrement","pre-decrement",1269674757),body__8033__auto__);
});

gamma.api.pre_decrement.cljs$lang$maxFixedArity = (0);

gamma.api.pre_decrement.cljs$lang$applyTo = (function (seq8108){
return gamma.api.pre_decrement.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8108));
});

gamma.api.set_div = (function gamma$api$set_div(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8262 = arguments.length;
var i__7281__auto___8263 = (0);
while(true){
if((i__7281__auto___8263 < len__7280__auto___8262)){
args__7287__auto__.push((arguments[i__7281__auto___8263]));

var G__8264 = (i__7281__auto___8263 + (1));
i__7281__auto___8263 = G__8264;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.set_div.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.set_div.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"set-div","set-div",991399498),body__8033__auto__);
});

gamma.api.set_div.cljs$lang$maxFixedArity = (0);

gamma.api.set_div.cljs$lang$applyTo = (function (seq8109){
return gamma.api.set_div.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8109));
});

gamma.api.pre_increment = (function gamma$api$pre_increment(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8265 = arguments.length;
var i__7281__auto___8266 = (0);
while(true){
if((i__7281__auto___8266 < len__7280__auto___8265)){
args__7287__auto__.push((arguments[i__7281__auto___8266]));

var G__8267 = (i__7281__auto___8266 + (1));
i__7281__auto___8266 = G__8267;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.pre_increment.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.pre_increment.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"pre-increment","pre-increment",-1566257876),body__8033__auto__);
});

gamma.api.pre_increment.cljs$lang$maxFixedArity = (0);

gamma.api.pre_increment.cljs$lang$applyTo = (function (seq8110){
return gamma.api.pre_increment.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8110));
});

gamma.api.conditional_choice = (function gamma$api$conditional_choice(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8268 = arguments.length;
var i__7281__auto___8269 = (0);
while(true){
if((i__7281__auto___8269 < len__7280__auto___8268)){
args__7287__auto__.push((arguments[i__7281__auto___8269]));

var G__8270 = (i__7281__auto___8269 + (1));
i__7281__auto___8269 = G__8270;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.conditional_choice.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.conditional_choice.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"conditional-choice","conditional-choice",1872771601),body__8033__auto__);
});

gamma.api.conditional_choice.cljs$lang$maxFixedArity = (0);

gamma.api.conditional_choice.cljs$lang$applyTo = (function (seq8111){
return gamma.api.conditional_choice.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8111));
});

gamma.api.set_PLUS_ = (function gamma$api$set_PLUS_(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8271 = arguments.length;
var i__7281__auto___8272 = (0);
while(true){
if((i__7281__auto___8272 < len__7280__auto___8271)){
args__7287__auto__.push((arguments[i__7281__auto___8272]));

var G__8273 = (i__7281__auto___8272 + (1));
i__7281__auto___8272 = G__8273;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.set_PLUS_.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.set_PLUS_.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"set+","set+",1784778737),body__8033__auto__);
});

gamma.api.set_PLUS_.cljs$lang$maxFixedArity = (0);

gamma.api.set_PLUS_.cljs$lang$applyTo = (function (seq8112){
return gamma.api.set_PLUS_.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8112));
});

gamma.api.set_ = (function gamma$api$set_(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8274 = arguments.length;
var i__7281__auto___8275 = (0);
while(true){
if((i__7281__auto___8275 < len__7280__auto___8274)){
args__7287__auto__.push((arguments[i__7281__auto___8275]));

var G__8276 = (i__7281__auto___8275 + (1));
i__7281__auto___8275 = G__8276;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.set_.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.set_.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"set-","set-",-1958952622),body__8033__auto__);
});

gamma.api.set_.cljs$lang$maxFixedArity = (0);

gamma.api.set_.cljs$lang$applyTo = (function (seq8113){
return gamma.api.set_.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8113));
});

gamma.api.constructor$ = (function gamma$api$constructor(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8277 = arguments.length;
var i__7281__auto___8278 = (0);
while(true){
if((i__7281__auto___8278 < len__7280__auto___8277)){
args__7287__auto__.push((arguments[i__7281__auto___8278]));

var G__8279 = (i__7281__auto___8278 + (1));
i__7281__auto___8278 = G__8279;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.constructor$.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.constructor$.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"constructor","constructor",-1953928811),body__8033__auto__);
});

gamma.api.constructor$.cljs$lang$maxFixedArity = (0);

gamma.api.constructor$.cljs$lang$applyTo = (function (seq8114){
return gamma.api.constructor$.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8114));
});

gamma.api.decrement = (function gamma$api$decrement(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8280 = arguments.length;
var i__7281__auto___8281 = (0);
while(true){
if((i__7281__auto___8281 < len__7280__auto___8280)){
args__7287__auto__.push((arguments[i__7281__auto___8281]));

var G__8282 = (i__7281__auto___8281 + (1));
i__7281__auto___8281 = G__8282;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.decrement.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.decrement.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"decrement","decrement",-725286119),body__8033__auto__);
});

gamma.api.decrement.cljs$lang$maxFixedArity = (0);

gamma.api.decrement.cljs$lang$applyTo = (function (seq8115){
return gamma.api.decrement.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8115));
});

gamma.api.set = (function gamma$api$set(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8283 = arguments.length;
var i__7281__auto___8284 = (0);
while(true){
if((i__7281__auto___8284 < len__7280__auto___8283)){
args__7287__auto__.push((arguments[i__7281__auto___8284]));

var G__8285 = (i__7281__auto___8284 + (1));
i__7281__auto___8284 = G__8285;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.set.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.set.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"set","set",304602554),body__8033__auto__);
});

gamma.api.set.cljs$lang$maxFixedArity = (0);

gamma.api.set.cljs$lang$applyTo = (function (seq8116){
return gamma.api.set.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8116));
});

gamma.api.set_STAR_ = (function gamma$api$set_STAR_(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8286 = arguments.length;
var i__7281__auto___8287 = (0);
while(true){
if((i__7281__auto___8287 < len__7280__auto___8286)){
args__7287__auto__.push((arguments[i__7281__auto___8287]));

var G__8288 = (i__7281__auto___8287 + (1));
i__7281__auto___8287 = G__8288;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.set_STAR_.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.set_STAR_.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"set*","set*",-966220230),body__8033__auto__);
});

gamma.api.set_STAR_.cljs$lang$maxFixedArity = (0);

gamma.api.set_STAR_.cljs$lang$applyTo = (function (seq8117){
return gamma.api.set_STAR_.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8117));
});

gamma.api.aget = (function gamma$api$aget(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8289 = arguments.length;
var i__7281__auto___8290 = (0);
while(true){
if((i__7281__auto___8290 < len__7280__auto___8289)){
args__7287__auto__.push((arguments[i__7281__auto___8290]));

var G__8291 = (i__7281__auto___8290 + (1));
i__7281__auto___8290 = G__8291;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.aget.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.aget.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"aget","aget",-149474981),body__8033__auto__);
});

gamma.api.aget.cljs$lang$maxFixedArity = (0);

gamma.api.aget.cljs$lang$applyTo = (function (seq8118){
return gamma.api.aget.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8118));
});

gamma.api._PLUS__ = (function gamma$api$_PLUS__(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8292 = arguments.length;
var i__7281__auto___8293 = (0);
while(true){
if((i__7281__auto___8293 < len__7280__auto___8292)){
args__7287__auto__.push((arguments[i__7281__auto___8293]));

var G__8294 = (i__7281__auto___8293 + (1));
i__7281__auto___8293 = G__8294;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api._PLUS__.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api._PLUS__.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"+-","+-",1426840219),body__8033__auto__);
});

gamma.api._PLUS__.cljs$lang$maxFixedArity = (0);

gamma.api._PLUS__.cljs$lang$applyTo = (function (seq8119){
return gamma.api._PLUS__.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8119));
});

gamma.api.for$ = (function gamma$api$for(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8295 = arguments.length;
var i__7281__auto___8296 = (0);
while(true){
if((i__7281__auto___8296 < len__7280__auto___8295)){
args__7287__auto__.push((arguments[i__7281__auto___8296]));

var G__8297 = (i__7281__auto___8296 + (1));
i__7281__auto___8296 = G__8297;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.for$.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.for$.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"for","for",-1323786319),body__8033__auto__);
});

gamma.api.for$.cljs$lang$maxFixedArity = (0);

gamma.api.for$.cljs$lang$applyTo = (function (seq8120){
return gamma.api.for$.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8120));
});

gamma.api.block = (function gamma$api$block(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8298 = arguments.length;
var i__7281__auto___8299 = (0);
while(true){
if((i__7281__auto___8299 < len__7280__auto___8298)){
args__7287__auto__.push((arguments[i__7281__auto___8299]));

var G__8300 = (i__7281__auto___8299 + (1));
i__7281__auto___8299 = G__8300;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.block.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.block.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"block","block",664686210),body__8033__auto__);
});

gamma.api.block.cljs$lang$maxFixedArity = (0);

gamma.api.block.cljs$lang$applyTo = (function (seq8121){
return gamma.api.block.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8121));
});

gamma.api.continue$ = (function gamma$api$continue(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8301 = arguments.length;
var i__7281__auto___8302 = (0);
while(true){
if((i__7281__auto___8302 < len__7280__auto___8301)){
args__7287__auto__.push((arguments[i__7281__auto___8302]));

var G__8303 = (i__7281__auto___8302 + (1));
i__7281__auto___8302 = G__8303;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.continue$.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.continue$.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"continue","continue",-207346553),body__8033__auto__);
});

gamma.api.continue$.cljs$lang$maxFixedArity = (0);

gamma.api.continue$.cljs$lang$applyTo = (function (seq8122){
return gamma.api.continue$.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8122));
});

gamma.api.break$ = (function gamma$api$break(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8304 = arguments.length;
var i__7281__auto___8305 = (0);
while(true){
if((i__7281__auto___8305 < len__7280__auto___8304)){
args__7287__auto__.push((arguments[i__7281__auto___8305]));

var G__8306 = (i__7281__auto___8305 + (1));
i__7281__auto___8305 = G__8306;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.break$.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.break$.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"break","break",126570225),body__8033__auto__);
});

gamma.api.break$.cljs$lang$maxFixedArity = (0);

gamma.api.break$.cljs$lang$applyTo = (function (seq8123){
return gamma.api.break$.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8123));
});

gamma.api.discard = (function gamma$api$discard(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8307 = arguments.length;
var i__7281__auto___8308 = (0);
while(true){
if((i__7281__auto___8308 < len__7280__auto___8307)){
args__7287__auto__.push((arguments[i__7281__auto___8308]));

var G__8309 = (i__7281__auto___8308 + (1));
i__7281__auto___8308 = G__8309;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.discard.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.discard.cljs$core$IFn$_invoke$arity$variadic = (function (body__8033__auto__){
return cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"discard","discard",-1939593545),body__8033__auto__);
});

gamma.api.discard.cljs$lang$maxFixedArity = (0);

gamma.api.discard.cljs$lang$applyTo = (function (seq8124){
return gamma.api.discard.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8124));
});

gamma.api.vec2 = (function gamma$api$vec2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8310 = arguments.length;
var i__7281__auto___8311 = (0);
while(true){
if((i__7281__auto___8311 < len__7280__auto___8310)){
args__7287__auto__.push((arguments[i__7281__auto___8311]));

var G__8312 = (i__7281__auto___8311 + (1));
i__7281__auto___8311 = G__8312;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.vec2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.vec2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"vec2","vec2",-762258640),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec2","vec2",-762258640));
});

gamma.api.vec2.cljs$lang$maxFixedArity = (0);

gamma.api.vec2.cljs$lang$applyTo = (function (seq8125){
return gamma.api.vec2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8125));
});

gamma.api.vec3 = (function gamma$api$vec3(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8313 = arguments.length;
var i__7281__auto___8314 = (0);
while(true){
if((i__7281__auto___8314 < len__7280__auto___8313)){
args__7287__auto__.push((arguments[i__7281__auto___8314]));

var G__8315 = (i__7281__auto___8314 + (1));
i__7281__auto___8314 = G__8315;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.vec3.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.vec3.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"vec3","vec3",1116680488),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec3","vec3",1116680488));
});

gamma.api.vec3.cljs$lang$maxFixedArity = (0);

gamma.api.vec3.cljs$lang$applyTo = (function (seq8126){
return gamma.api.vec3.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8126));
});

gamma.api.vec4 = (function gamma$api$vec4(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8316 = arguments.length;
var i__7281__auto___8317 = (0);
while(true){
if((i__7281__auto___8317 < len__7280__auto___8316)){
args__7287__auto__.push((arguments[i__7281__auto___8317]));

var G__8318 = (i__7281__auto___8317 + (1));
i__7281__auto___8317 = G__8318;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.vec4.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.vec4.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"vec4","vec4",631182126),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"vec4","vec4",631182126));
});

gamma.api.vec4.cljs$lang$maxFixedArity = (0);

gamma.api.vec4.cljs$lang$applyTo = (function (seq8127){
return gamma.api.vec4.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8127));
});

gamma.api.bvec2 = (function gamma$api$bvec2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8319 = arguments.length;
var i__7281__auto___8320 = (0);
while(true){
if((i__7281__auto___8320 < len__7280__auto___8319)){
args__7287__auto__.push((arguments[i__7281__auto___8320]));

var G__8321 = (i__7281__auto___8320 + (1));
i__7281__auto___8320 = G__8321;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.bvec2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.bvec2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"bvec2","bvec2",-148389679),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bvec2","bvec2",-148389679));
});

gamma.api.bvec2.cljs$lang$maxFixedArity = (0);

gamma.api.bvec2.cljs$lang$applyTo = (function (seq8128){
return gamma.api.bvec2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8128));
});

gamma.api.bvec3 = (function gamma$api$bvec3(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8322 = arguments.length;
var i__7281__auto___8323 = (0);
while(true){
if((i__7281__auto___8323 < len__7280__auto___8322)){
args__7287__auto__.push((arguments[i__7281__auto___8323]));

var G__8324 = (i__7281__auto___8323 + (1));
i__7281__auto___8323 = G__8324;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.bvec3.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.bvec3.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"bvec3","bvec3",-635324058),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bvec3","bvec3",-635324058));
});

gamma.api.bvec3.cljs$lang$maxFixedArity = (0);

gamma.api.bvec3.cljs$lang$applyTo = (function (seq8129){
return gamma.api.bvec3.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8129));
});

gamma.api.bvec4 = (function gamma$api$bvec4(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8325 = arguments.length;
var i__7281__auto___8326 = (0);
while(true){
if((i__7281__auto___8326 < len__7280__auto___8325)){
args__7287__auto__.push((arguments[i__7281__auto___8326]));

var G__8327 = (i__7281__auto___8326 + (1));
i__7281__auto___8326 = G__8327;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.bvec4.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.bvec4.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"bvec4","bvec4",1798744632),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"bvec4","bvec4",1798744632));
});

gamma.api.bvec4.cljs$lang$maxFixedArity = (0);

gamma.api.bvec4.cljs$lang$applyTo = (function (seq8130){
return gamma.api.bvec4.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8130));
});

gamma.api.ivec2 = (function gamma$api$ivec2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8328 = arguments.length;
var i__7281__auto___8329 = (0);
while(true){
if((i__7281__auto___8329 < len__7280__auto___8328)){
args__7287__auto__.push((arguments[i__7281__auto___8329]));

var G__8330 = (i__7281__auto___8329 + (1));
i__7281__auto___8329 = G__8330;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.ivec2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.ivec2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"ivec2","ivec2",148465998),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"ivec2","ivec2",148465998));
});

gamma.api.ivec2.cljs$lang$maxFixedArity = (0);

gamma.api.ivec2.cljs$lang$applyTo = (function (seq8131){
return gamma.api.ivec2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8131));
});

gamma.api.ivec3 = (function gamma$api$ivec3(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8331 = arguments.length;
var i__7281__auto___8332 = (0);
while(true){
if((i__7281__auto___8332 < len__7280__auto___8331)){
args__7287__auto__.push((arguments[i__7281__auto___8332]));

var G__8333 = (i__7281__auto___8332 + (1));
i__7281__auto___8332 = G__8333;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.ivec3.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.ivec3.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"ivec3","ivec3",-104254851),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"ivec3","ivec3",-104254851));
});

gamma.api.ivec3.cljs$lang$maxFixedArity = (0);

gamma.api.ivec3.cljs$lang$applyTo = (function (seq8132){
return gamma.api.ivec3.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8132));
});

gamma.api.ivec4 = (function gamma$api$ivec4(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8334 = arguments.length;
var i__7281__auto___8335 = (0);
while(true){
if((i__7281__auto___8335 < len__7280__auto___8334)){
args__7287__auto__.push((arguments[i__7281__auto___8335]));

var G__8336 = (i__7281__auto___8335 + (1));
i__7281__auto___8335 = G__8336;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.ivec4.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.ivec4.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"ivec4","ivec4",-537108439),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"ivec4","ivec4",-537108439));
});

gamma.api.ivec4.cljs$lang$maxFixedArity = (0);

gamma.api.ivec4.cljs$lang$applyTo = (function (seq8133){
return gamma.api.ivec4.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8133));
});

gamma.api.mat2 = (function gamma$api$mat2(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8337 = arguments.length;
var i__7281__auto___8338 = (0);
while(true){
if((i__7281__auto___8338 < len__7280__auto___8337)){
args__7287__auto__.push((arguments[i__7281__auto___8338]));

var G__8339 = (i__7281__auto___8338 + (1));
i__7281__auto___8338 = G__8339;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.mat2.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.mat2.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"mat2","mat2",238424363),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"mat2","mat2",238424363));
});

gamma.api.mat2.cljs$lang$maxFixedArity = (0);

gamma.api.mat2.cljs$lang$applyTo = (function (seq8134){
return gamma.api.mat2.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8134));
});

gamma.api.mat3 = (function gamma$api$mat3(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8340 = arguments.length;
var i__7281__auto___8341 = (0);
while(true){
if((i__7281__auto___8341 < len__7280__auto___8340)){
args__7287__auto__.push((arguments[i__7281__auto___8341]));

var G__8342 = (i__7281__auto___8341 + (1));
i__7281__auto___8341 = G__8342;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.mat3.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.mat3.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"mat3","mat3",402087048),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"mat3","mat3",402087048));
});

gamma.api.mat3.cljs$lang$maxFixedArity = (0);

gamma.api.mat3.cljs$lang$applyTo = (function (seq8135){
return gamma.api.mat3.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8135));
});

gamma.api.mat4 = (function gamma$api$mat4(var_args){
var args__7287__auto__ = [];
var len__7280__auto___8343 = arguments.length;
var i__7281__auto___8344 = (0);
while(true){
if((i__7281__auto___8344 < len__7280__auto___8343)){
args__7287__auto__.push((arguments[i__7281__auto___8344]));

var G__8345 = (i__7281__auto___8344 + (1));
i__7281__auto___8344 = G__8345;
continue;
} else {
}
break;
}

var argseq__7288__auto__ = ((((0) < args__7287__auto__.length))?(new cljs.core.IndexedSeq(args__7287__auto__.slice((0)),(0),null)):null);
return gamma.api.mat4.cljs$core$IFn$_invoke$arity$variadic(argseq__7288__auto__);
});

gamma.api.mat4.cljs$core$IFn$_invoke$arity$variadic = (function (body__8039__auto__){
return cljs.core.assoc.call(null,cljs.core.apply.call(null,gamma.ast.term,new cljs.core.Keyword(null,"mat4","mat4",-237531594),body__8039__auto__),new cljs.core.Keyword(null,"type","type",1174270348),new cljs.core.Keyword(null,"mat4","mat4",-237531594));
});

gamma.api.mat4.cljs$lang$maxFixedArity = (0);

gamma.api.mat4.cljs$lang$applyTo = (function (seq8098){
return gamma.api.mat4.cljs$core$IFn$_invoke$arity$variadic(cljs.core.seq.call(null,seq8098));
});
gamma.api.swizzle_type = (function gamma$api$swizzle_type(x,c){
var l = cljs.core.count.call(null,cljs.core.name.call(null,c));
return new cljs.core.PersistentArrayMap(null, 4, [(1),new cljs.core.Keyword(null,"float","float",-1732389368),(2),new cljs.core.Keyword(null,"vec2","vec2",-762258640),(3),new cljs.core.Keyword(null,"vec3","vec3",1116680488),(4),new cljs.core.Keyword(null,"vec4","vec4",631182126)], null).call(null,l);
});
gamma.api.swizzle = (function gamma$api$swizzle(x,c){
return cljs.core.assoc.call(null,gamma.ast.term.call(null,new cljs.core.Keyword(null,"swizzle","swizzle",-956643048),x),new cljs.core.Keyword(null,"swizzle","swizzle",-956643048),c,new cljs.core.Keyword(null,"type","type",1174270348),gamma.api.swizzle_type.call(null,x,c));
});

//# sourceMappingURL=api.js.map?rel=1476490290841